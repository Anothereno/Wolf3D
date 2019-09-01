/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:55:55 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/01 18:40:14 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_forward(t_player *player, t_map *map, float mode)
{
	float	pos_x;
	float	pos_y;

	player->move_indicate = 5;
	pos_x = (player->player_pos_x + (player->speed * mode *
			cosf(player->view_direction_rad)));
	pos_y = (player->player_pos_y + (player->speed * mode *
			sinf(player->view_direction_rad)));
	if (!check_wall(pos_x, pos_y, *map))
	{
		player->player_pos_x = pos_x;
		player->player_pos_y = pos_y;
	}
}

void	strafe(t_player *player, t_map *map, float mode)
{
	float	angle;
	float	pos_x;
	float	pos_y;

	player->move_indicate = 5;
	angle = (player->view_direction + (90 * mode)) * RAD;
	pos_x = (player->player_pos_x + (player->strafe_speed * cosf(angle)));
	pos_y = (player->player_pos_y + (player->strafe_speed * sinf(angle)));
	if (!check_wall(pos_x, pos_y, *map))
	{
		player->player_pos_x = pos_x;
		player->player_pos_y = pos_y;
	}
}
