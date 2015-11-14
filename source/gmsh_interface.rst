Import and Export of Gmsh files
===============================

BEM++ depends on the Gmsh v2.2 ASCII file format for import and export. While this
may be extended in the future in the following we describe some specific features of
interfacing with Gmsh files.

Basic import and export
-----------------------
The most basic operation is to import a Gmsh grid into BEM++. The command for this
operation is::

    grid = bempp.api.import_grid("my_grid.msh")

To export a grid object ``grid`` to Gmsh you can use the following command::

    bempp.api.export(grid=grid, file_name="my_grid.msh")

Similarly, to export a grid function to Gmsh use the command::

    bempp.api.export(grid_function=fun, file_name="my_grid.msh")

The ``export`` function requires that exported data is real. If the data in the grid
function is complex a ``transformation`` parameter can be given to map the grid function
data into real data. For example, to just store the real part of a grid function use::

    import numpy as np
    bempp.api.export(grid_function=fun, file_name="my_grid.msh", transformation=np.real)

The ``transformation`` parameter takes a callable that accepts as input a number and returns
a real number. This function is applied to each data value in the grid function during the export.

Advanced handling of Gmsh node and element keys
-----------------------------------------------
Quite often it is desirable to be able to map BEM++ indices to Gmsh element or node keys. This is
not fully trivial as BEM++ internally stores these objects in a different order than the one given
by a Gmsh file. To obtain this advanced information the ``FileReader`` class is provided. It is
instantiated as follows::

    from bempp.api.file_interfaces import FileReader
    reader = FileReader(file_name="filename.msh")
    grid = reader.grid

Please note that the filename always needs to be given as a positional argument. Assume that we want
to find out the Gmsh file key for the vertex with index 0 in BEM++. We can simply use::

    print(reader.vertex_index_to_file_key_map[0])

On the other hand we can print out the BEM++ index associated with a vertex in a Gmsh file using the
command::

    print(reader.vertex_file_key_to_index_map[vertex_key])

If the vertex associated with ``vertex_key`` has no correspondence in BEM++ a ``KeyError`` exception is
thrown.

To get the corresponding element information just replace ``vertex`` by ``element`` in the above commands.
When exporting a grid function to Gmsh we would often like to preserve the indexing given in the original Gmsh
file. This can be accomplished by passing the corresponding mapping information to the ``export`` function with::

    bempp.api.export(grid_function=grid_fun, file_name="export.msh", 
        vertex_index_to_file_key_map=reader.vertex_index_to_file_keymap,
        element_index_to_file_key_map=reader.element_index_to_file_key_map)

If this mapping information is not given the ``export`` function uses a default 1-1 map based on the BEM++
indices.







