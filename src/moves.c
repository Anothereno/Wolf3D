/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:27:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/06 18:50:37 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	check_event(t_union *my_union, t_map *map, const Uint8	*key)
{
	if (key[SDL_SCANCODE_ESCAPE])
	{
		exit(0);
	}
	if (key[SDL_SCANCODE_LEFT] && map->player_pos_x - 2 >= 0)
	{
		map->player_pos_x -= 2;
	}
	if (key[SDL_SCANCODE_RIGHT] && map->player_pos_x + 2 < my_union->win_x + 1 - map->player_heigth)
	{
		map->player_pos_x += 2;
	}
	if (key[SDL_SCANCODE_UP] && map->player_pos_y - 2 >= 0)
	{
		map->player_pos_y -= 2;
	}
	if (key[SDL_SCANCODE_DOWN] && map->player_pos_y + 2 < my_union->win_y + 1 - map->player_width)
	{
		map->player_pos_y += 2;
	}
}