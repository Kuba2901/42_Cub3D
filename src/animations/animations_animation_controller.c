/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_animation_controller.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:48:59 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 16:16:36 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_animations.h>
#include <cube_settings_animated_sprites.h>
#include <utils.h>

t_animation_controller	*anim_animation_controller_init( void )
{
	t_animation_controller	*animation_controller;

	animation_controller = malloc(sizeof(t_animation_controller));
	if (!animation_controller)
		return (NULL);
	animation_controller->attack = NULL;
	animation_controller->die = NULL;
	animation_controller->idle = NULL;
	animation_controller->open = NULL;
	animation_controller->reload = NULL;
	animation_controller->take_damage = NULL;
	animation_controller->current = NULL;
	animation_controller->playing = CUBE_FALSE;
	animation_controller->repeat = CUBE_FALSE;
	animation_controller->reverse = CUBE_FALSE;
	return (animation_controller);
}

void	anim_animation_controller_free(
	t_animation_controller *animation_controller)
{
	if (!animation_controller)
		return ;
	if (animation_controller->attack)
		anim_animation_free(animation_controller->attack);
	if (animation_controller->die)
		anim_animation_free(animation_controller->die);
	if (animation_controller->idle)
		anim_animation_free(animation_controller->idle);
	if (animation_controller->open)
		anim_animation_free(animation_controller->open);
	if (animation_controller->reload)
		anim_animation_free(animation_controller->reload);
	if (animation_controller->take_damage)
		anim_animation_free(animation_controller->take_damage);
	safe_free(animation_controller);
	animation_controller = NULL;
}

void	anim_animation_controller_set_animation(
	t_animation_controller *animation_controller,
	t_animation_type type, t_animated_frames *frames_ptr)
{
	if (!animation_controller || !frames_ptr)
		return ;
	if (type == ANIM_TYPE_ATTACK)
		animation_controller->attack = anim_animation_init(type, frames_ptr);
	else if (type == ANIM_TYPE_DIE)
		animation_controller->die = anim_animation_init(type, frames_ptr);
	else if (type == ANIM_TYPE_IDLE)
		animation_controller->idle = anim_animation_init(type, frames_ptr);
	else if (type == ANIM_TYPE_OPEN)
		animation_controller->open = anim_animation_init(type, frames_ptr);
	else if (type == ANIM_TYPE_RELOAD)
		animation_controller->reload = anim_animation_init(type, frames_ptr);
	else if (type == ANIM_TYPE_TAKE_DAMAGE)
		animation_controller->take_damage
			= anim_animation_init(type, frames_ptr);
}

void	anim_animation_controller_player_start(
	t_animation_controller *controller,
	t_animation_type type,
	t_bool reverse
)
{
	if (!controller)
		return ;
	if (type == ANIM_TYPE_ATTACK)
		controller->current = controller->attack;
	else if (type == ANIM_TYPE_DIE)
		controller->current = controller->die;
	else if (type == ANIM_TYPE_IDLE)
		controller->current = controller->idle;
	else if (type == ANIM_TYPE_OPEN)
		controller->current = controller->open;
	else if (type == ANIM_TYPE_RELOAD)
		controller->current = controller->reload;
	else if (type == ANIM_TYPE_TAKE_DAMAGE)
		controller->current = controller->take_damage;
	if (!controller->current)
		return ;
	controller->playing = CUBE_TRUE;
	controller->reverse = reverse;
}

void	anim_animation_controller_player_stop(
	t_animation_controller *controller
)
{
	if (!controller)
		return ;
	controller->playing = CUBE_FALSE;
	controller->current = controller->idle;
}
