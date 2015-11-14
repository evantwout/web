Frequently Asked Questions
==========================

Installation
------------
    1. :ref:`distribution-support`
    2. :ref:`python3-support`
    3. :ref:`docker-images`
    4. :ref:`mac-binaries`
    5. :ref:`ubuntu-ppa`
    6. :ref:`gcc-version`
    7. :ref:`compiler-error`


           
General Functionality
---------------------
    1. :ref:`logging`
    2. :ref:`cpp`
    3. :ref:`speed-up`
    4. :ref:`parallelization`
    5. :ref:`threading`
    6. :ref:`refinement`
    7. :ref:`h-algebra`
    8. :ref:`h-lu`
    9. :ref:`maxwell`

Future Plans
------------
    1. :ref:`release-schedule`
    2. :ref:`future-release`
    3. :ref:`windows`       
    4. :ref:`matlab`

Answers
-------

.. _distribution-support:

Why don't you provide binaries for distribution xyz?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
We aim to directly support the most widely used distributions
and are continuously expanding our list of supported environments.
Setting up a new environments means building a docker image for
our automatic binary creation scripts. So if it is technically
feasible and of interest we will add a new distribution.

.. _python3-support:

Does BEM++ support Python 3?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
BEM++ is continuously being tested on Python 3.4 and later
versions. Full support for Python 2.7 and Python 3.4+ is
of significant importance for us.

.. _docker-images:

Do you have Docker images?
^^^^^^^^^^^^^^^^^^^^^^^^^^
Internally we use Docker images as build environment. If
there is strong interest we can also release full Docker
images.

.. _mac-binaries:

Why are there no binaries for Mac?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
We provide Homebrew build scripts that are just as easy as
installing direct binaries.

.. _ubuntu-ppa:

Do you have a Ubuntu ppa?
^^^^^^^^^^^^^^^^^^^^^^^^^
A ppa for Ubuntu is in preparation.

.. _gcc-version:

What is the minimum gcc version for compilation?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Generally, we need a C++11 enabled compiler. We 
have tested gcc 4.8+. gcc 4.7 may work but is not
tested.

.. _compiler-error:

Compilation stops with an internal compiler error
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The compilation can require a lot of memory due to
the template structures in the library. An internal
compiler error is often a sign that the compiler has
run out of memory. In this case try to reduce the number
of parallel build processes in ``make``.

.. _logging:

Does BEM++ provide logging facilities?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
BEM++ integrates with the standard Python logging system.
To enable console logging use the command ``bempp.api.enable_console_logging``.
For file logging use the command ``bempp.api.enable_file_logging``.
Console logging can also be enabled with by setting the environment
variable ``BEMPP_CONSOLE_LOGGING`` to 1, e.g.::

    export BEMPP_CONSOLE_LOGGING=1

.. _cpp:

Can I use the C++ core directly?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
BEM++ until version 2 was essentially a C++ library with a Python interface
bolted on. This has changed. We have rewritten all the top layers of BEM++
in Python directly. It is now essentially a Python library with a fast
C++ core for low-level computations. Nevertheless, the C++ core can still be
used independently of Python. But most higher level functions will not be
available.

.. _speed-up:

How do I speed up BEM computations?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The main factors influencing the assembly speed are the order of the 
quadrature rule and the accuracy parameter ``eps`` in the H-Matrix assembly.
We provide relatively safe parameter values for many applications. Nevertheless, they
are not optimal in every situation and it is worth testing various different
parameter values to speed up the computation.

.. _parallelization:

What parallelization does BEM++ support?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
BEM++ uses Intel Threading Building Blocks for multithreading. 
We are currently working on integration with the IPython Parallel framework to
allow distributed assembly on multiple cluster nodes.

.. _threading:

Can I change the number of threads used by BEM++?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
To control the number of threads use the environment variable ``BEMPP_NUM_THREADS``, e.g. to set the maximum
number of threads to 2 use ``export BEMPP_NUM_THREADS=2``.

.. _refinement:

Why does the adaptive refinement not work?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
In the default configuration the adaptive refinement of individual elements leaves hanging nodes
in the mesh. The reason is that the grid manager used in BEM++ at the moment only supports
global refinement. BEM++ can optionally be compiled with Dune-Alugrid as grid manager. This is not
enabled by default for license reasons, but allows local refinement of meshes. To recompile BEM++
with Alugrid enabled use the CMake option ``WITH_ALUGRID=ON``.

.. _h-algebra:

Does BEM++ have a full H-matrix algebra?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Until BEM++ 2.0 BEM++ used the AHMED Library to provide
support for a full H-Matrix algebra. For license reason we
discontinued the use of AHMED and developed our own H-Matrix
compression. Implementation of a full H-Matrix algebra is
in planning though for a later version of BEM++.

.. _h-lu:

What happened to the H-LU decomposition?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
H-LU was part of AHMED, which has been removed from the library.
A self developed H-LU code is in planning for a later version of BEM++.

.. _maxwell:

What preconditioners are offered for Maxwell?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Currently we have no good Maxwell preconditioning built in. It is 
therefore recommended to use Maxwell in dense mode and solve via LU.
An efficient Calderon based preconditioner for Maxwell is almost finished, but
did not make it into the library in time for version 3.0. It will however be
integrated as soon as possible.

.. _release-schedule:

Release 3.0 took a long time. What is the future release schedule?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Release 3.0 is a major rewrite of the whole library after gaining some
experience with version 1 and 2 of BEM++ and seeing what worked and what not.
We now have a fairly complete development infrastructure in place and
much of the code is stabilized. So we expect to release more frequently updates
with functional enhancements.

.. _future-release:

What features are planned for the near future?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The focus of the BEM++ development is Maxwell and high-frequency
problems and we are planning to make several improvements in these areas.
Distributed assembly on clusters is quite far progressed and is currently being
tested on separate branches.

.. _windows:

Will there be a native Windows version?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Most likely no. We may be able with a lot of fixes to compile BEM++ in a Cygwin
environment. But none of the developers uses Windows. So it is of little priority to us.
We provide virtual machine images that run quite efficiently also under Windows.

.. _matlab:

Are you planning Matlab or Julia interfaces?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Matlab has growing Python support. So via the Matlab/Python bridge we may be able
to build a Matlab version. However, this is not of high priority for us. Julia is
a very interesting project. But before we invest time in it we would like to see it
stabilise and mature more.





 















