/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:58:18 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 16:17:01 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cube_entities.h>
#include <cube_settings.h>
#include <cube_mlx_handler.h>
#include <cube_animations.h>
#include <libft.h>

t_exit	*entities_exit_init(t_point pt, t_animated_frames *idle_frames_ptr,
	t_animated_frames *open_frames_ptr)
{
	t_exit	*ret;

	ret = malloc(sizeof(t_exit));
	if (!ret)
		return (NULL);
	ret->base = entities_entity_init(pt, ENTITY_TYPE_EXIT, idle_frames_ptr);
	if (!ret->base)
	{
		safe_free(ret);
		return (NULL);
	}
	anim_animation_controller_set_animation(
		ret->base->controller, ANIM_TYPE_OPEN, open_frames_ptr);
	ret->unlocked = CUBE_FALSE;
	return (ret);
}

void	entities_exit_free(t_exit *exit_entity)
{
	if (!exit_entity)
		return ;
	entities_entity_free(exit_entity->base);
	safe_free(exit_entity);
}
