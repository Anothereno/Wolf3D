/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:51:14 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:59:02 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	open_close_door(t_map *objects, t_map *map, int j, int i)
{
	if (objects->map[j][i] == 'D')
	{
		if (map->map[j][i] != 0)
			map->map[j][i] = 0;
		else
			map->map[j][i] = 2;
	}
}

void	check_door(t_map *map, t_map *objects, t_player *player,
					t_union *my_union)
{
	int pos_x;
	int pos_y;
	int i;
	int j;

	if (!my_union->door_timer_end)
	{
		my_union->door_timer_end = SDL_GetTicks();
		pos_x = (int)player->player_pos_x >> 6;
		pos_y = (int)player->player_pos_y >> 6;
		j = pos_y - 2;
		while (++j <= pos_y + 1)
		{
			i = pos_x - 2;
			while (++i <= pos_x + 1)
			{
				if (!check_bound(i, j, *map))
					continue;
				open_close_door(objects, map, j, i);
			}
		}
	}
}
