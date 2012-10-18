.. BEM++ documentation master file, created by
   sphinx-quickstart on Tue Mar 27 11:38:21 2012.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to BEM++
================

BEM++ is a project to develop a modern open source C++ boundary
element library. It is a joint project between University College
London (UCL), the University of Reading and the University of
Durham. The main coding team is located at UCL and consists of Simon
Arridge, Timo Betcke, Martin Schweiger and Wojciech Smigaj. Other project members include Stephen Langdon (Reading), Douglas Saddy (Reading), and Jon Trevelyan (Durham).

Status
------
The project is still in development but already usable for certain problems. The following features are implemented.

- Galerkin discretization of all standard boundary integral operators
  (single-layer potential, double-layer potential, adjoint double-layer
  potential, hypersingular operator) for Laplace, Helmholtz and modified
  Helmholtz problems in three dimensions.

- Numerical evaluation of boundary-element integrals (singular integrals dealt
  with using Sauter-Schwab quadrature rules).

- Triangular surface mesh handling. Import of meshes in Gmsh format.

- Piecewise constant and continuous piecewise linear basis functions.

- Dense-matrix representation of boundary integral operators supported natively.

- Assembly of H-matrix representations of boundary integral operators via
  adaptive cross approximation (ACA) supported thanks to an interface to
  M. Bebendorf’s `AHMED <http://bebendorf.ins.uni-bonn.de/AHMED.html>`_ library.

- H-matrix-based preconditioners (via AHMED).

- Easy creation of operators composed of several logical blocks.

- Interfaces to iterative linear solvers from Trilinos.

- Evaluation of potentials in space (away from the discretized surface).

- Export of solutions in VTK format.

- Parallel operation on shared-memory CPU architectures.

- C++ and Python interfaces.

Documentation
-------------

.. toctree::
   :maxdepth: 1

   Installation <installation>
   Tutorial <tutorial_dirichlet>
   C++ interface reference <http://www.bempp.org/cppref/index.html>
   Python interface reference <http://www.bempp.org/pythonref/index.html>

Acknowledgements
----------------
The project was made possible by EPSRC Grant EP/I030042/1, which started 01 October 2011 and provides initial funding for two years. Special thanks go also to the members of the `HyENA <http://portal.tugraz.at/portal/page/portal/Files/i2610/files/Forschung/Software/HyENA/html/index.html>`_ Team at TU Graz who gave us permission to use their Galerkin integration routines for BEM++.


Licensing
---------
The library itself is licensed under a BSD license. The full licensing text is:

Copyright (C) 2011 by the BEM++ Authors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

.. comment

   Indices and tables
   -------------------

   * :ref:`genindex`
   * :ref:`modindex`
   * :ref:`search`

