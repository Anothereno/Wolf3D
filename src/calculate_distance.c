/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:26:44 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/01 18:24:11 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		get_start_draw(t_union my_union)
{
	if (my_union.wall_heigth >= my_union.cur_win_y)
		return ((my_union.wall_heigth >> 1) - my_union.half_win_y);
	return (0);
}

void	calc_line(t_union *my_union, t_ray ray, float betta)
{
	ray.res_distance = ray.res_distance * cosf(betta);
	my_union->wall_heigth = my_union->wall_height_cof / ray.res_distance * 277;
	my_union->start = (-my_union->wall_heigth >> 1) + my_union->half_win_y;
	if (my_union->start < 0)
		my_union->start = 0;
	my_union->end = (my_union->wall_heigth >> 1) + my_union->half_win_y;
	if (my_union->end >= my_union->cur_win_y)
		my_union->end = my_union->cur_win_y - 1;
}

void	choose_distance(t_ray *ray)
{
	if (ray->hor_distance < ray->vert_distance)
	{
		ray->x = ray->end_hor_x;
		ray->y = ray->end_hor_y;
		ray->res_distance = ray->hor_distance;
		ray->mode = 0;
	}
	else
	{
		ray->x = ray->end_vert_x;
		ray->y = ray->end_vert_y;
		ray->res_distance = ray->vert_distance;
		ray->mode = 1;
	}
}

float	take_range_angle(float angle)
{
	if (angle < 0)
		angle = (360 + angle);
	if (angle >= 360)
		angle = (angle - 360);
	return (angle);
}

int		take_textures_offset(t_ray ray)
{
	if (!ray.mode)
		return ((int)ray.x % BLOCK_SIZE);
	else
		return ((int)ray.y % BLOCK_SIZE);
}
