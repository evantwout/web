Installation Instructions
=========================

In the following we describe different ways of installing BEM++. We
offer the following installation options.

* :ref:`virtualbox`
* :ref:`linuxbinary`
* :ref:`installhomebrew`
* :ref:`sourceinstall`

**It is highly recommended to install Gmsh and make it available in the system path as BEM++ uses it for visualization and the shapes module.**

.. _virtualbox:

Using a VirtualBox image of BEM++ (Windows, Linux, MacOS) 
---------------------------------------------------------

We provide a VirtualBox image with a preconfigured IPython Notebook
server that runs BEM++ and `FEniCS <www.fenicsproject.org>`_. To use this image please do the following.

* Download a recent version of `Oracle VirtualBox <https://www.virtualbox.org>`_ and install it. VirtualBox is a free and capable virtualization environment.
* Download the `BEM++ VirtualBox image <http://www.bempp.org/files/Ubuntu_BEMPP_3.0.0.ova>`_
* Start VirtualBox and import the image using ``File -> Import Appliance``.
* After importing the image you will see a new entry for BEMPP in the list of virtual machines. Click on it and then click on the Settings icon.
* In the settings under ``System`` adapt the available memory and number of processes that the virtual machine should use. Default is 4 Cores and 4GB RAM. This depends on your system and should not exceed your existing hardware.
* Then under ``Shared Folders`` add a new shared folder that will hold the IPython Notebooks. Under ``Folder Path`` choose the directory on your host system that you want to use. As folder name you must use the name ``export``. The virtual machine image depends on it. Then click the box next to ``Make Permanent`` to store the settings. Click ``OK`` and you are done.
* Start the virtual machine on the main screen using the ``Show`` button. By holding ``Shift`` while clicking it the image will be started without an extra window appearing.
* Once the machine is fully booted use the address http://localhost:8888 in your webbrowser to access the IPython notebook server in the virtual image. You can load and save notebooks in the export folder specified earlier. The IPython environment provides Numpy, Scipy, Matplotlib, FEniCS and BEM++. Gmsh is also installed to access certain functions of the ``shapes`` module in BEM++.

If you need to login to the image and modify settings the username, password and root password are all ``bempp``. The image itself is based on a Ubuntu 14.04 base system. The image is preconfigured to accept all connections on port 8888 where the IPython Notebook server is running.

.. _linuxbinary:

Installing a binary package on Linux
------------------------------------

We offer binary packages for various Linux distribution. Currently, the following are supported.

* `Ubuntu 14.04 <http://www.bempp.org/files/python-bempp_trusty_3.0.0_amd64.deb>`_
* `Ubuntu 15.04 <http://www.bempp.org/files/python-bempp_vivid_3.0.0_amd64.deb>`_
* `Ubuntu 15.10 <http://www.bempp.org/files/python-bempp_wily_3.0.0_amd64.deb>`_

To work properly at least the packages ``libtbb2`` and ``python-scipy`` also need to be installed. To install the packages from the command line in Ubuntu just use the commands::

    sudo dpkg -i <file>
    sudo apt-get -f install

Here, ``<file>`` is the name of the downloaded file. The second command installs any missing dependencies.

.. _installhomebrew:

Installation on MacOS using Homebrew
------------------------------------

On MacOS the most simple way of installing BEM++
is to use `Homebrew <http://brew.sh>`_. Before the installation
make sure that you have a recent XCode version installed
together with the corresponding command line development tools.
If you are unsure open a terminal and type ``gcc --version``.
It should show ``Apple LLVM version 7.0.0`` or higher. Older
versions may work but are untested.

The following instructions assume a fresh Homebrew installation.
If Homebrew is already installed on the system please ensure that
all packages are up to date by running::

    brew update
    brew upgrade

To install Homebrew follow the instructions at the `Homebrew <http://brew.sh>`_ homepage. Installation is simple and just takes a minute.

We use by default the Python environment provided by Homebrew. After Homebrew is installed use::

    brew install python

to install a Python 2.7 environment. Now install the Python dependencies by::

    pip install --upgrade numpy
    pip install --upgrade scipy
    pip install --upgrade cython

The option ``--upgrade`` ensures that recent versions of these packages are installed even if older packages are already present in an existing Homebrew environment (Python packages cannot be updated by the ``brew upgrade`` command).

We need to activate the BEM++ repository by::

    brew tap bempp/homebrew-bempp

To install BEM++ now simply use the command::

    brew install bempp

Installation can take a few minutes since several dependencies need to be installed first.

It is highly recommended to install Gmsh. The BEM++ shapes module and visualization depends on Gmsh. Gmsh can be installed using Homebrew by::

    brew tap homebrew/science
    brew install gmsh --with-fltk 

This can take a long time as several dependencies need to be installed first. Another option is to install Gmsh directly from the `Gmsh Homepage <http://geuz.org/gmsh/>`_ into the ``/Applications`` folder and then to link the Gmsh binary by::

    cd /usr/local/bin
    ln -s /Applications/Gmsh.app/Contents/MacOS/gmsh gmsh

Testing the installation
^^^^^^^^^^^^^^^^^^^^^^^^

To test BEM++ you should use pytest. The built-in test runner in BEM++ currently has problems with Homebrew. To perform the unit tests first install pytest with::

    pip install --upgrade pytest

Then run::

    py.test /usr/local/lib/python2.7/site-packages/bempp

This runs a range of unit tests. Note that if Gmsh is not installed then several unit tests may not work properly.


.. _sourceinstall:

Building BEM++ from scratch
---------------------------

Dependencies
^^^^^^^^^^^^

To build and install BEM++ you will need to have the following installed:

*   Python 2.7 or Python 3.4/3.5

*   `Git version control system <http://git-scm.com/>`_.

*   `CMake <http://www.cmake.org/>`_.

*   Cython v0.22 or higher

*   Scipy v0.14.0 or higher

*   Numpy 1.7 or higher

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







