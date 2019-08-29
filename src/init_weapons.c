/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:43:43 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/29 18:15:34 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_weapon_arrays(t_union *my_union)
{
	int i;

	my_union->weapons_mini_array = (SDL_Surface **)malloc(
			sizeof(SDL_Surface *) * 3);
	my_union->weapons_surfaces = (SDL_Surface ***)malloc(
			sizeof(SDL_Surface **) * 3);
	i = -1;
	while (++i < 3)
	{
		if (!i)
			my_union->weapons_surfaces[i] = (SDL_Surface **)malloc(
					sizeof(SDL_Surface *) * 5);
		else
			my_union->weapons_surfaces[i] = (SDL_Surface **)malloc(
					sizeof(SDL_Surface *) * 10);
	}
}

void	init_weapon(t_union *my_union)
{
	my_union->weapon_place.w = my_union->cur_win_x * 0.4;
	my_union->weapon_place.h = my_union->weapon_place.w;
	my_union->weapon_place.x = my_union->half_win_x -
			(my_union->weapon_place.w >> 1);
	my_union->weapon_place.y = (my_union->half_win_y >> 1) - 50;
	my_union->weapon_plce.y_start = my_union->half_win_y - 100;
	my_union->weapon_plce.y_end = my_union->hud_start;
	my_union->weapon_plce.width =
			my_union->weapon_plce.y_end - my_union->weapon_plce.y_start;
	my_union->weapon_plce.x_start = my_union->half_win_x -
			(my_union->weapon_plce.width >> 1);
	my_union->weapon_plce.x_end = my_union->half_win_x +
			(my_union->weapon_plce.width >> 1);
	my_union->weapon_plce.scale = (float)BLOCK_SIZE /
			my_union->weapon_plce.width;
	my_union->weapon_plce.cur_x = 0;
	my_union->weapon_plce.changing_flag = 0;
}

void	placement_stat_rects(t_union *my_union)
{
	my_union->stat_rects[0].x = my_union->hud_rect.x + 50;
	my_union->stat_rects[0].w = my_union->stat_rects[0].h >> 1;
	my_union->stat_rects[1].x = my_union->hud_rect.x + 165;
	my_union->stat_rects[1].w = my_union->stat_rects[1].h << 1;
	my_union->stat_rects[2].x = my_union->hud_rect.x + 440;
	my_union->stat_rects[2].w = my_union->stat_rects[2].h >> 1;
	my_union->stat_rects[3].x = my_union->hud_rect.x + 670;
	my_union->stat_rects[3].w = (my_union->stat_rects[3].h << 1) - 50;
	my_union->stat_rects[4].x = my_union->hud_rect.x + 840;
	my_union->stat_rects[4].w = (my_union->stat_rects[4].h >> 1);
	my_union->stat_rects[5].x = my_union->hud_rect.x + 1050;
	my_union->stat_rects[5].w = my_union->stat_rects[4].h << 1;
	my_union->stat_rects[5].y -= 5;
	my_union->stat_rects[6].x =
			my_union->stat_rects[4].x + my_union->stat_rects[4].w;
	my_union->stat_rects[6].w = my_union->stat_rects[6].h - 20;
	my_union->stat_rects[7].h = 40;
	my_union->stat_rects[7].w = 40;
	my_union->stat_rects[7].x = 0;
	my_union->stat_rects[7].y = -10;
}

void	init_stats_rects(t_union *my_union)
{
	int i;

	my_union->stat_rects = (SDL_Rect *)malloc(sizeof(SDL_Rect) * 8);
	i = -1;
	while (++i < 7)
	{
		my_union->stat_rects[i].h = my_union->hud_rect.h - 20;
		my_union->stat_rects[i].y = my_union->hud_rect.y + 20;
	}
	placement_stat_rects(my_union);
}

void	init_union(t_union *my_union)
{
	ft_bzero(my_union, sizeof(my_union));
	my_union->mouse_handling = 1;
	my_union->load_mark = 0;
	my_union->fullscreen_mode = 1;
	my_union->cur_win_x = 1280;
	my_union->cur_win_y = 720;
	my_union->wall_height_cof = BLOCK_SIZE << (int)(my_union->cur_win_x / 640);
	my_union->half_win_y = my_union->cur_win_y >> 1;
	my_union->half_win_x = my_union->cur_win_x >> 1;
	my_union->door_timer_end = 0;
	my_union->escape_timer = 0;
	my_union->sens = 2.4;
	my_union->mouse_x = my_union->half_win_x;
	my_union->mouse_y = my_union->half_win_y;
	my_union->rel_mouse_mode_timer = 0;
	my_union->font = NULL;
	my_union->weapon_down_mode = 0;
	my_union->menu_mode = 1;
	my_union->menu_tick = 0;
	my_union->shoot_timer = 0;
	my_union->reload_timer = 0;
	my_union->weapon_down_timer = 0;
	my_union->go_to_menu = 0;
	my_union->menu_frame = 0;
	my_union->change_weapon_mode = 0;
	srand(time(NULL));
}
