.. BEM++ documentation master file, created by
   sphinx-quickstart on Tue Mar 27 11:38:21 2012.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to BEM++
=================================

BEM++ is a project to develop a modern C++ boundary element library including the following features.

* Support of the standard kernels for Laplace, Elasticity, Helmholtz, and Maxwell problems.
* Extensibility for adding other kernels.
* Galerkin boundary element discretisation
* Piecewise constant, and linear/quadratic conforming boundary element spaces
* Extensive linear solver library via interface to Trilinos
* Fast boundary elements via Adaptive Cross Approximation or Fast Multipole Methods.
* Support for multi-threading on multi-core systems, and MPI on clusters.
* GPU acceleration via OpenCL.
* Complete bindings to Python and Matlab.

BEM++ is a joint project between University College London (UCL), the University of Reading and the University of Durham. The main coding team is located at UCL and consists of *Simon Arridge, Timo Betcke, Joel Phillips, Martin Schweiger, Wojciech Smigaj*. Other project members include Stephen Langdon (Reading), Douglas Saddy (Reading), and Jon Trevelyan (Durham).

Status
---------------
The project is in heavy development, and we do net yet consider it usable for the wider public. The following features are already implemented.

* Laplace Single/Double/Conjugate Double and Hypersingular Potential for problems in three dimensions.
* Piecewise constant and continuous piecewise linear basis functions.
* Integrators for Galerkin discretisation
* Mesh handling via Dune and interfaces for surface triangular meshes. Currently, we ony support Gmsh input.
* Partial interfaces to Python.
* Linear Algebra Interfaces to Trilinos.
* Interfaces to AHMED for H-Matrix acceleration and Preconditioning.
* Experimental support for OpenCL integrators.

Most of these features need further testing and performance optimisation. We therefore do not yet consider them ready for general use.

Acknowledgements
----------------
The project was made possible by EPSRC Grant EP/I030042/1, which started 01 October 2011 and provides initial funding for two years. A special thanks also goes to the members of the `HyENA <http://portal.tugraz.at/portal/page/portal/Files/i2610/files/Forschung/Software/HyENA/html/index.html>`_ Team at TU Graz who gave us permission to use their Galerkin integration routines for BEM++.


Licensing
----------------
The library is licensed under a BSD license. 

Contents:

.. toctree::
   :maxdepth: 2

   intro
   tutorial

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

