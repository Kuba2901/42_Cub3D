/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:46:01 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/09 20:48:49 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_animations.h>
#include <cube_settings_animated_sprites.h>
#include <utils.h>

t_animation	*anim_animation_init(t_animation_type type,
	t_animated_frames *frames_ptr)
{
	t_animation	*animation;

	animation = malloc(sizeof(t_animation));
	if (!animation)
		return (NULL);
	animation->frame = 0;
	animation->type = type;
	animation->frames_ptr = frames_ptr;
	return (animation);
}

void	anim_animation_free(t_animation *animation)
{
	safe_free(animation);
	animation = NULL;
}
