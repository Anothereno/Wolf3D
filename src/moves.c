/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:27:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/07 13:52:58 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	check_event(t_union *my_union, t_map *map, t_player *player, const Uint8	*key)
{
	if (key[SDL_SCANCODE_ESCAPE])
	{
		exit(0);
	}
	if (key[SDL_SCANCODE_LEFT] && player->player_pos_x - 4 >= 0)
	{
		player->player_pos_x -= 4;
	}
	if (key[SDL_SCANCODE_RIGHT] && player->player_pos_x + 4 < my_union->win_x + 1 - player->player_heigth)
	{
		player->player_pos_x += 4;
	}
	if (key[SDL_SCANCODE_UP] && player->player_pos_y - 4 >= 0)
	{
		player->player_pos_y -= 4;
	}
	if (key[SDL_SCANCODE_DOWN] && player->player_pos_y + 4 < my_union->win_y + 1 - player->player_width)
	{
		player->player_pos_y += 4;
	}
}