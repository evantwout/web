#ifndef bempp_examples_helmholtz_3d_combined_boundary_operator_hpp
#define bempp_examples_helmholtz_3d_combined_boundary_operator_hpp

#include "helmholtz_3d_combined_potential_kernel_functor.hpp"

#include "assembly/boundary_operator.hpp"

#include "fiber/scalar_function_value_functor.hpp"
#include "fiber/simple_test_scalar_kernel_trial_integrand_functor.hpp"

#include "assembly/general_elementary_singular_integral_operator_imp.hpp"

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

#endif
