.. highlight:: none
.. _interior_laplace_neumann:

Interior Neumann Problem for the Laplace Equation
===================================================

Mathematical background
-----------------------

We want to solve the interior Neumann problem

.. math::

   \begin{align}
    -\Delta u &= 0~\text{in}~\Omega,\\
    \frac{\partial u}{\partial n} &= g~\text{on}~\Gamma,
  \end{align}

where :math:`\frac{\partial}{\partial n}` is the normal derivative with normal pointing towards the exterior of the domain :math:`\Omega\subset\mathbb{R}^3`. :math:`\Gamma` denotes the boundary of :math:`\Omega`. For an interior Neumann problem we need an additional solvability condition, which is given by

.. math::

   \int_\Gamma g(x)ds(x) = 0.

Denote by :math:`\Gamma`



