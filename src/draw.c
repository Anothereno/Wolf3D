/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:43:30 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 11:39:08 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_walls(t_union *my_union, t_ray ray, int x, t_map map)
{
	int			y;
	float		wall_scale;

	my_union->start_for_draw = 0;
	y = get_start_draw(*my_union);
	wall_scale = BLOCK_SIZE / (float)my_union->wall_heigth;
	while (++my_union->start_for_draw < my_union->end)
	{
		if (my_union->start_for_draw >= my_union->start &&
				my_union->start_for_draw < my_union->end)
		{
			if (my_union->start_for_draw > my_union->hud_start)
				continue;
			choose_surface_wall(my_union, ray, map);
			get_surface_pixel(my_union, ray.offset, y * wall_scale,
					&my_union->texturing);
			y++;
			put_pixel(my_union, x, my_union->start_for_draw,
					&my_union->texturing);
		}
	}
	my_union->start_for_draw--;
}

void	draw_ceiling_floor(t_union *my_union, t_player player, float angle,
		int x)
{
	t_ceil_floor	cf;
	float			cur_dist;
	float			dist;

	dist = my_union->dist / cosf(angle - player.view_direction_rad);
	cf.cos_angle = cosf(angle);
	cf.sin_angle = sinf(angle);
	while (++my_union->start_for_draw < my_union->cur_win_y)
	{
		cur_dist = dist / (my_union->start_for_draw - my_union->half_win_y);
		cf.x = (int)(cur_dist * cf.cos_angle + player.player_pos_x) % 64;
		cf.y = (int)(cur_dist * cf.sin_angle + player.player_pos_y) % 64;
		if (my_union->start_for_draw < my_union->hud_start)
		{
			choose_surface_floor_ceiling_hud(my_union, 'f');
			get_surface_pixel(my_union, cf.x, cf.y, &my_union->texturing);
			put_pixel(my_union, x, my_union->start_for_draw,
					&my_union->texturing);
		}
		cf.diff = my_union->cur_win_y - my_union->start_for_draw;
		choose_surface_floor_ceiling_hud(my_union, 'c');
		get_surface_pixel(my_union, cf.x, cf.y, &my_union->texturing);
		put_pixel(my_union, x, cf.diff, &my_union->texturing);
	}
}

void	put_cross(t_union *my_union, t_player *player)
{
	int i;

	i = 3 + player->move_indicate;
	while (++i < 10 + player->move_indicate)
	{
		my_union->pixel_array[my_union->half_win_y * my_union->cur_win_x +
			my_union->half_win_x + i] = 0xFFFFFF;
		my_union->pixel_array[my_union->half_win_y * my_union->cur_win_x +
			my_union->half_win_x - i] = 0xFFFFFF;
		my_union->pixel_array[(my_union->half_win_y + i) *
			my_union->cur_win_x + my_union->half_win_x] = 0xFFFFFF;
		my_union->pixel_array[(my_union->half_win_y - i) *
			my_union->cur_win_x + my_union->half_win_x] = 0xFFFFFF;
	}
}

void	draw_hud(t_union *my_union, t_player *player)
{
	SDL_RenderCopy(my_union->renderer, my_union->hud_texture,
			NULL, &my_union->hud_rect);
	show_stats(my_union, player);
}

int		check_wall(float cur_x, float cur_y, t_map map)
{
	if (cur_x >= (map.size_x << 6) || cur_x < 0 ||
		cur_y >= (map.size_y << 6) || cur_y < 0 ||
		map.map[(int)cur_y >> 6][(int)cur_x >> 6])
		return (1);
	return (0);
}
