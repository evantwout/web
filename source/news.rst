News
====

13 October 2014: Maintenance release 2.0.2
..........................................
A maintenance release that fixes a number of bugs discovered over the last few months:

- A memory leak in one of the integrators (issue `#165 <https://github.com/bempp/bempp/issues/165>`_)
- A compilation error occurring in the 32-bit mode (issue `#160 <https://github.com/bempp/bempp/issues/160>`_)
- A bug in ``Solver::checkConsistency()`` (issue `#150 <https://github.com/bempp/bempp/issues/150>`_)
- Incorrect Teuchos library name in the CMake config file installed with BEM++ (issue `#88 <https://github.com/bempp/bempp/issues/88>`_) 

10 March 2014: AHMED issues
...........................
AHMED 1.0 is not available for download any more. BEM++ is not compatible with the current AHMED version. We are working on a fix for this issue. But it may take a few more weeks to be available. In the meantime we recommend to compile BEM++ in dense mode by not enabling AHMED support in the configuration.

27 February 2014: Updated preprint
..................................
The BEM++ preprint on this page has been updated to contain various new examples such as opposite order
preconditioning and problems with mixed boundary data. It is in sync with the current version 2.0.1 of
BEM++. A shortened version of this preprint has been accepted for publication in the ACM Transactions on
Mathematical Software.

17 October 2013: Maintenance release 2.0.1
..........................................
A maintenance release that fixes the following issues

- Support for barycentric grids on block operators
  
- An MKL linking issue introduced in Version 2.0.0

- Support for Anaconda Python 1.7


13 October 2013: MKL linking issue in Version 2.0
.................................................
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
.......................................
This is a major new release. It contains many bugfixes to the 1.9 beta release
and supports opposite order preconditioning for Dirichlet and Helmholtz problems.

