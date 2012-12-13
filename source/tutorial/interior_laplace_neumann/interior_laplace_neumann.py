#!/usr/bin/env python

# PART 1: Import the necessary modules #########################################

BEMPP_PREFIX = "/home2/wojtek/Projects/BEM/bempp-work/bempp/install-debug-enthought-7.3/bempp/"

import sys
sys.path.append(BEMPP_PREFIX + "python")

from bempp.lib import *
import numpy as np

# PART 2: Set quadrature and assembly options ##################################

# Create quadrature strategy

accuracyOptions = createAccuracyOptions()
# Increase by 2 the order of quadrature rule used to approximate
# integrals of regular functions on pairs on elements
accuracyOptions.doubleRegular.setRelativeQuadratureOrder(2)
# Increase by 2 the order of quadrature rule used to approximate
# integrals of regular functions on single elements
accuracyOptions.singleRegular.setRelativeQuadratureOrder(2)
quadStrategy = createNumericalQuadratureStrategy(
    "float64", "float64", accuracyOptions)

# Set assembly options -- switch to ACA

assemblyOptions = createAssemblyOptions()
acaOptions = createAcaOptions()
acaOptions.eps = 1e-5
assemblyOptions.switchToAca(acaOptions)

# Combine the quadrature strategy and assembly options into an assembly context

context = createContext(quadStrategy, assemblyOptions)

# PART 3: Define the system of integral equations to be solved #################

# Import mesh

grid = createGridFactory().importGmshGrid(
    "triangular", "../meshes/sphere-ico-3.msh")

# Create function spaces

pconsts = createPiecewiseConstantScalarSpace(context, grid)
plins = createPiecewiseLinearContinuousScalarSpace(context, grid)
unit = createUnitScalarSpace(context, grid)

# Construct elementary operators

adlpOp = createLaplace3dAdjointDoubleLayerBoundaryOperator(
    context, pconsts, pconsts, plins, "ADLP")
hypOp = createLaplace3dHypersingularBoundaryOperator(
    context, plins, pconsts, plins, "Hyp")
idOp = createIdentityOperator(
    context, pconsts, pconsts, plins, "Id")
avgOp = createIdentityOperator(
    context, plins, unit, unit, "Avg")
adjAvgOp = createIdentityOperator(
    context, unit, pconsts, plins, "adjAvg")

lhsOp = createBlockedBoundaryOperator(
    context, [[hypOp, adjAvgOp], [avgOp, None]])

# Form the right-hand-side operator sum

rhsOp = 0.5 * idOp - adlpOp

# Create a grid function representing the input Neumann trace

def evalNeumannTrace(point, normal):
    x, y, z = point
    nx, ny, nz = normal
    dist = np.sqrt((x - 2)**2 + (y - 2)**2 + (z - 2)**2)
    numerator = (x - 2) * nx + (y - 2) * ny + (z - 2) * nz
    return numerator / (-4 * np.pi * dist**3)

neumannTrace = createGridFunction(
    context, pconsts, plins, evalNeumannTrace, surfaceNormalDependent=True)

def evalExactDirichletTrace(point):
    x, y, z = point
    dist = np.sqrt((x - 2)**2 + (y - 2)**2 + (z - 2)**2)
    return 1 / (4 * np.pi * dist)

exactDirichletTrace = createGridFunction(
    context, plins, pconsts, evalExactDirichletTrace)

# Construct the right-hand-side grid function list

rhs = [rhsOp * neumannTrace, avgOp * exactDirichletTrace]

# PART 4: Discretize and solve the equations ###################################

solver = createDefaultIterativeSolver(lhsOp)
solver.initializeSolver(defaultGmresParameterList(1e-8))

# Solve the equation

solution = solver.solve(rhs)
print solution.solverMessage()

# PART 5: Extract and export the solution ######################################

# Extract solution in the form of a grid function

solFun = solution.gridFunction(0) # first element of the solution

# Export the solution to a VTK file "solution.vtu"

solFun.exportToVtk("vertex_data", "dirichlet_trace", "solution")

# PART 6: Compare the numerical and analytical solution ########################

evalOptions = createEvaluationOptions()
absError, relError = estimateL2Error(solFun, evalExactDirichletTrace,
                                     quadStrategy, evalOptions)
print "Absolute L^2 error:", absError
print "Relative L^2 error:", relError
