/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_and_weapon.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:41:01 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_loaded(t_union *my_union, int index,
								int size, int dimension)
{
	int i;

	i = -1;
	while (++i < size)
		if ((dimension == 1 && !my_union->wall_surfaces_array[i]) ||
			(dimension == 2 && !my_union->weapons_surfaces[index][i]))
			return (0);
	return (1);
}

void	init_player_ammunition(t_player *player)
{
	player->ammo = (int*)malloc(sizeof(int) * 3);
	player->clip_volume = (int*)malloc(sizeof(int) * 3);
	player->clip = (int*)malloc(sizeof(int) * 3);
	player->ammo[0] = 1;
	player->ammo[1] = 40;
	player->ammo[2] = 80;
	player->clip_volume[0] = 1;
	player->clip_volume[1] = 7;
	player->clip_volume[2] = 20;
	player->clip[0] = player->clip_volume[0];
	player->clip[1] = player->clip_volume[1];
	player->clip[2] = player->clip_volume[2];
}

void	init_player(t_player *player)
{
	player->view_direction = 0;
	player->view_direction_rad = player->view_direction * RAD;
	player->speed = BLOCK_SIZE >> 3;
	player->strafe_speed = (BLOCK_SIZE >> 4) + 1;
	player->move_indicate = 0;
	player->rotate_angle = 3;
	player->fov = 60;
	player->half_fov = player->fov * 0.5f;
	player->score = 7200;
	player->level = 2;
	player->lives = 3;
	player->health = 100;
	player->weapon = 1;
	player->weapon_frame = 1;
	player->shoot_mode = 0;
	init_player_ammunition(player);
}

void	change_hud_rect(t_union *my_union)
{
	if (!my_union->fullscreen_mode)
	{
		my_union->hud_rect.w = my_union->cur_win_x;
		my_union->hud_rect.h = my_union->cur_win_y / 6;
		my_union->hud_rect.x = 0;
		my_union->hud_rect.y = my_union->cur_win_y - my_union->hud_rect.h;
		my_union->hud_start = my_union->hud_rect.y;
	}
	else
	{
		my_union->hud_rect.w = 2560;
		my_union->hud_rect.h = 1440 / 6;
		my_union->hud_rect.x = 0;
		my_union->hud_rect.y = 1440 - my_union->hud_rect.h;
		my_union->hud_start = my_union->hud_rect.y;
	}
}

void	init_hud(t_union *my_union)
{
	change_hud_rect(my_union);
	my_union->hud_texture = SDL_CreateTextureFromSurface(my_union->renderer,
			my_union->hud_surface);
	init_stats_rects(my_union);
}
