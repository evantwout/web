Installation
============

Obtaining the code
------------------

The code is available from https://github.com/bempp/bempp.

To download the code, you need to have the Git version control system
(`<http://git-scm.com>`_) installed. To get the (stable) version 1.1
of the library, execute ::

    git clone -b release_1.1 git://github.com/bempp/bempp.git

from the command line in an empty directory. To download the current development
version, run ``git clone git://github.com/bempp/bempp.git`` instead. (Note
that the development version is by definition less stable and less well tested.)

Installation
------------

To build and install the library, you need

- a recent version of Python 2 (2.6 or newer; we recommend using the `Enthought
  Python Distribution <http://www.enthought.com/products/epd.php>`_)

- a modern C++ compiler

- a Fortran compiler (required by Dune, one of the BEM++ dependencies)

- a BLAS and LAPACK implementation (**Important:** read the information in the
  :ref:`Location of BLAS and LAPACK <location-of-blas-and-lapack>` paragraph
  below)

- (optional) sources of the AHMED library for H-matrix calculations; you can
  download them from `<http://bebendorf.ins.uni-bonn.de/AHMED.html>`_.

- (optional) the Python Mayavi module, if you want to use the visualization
  features from the Python interface to BEM++.

The build system used to compile BEM++ (CMake) and the remaining dependencies of
the library (currently Armadillo, Boost, Dune, Intel TBB, Swig and Trilinos)
are automatically downloaded and compiled by the installer. You need at least
2.5 GB of free space to build the library and all its dependencies; however,
most of this space can be recovered after a successful installation.

The library has been tested under Scientific Linux 6.1, Ubuntu 12.04,
OpenSUSE 12.1 and Mac OS 10.7.

To build the library, do the following:

1. Copy the file ``bempp_setup.cfg.template`` into another file
   (e.g. ``bempp_setup.cfg``) and adapt the configuration variables.

   You may wish to change at least the following options:

   .. _location-of-blas-and-lapack:

   - Location of BLAS and LAPACK.  You can either use Intel MKL or manually
     specify BLAS and LAPACK libraries.  If you intend to use the Python
     wrappers of BEM++, we recommend linking BEM++ with the same BLAS and LAPACK
     as the NumPy package.  If your NumPy is linked with MKL, as is the case
     with the full version of Enthought Python Distribution (i.e. other than EPD
     Free), you can tell the BEM++ installer to detect the location of the MKL
     libraries automatically.

     .. warning:: Many Linux distributions come with
        versions of BLAS and LAPACK built with the gfortran compiler.
        Unfortunately, with its default compilation settings, gfortran
        produces non-threadsafe versions of some LAPACK routines (more
        information can be found `here
        <http://icl.cs.utk.edu/lapack-forum/viewtopic.php?f=2&t=1930>`_). Linked
        against such versions of LAPACK and used in multithreaded
        mode, BEM++ will produce incorrect (random) results. Therefore
        you are strongly advised to either use LAPACK from Intel MKL,
        which is free from this bug, or to compile LAPACK yourself,
        including ``-fmax-stack-var-size=66560`` in the list of
        gfortran compilation options.

     .. note:: BEM++ by default uses multiple threads to assemble matrix
        representations of integral operators. To avoid performance loss due to
        nested parallelization, BLAS and LAPACK routines should therefore run in
        serial mode. For some popular BLAS and LAPACK implementations, this can
        be ensured as follows:

        - MKL: no need to do anything, BEM++ manages the number of threads
          automatically.
        - GotoBLAS and OpenBLAS: set the environmental variable OMP_NUM_THREADS to
          1 before running programs using BEM++.
        - ATLAS: number of threads is determined at compilation time. Use a serial
          version of ATLAS.

     .. admonition:: Take-home message
        :class: warning

        If you do not feel comfortable with compiling LAPACK and NumPy on
        your own, and if you have access to a full version of the Enthought
        Python Distribution (i.e. other than EPD Free), we strongly recommend
        you to use it to install BEM++. In this case, you should uncomment the
        lines ``enable_mkl=yes`` and ``source=like_numpy`` in the ``MKL``
        section of the configuration file. Note that academic users can obtain a
        full version of the Enthought Python Distribution free of charge.

   - Enable AHMED for H-Matrix support. You need to uncomment
     ``enable_ahmed=yes`` and set the option ``file_name`` in the AHMED section
     to the location of the archive with AHMED source code.

2. Run the command ::

        python bempp_setup.py -b bempp_setup.cfg

   This bootstrap phase downloads all dependencies, setups the
   necessary directories and compiles and installs CMake into the
   BEM++ installation directory. Note that you need to have write access
   to the installation directory.

3. Run the command ::

       python bempp_setup.py -c bempp_setup.cfg

   This extracts all library dependencies (currently Armadillo, Boost, Dune, Swig, TBB and Trilinos), patches the sources where necessary and generates a config file with automatially detected options.

4. Run the command ::

       python bempp_setup.py -i all bempp_setup.cfg

   This builds all the dependencies and installs them, and subsequently proceeds to building and installing BEM++ itself.

   The library will be installed into ``<prefix>/bempp/lib`` and the python
   module at ``<prefix>/bempp/python``, where ``<prefix>`` is the directory
   specified in the configuration file.  Note that the generation of the Python
   module takes rather a long time. Therefore, the installer may seem to hang
   for a few minutes without doing anything.

5. If you have Doxygen installed, you can generate documentation of the C++ API
   of BEM++ by going into ``<build_dir>`` and typing ``make doc``. The
   documentation is generated in the ``<build_dir>/doc/html`` directory. You are
   advised to use a recent version of Doxygen (e.g. 1.8.2), since older versions
   do not always parse C++ templates properly.

6. If you have Sphinx installed, you can generate documentation of the Python
   API of BEM++ by going into ``<build_dir>`` and typing ``make
   python_doc``. The documentation is generated in the
   ``<build_dir>/python/doc/html`` directory.

7. If you use Mac OS, you need to add the ``<prefix>/bempp/lib`` directory
   to the ``DYLD_LIBRARY_PATH`` environmental variable by running the command ::

       export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:<prefix>/bempp/lib

   (with ``<prefix>`` replaced with the path to the BEM++ installation
   directory). If you wish, you can add this line to the ``.bash_profile`` file
   in your home directory to make sure that this setting is applied each time a
   new Terminal session is started.

Updates
-------

Bugfixes to the stable version of BEM++ will be committed to the release_1.0
git branch. You can obtain the latest bugfixes by executing ::

   python bempp_setup.py -u all bempp_setup.cfg

in BEM++ source directory. This will check whether any updates are available,
and if yes, download them, recompile and install the library.

Usage
-----

As mentioned above, the ``examples`` and ``python/examples`` directories contain
a few examples demonstrating the usage of the C++ and Python interfaces to the
library. In particular, the ``tutorial_dirichlet.cpp`` and
``tutorial_dirichlet.py`` are described in detail on the BEM++ website
(``http://www.bempp.org/tutorial_dirichlet.html``). After a successful BEM++
installation, the compiled version of C++ examples are available in
``<prefix>/examples``.

To build your own programs using BEM++, you need to add the
``<prefix>/bempp/include`` and ``<prefix>/bempp/include/bempp`` paths to the
include path of your compiler, and link to the ``bempp`` and ``teuchos``
libraries installed in ``<prefix>/bempp/lib`` (the latter is a component of
Trilinos). On Linux, it is also advisable to include ``<prefix>/bempp/lib`` in
the runtime path of your executable. On a Mac, you should add
``<prefix>/bempp/lib`` to the ``DYLD_LIBRARY_PATH`` environmental variable
before running your program, as explained in the previous section.

A schematic GCC invocation for compiling and linking a program ``my_program``
with BEM++ on Linux looks as follows::

    g++ -I <prefix>/bempp/include -I <prefix>/bempp/include/bempp my_program.cpp
        -o my_program -L <prefix>/bempp/lib -lbempp -lteuchos
        -Wl,-rpath,<prefix>/bempp/lib

On a Mac, you can omit ``-Wl,-rpath,<prefix>/bempp/lib``.

The file ``doc/misc/CMakeLists.txt.example`` contains an example ``CMakeLists``
file that can be used to build a program employing BEM++ with CMake.

To use the Python interface to BEM++, simply put ::

    import sys
    sys.path.append("<prefix>/bempp/python")
    import bempp.lib as blib

at the beginning of your Python script (replacing ``<prefix>`` with the path to
the BEM++ installation directory).

Troubleshooting
---------------

Known issues
............

**Attempt at loading the ``visualization`` Python module fails with the error message "ImportError: Could not import backend for traits"**

This problem occurs with Enthought Python Distribution installed in some recent
Linux distributions and is usually caused by a missing ``libpng.12.so.0``
library. To confirm this diagnosis, start Python and execute ``import
enthought.tvtk.api``. If you receive the message *ImportError: libpng.12.so.0:
cannot open shared object file: No such file or directory*, you need to install
the ``libpng12`` package using your distribution's package management system.

**Single-precision calculations on MacOS X 10.7 using the Accelerate framework give erroneous results**

This problem occurs because the interface of the ``sdot()`` function from
Accelerate is incompatible with AHMED: the function returns a double-precision
number, whereas AHMED expects a single-precision result. Until this problem is
fixed, you can either do calculations in double precision or switch to a
different BLAS implementation (e.g. MKL). Please contact us if these workarounds
are not feasible for you.

Other problems
..............

If you run into other problems with installation or usage of BEM++, please let
us know by opening an issue at https://github.com/bempp/bempp/issues.

                                                               -- The BEM++ Team
