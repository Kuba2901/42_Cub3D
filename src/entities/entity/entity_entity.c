/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:58:18 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 16:16:43 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cube_entities.h>
#include <cube_settings.h>
#include <cube_mlx_handler.h>
#include <cube_animations.h>
#include <libft.h>

t_entity	*entities_entity_init(t_point pt, t_entity_type type,
	t_animated_frames *frames_ptr)
{
	t_entity	*entity;
	t_location	location;

	entity = malloc(sizeof(t_entity));
	if (!entity)
		return (NULL);
	if (type == ENTITY_TYPE_PLAYER)
		entity->controller = NULL;
	else
	{
		entity->controller = anim_animation_controller_init();
		anim_animation_controller_set_animation(
			entity->controller, ANIM_TYPE_IDLE, frames_ptr);
		entity->controller->playing = CUBE_FALSE;
		entity->controller->repeat = CUBE_FALSE;
		entity->controller->current = entity->controller->idle;
	}
	entity->hp = 100;
	location.x = pt.x + ENTITY_CENTRAL_OFFSET;
	location.y = pt.y + ENTITY_CENTRAL_OFFSET;
	entity->current_location = location;
	return (entity);
}

void	entities_entity_free(t_entity *entity)
{
	if (!entity)
		return ;
	anim_animation_controller_free(entity->controller);
	safe_free(entity);
}
