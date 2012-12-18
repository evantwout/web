.. highlight:: none
.. _interior_laplace_dirichlet:

An interior Dirichlet problem for the Laplace equation
===================================

In this section we solve a simple interior Laplace problem with Dirichlet boundary conditions. By going through this tutorial the reader will get to know some of
the main concepts of BEM++, namely reading a mesh, initializing function spaces, creating boundary integral operators, solving the resulting system and
exporting the solution data.

Mathematical formulation
-------------------------


We want to solve the problem

.. math::
    \begin{eqnarray}
        -\Delta u & =  & 0~\text{in}~\Omega,\nonumber\\
                   u & = & g~\text{on}~\Gamma.
     \end{eqnarray}

The Galerkin discretization of this problem was already discussed in
in :ref:`mathematics_background`. 

The continuous boundary
integral formulation is given as

.. math:: Vt = \left(\frac{1}{2}I+K\right)g,
    :label: slpequation

and the discrete problem takes the form

.. math:: \mathsf{V}\mathbf{t}^{int} = \left(\mathsf{\frac{1}{2}M+K}\right)\mathbf{v}^{int},


where the matrices are defined by

.. math::
    \begin{align*}
       \mathsf{V}_{i,j} &= \int_\Gamma\psi_i^{(0)}(x)\int_\Gamma g(x,y)\,\psi_j^{(0)}(y)ds(y)ds(x),\\
       \mathsf{M}_{i,j} &= \int_\Gamma\psi_i^{(0)}(x)\,\phi_j^{(1)}(x)ds(x),\\
      \mathsf{K}_{i,j} &= \int_\Gamma\psi_i^{(0)}(x)\int_\Gamma g(x,y)\,\phi_j^{(1)}(y)ds(y)ds(x).
    \end{align*}

Here, the :math:`\psi_i^{(0)}` are piecewise constant basis functions
and the :math:`\phi_i^{(1)}` are piecewise linear basis functions on the boundary mesh.

Implementation in BEM++
------------------------

We now describe how to implement the solution of the interior
interior Dirichlet problem for the Laplace equation with BEM++ using the Python interface.

Initialisation of the library
^^^^^^^^^^^^^^^^^^^^^^^^


We start by importing symbols from the ``lib`` module of the ``bempp``
package. We also load NumPy.

::

  from bempp.lib import *
  import numpy as np


The first step in a typical BEM++ session is to set options that
control the accuracy of the quadrature and the data types for the discretisation.

::

  accuracyOptions = createAccuracyOptionsEx()
  accuracyOptions.setDoubleSingular(2)
  quadStrategy = createNumericalQuadratureStrategy(
      "float64", "float64", accuracyOptions)

The first line initializes a new ``AccuracyOptionsEx`` object, which
controls the accuracy of the numerical quadrature.  By default, regular
quadrature is done using the least expensive rule ensuring exact integration of
a product of a test and a trial basis function. Since boundary-element
integrals contain, in addition, kernel functions, it is often a good idea to
increase the regular quadrature orders slightly, as we did in the above code
snippet. The default singular quadrature order is usually adequate.

The function ``createNumericalQuadratureStragety`` initializes the
numerical quadrature stragety. The first two parameters initialise the
*BasisFunctionType* and the *ResultType* of the numerical
discretisation.

Allowed values are : *float32*, *float64*, *complex64* and
*complex128*. These are the standard NumPy keywords for the C++
types *float*, *double* , *complex<float>*,
*complex<double>*. Not all combination of keywords for
*BasisFunctionType* and *ResultType* are admissible. BEM++ does not
allow to mix precisions, e.g. the combination of *float32* for the
*BasisFunctionType* and *complex128* for the *ResultType* is not allowed.

The third parameter to ``createNumericalQuadratureStrategy`` is the
``AccuracyOptionsEx`` object, initialised earlier.

Higher-level aspects of the weak-form assembly are controlled by
``AssemblyOptions`` objects. In particular, these determine whether the ACA
algorithm is used to accelerate the assembly and to reduce the memory
consumption. They can also be used to switch between serial and parallel
assembly. To turn on ACA (which is off by default), it suffices to write

::

  assemblyOptions = createAssemblyOptions()
  acaOptions = createAcaOptions()
  assemblyOptions.switchToAca(acaOptions)

The default accuracy for the Aca is set to 1e-4. Changing the value to
1e-5 is easily done by inserting ``acaOptions.eps = 1e-5`` between the
second and the third line of the above code snippet.

We now combine the  ``quadStrategy`` and the
``assemblyOptions`` into a single ``context`` object, which stores all
the information that BEM++ needs to create discretisations of boundary
integral operators.

::

  context = createContext(quadStrategy, assemblyOptions)


Loading the grid and initialising the boundary element spaces
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We now load a triangular grid using the command

::

  grid = createGridFactory().importGmshGrid("triangular",
                                              "<prefix>/bempp/examples/meshes/sphere-h-0.1.msh")

The variable *<prefix>* needs to be replaced by the installation
prefix of BEM++. Currently, BEM++ only supports triangular surface
grids in Gmsh format. The following output is created when the grid file
is read successfully.

::

  Reading 2d Gmsh grid...
  version 2.2 Gmsh file detected
  file contains 1288 nodes
  file contains 2757 elements
  number of real vertices = 1287
  number of boundary elements = 180
  number of elements = 2570

Now we can define the approximation spaces. We define the two spaces
of piecewise constant functions and piecewise linear continuous
functions as


::

  pconsts = createPiecewiseConstantScalarSpace(context, grid)
  plins = createPiecewiseLinearContinuousScalarSpace(context, grid)

To find out about the number of degrees of freedom in these two spaces
we can use the method ``globalDofCount()`` to obtain the following output.

::

  pconsts.globalDofCount()
  2570L

  plins.globalDofCount()
  1287L

The number of dofs in the space of piecewise constant functions is
identical to the number of elements in the grid and the number of dofs
in the space of continuous piecewise linear functions is identical to
the number of nodes in the grid.


Operators
^^^^^^^^^^^^^

We have everything together to define the boundary operators. This is
done with the following three commands.

::

  slpOp = createLaplace3dSingleLayerBoundaryOperator(
      context, pconsts, plins, pconsts)
  dlpOp = createLaplace3dDoubleLayerBoundaryOperator(
      context, plins, plins, pconsts)
  idOp = createIdentityOperator(
      context, plins, plins, pconsts)

An explanation is necessary here. BEM++ requires three spaces for each
operator, the domain space, the range space, and the dual-to-range
space.

The single layer potential :math:`V` maps the space
:math:`H^{-1/2}(\Gamma)` into the space
:math:`H^{1/2}(\Gamma)`. Natural discretisations of these two spaces
are the space of piecewise constant functions ``pconsts`` for
:math:`H^{-1/2}(\Gamma)` and the space of continuous piecewise linear
functions ``plins`` for :math:`H^{1/2}(\Gamma)`. The third space is the
discretisation of the dual space. Since :math:`H^{1/2}(\Gamma)` is
dual to :math:`H^{-1/2}(\Gamma)` we choose the space ``pconsts`` again.

Having to provide both, the range space and the dual-to-range space,
makes it possible to define an operator algebra in BEM++ that can also
deal with products of operators.

The composite operator :math:`\frac{1}{2}I + K` occurring on the right-hand side of
:eq:`slpequation` can be constructed simply by writing

::

  rhsOp = 0.5*idOp+dlpOp

in Python.

Defining the boundary data
^^^^^^^^^^^^^^^^^^^^^^^^^

We now need an object representing the expansion of the known
Dirichlet data :math:`g` in the space of piecewise linears. We will
take :math:`g` to correspond to the boundary data of
the exact solution of the Laplace equation

.. math::
  u_{exact}(x) = \frac{1}{4\pi|x - x_0|}
  \quad\text{with}\quad
  x_0 = (2, 2, 2).

We define, therefore, a native Python function
::

    def evalDirichletTrace(point):
        x, y, z = point
        dist = np.sqrt((x - 2)**2 + (y - 2)**2 + (z - 2)**2)
        return 1 / (4 * np.pi * dist)

receiving an array of coordinates of a single point and returning the
value of :math:`g` at this point. Subsequently, we pass it as the last
argument of ``createGridFunction``
::
  dirichletTrace = createGridFunction(
      context, plins, pconsts, evalDirichletTrace)

The function ``createGridFunction`` creates functions that live in a
function space defined over the grid. If a Python callable is given,
as in the example above, the function is obtained by a projection into
the domain space (in this case ``plins``), using functions from the
dual space of the domain space, which here is discretised by ``pconsts``.

Grid functions can also be initialised from vectors of coefficients or
projections. The help of ``createGridFunction`` contains all possible options.

The function on the right-hand side of :eq:`slpequation` is now
created using the operations

::

  rhs = rhsOp * dirichletTrace



