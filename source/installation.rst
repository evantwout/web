Installation
============

Obtaining the code
---------------

The code is available from https://github.com/bempp/bempp. To check it
out, use ``git clone git://github.com/bempp/bempp.git``.

Installation
---------

To build the library you need a current version of Python 2 (2.6 or
newer).  The Python interface has mostly been tested with
Enthought Python, but other distributions will also work. However, Python
visualization depends on Mayavi being available. The remaining dependencies of
the library (currently Armadillo, Boost, Dune, Swig, Intel TBB and Trilinos) are
automatically downloaded and compiled by the installer. The installer
depends on CMake as a build tool. Since not every system provides
CMake by default it is automatically downloaded and installed into the
bempp installation directory before the other dependencies are compiled and installed.
You need at least 2.5 GB of free space to build the library and all its dependencies; however, most of
this space can be recovered after a successful installation. The library has been
tested under Scientific Linux 6.1, Ubuntu 12.04, OpenSUSE 12.1 and Mac OS 10.7.


To build the library, do the following:

1. Copy the file ``bempp_setup.cfg.template`` into another file
   (e.g. ``bempp_setup.cfg``) and adapt the configuration variables.

   You may wish to change at least the following options:

   - Location of BLAS and Lapack.  You can either use MKL or manually specify
     BLAS and Lapack libraries.  If you intend to use the Python wrappers of
     BEM++, we recommend linking BEM++ with the same BLAS and Lapack as the
     NumPy package.  If your NumPy is linked with MKL (this is the case in
     Enthought Python, in particular), you can tell the BEM++ installer to
     detect the location of the MKL libraries automatically.

     Note for Ubuntu users: in Ubuntu 12.04, we have observed problems with
     linking with MKL 10.3.1, the version bundled with Enthought Python.
     Newer versions of MKL (specifically 10.3.7) work correctly.

   - Enable AHMED for H-Matrix support. You need to uncomment
     ``enable_ahmed=yes`` and set the option ``file_name`` in the AHMED section
     to the location of the AHMED installer file. You can download the file from
     `here <http://bebendorf.ins.uni-bonn.de/AHMED.html>`_.

2. Run the command ::


        python bempp_setup.py -b bempp_setup.cfg


   This bootstrap phase downloads all dependencies, setups the
   necessary directories and compiles and installs CMake into the
   bempp installation directory. Note that you need to have write access to the installation directory.

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

Usage
-----

As mentioned above, the ``examples`` and ``python/examples`` directories contain
a few examples demonstrating the usage of the C++ and Python interfaces to the
library. In particular, the ``tutorial_dirichlet.cpp`` and
``tutorial_dirichlet.py`` are described in detail on the BEM++ website
(``http://www.bempp.org/tutorial_dirichlet.html``). After a successful BEM++
installation, the compiled version of C++ examples are available in
``<build_dir>/examples``.

To build your own programs using BEM++, you need to add the
``<prefix>/bempp/include`` and ``<prefix>/bempp/include/bempp`` paths to the
include path of your compiler, and link to the ``bempp`` and ``teuchos``
libraries installed in ``<prefix>/bempp/lib`` (the latter is a component of
Trilinos). On Linux, it is also advisable to include ``<prefix>/bempp/lib`` in
the runtime path of your executable. On a Mac, you should add
``<prefix>/bempp/lib`` to the ``DYLD_LIBRARY_PATH`` environment variable before
running your program.

A schematic GCC invocation for compiling and linking a program ``my_program``
with BEM++ on Linux looks as follows::

    g++ -I <prefix>/bempp/include -I <prefix>/bempp/include/bempp my_program.cpp
        -o my_program -L <prefix>/bempp/lib -lbempp -lteuchos
        -Wl,-rpath,<prefix>/bempp/lib

On a Mac, you would omit ``-Wl,-rpath,<prefix>/bempp/lib``, but type ``export
DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:<prefix>/bempp/lib`` before running
``my_program``.

The file ``doc/CMakeLists.txt.example`` contains an example ``CMakeLists`` file
that can be used to build a program employing BEM++ with CMake.

To use the Python interface to BEM++, simply put ::

    import sys
    sys.path.append("<prefix>/bempp/python")
    import bempp.lib as blib

at the beginning of your Python script (replacing ``<prefix>`` with the path to
the BEM++ installation directory).

Final note
--------

The library is not yet officially released. We are still working on the
documentation and smaller issues with the code. The library is in an alpha
state: the interfaces are not stable yet and might change in a
backward-incompatible way. If you want to try BEM++ and run into problems, please
let us know.

                                                               -- The BEM++ Team
