Features
========

- Galerkin discretization of all standard boundary integral operators
  (single-layer potential, double-layer potential, adjoint double-layer
  potential, hypersingular operator) for Laplace, Helmholtz, modified
  Helmholtz and Maxwell problems in three dimensions.

- Numerical evaluation of boundary-element integrals (singular integrals dealt
  with using Sauter quadrature rules).

- Triangular surface mesh handling. Import of meshes in Gmsh format.

- Polynomial and discontinuous polynomial basis functions of various orders.

- Dense-matrix representation of boundary integral operators supported natively.

- Easy creation of operators composed of several logical blocks.

- Evaluation of potentials in space (away from the discretized surface).

- Export of solutions in VTK format.

- Parallel operation on shared-memory CPU architectures.

- C++ and Python interfaces.

- FEM/BEM Coupling with `FEniCS <http://www.fenicsproject.org>`_.

Changes to Version 2.0
----------------------

The current development branch is a major redevelopment compared to Version 2.0. While many
features have already been updated and some new developments included, not all Version 2.0 features
are available yet. A major focus in the current development branch is the Python support. Python
will become the preferred language for BEM++ and several non-performance critical features have
been directly implemented in Python. The C++ core is interfaced via Cython. **Unless H-Matrix support
via AHMED 1.0 is crucial we recommend to use the development branch. Version 2 will not be
further developed.** Native H-Matrix support is currently in development.

The following table compares the features of version 2.0 with the current development release. This will be updated as development progresses.

=================================== =============== =============================
Feature                             Version 2       Development Branch
=================================== =============== =============================
Laplace Kernels                     yes             yes
Helmholtz Kernels                   yes             yes
Maxwell Kernels                     yes             not yet from Python
Discontinuous polynomial spaces     yes             yes
Continuous polyomial spaces         yes             yes
H-Matrices                          via AHMED 1.0   native support in development 
Dual Spaces on Barycentric Grids    yes             in development
High-Freq. Preconditioning          no              in development
FEM/BEM Coupling                    no              via FEniCS (DUNE to come)
Grid Management                     Foamgrid        any Dune Grid Manager
FMM                                 no              in planning
Higher-Order Elements               no              in development
Python Interface                    Swig            Cython
Installer                           custom          CMake
=================================== =============== =============================
