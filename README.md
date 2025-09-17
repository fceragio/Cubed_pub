--How to use--

-Build with make from the root of the repository.
-Execute with "./cubed" "path_of_the_file_with_the_informations_for_the_map_to_render".
ex:
	./cubed cub_files/test_file.cub

In the header file you can change the macro DEBUG_MODE to 0 to render a 2D overview instead of the 3D raycaster style.

The assignment is realized with the very basic MinilibX, so it can only use sprites in an old .xpm format.

Maps are composed from 1s and 0s:
	1s are wall tiles
	0s are floor tiles
	space " " can be used only as a padding tool
	map has to have one and only one spawn tile for the player (N, E, W or S),
		and it has to be impossible for the player to "fall" out of the map
