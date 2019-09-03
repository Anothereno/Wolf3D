/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:43:43 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
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

void	stat_rects_fullscreen(t_union *my_union)
{
	my_union->stat_rects[0].x = my_union->hud_rect.x + 100;
	my_union->stat_rects[0].w = my_union->stat_rects[0].h >> 1;
	my_union->stat_rects[1].x = my_union->hud_rect.x + 300;
	my_union->stat_rects[1].w = my_union->stat_rects[1].h << 1;
	my_union->stat_rects[2].x = my_union->hud_rect.x + 880;
	my_union->stat_rects[2].w = my_union->stat_rects[2].h >> 1;
	my_union->stat_rects[3].x = my_union->hud_rect.x + 1350;
	my_union->stat_rects[3].w = (my_union->stat_rects[3].h << 1) - 150;
	my_union->stat_rects[4].x = my_union->hud_rect.x + 1670;
	my_union->stat_rects[4].w = (my_union->stat_rects[4].h >> 1);
	my_union->stat_rects[5].x = my_union->hud_rect.x + 2050;
	my_union->stat_rects[5].w = my_union->stat_rects[4].h << 1;
	my_union->stat_rects[5].y -= 5;
	my_union->stat_rects[6].x =
			my_union->stat_rects[4].x + my_union->stat_rects[4].w;
	my_union->stat_rects[6].w = my_union->stat_rects[6].h - 40;
	my_union->stat_rects[7].h = 40;
	my_union->stat_rects[7].w = 40;
	my_union->stat_rects[7].x = 0;
	my_union->stat_rects[7].y = -10;
}

void	init_stats_rects(t_union *my_union)
{
	my_union->stat_rects = (SDL_Rect *)malloc(sizeof(SDL_Rect) * 8);
	change_stat_rects(my_union);
}

void	init_timers(t_union *my_union)
{
	my_union->menu_mode = 1;
	my_union->menu_tick = 0;
	my_union->shoot_timer = 0;
	my_union->reload_timer = 0;
	my_union->weapon_down_timer = 0;
	my_union->return_timer = 0;
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
	my_union->sens = 2.4f;
	my_union->mouse_x = my_union->half_win_x;
	my_union->mouse_y = my_union->half_win_y;
	my_union->rel_mouse_mode_timer = 0;
	my_union->font = NULL;
	my_union->weapon_down_mode = 0;
	my_union->go_to_menu = 0;
	my_union->submenu_mode = 0;
	my_union->menu_frame = 0;
	my_union->change_weapon_mode = 0;
	init_timers(my_union);
	srand(time(NULL));
}
