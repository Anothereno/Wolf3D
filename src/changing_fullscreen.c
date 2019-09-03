/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changing_fulscreen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 16:27:17 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	change_weapon_rect(t_union *my_union)
{
	if (my_union->fullscreen_mode)
		weapon_to_fullscreen(my_union);
	else
		weapon_to_windowed(my_union);
}

void	weapon_to_fullscreen(t_union *my_union)
{
	my_union->weapon_place.w = 2560 * 0.4;
	my_union->weapon_place.h = my_union->weapon_place.w;
	my_union->weapon_place.x = 1280 -
			(my_union->weapon_place.w >> 1);
	my_union->weapon_place.y = 310;
	my_union->weapon_plce.y_start = 620;
	my_union->weapon_plce.y_end = my_union->hud_start;
	my_union->weapon_plce.width =
			my_union->weapon_plce.y_end - my_union->weapon_plce.y_start;
	my_union->weapon_plce.x_start = 1280 -
			(my_union->weapon_plce.width >> 1);
	my_union->weapon_plce.x_end = 1280 +
			(my_union->weapon_plce.width >> 1);
	my_union->weapon_plce.scale = (float)BLOCK_SIZE /
			my_union->weapon_plce.width;
	my_union->weapon_plce.cur_x = 0;
	my_union->weapon_plce.changing_flag = 0;
}

void	weapon_to_windowed(t_union *my_union)
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

void	change_stat_rects(t_union *my_union)
{
	int i;

	i = -1;
	while (++i < 7)
	{
		my_union->stat_rects[i].h = my_union->hud_rect.h - 20;
		my_union->stat_rects[i].y = my_union->hud_rect.y + 20;
	}
	if (my_union->fullscreen_mode)
		stat_rects_fullscreen(my_union);
	else
		stat_rects_windowed(my_union);
}

void	stat_rects_windowed(t_union *my_union)
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
