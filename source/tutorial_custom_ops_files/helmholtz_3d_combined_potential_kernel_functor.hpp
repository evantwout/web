#ifndef bempp_examples_helmholtz_3d_combined_potential_kernel_functor_hpp
#define bempp_examples_helmholtz_3d_combined_potential_kernel_functor_hpp

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

#endif
