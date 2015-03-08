Installation
============


Please note that the installation instructions presented here refer to the current development release (2.9+). Instructions for BEM++ 2.0 can be found `here <old_installation.html>`_.

In the following we describe the installation under Mac OS X 10.10 and Ubuntu 14.04. Later Ubuntu versions and other Linux flavors may work if the dependencies are satisfied. But we are not testing them explicitly.

The installation described below assumes that the default system Python interpreter is used. We strongly recommend to download `Anaconda Python <https://store.continuum.io/cshop/anaconda/>`_ and to install the commercial MKL module, which is `free <https://store.continuum.io/cshop/academicanaconda>`_ for academic use. Once the installation is in place one can use the command ``conda install mkl`` to install the MKL module. The BEM++ installer will automatically pick this up and use it as its BLAS library. In the future we may fully remove the dependency to external BLAS libraries. If Anaconda together with Intel MKL is not installed BEM++ will use the available system BLAS library.

**In the future we may remove the dependency to external BLAS libraries.**

Mac OS X Dependencies
---------------------

If you haven't done so you need to install XCode from the App Store to get the necessary development tools. In addition you need to install recent versions of *cmake* and *pkg-config*. If you have `Homebrew <brew.sh>`_ you can install these dependencies with the commands:

* ``brew install cmake``
* ``brew install pkg-config``

Ubuntu 14.04 Dependencies
-------------------------

To install BEM++ on Ubuntu 14.04 you need to install several dependencies. This can be accomplished with the command::

    sudo apt-get install g++ cmake libopenblas-dev ipython-notebook python-numpy \
    python-scipy libvtk6-dev vtk6 libxml2 libxml2-dev \
    zlib1g-dev git python-setuptools libbz2-dev liblapack3 \ 
    libarmadillo-dev mpi-default-bin


Obtaining the Code
------------------

The code is available from https://github.com/bempp/bempp. You can
get the latest stable version be executing::

    git clone https://github.com/bempp/bempp.git

This creates a directory ``bempp`` in the current subdirectory.

Compilation
--------------------------


To compile BEM++ use the following commands::

    cd bempp
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release -DWITH_FENICS=ON ..
    make -j6

The last command ``make -j6`` compiles BEM++ in parallel using six build instances. The option `-j6` is best for quad-core machines. If you have more or fewer cores available you should adapt this command.

The option ``-DWITH_FENICS=ON`` builds `FEniCS <http://fenicsproject.org>`_ as part of BEM++. FEniCS is a modern FEM library with a Python interface. BEM++ allows the solution of certain coupled FEM/BEM problems with FEniCS.


Running BEM++
-------------

To run a Python or IPython environment including BEM++, run::

    build/bin/bempp

for a Python environment

or::

    build/bin/ibempp

for an IPython environment

If you add the command::

    export PATH="/path/to/bempp/build/bin:$PATH"

to your `.bashrc` or `.bash_profile` file you can run `bempp` or `ibempp` from your terminal.

