.. highlight:: none
.. _interior_laplace_dirichlet:

An interior Dirichlet problem for the Laplace equation
===================================

In this section we solve a simple interior Laplace problem with Dirichlet boundary conditions. By going through this tutorial the reader will get to know some of
the main concepts of BEM++, namely reading a mesh, initializing function spaces, creating boundary integral operators, solving the resulting system and
exporting the solution data.

Mathematical formulation
-------------------------

For an overview of the mathematical theory of Galerkin boundary element methods we refer to :ref:`mathematics_background`.

We want to solve the problem

.. math::
    \begin{eqnarray}
        -\Delta u & =  & 0~\text{in}~\Omega,\nonumber\\
                   u & = & g~\text{on}~\Gamma.
     \end{eqnarray}

 The corresponding boundary integral formulation is

.. math::
     Vt = \left(\frac{1}{2}I+K\right)g.






