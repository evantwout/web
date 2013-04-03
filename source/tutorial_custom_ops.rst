.. highlight:: c++

Extending BEM++ with new operators
==================================

Introduction
------------

In this tutorial we want to show how to extend BEM++ with custom integral operators. As an illustration, we will take the operator :math:`C = K - i k V` occurring in the combined-potential integral formulation of the Helmholtz equation. Here, :math:`V` denotes the single- and :math:`K` the double-layer-potential boundary operator, while :math:`i` is the imaginary unit and :math:`k` the wave number. Obviously, the operator :math:`C` may be formed very simply in BEM++: it suffices to create the single- and double-layer operator objects with ::

    V = createHelmholtzSingleLayerBoundaryOperator(context, space, space, space, k)
    K = createHelmholtzDoubleLayerBoundaryOperator(context, space, space, space, k)

(using the Python interface) and then add them together::

    C = K - 1j * k * V

In this way, we create a composite (nonelementary) operator ``C``. Its discretized weak form is not stored as a single matrix; instead, the object ``C`` contains references to the discretized weak forms of ``K`` and ``V`` as well as the value of the coefficient ``-1j * k``. When ``C`` is asked to act on a grid function ``f``, it first collects the results of applying ``V`` and ``K`` to ``f`` and adds them together with appropriate weights.

The composite-operator mechanism is very powerful and convenient, but it can also be inefficient: we need to create, store and manipulate two matrices instead of one. Therefore, if we do many calculations with the combined Helmholtz operator, we may want to make the effort to implement it as a new elementary operator.

The assembly of operator matrices is often the most time-consuming part of a boundary-element simulation. It should therefore come as no surprise that extension of BEM++ with new operators requires writing some C++ code---a Python implementation would simply be too slow. Later in this tutorial we will show, however, how to make the newly written C++ operator accessible from the Python interface to BEM++.

We expect the reader to be familiar with the description of the low-level representation of integral operators in BEM++ contained in section 3.9 of the technical report `Solving Boundary Integral Problems with BEM++ <http://www.bempp.org/files/bempp-toms-preprint.pdf>`_.

C++ implementation
------------------

Kernel functor
...................

As indicated in section 3.9 of the technical report mentioned above, BEM++ contains a class ``GeneralElementarySingularIntegralOperator`` that can be used to represent any singular integral operator, including :math:`C`. The constructor of this class is declared as ::

    template <typename KernelFunctor, typename TestTransformationsFunctor,
              typename TrialTransformationsFunctor,
              typename IntegrandFunctor>
    GeneralElementarySingularIntegralOperator(
            const shared_ptr<const Space<BasisFunctionType> >& domain,
            const shared_ptr<const Space<BasisFunctionType> >& range,
            const shared_ptr<const Space<BasisFunctionType> >& dualToRange,
            const std::string& label,
            int symmetry,
            const KernelFunctor& kernelFunctor,
            const TestTransformationsFunctor& testTransformationsFunctor,
            const TrialTransformationsFunctor& trialTransformationsFunctor,
            const IntegrandFunctor& integrandFunctor);

and accepts four functor objects that are used to evaluate the weak form of the operator. The weak form of our operator :math:`C` looks as follows:

.. math::

    \langle \phi, C \psi \rangle =
    \int_\Gamma \int_\Gamma
    \phi^*(\mathbf x)
    \underbrace{
    \frac{(\mathbf x - \mathbf y) \cdot \mathbf n_{\mathbf y}
    (1 - i k \lvert\mathbf x - \mathbf y\rvert)
    - i k \lvert\mathbf x - \mathbf y\rvert^2}
    {4\pi \lvert\mathbf x - \mathbf y\rvert^3}
    \exp(i k \lvert\mathbf x - \mathbf y\rvert)}
    _{\equiv\mathcal C(\mathbf x, \mathbf y)}\,
    \psi(\mathbf y)\,
    \mathrm d \Gamma(\mathbf x)\,
    \mathrm d \Gamma(\mathbf y).

We can see that the integrand has the form of the product of the conjugated test function :math:`\phi`, a kernel :math:`\mathcal C` and the trial function :math:`\psi`. All the quantities are scalar. It should come as no surprise that BEM++ already provides appropriate classes for the functors responsible for the evaluation of the test and trial basis function transformations (``ScalarFunctionValueFunctor``) of the integrand (``SimpleTestScalarKernelTrialIntegralFunctor``). These functors are briefly described in the technical report. They are already used e.g. in the implementation of the Helmholtz single- and double-layer-potential boundary operators---thus one could just look at the source code of these operators to find the names of the needed functors. The only functor that we need to implement ourselves is the one responsible for the calculation of what is called the *collection of kernels* appearing in the integral---in our case, composed of just a single kernel, :math:`\mathcal C`.

The interface expected from a kernel-collection functor is described
in detail in the documentation of the ``DefaultCollectionOfKernels``
class. However, the simplest way of implementing such a functor for a
new operator is to take a kernel-collection functor belonging to a
similar operator and to adapt it to appropriately. In our case, we
started from the kernel of the modified Helmholtz
double-layer-potential boundary operator. The end result looks like this::

    // helmholtz_3d_combined_potential_kernel_functor.hpp
    #include "common/scalar_traits.hpp"
    #include "fiber/geometrical_data.hpp"

    template <typename ValueType_>
    class Helmholtz3dCombinedPotentialKernelFunctor
    {
    public:
        typedef ValueType_ ValueType;
        typedef typename Bempp::ScalarTraits<ValueType_>::RealType CoordinateType;

        explicit Helmholtz3dCombinedPotentialKernelFunctor(ValueType waveNumber) :
            m_kappa(ValueType(0., 1.) * waveNumber)
        {}

        int kernelCount() const { return 1; }
        int kernelRowCount(int kernelIndex) const { return 1; }
        int kernelColCount(int kernelIndex) const { return 1; }

        void addGeometricalDependencies(size_t& testGeomDeps,
                                        size_t& trialGeomDeps) const {
            testGeomDeps |= Fiber::GLOBALS;
            trialGeomDeps |= Fiber::GLOBALS | Fiber::NORMALS;
        }

        template <template <typename T> class CollectionOf2dSlicesOfNdArrays>
        void evaluate(
                const Fiber::ConstGeometricalDataSlice<CoordinateType>& testGeomData,
                const Fiber::ConstGeometricalDataSlice<CoordinateType>& trialGeomData,
                CollectionOf2dSlicesOfNdArrays<ValueType>& result) const {
            const int coordCount = 3;
            CoordinateType d_dot_n = 0., d_dot_d = 0.;
            for (int coordIndex = 0; coordIndex < coordCount; ++coordIndex) {
                CoordinateType diff = trialGeomData.global(coordIndex) -
                        testGeomData.global(coordIndex);
                d_dot_d += diff * diff;
                d_dot_n += diff * trialGeomData.normal(coordIndex);
            }
            CoordinateType d = sqrt(d_dot_d);
            result[0 /* kernel index */](0 /* row */, 0 /* column */) =
                   (d_dot_n * (static_cast<CoordinateType>(1.) - m_kappa * d) + m_kappa * d_dot_d) *
                   exp(m_kappa * d) / (static_cast<CoordinateType>(-4. * M_PI) * d_dot_d * d);
        }

    private:
        ValueType m_kappa;
    };

The constructor of the above functor takes a single parameter: the wave number :math:`k`. The function ``kernelCount()`` returns the number of kernels contained in the collection (one), and the functions ``kernelRowCount()`` and ``kernelColCount()`` the dimensions of tensors being the values of the individual kernels. In our case, the kernel is scalar-valued, so these functions return 1. The fact that the kernel depends on the global coordinates of the test and trial points as well as on the components of the unit vector normal to the surface at the trial point is reflected in the implementation of ``addGeometricalDependencies()``.

The heart of the functor is its ``evaluate()`` method. It is supplied with
``ConstGeometricalDataSlice`` objects that give access to the
geometrical data at a single test and trial point. The values of the kernels making up the collection need to be stored in the ``result`` output argument. The
``evaluate()`` function is parametrised with the type of this argument
because depending on whether the kernels are being evaluated on a tensor or
non-tensor grid of quadrature points, ``evaluate()`` may be passed either a
``CollectionOf2dSlicesOf3dArrays`` or a
``CollectionOf2dSlicesOf4dArrays``. Both these classes,
however, are used in the same way: ``result[i](j, k)`` returns a reference
to the (``j``, ``k``)th element of the tensor of ``i``\th kernel
in the collection. We can see that by combining the kernels of the single- and double-layer-potential operators into a single function we can reuse a lot of information, such as the distance
between the test and trial points and the value of the exponential. It should be noted that all the array classes used in BEM++ perform
bounds checking when the symbol ``NDEBUG`` is not defined, which
makes it easier to debug index errors.

Operator construction
..................................

We need now a function that will construct a ``BoundaryOperator`` object
representing the combined-potential operator. The code of this function is
shown here::

    // helmholtz_3d_combined_boundary_operator.hpp
    #include "helmholtz_3d_combined_potential_kernel_functor.hpp"

    #include "assembly/boundary_operator.hpp"
    #include "assembly/general_elementary_singular_integral_operator_imp.hpp"
    #include "fiber/scalar_function_value_functor.hpp"
    #include "fiber/simple_test_scalar_kernel_trial_integrand_functor.hpp"

    #include <boost/make_shared.hpp>

    template <typename BasisFunctionType>
    Bempp::BoundaryOperator<BasisFunctionType,
        typename Bempp::ScalarTraits<BasisFunctionType>::ComplexType>
    helmholtz3dCombinedBoundaryOperator(
            const boost::shared_ptr<const Bempp::Context<BasisFunctionType,
                typename Bempp::ScalarTraits<BasisFunctionType>::ComplexType>
                >& context,
            const boost::shared_ptr<const Bempp::Space<BasisFunctionType> >& domain,
            const boost::shared_ptr<const Bempp::Space<BasisFunctionType> >& range,
            const boost::shared_ptr<const Bempp::Space<BasisFunctionType> >& dualToRange,
            typename Bempp::ScalarTraits<BasisFunctionType>::ComplexType waveNumber,
            const std::string& label = "")
    {
        typedef typename Bempp::ScalarTraits<BasisFunctionType>::ComplexType KernelType;
        typedef typename Bempp::ScalarTraits<BasisFunctionType>::ComplexType ResultType;
        typedef typename Bempp::ScalarTraits<BasisFunctionType>::RealType CoordinateType;

        typedef Helmholtz3dCombinedPotentialKernelFunctor<KernelType> KernelFunctor;
        typedef Fiber::ScalarFunctionValueFunctor<CoordinateType>
        TransformationFunctor;
        typedef Fiber::SimpleTestScalarKernelTrialIntegrandFunctor<
        BasisFunctionType, KernelType, ResultType> IntegrandFunctor;

        typedef Bempp::GeneralElementarySingularIntegralOperator<
                BasisFunctionType, KernelType, ResultType> Op;
        return Bempp::BoundaryOperator<BasisFunctionType, ResultType>(
                    context, boost::make_shared<Op>(
                        domain, range, dualToRange, label, Bempp::NO_SYMMETRY,
                        KernelFunctor(waveNumber),
                        TransformationFunctor(),
                        TransformationFunctor(),
                        IntegrandFunctor()));
    }

Despite appearances, the code is very simple. The only executable
statement in the body of the function is the last one, where we create
an instance of ``GeneralElementarySingularIntegralOperator``, the
versatile operator class that has been mentioned before, immediately
wrap the resulting abstract operator with a ``BoundaryOperator``
object and return this object to the caller. All the previous lines
are ``typedef``\s. We use the ``ScalarTraits`` to identify the real and
complex types of the same precision as ``BasisFunctionType``, and
define appropriately the types used to represent the coordinates, the
values of the kernel and those of the whole operator. Subsequently, we
specify the types of functors used to evaluate the collection of
kernels, test and trial basis transformations and the weak-form
integral. The former is set to the class we have defined in the
previous step; the remaining types are identical to those used in the
standard single- and double-layer-potential boundary operators. In the
penultimate statement we define an abreviation for the appropriate
instantiation of ``GeneralElementarySingularIntegralOperator``.

Python module preparation
-------------------------

The above procedure is all that we need to do in order to make our new
operator usable from C++. However, to create combined Helmholtz
operators in Python code, we need to wrap the
``helmholtz3dCombinedBoundaryOperator()`` function in a Python
extension module. Thanks to SWIG, this is not difficult.

We will assume here that the new extension module will only be used in
combination with function spaces having real-valued basis functions
represented with double-precision floating-point numbers. This is
certainly the most common use case. With this assumption, the wrapping
procedure becomes particularly straightforward. We need to write a
short SWIG interface file ``combined_operators_core.i`` describing the
functionality to be wrapped; this file will be processed by SWIG to
generate the C++ code of the extension module. We define the name of
the module, insert the module initialisation code using the
``SWIG_FILE_WITH_INIT`` macro and include the header with the
declaration of ``helmholtz3dCombinedBoundaryOperator()``::

    // combined_helmholtz.i
    %module combined_helmholtz
    %{
    #define SWIG_FILE_WITH_INIT
    #include "helmholtz_3d_combined_boundary_operator.hpp"
    %}

We then include the ``bempp.swg`` interface file provided by BEM++::

    %{ // temporarily necessary due to a deficiency in bempp.swg
        #include <dune/common/exceptions.hh>
    %}
    %include "bempp.swg"

Due to a deficiency in this file, it is currently necessary to include
a header file from the DUNE library beforehand. This will be removed
in the next version of BEM++.

The ``bempp.swg`` file makes information about the elements of BEM++ wrapped in the library's
Python interface available to SWIG as it processes our new interface file. In
this way, types for which Python
bindings have already been created, such as ``Context`` or ``Space``,
will be recognised and parsed correctly. Lastly, we fetch our header file to the
SWIG parser and instantiate the function template ``helmholtz3dCombinedBoundaryOperator()`` with ``BasisFunctionType`` set to ``double``, telling SWIG to name the resulting Python wrapper ``createHelmholtz3dCombinedBoundaryOperator()``::

    %feature("compactdefaultargs") helmholtz3dCombinedBoundaryOperator;
    %include "helmholtz_3d_combined_boundary_operator.hpp"
    %template(createHelmholtz3dCombinedBoundaryOperator)
        helmholtz3dCombinedBoundaryOperator<double>;

The line with ``compactdefaultargs`` prevents SWIG from generating a separate wrapper function for each variant of ``helmholtz3dCombinedBoundaryOperator()`` with a different number of default arguments.

The last step is the generation and compilation of the Python
wrappers. This can be done by hand or automated in various ways, for
instance using the ``distutils`` module as described in the SWIG
documentation. We prefer to use CMake, and the listing below shows an
example CMake script that builds and installs the newly written
module. ::

    cmake_minimum_required(VERSION 2.8)

    # Find the BEM++ library installed on your disk
    find_package(Bempp REQUIRED CONFIG)
    find_library(BEMPP_LIBRARY bempp PATHS ${BEMPP_LIBRARY_DIR})
    # Add the BEM++ installation directory to CMake search path to ensure that
    # e.g. the version of SWIG coming with BEM++ is used
    set(CMAKE_PREFIX_PATH "${BEMPP_PREFIX}/bempp;${CMAKE_PREFIX_PATH}"
        CACHE STRING "")
    # Make the new module be installed in the main BEM++ directory, by default
    set(CMAKE_INSTALL_PREFIX "${BEMPP_PREFIX}/bempp" CACHE PATH "" FORCE)
    # By default, compile the new module with optimizations turned on
    if (NOT CMAKE_BUILD_TYPE)
       set(CMAKE_BUILD_TYPE "Release" CACHE STRING
           "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
           FORCE)
    endif ()

    # Find SWIG
    find_package(SWIG REQUIRED)
    include(${SWIG_USE_FILE})
    set(CMAKE_SWIG_FLAGS "-modern")
    # Add include directories necessary for compilation of the new module
    include_directories("${BEMPP_PYTHON_INCLUDE_DIRS}") # Python and NumPy headers
    include_directories("${BEMPP_INCLUDE_DIR}")
    include_directories("${BEMPP_INCLUDE_DIR}/bempp")
    include_directories("${BEMPP_INCLUDE_DIR}/bempp/swig")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
    # Specify the source files and name of the new module
    set_source_files_properties(combined_helmholtz.i PROPERTIES CPLUSPLUS ON)
    swig_add_module(combined_helmholtz python combined_helmholtz.i)
    swig_link_libraries(combined_helmholtz
        ${BEMPP_PYTHON_LIBRARY}
        ${BEMPP_LIBRARY}
        ${BEMPP_TEUCHOS_LIBRARY})

    # Specify files to be installed
    install(FILES helmholtz_3d_combined_boundary_operator.hpp
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bempp/assembly")
    set(FILES_TO_INSTALL
        "${CMAKE_BINARY_DIR}/combined_helmholtz.py"
        "${CMAKE_BINARY_DIR}/_combined_helmholtz.so")
    install(FILES ${FILES_TO_INSTALL}
        DESTINATION "${CMAKE_INSTALL_PREFIX}/python/bempp")

[TODO: say how to write an extension module supporting all types (not only ``double``)]

Testing
--------

To test the new operator, we have written a `script <files/sound_soft_sphere.py>`_ that calculates the field generated by an acoustic plane wave impinging on a sound-soft sphere. Whether the user-defined combined-potential operator is used or not (in which case :math:`C` is formed from the standard single- and double-layer-potential operators) is determined by the value of the ``useCustomOperator`` variable. As expected, in both cases the script generates the same picture:

.. only:: html

    .. image:: sound_soft_sphere_result.png

.. only:: not html

    .. image:: sound_soft_sphere_result.png
        :width: 300pt

However, use of the custom operator reduces time and memory
consumption almost by half, as the following tables show. All
results were obtained on a 12-core 2.8-GHz Intel workstation with ACA
turned on (with default parameters) and GMRES tolerance 10E-8. The
test and trial spaces for discretisation were composed of piecewise
constant functions.

Standard operators:

=========  =========  =========  =========  =========  ===============
#Elements  Assembly time (s)        Memory (MB)        Solver time (s)
---------  --------------------  --------------------  ---------------
\          :math:`K`  :math:`V`  :math:`K`  :math:`V`  \
=========  =========  =========  =========  =========  ===============
2570	   0.6        0.4	 26	    25	       0.3
11459	   2.8        2.2	 147	    146	       1.3
46935	   15.2	      13.0	 771	    775	       7.7
=========  =========  =========  =========  =========  ===============

Custom combined-potential operator:

=========  =================  ===========  ===============
#Elements  Assembly time (s)  Memory (MB)  Solver time (s)
=========  =================  ===========  ===============
2570	   0.6	              26	   0.1
11459	   2.8	              151	   0.8
46935	   14.9               791	   4.0
=========  =================  ===========  ===============

\

Closing remarks
===============

For more complicated operators it may be necessary to develop custom
functors evaluating weak-form integrands or basis function
transformations. The expected interface of these functors is described
in the documentation of the ``DefaultTestKernelTrialIntegral`` and
``DefaultCollectionOfBasisTransformations`` classes,
respectively. The source code of the Fiber module of BEM++ provides
several examples of such functors. If you want to implement your own
operators and come across problems, please open an issue on the GitHub page
of BEM++---we'll be happy to help.

Source code
===========

The complete source code for this tutorial can be downloaded from
`here <files/tutorial_custom_ops_files.zip>`_

.. and use a macro defined in \texttt{bempp.swg} to instantiate the function
.. template \texttt{helmholtz\-3d\-Combined\-Hypersingular\-Boundary\-Operator()} for all the
.. four allowed values of \texttt{Basis\-Function\-Type}:
.. \begin{verbatim}
..     BEMPP_INSTANTIATE_SYMBOL_TEMPLATED_ON_BASIS(
..         helmholtz3dCombinedHypersingularBoundaryOperator);
.. \end{verbatim}
.. This makes SWIG generate Python functions
.. \texttt{helmholtz\-3d\-Combined\-Hypersingular\-Boundary\-Operator\_\allowbreak
..   float32()},
.. \texttt{helmholtz\-3d\-Combined\-Hypersingular\-Boundary\-Op\-er\-a\-tor\_\allowbreak
..   complex128()} etc., corresponding to the C++ ones
.. \texttt{helmholtz\-3d\-Combined\-Hyper\-singular\-Boundary\-Operator<float>()},
.. \texttt{helmholtz\-3d\-Combined\-Hyper\-singular\-Boundary\-Operator<std::complex<double>
..   >()} etc. To obtain cleaner-looking docstrings for these functions, which take
.. several default arguments, we may additionally put the line
.. \begin{verbatim}
..     %feature("compactdefaultargs")
..         helmholtz3dCombinedHypersingularBoundaryOperator;
.. \end{verbatim}
.. before the last \texttt{\%include} statement.

.. Compilation of SWIG Python wrappers is discussed in SWIG's documentation
.. \cite{SwigWebpage} and will not be detailed here. We only point out that it is
.. necessary to add the directories containing BEM++ headers and its SWIG interface
.. files to the include path of SWIG and the C++ compiler. A CMake script that was
.. used to compile the wrappers presented here can be found in the Supplementary
.. Material. [\textit{The CMake script looks perhaps a bit complicated... should we
..   use a distutils script instead? The problem with the latter is that the SWIG
..   executable path is not so easily customisable.}]

.. The result of the above procedure is a shared library
.. \texttt{\_combined\_operators\_core.so} and a Python module file
.. \texttt{combined\_operators\_core.py}. As already mentioned, the module contains
.. separate functions for different basis function types. This is not ideal and
.. goes against the spirit of Python as a type-free language. To help remedy this,
.. we take an additional step and wrap the functionality from
.. \texttt{combined\_operators\_core.py} in a separate Python module,
.. \texttt{combined\_operators.py}:
.. \begin{verbatim}
..     import combined_operators_core
..     import bempp.lib as lib

..     def _constructHelmholtz3dCombinedOperator(
..             callableName, context, domain, range, dualToRange, *args):
..         basisFunctionType = context.basisFunctionType()
..         if (context.resultType() !=
..                 lib.promoteTypeToComplex(basisFunctionType)):
..             raise TypeError("context has incorrect ResultType")
..         if (domain.basisFunctionType() != basisFunctionType or
..                 range.basisFunctionType() != basisFunctionType or
..                 dualToRange.basisFunctionType() != basisFunctionType):
..             raise TypeError("BasisFunctionType of context and all spaces "
..                             "must be the same")
..         callable_ = getattr(combined_operators_core,
..                          callableName + "_" + basisFunctionType)
..         return callable_(context, domain, range, dualToRange, *args)

..     def createHelmholtz3dCombinedHypersingularBoundaryOperator(
..             context, domain, range, dualToRange,
..             kExt, kInt, wInt, label=None):
..         if not label: label = "" # convert None to a string
..         return _constructHelmholtz3dCombinedOperator(
..             "helmholtz3dCombinedHypersingularBoundaryOperator",
..             context, domain, range, dualToRange,
..             kExt, kInt, wInt, label)
.. \end{verbatim}
.. The function \texttt{createHelmholtz3dCombinedHypersingularBoundaryOperator()}
.. is intended to be called by the user. It does not take any explicit type
.. information. Instead, it passes its arguments to
.. \texttt{\_construct\-Helmholtz\-3d\-Combined\-Operator()}. This function first
.. retrieves the \texttt{Basis\-Function\-Type} from the assembly context and
.. verifies that its \texttt{ResultType} is the complex type of the same precision
.. as \texttt{Basis\-Function\-Type} and that the \texttt{Basis\-Function\-Type}s
.. of the three spaces match. Subsequently, it determines the name of the function
.. from \texttt{combined\_operators\_core.py} that needs to be used to construct
.. the hypersingular operator with appropriate \texttt{Basis\-Function\-Type},
.. calls this function and returns the newly created object. The
.. \texttt{\_construct\-Helmholtz\-3d\-Combined\-Operator()} function relies on the
.. fact that the Python wrappers of class templates from BEM++ define additional
.. methods \texttt{basis\-Function\-Type()}, \texttt{result\-Type()} and/or
.. \texttt{value\-Type()} (as appropriate) that return the standard NumPy
.. \emph{dtype} names of the relevant types. Note that the type-checking code in
.. \texttt{\_construct\-Helmholtz\-3d\-Combined\-Operator()} is not strictly
.. necessary---an incorrect type combination would be detected by Python or
.. SWIG---however, it produces more meaningful error messages.
