/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   credits_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:17 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 18:29:06 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>
#include <cube_mlx_handler.h>
#include <cube_drawing.h>
#include <mlx.h>
#include <libft.h>
#include <fcntl.h>

static int	credits_count_lines(void)
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

char	**credits_lines_load(void)
{
	char	**ret;
	char	*line;
	int		fd;
	int		i;

	ret = malloc(sizeof(char *) * (credits_count_lines() + 1));
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
		ret[i] = line;
		i++;
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
