/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:22:53 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 19:53:23 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_entities.h>
#include <cube_sprites.h>

void	sprite_sort(int *order, double *dist, int amount)
{
	int		temp_order;
	double	temp_dist;
	int		i;
	int		j;

	i = -1;
	while (++i < amount - 1)
	{
		j = -1;
		while (++j < amount - 1)
		{
			if (dist[j] < dist[j + 1])
			{
				temp_dist = dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = temp_dist;
				temp_order = order[j];
				order[j] = order[j + 1];
				order[j + 1] = temp_order;
			}
		}
	}
}
