Installation Instructions
=========================

Building BEM++ from scratch
---------------------------

Dependencies
^^^^^^^^^^^^

To build and install BEM++ you will need to have the following installed:

*   Python 2.7 or Python 3.4/3.5

*   `Git version control system <http://git-scm.com/>`_.

*   `CMake <http://www.cmake.org/>`_.

*   Cython v0.22 or higher

*   Scipy v0.16.0 or higher

*   Numpy 1.9 or higher

  

Obtaining the Code
^^^^^^^^^^^^^^^^^^

The code is available from https://github.com/bempp/bempp. You can
get the latest stable version be executing::

    git clone https://github.com/bempp/bempp.git

Compiling
^^^^^^^^^

To compile BEM++, navigate to the directory where the source code has
downloaded::

    cd bempp

then make a folder called build and navigate into it::

    mkdir build
    cd build

BEM++ will compile in this directory. Next, make the configuration file
for the build with cmake::

    cmake -DCMAKE_INSTALL_PREFIX=<install_dir> ..

Substitute ``<install_dir>`` by the directory where BEM++ should be
installed (e.g. ``$HOME/bempp``)

Next, compile the BEM++ library::

    make -j4

The parameter ``-j4`` denotes that we use 4 parallel build processes.
If you have a system with a larger number of cores you can set
it to ``-j8`` or higher to speed up the installation.
The installer will download any dependencies you do not have.

After successful compilation run::

    make install

to install BEM++ to the specified location.



Running BEM++
^^^^^^^^^^^^^

You will need to point the ``PYTHONPATH`` environment variable to BEM++. For example, if BEM++ was installed in ``/home/foo/bempp`` using Python 2.7 use::

    export PYTHONPATH=/home/foo/bempp/lib/python2.7/site-packages

It may be necessary to also adapt the ``LD_LIBRARY_PATH`` (Linux) or ``DYLD_LIBRARY_PATH`` environment variable (Mac), i.e.::

    export LD_LIBRARY_PATH=/home/foo/bempp/lib







