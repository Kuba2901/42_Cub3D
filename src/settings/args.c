/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:02:31 by gromiti           #+#    #+#             */
/*   Updated: 2025/06/23 17:06:52 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_settings_args.h>

/*
** check_extension - Check if the file has a .cub extension
** @filename: The name of the file to check.
**
** Return: 0 if the extension is valid, 1 if it is not.
**
** This function checks if the last four characters of the filename are ".cub".
** If not, it prints an error message and returns 1. Otherwise, it returns 0.
*/
void	check_extension(char *filename)
{
	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nInvalid file extension. Expected .cub\n", 2);
		exit (EXIT_FAILURE);
	}
}

/*
** check_args - Check the number of arguments and the file extension
** @argc: The number of arguments.
** @argv: The array of arguments.
** @config: The configuration structure to fill.
**
** Return: 0 if the arguments are valid, 1 if they are not.
**
** This function checks if the number of arguments is correct (2) and if the
** file has a valid extension. If not, it prints an error message and returns 1.
** Otherwise, it returns 0.
*/
void	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		exit (EXIT_FAILURE);
	}
	check_extension(argv[1]);
}
