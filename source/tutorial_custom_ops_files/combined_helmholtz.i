%module combined_helmholtz
%{
#define SWIG_FILE_WITH_INIT
#include "helmholtz_3d_combined_boundary_operator.hpp"
%}

%include "bempp.swg"

%feature("compactdefaultargs") helmholtz3dCombinedBoundaryOperator;

%include "helmholtz_3d_combined_boundary_operator.hpp"

%feature("autodoc",
"
Create and return a combined boundary operator for the Helmholtz equation
in 3D,

   C = K - 1j * k * V,

where V and K are the single- and double-layer-potential boundary operators
with wave number k.

*Parameters:*
   - context (Context)
        A Context object to control the assembly of the weak form of the
        newly constructed operator. context.basisFunctionType() must be
        \"float64\" and context.resultType(), \"complex128\".
   - domain (Space)
        Function space to be taken as the domain of the operator.
   - range (Space)
        Function space to be taken as the range of the operator.
   - dualToRange (Space)
        Function space to be taken as the dual to the range of the operator.
   - waveNumber (complex)
        Wave number.
   - label (string)
        Textual label of the operator. If set to None (default), a unique
        label will be generated automatically.

*Returns* a newly constructed BoundaryOperator_float64_complex128 object.
") helmholtz3dCombinedBoundaryOperator;
%template(createHelmholtz3dCombinedBoundaryOperator) helmholtz3dCombinedBoundaryOperator<double>;

