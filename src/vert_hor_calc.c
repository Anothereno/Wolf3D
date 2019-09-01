/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_hor_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 18:15:05 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/01 18:42:57 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		setup_horizontal(float sin_alpha, t_point *points, t_player player,
							t_ray *ray)
{
	if (sin_alpha < 0)
	{
		points->first_intersect_y = ((int)player.player_pos_y & 0xffc0)
				- 0.001;
		points->step_y = -BLOCK_SIZE;
	}
	else if (sin_alpha > 0)
	{
		points->first_intersect_y = ((int)player.player_pos_y & 0xffc0)
				+ 64.001;
		points->step_y = BLOCK_SIZE;
	}
	else
	{
		ray->hor_distance = 99999;
		return (0);
	}
	return (1);
}

void	hor_distance(t_player player, t_map map, t_ray *ray, float alpha)
{
	float	sin_alpha;
	t_point	points;

	sin_alpha = sinf(alpha);
	if (!setup_horizontal(sin_alpha, &points, player, ray))
		return ;
	points.first_intersect_x = player.player_pos_x + (points.first_intersect_y
			- player.player_pos_y) / tanf(alpha);
	points.step_x = -points.step_y / tanf(-alpha);
	check_intersection(map, &points);
	ray->end_hor_x = points.cur_point_x;
	ray->end_hor_y = points.cur_point_y;
	ray->hor_distance = fabsf((player.player_pos_y - points.cur_point_y)
			/ sin_alpha);
}

int		setup_vertical(float cos_alpha, t_point *points, t_player player,
		t_ray *ray)
{
	if (cos_alpha < 0)
	{
		points->first_intersect_x = ((int)player.player_pos_x & 0xffc0)
				- 0.001;
		points->step_x = -BLOCK_SIZE;
	}
	else if (cos_alpha > 0)
	{
		points->first_intersect_x = ((int)player.player_pos_x & 0xffc0)
				+ 64.001;
		points->step_x = BLOCK_SIZE;
	}
	else
	{
		ray->vert_distance = 99999;
		return (0);
	}
	return (1);
}

void	check_intersection(t_map map, t_point *points)
{
	points->cur_point_x = points->first_intersect_x;
	points->cur_point_y = points->first_intersect_y;
	while (!check_wall(points->cur_point_x, points->cur_point_y, map))
	{
		points->cur_point_x += points->step_x;
		points->cur_point_y += points->step_y;
	}
}

void	vert_distance(t_player player, t_map map, t_ray *ray, float alpha)
{
	float	cos_alpha;
	t_point	points;

	cos_alpha = cosf(alpha);
	if (!setup_vertical(cos_alpha, &points, player, ray))
		return ;
	points.first_intersect_y = player.player_pos_y + (points.first_intersect_x
			- player.player_pos_x) * tanf(alpha);
	points.step_y = -points.step_x * tanf(-alpha);
	check_intersection(map, &points);
	ray->end_vert_x = points.cur_point_x;
	ray->end_vert_y = points.cur_point_y;
	ray->vert_distance = fabsf((player.player_pos_x - points.cur_point_x)
			/ cos_alpha);
}
