/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:50:14 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	update_renderer(t_union *my_union, t_player *player)
{
	put_cross(my_union, player);
	SDL_UpdateTexture(my_union->main_window_texture, NULL,
			my_union->pixel_array, my_union->cur_win_x * sizeof(Uint32));
	SDL_RenderCopy(my_union->renderer, my_union->main_window_texture,
			NULL, NULL);
	draw_weapon(my_union, player);
	draw_hud(my_union, player);
}

void	raycast(t_union *my_union, t_map *map, t_player *player, t_ray *ray)
{
	int		x;
	float	angle_rad;
	float	angle;
	float	one_angle;

	x = -1;
	one_angle = player->fov / my_union->cur_win_x;
	angle = (player->view_direction - player->half_fov);
	my_union->weapon_plce.cur_x = 0;
	while (++x < my_union->cur_win_x)
	{
		my_union->flag = 0;
		angle = take_range_angle(angle);
		angle_rad = angle * RAD;
		hor_distance(*player, *map, ray, angle_rad);
		vert_distance(*player, *map, ray, angle_rad);
		choose_distance(ray);
		calc_line(my_union, *ray, angle_rad - player->view_direction_rad);
		ray->offset = take_textures_offset(*ray);
		draw_walls(my_union, *ray, x, *map);
		draw_ceiling_floor(my_union, *player, angle_rad, x);
		angle += one_angle;
	}
	update_renderer(my_union, player);
}

int		check_bound(float x, float y, t_map map)
{
	if (x < 0 || x > (map.size_x << 6) || y < 0 || y > (map.size_y << 6))
		return (0);
	return (1);
}
