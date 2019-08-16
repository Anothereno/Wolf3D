/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_surfaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 15:26:12 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/16 18:55:03 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_weapon(t_union *my_union, t_player *player, t_map *map)
{
	if (my_union->weapon_down_mode)
		weapon_down(my_union, player);
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
		weapon_down(my_union, player);
		player->clip[player->weapon] = player->clip_volume[player->weapon];
		player->ammo[player->weapon] -= player->clip_volume[player->weapon];
	}
	else if (player->ammo[player->weapon] < player->clip_volume[player->weapon] &&
				player->clip[player->weapon] < player->ammo[player->weapon])
	{
		weapon_down(my_union, player);
		player->clip[player->weapon] = player->ammo[player->weapon];
		player->ammo[player->weapon] -= player->clip_volume[player->weapon];
	}
	if (player->ammo[player->weapon] < 0)
		player->ammo[player->weapon] = 0;
}

void	weapon_down(t_union *my_union, t_player *player)
{
	if (!my_union->weapon_down_mode)
	{
		my_union->weapon_down_timer = SDL_GetTicks();
		my_union->weapon_down_mode = 1;
	}
	else
	{
		if (my_union->weapon_down_mode == 21)
		{
			my_union->weapon_down_mode = 0;
			my_union->change_weapon_mode = 0;
		}
		else if (my_union->start_tick - my_union->weapon_down_timer >= 12)
		{
			my_union->weapon_down_timer = SDL_GetTicks();
			my_union->weapon_down_mode++;
			if (my_union->weapon_down_mode <= 11)
				my_union->weapon_place.y += 20;
			else
			{
				my_union->weapon_place.y -= 20;
				if (my_union->change_weapon_mode)
					player->weapon = player->new_weapon;
			}
		}

	}
}