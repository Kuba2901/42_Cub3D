#include <cube.h>
#include <cube_mlx_handler.h>
#include <cube_drawing.h>
#include <mlx.h>
#include <libft.h>
#include <fcntl.h>

int	credits_put_centered_text(t_cube *cube, int y, int color, char *string)
{
	int     text_width;
	int     x;
	
	text_width = 0;
	if (string)
		text_width = ft_strlen(string) * CREDITS_CHAR_WIDTH;
	x = (WINDOW_WIDTH - text_width) / 2;
	if (x < 0)
		x = 0;
	if (!string)
		return (0);
	string[ft_strlen(string) - 1] = ' ';
	return (mlx_string_put(cube->mlx_handler->mlx, cube->mlx_handler->mlx_win, 
		x, y, color, string));
}

static void	credits_render_black_screen(t_cube *cube)
{
	t_mlx_handler	*mlx_handler;
	int				y;
	int				x;

	mlx_handler = cube->mlx_handler;
	draw_clear_screen(cube);
	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
			draw_my_mlx_pixel_put(mlx_handler->mlx_img, x, y, DRAW_BLACK_COLOR);
	}
	mlx_put_image_to_window(cube->mlx_handler->mlx, cube->mlx_handler->mlx_win, 
						   cube->mlx_handler->mlx_img->img, 0, 0);
}

static int	credits_count_lines()
{
	char	*line;
	int		lines;
	int		fd;

	lines = 0;
	fd = open(CREDITS_PATH, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	return (lines);
}

static char	**credits_lines_load()
{
	char	**ret;
	char	*line;
	int		lines;
	int		fd;
	int		i;

	lines = credits_count_lines();
	ret = malloc(sizeof(char *) * (lines + 1));
	if (!ret)
		return (NULL);
	fd = open(CREDITS_PATH, O_RDONLY);
	if (fd < 0)
	{
		free(ret);
		return (NULL);
	}
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		ret[i++] = line;
		line = get_next_line(fd);
	}
	ret[i] = NULL;
	return (ret);
}

void	credits_lines_free(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = -1;
	while (lines[++i])
		free(lines[i]);
	free(lines);
}

void    credits_display(t_cube *cube)
{
	int     y_pos;
	int     line_height;
	char	**lines;
	int     i;
	int		current_y;

	line_height = 30;
	lines = credits_lines_load();
	y_pos = WINDOW_HEIGHT;
	while (y_pos + (line_height * 2) > 0)
	{
		credits_render_black_screen(cube);
		i = 0;
		current_y = y_pos;
		while (lines[i])
		{
			credits_put_centered_text(cube, current_y, DRAW_WHITE_COLOR, lines[i]);
			current_y += line_height;
			i++;
		}
		y_pos -= 2;
		mlx_do_sync(cube->mlx_handler->mlx);
		usleep(30000);
	}
	credits_lines_free(lines);
}