.. BEM++ documentation master file, created by
   sphinx-quickstart on Tue Mar 27 11:38:21 2012.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to BEM++
================

BEM++ is a modern open-source C++/Python boundary element library. Its
development is a joint project between University College London
(UCL), the University of Reading and the University of Durham. The
main coding team is located at UCL and consists of Simon Arridge, Timo
Betcke, Richard James, Nicolas Salles, Martin Schweiger, Matthew Scroggs and
Wojciech Śmigaj.

Features
--------

- Galerkin discretization of all standard boundary integral operators
  (single-layer potential, double-layer potential, adjoint double-layer
  potential, hypersingular operator) for Laplace, Helmholtz, modified
  Helmholtz and Maxwell problems in three dimensions.

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

Publications
------------

W. Śmigaj, S. Arridge, T. Betcke, J. Phillips, M. Schweiger, "Solving Boundary
Integral Problems with BEM++", to appear in *ACM Trans. Math. Software* 
(`extended and revised preprint <http://www.bempp.org/files/bempp-toms-preprint.pdf>`_, `example
scripts <http://www.bempp.org/files/bempp-toms-examples.zip>`_).

Acknowledgements
----------------
This project was made possible by EPSRC Grants EP/I030042/1 and EP/K03829X/1, which
started on 1 October 2011 and provide funding for four years. 
Special thanks go also to the members of the `HyENA <http://portal.tugraz.at/portal/page/portal/Files/i2610/files/Forschung/Software/HyENA/html/index.html>`_ Team at TU Graz who gave us permission to use their Galerkin integration routines for BEM++.

Licensing
---------
The library itself is covered by a BSD license. The full licensing text is:

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


