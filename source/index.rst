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
Arridge, Timo Betcke, Martin Schweiger and Wojciech Śmigaj. Other project members include Stephen Langdon (Reading), Douglas Saddy (Reading), and Jon Trevelyan (Durham).

News
----

12 December 2012: New BEM++ preprint
........................................

The preprint  `Solving boundary integral problems with BEM++
<http://www.bempp.org/files/bempp-toms-preprint.pdf>`_ is now
available. It describes the design of BEM++ and discusses several
example applications.


11 December 2012: released version 1.1.0
........................................

New features:

- Significantly simplified the implementation of custom boundary operators:

  * Thanks to the new ``GeneralElementarySingularIntegralOperator`` class there is
    no need to declare a new subclass of ``ElementaryIntegralOperator`` for each new
    kernel.

  * The mechanism of discrete weak-form caching has been modified and is no
    longer based on a global cache indexed with identifiers of abstract boundary
    operators. As a result, implementation of the ``AbstractBoundaryOperator::id()``
    method in new operator classes can be safely skipped, as this method is no
    longer used.

- Improved the conversion of discrete operators into the H-matrix format:

  * This functionality has been implemented for discrete operators stored as
    sparse matrices and for blocked discrete operator. This means in particular
    that a discrete operator composed of several blocks stored as separate H-
    and/or sparse matrices can now be converted into a *single* H-matrix.

  * The default values of the arguments to
    ``DiscreteBoundaryOperator::asDiscreteAcaBoundaryOperator()`` have been changed
    to reduce the chances of unintended loss of accuracy during addition of
    H-matrices.

- Added the ``adjoint()`` function returning the adjoint of a boundary operator.

- Added the ``transpose()``, ``conjugate()`` and ``conjugateTranspose()`` functions
  returning the respective transformations of discrete boundary operators.

- Added the ``UnitSpace`` class, representing the space consisting of the single
  function equal to 1 everywhere. This class is useful in the solution of
  Neumann problems.

- Added the ``estimateL2Error()`` function, which can be used to calculate
  accurately the :math:`L^2` norm of the difference between a numerical and analytical
  solution of a problem.

- ``GridFunction`` objects are now able to calculate their projections on any dual
  space, specified by a new parameter of the ``GridFunction::projections()`` method.
  For compatibility, it remains possible to fix the dual space during
  construction of a ``GridFunction`` and to call ``projections()`` without arguments.

- The quadrature order for single regular integrals specified with
  ``AccuracyOptions`` is now used during the discretisation of functions into
  ``GridFunction`` objects (previously it was only used during potential
  evaluation).

This version maintains source-level (but not binary-level) backward
compatibility with versions 1.0.x.

12 November 2012: released version 1.0.2
........................................

A maintenance release fixing a few minor bugs in BEM++. It contains a workaround
for a suspected compiler bug in llvm-gcc on MacOS X 10.7 in 64-bit mode and
adds support for GCC 4.7.

3 November 2012: released version 1.0.1
.......................................

This is a maintenance release correcting two bugs in the AHMED interface
and improving the update procedure.

29 October 2012: released version 1.0.0
.......................................

This is the first official release of the library, including the
following features:

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
   A BEM++ tutorial <tutorial/index>
   C++ interface reference (version 1.1) <http://www.bempp.org/cppref/1.1/index.html>
   Python interface reference (version (1.1) <http://www.bempp.org/pythonref/1.1/index.html>
   C++ interface reference (version 1.0) <http://www.bempp.org/cppref/1.0/index.html>
   Python interface reference (version (1.0) <http://www.bempp.org/pythonref/1.0/index.html>

Publications
------------

W. Śmigaj, S. Arridge, T. Betcke, J. Phillips, M. Schweiger, "Solving Boundary Integral Problems with BEM++", submitted to *ACM Trans. Math. Software* (`preprint <http://www.bempp.org/files/bempp-toms-preprint.pdf>`_).

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

