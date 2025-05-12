/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_runtime.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:24:31 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/12 12:10:09 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_RUNTIME_H
# define CUBE_RUNTIME_H

# include <stdlib.h>
# include <utils.h>

typedef struct s_runtime_handler
{
	size_t	time;
	size_t	old_time;
	t_bool	running;
	double	frametime;
	double	frames_per_second;
	t_bool	display_credits;
	t_bool	displaying_credits;

	t_bool	displaying_intro;
}	t_runtime_handler;

t_runtime_handler	*runtime_runtime_handler_init( void );
void				runtime_runtime_handler_free(
						t_runtime_handler *runtime_handler);

#endif