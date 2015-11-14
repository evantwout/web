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

- Built-in H-Matrix assembly of boundary operators and potentials

- High-Frequency OSRC preconditioners for Helmholtz

- Dual grid based operator preconditioning for Laplace and Helmholtz

- Parallel operation on shared-memory CPU architectures.

- Pythonic library interface

- FEM/BEM Coupling with `FEniCS <http://www.fenicsproject.org>`_.

Changes to Version 2.0
----------------------

Version 3.0 is a major rewrite of BEM++. Most higher-order routines have been redeveloped in Python to provide a better Python integration. H-Matrix compression is now handled by a native built-in library. The dependency on external libraries was reduced and the compilation is now based on standard CMake scripts. While Version 3.0 is an improvement in almost every respect it does not yet have a built-in H-LU decomposition. This is one of the priority areas for the further development of BEM++.

The following table compares the features of version 2.0 with 3.0. 

=================================== =============== =============================
Feature                             Version 2       Version 3
=================================== =============== =============================
Laplace Kernels                     yes             yes
Helmholtz Kernels                   yes             yes
Maxwell Kernels                     yes             yes
Discontinuous polynomial spaces     yes             yes
Continuous polyomial spaces         yes             yes
H-Matrices                          via AHMED 1.0   native support
Dual Spaces on Barycentric Grids    yes             yes
High-Freq. Preconditioning          no              yes
FEM/BEM Coupling                    no              via FEniCS 
Grid Management                     Foamgrid        any Dune Grid Manager
FMM                                 no              in planning
Higher-Order Elements               no              no
Python Interface                    Swig            Cython
Installer                           custom          CMake
=================================== =============== =============================
