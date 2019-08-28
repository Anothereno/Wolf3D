/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_surfaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 15:26:12 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/20 12:27:36 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	change_weapon_frame(t_union *my_union, t_player *player)
{
	if ((player->weapon == 1 &&
			my_union->start_tick - my_union->shoot_timer >= 15) ||
			(player->weapon == 2 &&
			my_union->start_tick- my_union->shoot_timer >= 7) ||
			(player->weapon == 0 &&
			my_union->start_tick - my_union->shoot_timer >= 4))
	{
		my_union->shoot_timer = SDL_GetTicks();
		player->weapon_frame++;
	}
}

void	draw_weapon(t_union *my_union, t_player *player, t_map *map)
{
	if (my_union->weapon_down_mode)
		weapon_down(my_union, player);
	my_union->weapon_texture = SDL_CreateTextureFromSurface(my_union->renderer,
			my_union->weapons_surfaces[player->weapon][player->weapon_frame]);
	SDL_RenderCopy(my_union->renderer, my_union->weapon_texture, NULL, &my_union->weapon_place);
	SDL_DestroyTexture(my_union->weapon_texture);
	if (player->shoot_mode)
		change_weapon_frame(my_union, player);
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

void change_weapon(t_player *player, const Uint8 *key, t_union *my_union)
{
	if (key[SDL_SCANCODE_1] && player->weapon != 0)
	{
		weapon_down(my_union, player);
		my_union->change_weapon_mode = 1;
		player->new_weapon = 0;
	}
	else if (key[SDL_SCANCODE_2] && player->weapon != 1)
	{
		weapon_down(my_union, player);
		my_union->change_weapon_mode = 1;
		player->new_weapon = 1;
	}
	else if (key[SDL_SCANCODE_3] && player->weapon != 2)
	{
		weapon_down(my_union, player);
		my_union->change_weapon_mode = 1;
		player->new_weapon = 2;
	}
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