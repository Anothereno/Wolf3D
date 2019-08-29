/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:55:55 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/29 15:14:06 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_forward(t_player *player, t_map *map, int mode, t_union *my_union)
{
	double center_x;
	double center_y;
	double pos_x;
	double pos_y;

	player->move_indicate = 5;
	center_x = player->player_pos_x;
	center_y = player->player_pos_y;
	pos_x = (center_x + (player->speed * mode *
			cos(player->view_direction_rad)));
	pos_y = (center_y + (player->speed * mode *
			sin(player->view_direction_rad)));
	if (!check_wall(pos_x, pos_y, *map))
	{
		player->player_pos_x = pos_x;
		player->player_pos_y = pos_y;
	}
}

void	strafe(t_player *player, t_map *map, int mode)
{
	double center_x;
	double center_y;
	double angle;
	double pos_x;
	double pos_y;

	player->move_indicate = 5;
	angle = (player->view_direction + (90 * mode)) * RAD;
	center_x = player->player_pos_x;
	center_y = player->player_pos_y;
	pos_x = (center_x + (player->strafe_speed * cos(angle)));
	pos_y = (center_y + (player->strafe_speed * sin(angle)));
	if (!check_wall(pos_x, pos_y, *map))
	{
		player->player_pos_x = pos_x;
		player->player_pos_y = pos_y;
	}
}
