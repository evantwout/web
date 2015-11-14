Solving linear systems
======================

Consider a simple operator equation of the form

.. math::

    A\phi = f
    
Here, :math:`f` and :math:`\phi` are grid functions and :math:`A` is a boundary integral operator.

The weak form of the above equation is given by

.. math::

    \langle Au, v\rangle = <f, v>

for all :math:`v` in the dual space to the range space.

The standard way to solve this system in BEM++ consists of the following steps.

    1. Compute the weak form of :math:`A` using ``discrete_op = A.weak_form()``.
    2. Compute the projection of the right-hand side :math:`f` onto the dual space by ``p = f.projections(dual_to_range)``, where ``dual_to_range`` is the name of the dual space.
    3. Solve using an iterative solver from Scipy (e.g.CG or GMRES), potentially together with a suitable preconditioner, that is ``x, info = gmres(discrete_op, p)``.
    4. Turn the result :math:`x` back into a grid function using the command::
   
            sol_fun = bempp.api.GridFunction(A.domain, coefficients=x).

In order to make these steps shorter BEM++ implements within the ``bempp.api.linalg`` module wrappers that look like the corresponding functions in Scipy but automatically do the unpacking of the operators and wrapping of the solution into a grid function. Hence, we can simply call::

    from bempp.api.linalg.iterative_solvers import gmres
    phi = gmres(A, f)

The functions in the linalg module accept all the usual parameters that are also accepted by the corresponding Scipy routines. 

A frequently used form of preconditioning is via the mass matrix. BEM++ has its own discretization mode that automatically applies the inverse of the mass matrix by computing its LU factorization. In this case we would use::

    from scipy.sparse.linalg import gmres
    discrete_op = A.strong_form()
    coeffs = f.coefficients
    x, info = gmres(A, coeffs)

Please note that instead of the projections on the right-hand side we now need to use the basis coefficients themselves. This typically converges faster than the standard weak form discretization.

If the linear system should be solved by a dense LU decomposition we need a representation of the Galerkin discretization as Numpy array. This is achieved via the command ``numpy_mat = bempp.api.as_matrix(A)``. If H-Matrix discretization was enabled this operation can be very slow. It should only be used for very small problems.

Function and class reference
----------------------------
.. autofunction:: bempp.api.linalg.iterative_solvers.cg
.. autofunction:: bempp.api.linalg.iterative_solvers.gmres
.. autofunction:: bempp.api.linalg.direct_solvers.lu
.. autofunction:: bempp.api.as_matrix
