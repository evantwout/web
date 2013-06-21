News archive
====

21 June 2013: released version 1.9.0
....................................

This is a preview (beta) of the upcoming BEM++ 2.0. It provides the following
new features:

- Solution of Maxwell equations. See the documentation of the Maxwell module for
  more information about the available operators, and the
  ``maxwell_scattering_diel.py``, ``maxwell_scattering_pec.py`` and
  ``maxwell_diffraction_by_plate.py`` scripts for usage examples.

- More robust ACA assembly of operators containing zero or small-magnitude
  subblocks stemming from flat or nearly flat parts of surfaces (e.g. the
  double-layer potential boundary operator).

- New, faster methods of ACA assembly of integral operators (especially
  hypersingular operators). See the documentation of AcaOptions::mode for more
  information.

- ACA-accelerated evaluation of potentials in space. See the documentation of
  EvaluationOptions::switchToAcaMode for more information.

- New ``visualization2`` module for interactive visualization of calculation
  results in Python. Based on the Mayavi library, this module makes it possible
  to change plot properties (e.g. colour schemes, colour scales) using a
  GUI. Note that the old ``visualization`` module is still supported.

- The versions of some libraries downloaded by the BEM++ installer
  (specifically, DUNE and Trilinos) have been updated.

10 June 2013: released version 1.1.4
........................................

This version brings some improvements to the documentation of the C++
interface. In particular, standalone functions are now visible in the
documentation of the most closely related class; classes responsible
for grid management have been separated into the new Grid module; and
the Doxygen documentation is now searchable.

In addition, a missing ``#include`` directive has been added to the Swig
interface file bempp.swg. This is only important for users
implementing their own boundary operator classes.

10 May 2013: released version 1.1.3
.......................................

This version adds support for the new version of Enthought Python Distribution,
`Canopy <https://www.enthought.com/products/canopy>`_. See the `installation
instructions <installation.html>`_ for more information about installing BEM++
with Canopy. At the time of writing, the Mac version of Canopy seems to be more
stable than the Linux version. Linux users might consider using the older EPD
7.3 version for the time being.

11 April 2013: new tutorial
...........................

New `tutorial <tutorial_custom_ops.html>`_ on extending BEM++ with custom operators.

28 January 2013: released version 1.1.2
.......................................

A maintenance release improving the detection of the G77 linking convention on
32-bit systems.


7 January 2013: released version 1.1.1
......................................

A maintenance release fixing problems encountered during compilation without
AHMED.

12 December 2012: New BEM++ preprint
........................................

The preprint `Solving boundary integral problems with BEM++
<http://www.bempp.org/files/bempp-toms-preprint.pdf>`_ is now available together
with the accompanying `example scripts
<http://www.bempp.org/files/bempp-toms-examples.zip>`_. It describes the design
of BEM++ and discusses several example applications.


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

