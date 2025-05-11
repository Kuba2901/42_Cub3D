/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:24:48 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:24:48 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef enum s_bool
{
	CUBE_FALSE,
	CUBE_TRUE
}	t_bool;

void	safe_free(void *param);

#endif
