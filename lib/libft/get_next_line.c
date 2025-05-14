/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:12:37 by gromiti           #+#    #+#             */
/*   Updated: 2024/04/21 19:01:51 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_buffs(char *st_buff, char *buffer)
{
	char	*joined;

	joined = ft_strjoin(st_buff, buffer);
	free(st_buff);
	return (joined);
}

char	*ft_read(int fd, char *st_buff, int bytes_read)
{
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		st_buff = ft_join_buffs(st_buff, buffer);
		if (ft_check_newline(st_buff) != -1)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		free(buffer);
		return (NULL);
	}
	if (bytes_read == 0 && *st_buff == 0)
	{
		free(st_buff);
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (st_buff);
}

char	*ft_get_line(char	*buff)
{
	char	*line;
	size_t	i;
	size_t	line_len;

	i = 0;
	if (ft_check_newline(buff) != -1)
		line_len = ft_index_newline(buff);
	else
		line_len = ft_strlen(buff);
	if (!buff)
		return (NULL);
	line = ft_calloc(line_len + 2, sizeof(char));
	if (!line)
		return (NULL);
	while (i < line_len)
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\0')
		line[i] = '\0';
	else
		line[i] = '\n';
	return (line);
}

char	*ft_update_buff(char *buff)
{
	char	*updated;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buff[i] != '\0' && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	i++;
	updated = ft_calloc(ft_strlen(buff) - i + 1, sizeof(char));
	while (buff[i] != '\0')
	{
		updated[j] = buff[i];
		i++;
		j++;
	}
	free(buff);
	return (updated);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*ret;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buff)
		buff = ft_calloc(1, 1);
	bytes_read = 0;
	buff = ft_read(fd, buff, bytes_read);
	if (!buff)
		return (NULL);
	ret = ft_get_line(buff);
	buff = ft_update_buff(buff);
	return (ret);
}
