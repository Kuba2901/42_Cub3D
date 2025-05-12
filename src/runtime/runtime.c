/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:03:31 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/12 12:07:17 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_runtime.h>

t_runtime_handler	*runtime_runtime_handler_init( void )
{
	t_runtime_handler	*runtime_handler;

	runtime_handler = malloc(sizeof(t_runtime_handler));
	if (!runtime_handler)
		return (NULL);
	runtime_handler->frames_per_second = 0;
	runtime_handler->frametime = 0;
	runtime_handler->time = 0;
	runtime_handler->old_time = 0;
	runtime_handler->running = CUBE_TRUE;
	runtime_handler->display_credits = CUBE_FALSE;
	runtime_handler->displaying_credits = CUBE_FALSE;
	runtime_handler->displaying_intro = CUBE_TRUE;
	return (runtime_handler);
}

void	runtime_runtime_handler_free(t_runtime_handler *runtime_handler)
{
	if (!runtime_handler)
		return ;
	free(runtime_handler);
	runtime_handler = NULL;
}
