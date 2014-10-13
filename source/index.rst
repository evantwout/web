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
Betcke, Richard James, Nicolas Salles, Martin Schweiger and Wojciech Śmigaj. 

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

News
----

10 March 2014: AHMED Issues
................................
AHMED 1.0 is not available for download any more. BEM++ is not compatible with the current AHMED version. We are working on a fix for this issue. But it may take a few more weeks to be available. In the meantime we recommend to compile BEM++ in dense mode by not enabling AHMED support in the configuration.


27 February 2014: Updated preprint
.................................
The BEM++ preprint on this page has been updated to contain various new examples such as opposite order
preconditioning and problems with mixed boundary data. It is in sync with the current version 2.0.1 of
BEM++. A shortened version of this preprint has been accepted for publication in the ACM Transactions on
Mathematical Software.

17 October 2013: Maintenance Release 2.0.1
..........................................
A maintenance release that fixes the following issues

- Support for barycentric grids on block operators
  
- An MKL linking issue introduced in Version 2.0.0

- Support for Anaconda Python 1.7


13 October 2013: MKL linking issue in Version 2.0
..................................................
We discovered an MKL linkage issue in BEM++ 2.0. This can for example
occur if BEM++ is linked against the MKL version in Enthought Canopy.
So far the observed effect of this issue is potentially wrong results
in the output of PotentialOperators for the evaluation of solution fields
away from the computation surface.

We are currently investigating this problem and until it is fully resolved we
recommend to use the BEM++ version in the branch ``release_2.0_bug_fixes`` which seems to
fix the issue, i.e.
download BEM++ with ``git clone -b release_2.0_bug_fixes https://github.com/bempp/bempp.git``. 
Note that this version has compatibility problems with Ubuntu 12.04. However,
it has been successfully tested with Ubuntu 13.04

When the issue is fully resolved a fix will be merged back in the main release_2.0
branch.

27 September 2013: released version 2.0
......................................
This is a major new release. It contains many bugfixes to the 1.9 beta release
and supports opposite order preconditioning for Dirichlet and Helmholtz problems.


22 June 2013: released version 1.9.0
....................................

This is a preview (beta) of the upcoming BEM++ 2.0. It provides the following
new features:

- Solution of Maxwell equations. See the `documentation of the Maxwell module
  <http://www.bempp.org/cppref/1.9/group__maxwell__3d.html>`_ for more
  information about the available operators, and the
  ``maxwell_scattering_diel.py``, ``maxwell_scattering_pec.py`` and
  ``maxwell_diffraction_by_plate.py`` scripts for usage examples.

- More robust ACA assembly of operators containing zero or small-magnitude
  subblocks stemming from flat or nearly flat parts of surfaces (e.g. the
  double-layer potential boundary operator).

- New, faster methods of ACA assembly of integral operators (especially
  hypersingular operators). See the `documentation of AcaOptions::mode
  <http://www.bempp.org/cppref/1.9/structBempp_1_1AcaOptions.html#ae8a1d643f44c030552e94e62c052f1d0>`_
  for more information.

- ACA-accelerated evaluation of potentials in space. See the `documentation of
  EvaluationOptions::switchToAcaMode
  <http://www.bempp.org/cppref/1.9/classBempp_1_1EvaluationOptions.html#ad747e4f5e84017493c9edc3fc3e95fc9>`_
  for more information.

- New ``visualization2`` module for interactive visualization of calculation
  results in Python. Based on the Mayavi library, this module makes it possible
  to change plot properties (e.g. colour schemes, colour scales) using a
  GUI. Note that the old ``visualization`` module is still supported.

- The versions of some libraries downloaded by the BEM++ installer
  (specifically, DUNE and Trilinos) have been updated.

21 June 2013: update on AHMED
.............................

It is again possible to download the 1.0 version of AHMED (1.0), with which
BEM++ is compatible, from `M. Bebendorf’s webpage
<http://bebendorf.ins.uni-bonn.de/AHMED.html>`_. Note that you should download
the tarball with AHMED 1.0 rather than clone the Git repository: the latter
contains AHMED 1.1.

Support for AHMED 1.1 will be added in due course.

13 June 2013: new version of AHMED
..................................

It has been brought to our attention that the mode of distribution of AHMED has
changed -- to obtain it, one needs now to clone a Git repository rather than to
download a tar.gz file. We have seen reports that BEM++ does not compile
successfully against the version of AHMED available from the Git repository. We
do not yet have access to the new AHMED repository; as soon as we get it, we
will investigate the problem and update BEM++ to cooperate with the new version
of AHMED.

`Older news >> <files/older_news.html>`_

Documentation
-------------

.. toctree::
   :maxdepth: 1

   Installation <installation>
   Tutorial: exterior Dirichlet problem for the Laplace equation <tutorial_dirichlet>
   Tutorial: adding custom operators <tutorial_custom_ops>
   C++ interface reference (version 2.0) <http://www.bempp.org/cppref/2.0/index.html>
   Python interface reference (version 2.0) <http://www.bempp.org/pythonref/2.0/index.html>
   C++ interface reference (version 1.9) <http://www.bempp.org/cppref/1.9/index.html>
   Python interface reference (version 1.9) <http://www.bempp.org/pythonref/1.9/index.html>
   C++ interface reference (version 1.1) <http://www.bempp.org/cppref/1.1/index.html>
   Python interface reference (version 1.1) <http://www.bempp.org/pythonref/1.1/index.html>
   C++ interface reference (version 1.0) <http://www.bempp.org/cppref/1.0/index.html>
   Python interface reference (version 1.0) <http://www.bempp.org/pythonref/1.0/index.html>

The preprint mentioned below is also a useful source of information.

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

