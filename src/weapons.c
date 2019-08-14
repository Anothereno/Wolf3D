/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_surfaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 15:26:12 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/14 16:55:38 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_weapon(t_union *my_union, t_player *player, t_map *map)
{
	my_union->weapon_texture = SDL_CreateTextureFromSurface(my_union->renderer,
			my_union->weapons_surfaces[player->weapon][player->weapon_frame]);
	SDL_RenderCopy(my_union->renderer, my_union->weapon_texture, NULL, &my_union->weapon_place);
	SDL_DestroyTexture(my_union->weapon_texture);
	if (player->shoot_mode && my_union->start_tick - my_union->shoot_timer >= 35)
	{
		player->weapon_frame++;
	}
	if ((!player->weapon && player->weapon_frame == 4) ||
			(player->weapon && player->weapon_frame == 9))
	{
		player->weapon_frame = 0;
		player->shoot_mode = 0;
	}
}

void	reload(t_union *my_union, t_player *player)
{
	if (player->ammo[player->weapon] >= player->clip_volume[player->weapon] &&
			player->clip[player->weapon] < player->clip_volume[player->weapon])
	{
		player->clip[player->weapon] = player->clip_volume[player->weapon];
		player->ammo[player->weapon] -= player->clip_volume[player->weapon];
	}
	else if (player->ammo[player->weapon] < player->clip_volume[player->weapon] &&
				player->clip[player->weapon] < player->ammo[player->weapon])
	{
			player->clip[player->weapon] = player->ammo[player->weapon];
			player->ammo[player->weapon] -= player->clip_volume[player->weapon];
	}
	if (player->ammo[player->weapon] < 0)
		player->ammo[player->weapon] = 0;
}

void	weapon_down(t_union *my_union, t_player *player)
{

}