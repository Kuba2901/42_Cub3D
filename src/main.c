#include <X11/X.h>
#include <cube.h>
#include <stdlib.h>
#include <cube_runtime.h>
#include <stdio.h>
#include <cube_mock.h>
#include <cube_settings_textures.h>
#include <cube_mlx_handler.h>
#include <cube_lifecycle.h>
#include <cube_input_handler.h>
#include <cube_drawing.h>
#include <mlx.h>

int	main(int argc, char **argv)
{
	t_cube	*cube;

	cube = cube_cube_init(argc, argv);
	// mlx_mouse_hide(cube->mlx_handler->mlx, cube->mlx_handler->mlx_win);
	mlx_hook(cube->mlx_handler->mlx_win, 2, 1L << 0, input_handler_key_press, cube);
	mlx_hook(cube->mlx_handler->mlx_win, 3, 1L << 1, input_handler_key_release, cube);
	mlx_hook(cube->mlx_handler->mlx_win, DestroyNotify,
		StructureNotifyMask, &lifecycle_on_destroy, cube);
	mlx_hook(cube->mlx_handler->mlx_win, 6, 1L << 6, input_handler_mouse_movement, cube);
	mlx_loop_hook(cube->mlx_handler->mlx, lifecycle_game_loop, cube);
	mlx_loop(cube->mlx_handler->mlx);
	cube_cube_free(cube);
	return (EXIT_SUCCESS);
}
