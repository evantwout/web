
.. note:: This website uses cookies for certain functionalities and to collect usage data. Please see the `Privacy <privacy.html>`_ page for more information.


Welcome to BEM++
================

BEM++ is an open-source Galerkin boundary element library that
handles Laplace, Helmholtz and Maxwell problems on bounded and unbounded
domains.

Current Version
---------------
Version: 3.0.0 

Getting Help
------------
* To download and install BEM++ check out the `Installation <installation.html>`_ page.
* For example use of BEM++ see the `Tutorials <tutorials.html>`_.
* To receive announcements and for general support sign up to the `BEM++ mailing list <https://groups.google.com/forum/#!forum/bempp>`_.
* For project updates follow us on `Twitter <https://twitter.com/BemppProject>`_.
* Submit bug reports at https://github.com/bempp/bempp/issues.

Quick Start
-----------

* Download the `BEM++ VirtualBox image <http://www.bempp.org/files/Ubuntu_BEMPP_3.0.0.ova>`_
* In VirtualBox configure a shared folder named ``export``.
* Adapt the settings for number of processors and memory to your hardware.
* Start the image.
* Open an IPython notebook session on http://localhost:8888 to load or write new IPython notebooks for BEM++.

For more detailed information, binary installers for Linux, Homebrew installers for Mac or source code compilation of BEM++ see the `Installation <installation.html>`_ page.

Citing BEM++
------------
If you use BEM++ in your research please include the following citation in your publications:

* W. Śmigaj, S. Arridge, T. Betcke, J. Phillips, M. Schweiger, "Solving Boundary 
  Integral Problems with BEM++", *ACM Trans. Math. Software 41*, pp. 6:1--6:40 (2015)  

Licensing
---------
The library source code is covered by the MIT license. The full licensing text is:

Copyright (C) 2015 by the BEM++ Authors

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

**Please note that depending on the chosen linking options with 3rd party librarys 
the compiled BEM++ library may have a more restrictive license.**

Development
-----------
BEM++ is developed at `University College London <http://www.ucl.ac.uk>`_. The
current development team includes Simon Arridge, Timo Betcke,
Matthew Scroggs and Elwin Van 't Wout. Much of the original work on BEM++ was done by Wojciech Śmigaj, now at Simpleware Ltd. BEM++ is supported by `EPSRC <http://www.epsrc.ac.uk>`_ Grants EP/I030042/1 and EP/K03829X/1. The testing and installation infrastructure for BEM++ was developed by the UCL Research Software Development Team.

.. toctree::
    :hidden:
    :maxdepth: 2

    self
    features
    installation
    docs
    tutorials
    publications
    privacy
