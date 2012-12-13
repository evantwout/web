.. highlight:: none
.. _mathematics_background:

A brief introduction to the mathematics of Galerkin boundary element methods
===================================================

In this section we will give a brief informal and not fully rigorous overview of some of the concepts of boundary integral equations.
For a complete presentation of the theory of boundary integral equation see e.g. [Steinbach]_.


Boundary Integral Operators and the Calderon Projector
----------------------------------------------

Let :math:`\Omega\subset\mathbb{R}^3` be a bounded Lipschitz domain. We want to solve the elliptic PDE

.. math::

    Lu(x) = 0,~x\in\Omega,

where :math:`L` is an elliptic partial differential operator. Examples are the Laplace equation :math:`L=-\Delta` or the Helmholtz equation :math:`L=-\Delta u-k^2`.

We denote by :math:`v:=\gamma_0^{int}u` the trace (i.e. the boundary values) of the solution :math:`u` on :math:`\Gamma`, and by :math:`t:=\gamma_1^{int}u` the conormal derivative of :math:`u`. For the Laplace and the Helmholtz equation the conormal derivative is identical to the normal derivative :math:`\frac{\partial u}{\partial n}`. By convention we assume that the normal direction :math:`n` points towards the exterior of :math:`\Omega`.

For the following we need to define the single-layer potential operator :math:`\mathcal{V}` and the double-layer potential operator :math:`\mathcal{K}` by

.. math::

  [\mathcal{V}\psi](x) = \int_\Gamma g(x,y) \psi(y)ds(y),\quad [\mathcal{K}\phi](x)=\int_\Gamma \gamma_{1,y}g(x,y)\phi(y)ds(y),~x\in\Omega.

The function :math:`g(x,y)` is the Green's function. For the Laplace equation it is defined as 

.. math::

  g(x,y)=\frac{1}{4\pi|x-y|} 

and for the Helmholtz equation as 

.. math::

  g(x,y)=\frac{1}{4\pi}\frac{e^{ik|x-y|}}{|x-y|}.


With the help of Green's representation theorem we can now represent the solution :math:`u` in terms of :math:`v` and :math:`t` as

.. math:: u = \mathcal{V}t-\mathcal{K}u.
       :label: green

By applying the trace and the conormal derivative operator to :eq:`green` we obtain the following two equations:

.. math:: v  =  \gamma_0^{int}\left[\mathcal{V}t\right]-\gamma_0^{int}\left[\mathcal{K}u\right], 
     :label: calderon11
.. math:: t  =  \gamma_1^{int}\left[\mathcal{V}t\right]-\gamma_1^{int}\left[\mathcal{K}u\right]. 
     :label: calderon12

We can write this in matrix form as

.. math:: \begin{bmatrix}
      v \\ t
   \end{bmatrix}
   =
   \begin{bmatrix}
   -\gamma_0^{int}\mathcal{K} & \gamma_0^{int}\mathcal{V}    \\
   -\gamma_1^{int}\mathcal{K} & \gamma_1^{int}\mathcal{V}
   \end{bmatrix}   
   = \begin{bmatrix} v \\ t\end{bmatrix} 
  :label: calderon1

This representation is known as Calderon projection. It connects the Dirichlet data :math:`v` and the Neumann data :math:`t` with each other, and can be used to derive various integral equation formulations. However, before we proceed to specific formulations we need to evaluate the representations for the traces and conormal derivatives of :math:`\mathcal{V}` and :math:`\mathcal{K}`.

We define the following boundary potential operators

* The single-layer boundary potential operator
   .. math::
             [V\psi](x) = \int_\Gamma g(x,y)\psi(y)ds(y),~x\in\Gamma.
* The double-layer boundary potential operator
   .. math::
            [K\phi](x) = \int_\Gamma \gamma_{1,y}^{int} g(x,y)\phi(y)ds(y),~x\in\Gamma.
* The adjoint-double-layer boundary potential operator
   .. math::
            [T\psi](x) = \int_\Gamma \gamma_{1,x}^{int} g(x,y)\psi(y)ds(y),~x\in\Gamma.
* The hypersingular boundary potential operator
   .. math::
           [D\phi](x) = -\gamma_{1,x}^{int}\int_\Gamma \gamma_{1,y}^{int} g(x,y)\phi(y)ds(y),~x\in\Gamma.

With the help of these operators we can express the traces and conormal derivatives of :math:`\mathcal{V}` and :math:`\mathcal{K}` as

.. math:: 
   \begin{eqnarray}
     [\gamma_0^{int}\mathcal{V}\psi](x) &=& [V\psi](x)\nonumber\\
     [\gamma_1^{int}\mathcal{V}\psi](x) &=& \frac{1}{2}\psi(x)+[T\psi](x)\nonumber\\
     [\gamma_0^{int}\mathcal{K}\phi](x) &=& -\frac{1}{2}\phi(x)+[K\phi](x)\nonumber\\
    [\gamma_1^{int}\mathcal{K}\phi](x) &=& -[D\phi](x)\nonumber
   \end{eqnarray}

Note that the term :math:`\frac{1}{2}I` comes from the jump relationship of the double-layer potential and the conormal derivative of the single-layer potential operators. In a strict sense the factor :math:`\frac{1}{2}` holds only almost everywhere on the boundary (e.g. on corners and edges it differs).

Returning to the definition of the Calderon projector in :eq:`calderon1` we obtain

.. math:: \begin{bmatrix}
      v \\ t
     \end{bmatrix}
     =
     \begin{bmatrix}
     \frac{1}{2}I-K & V   \\
     D & \frac{1}{2}I+T 
     \end{bmatrix}   
     = \begin{bmatrix} v \\ t\end{bmatrix}.
  :label: calderon2

If we want to solve an exterior problem, that is instead of :math:`\Omega` we consider the complement :math:`\Omega^{c}:=\mathbb{R}^3\backslash\overline{\Omega}` then the Calderon projection takes the following form

.. math:: \begin{bmatrix}
      v^{ext} \\ t^{ext}
     \end{bmatrix}
     =
     \begin{bmatrix}
     \frac{1}{2}I+K & -V   \\
     -D & \frac{1}{2}I-T 
     \end{bmatrix}   
     = \begin{bmatrix} v^{ext} \\ t^{ext}\end{bmatrix},
  :label: calderon2
where we now have to consider :math:`v^{ext}` and :math:`t^{ext}` as Dirichlet and Neumann data taken with respect to the exterior problem. However, the convention is that the normal directions still point to the exterior of :math:`\Omega`, that is into :math:`\Omega^c`.


We close this section with a brief review of mapping properties of these operators. This will be important for the choice of discretization bases in Galerkin boundary element methods.

We denote by :math:`H^s(\Gamma)` the Sobolev space of order :math:`s` on :math:`\Gamma`. Then the above defined operators satisfy the following mapping properties.

.. math::
    \begin{align}
       V&:H^{-1/2}(\Gamma) \rightarrow H^{1/2}(\Gamma)\\
       K&:H^{1/2}(\Gamma) \rightarrow H^{1/2}(\Gamma)\\
       T&:H^{-1/2}(\Gamma)\rightarrow H^{-1/2}(\Gamma)\\
       D&:H^{1/2}(\Gamma)\rightarrow H^{-1/2}(\Gamma)
   \end{align}

As an intuitive explanation of these spaces consider that the space :math:`H^{0}(\Gamma)` is identical to the space :math:`L^2(\Gamma)` of square integrable functions defined on :math:`\Gamma`. The space :math:`H^{1/2}(\Gamma)` is the correct space to represent the Dirichlet traces :math:`v` of the solution :math:`u` to the elliptic PDE :math:`Lu=0` in :math:`\Omega`, and the space :math:`H^{-1/2}(\Gamma)` is the natural space to represent the conormal derivatives :math:`t`. It follows that the Calderon projection acts on pairs of functions in the product space :math:`H^{1/2}(\Gamma)\times H^{-1/2}(\Gamma)`.

Boundary element spaces
----------------------

To discretise the Sobolev spaces :math:`H^{-\frac12}(\Gamma)` and :math:`H^{\frac12}(\Gamma)` we introduce the triangulation :math:`\mathcal{T}_h` of :math:`\Gamma` with triangular surface elements :math:`\tau_\ell` and associated nodes :math:`x_i` such that
:math:`\overline{\mathcal{T}_h}=\bigcup_\ell\overline{\tau_\ell}`. Here, :math:`h` denotes the mesh size. We define two spaces of functions.

* The space  of  *piecewise constant functions* :math:`S_h^0(\Gamma):=\text{span}\{\psi_k^{(0)}\}` with :math:`\psi_k^{(0)}(x)=1` for :math:`x\in \tau_k`.
* The space of *continuous piecewise linear functions* :math:`S_h^1(\Gamma):=\text{span}\{\phi_j^{(1)}\}` with :math:`\phi_j^{(1)}(x_i)=\left\{\begin{array}{cc} 1 & i=j\\ 0 & i\neq j\end{array}\right.`.

We will use the space :math:`S_h^{0}` to approximate functions in :math:`H^{-1/2}(\Gamma)` and the space :math:`S_h^{1}` to approximate functions in :math:`H^{1/2}(\Gamma)`.

Galerkin approximations
----------------------

As example we consider the interior Dirichlet problems, that is the Dirichlet data :math:`v` is given and we want to approximate the Neumann data :math:`t`. The first line of the Calderon projection :eq:`calderon2` leads to the formulation

.. math:: Vt = \left(\frac{1}{2}I+K\right)v.
    :label: dirichlet

.. math:: \langle f, g \rangle = \int_\Gamma \overline{f}(x)g(x)ds(x).
     :label: iproduct

The definition :eq:`iproduct` is only well defined if :math:`f` is in the dual space of :math:`g`. We will not go into details of dual spaces here, but only remark that the dual space of :math:`L^2(\Gamma)` is again :math:`L^2(\Gamma)`, the dual space of :math:`H^{1/2}(\Gamma)` is :math:`H^{-1/2}(\Gamma)` and the dual space of :math:`H^{-1/2}(\Gamma)` is :math:`H^{1/2}(\Gamma)`.

Both sides of :eq:`dirichlet` map into :math:`H^{1/2}(\Gamma)`. We therefore take on both sides of :eq:`dirichlet` inner products with functions :math:`\psi\in H^{-1/2}(\Gamma)` to obtain the following variational formulation:

Find :math:`t\in H^{-1/2}(\Gamma)` such that

.. math:: \langle \psi,Vt \rangle = \langle \psi ,\left(\frac{1}{2}I+K\right)v\rangle
     :label: vardirichlet

for all :math:`\psi\in H^{-1/2}(\Gamma)`.

The Galerkin discretization is now obtained by restricting the space :math:`H^{1/2}(\Gamma)` to :math:`S_h^{1}(\Gamma)` and the space :math:`H^{-1/2}(\Gamma)` to :math:`S_h^{0}(\Gamma)` in the above variational formulation. We obtain the following matrix problem

.. math:: \mathsf{V}\mathbf{t} = \left(\mathsf{\frac{1}{2}M+K}\right)\mathbf{v},

where the matrices are defined by

.. math::
    \begin{align*}
       \mathsf{V}_{i,j} &= \int_\Gamma\psi_i^{(0)}(x)\int_\Gamma g(x,y)\,\phi_j^{(0)}(y)ds(y)ds(x),\\
       \mathsf{M}_{i,j} &= \int_\Gamma\psi_i^{(0)}(x)\,\phi_j^{(1)}(x)ds(x),\\
      \mathsf{K}_{i,j} &= \int_\Gamma\psi_i^{(0)}(x)\int_\Gamma g(x,y)\,\phi_j^{(1)}(y)ds(y)ds(x).
    \end{align*}





References
-----------

.. [Steinbach] O. Steinbach, Numerical Approximation Methods for Elliptic Boundary Value Problems, Springer, New York, 2008
