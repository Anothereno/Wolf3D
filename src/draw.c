/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:50:14 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/30 11:31:35 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	clear_window(t_union my_union)
{
	SDL_SetRenderDrawColor(my_union.renderer, 0, 0, 0, 255);
	SDL_RenderClear(my_union.renderer);
}

void	take_vector_of_view(t_player *player)
{
	double center_x;
	double center_y;
	double last_x;
	double rad;

	rad = 0.0174533;
	center_x = player->player_pos_x + (player->player_width >> 1);
	center_y = player->player_pos_y + (player->player_heigth >> 1);
	last_x = player->direct_x;
	player->direct_x = player->direct_x * cos(player->view_direction * rad) - player->direct_y * sin(player->view_direction * rad);
	player->direct_y = last_x * sin(player->view_direction * rad) + player->direct_y * sin(player->view_direction * rad);
//	printf("%f, %f\n", player->direct_x, player->direct_y);
}

void	calc_line(t_union *my_union, t_ray ray, double betta)
{
	ray.res_distance = ray.res_distance * cos(betta);
	my_union->line_length = (BLOCK_SIZE << (int)(my_union->win_x / 640)) / ray.res_distance * 277;
	my_union->start = -my_union->line_length / 2 + my_union->win_y / 2;
	if (my_union->start < 0)
		my_union->start = 0;
	my_union->end = my_union->line_length / 2 + my_union->win_y / 2;
	if (my_union->end >= my_union->win_y)
		my_union->end = my_union->win_y - 1;
}

//void	calc_line(t_union *my_union, double betta)
//{
//	my_union->distance = my_union->distance * cos(betta);
//	my_union->line_length = (BLOCK_SIZE << (int)(my_union->win_x / 640)) / my_union->distance * 277;
//	my_union->start = -my_union->line_length / 2 + my_union->win_y / 2;
//	if (my_union->start < 0)
//		my_union->start = 0;
//	my_union->end = my_union->line_length / 2 + my_union->win_y / 2;
//	if (my_union->end >= my_union->win_y)
//		my_union->end = my_union->win_y - 1;
//}

void	choose_distance(t_ray *ray) {
	if (ray->hor_distance < ray->vert_distance)
	{
		ray->x = ray->end_hor_x;
		ray->y = ray->end_hor_y;
		ray->res_distance = ray->hor_distance;
	}
	else
	{
		ray->x = ray->end_vert_x;
		ray->y = ray->end_vert_y;
		ray->res_distance = ray->vert_distance;
	}
}

double take_range_angle(double angle)
{
	if (angle < 0)
		angle = (360 + angle);
	if (angle >= 360)
		angle = (angle - 360);
	return angle;

}

void	raycast(t_union my_union, t_map map, t_player player, t_ray ray)
{
	int		i;
	double	center_x;
	double	angle;
	double 	one_angle;
	double 	begin_angle;
	double	center_y;

	i = -1;
	center_x = player.player_pos_x + (player.player_width >> 1);
	center_y = player.player_pos_y + (player.player_heigth >> 1);
	one_angle = player.fov / my_union.win_x;
	begin_angle = (player.view_direction - (player.fov / 2));
	angle = begin_angle;
	while (++i < my_union.win_x) {
		my_union.flag = 0;
		angle = take_range_angle(angle);
		hor_distance(&my_union, player, map, &ray, angle * RAD);
		vert_distance(&my_union, player, map, &ray, angle * RAD);
		choose_distance(&ray);
		calc_line(&my_union, ray, angle * RAD - player.view_direction * RAD);
		SDL_SetRenderDrawColor(my_union.renderer, 155, 155, 155, 255);
		SDL_RenderDrawLine(my_union.renderer, i, my_union.start, i, my_union.end);
//		SDL_SetRenderDrawColor(my_union.renderer, 244, 244, 66, 255);
//		SDL_RenderDrawLine(my_union.renderer, (int) center_x >> 2, (int)center_y >> 2, (int)ray.x >> 2, (int)ray.y >> 2);
		angle += one_angle;
	}
}

// ПРАВИЛЬНЫЙ РЭЙКАСТ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//void	raycast(t_union my_union, t_map map, t_player player)
//{
//	int		i;
//	double	center_x;
//	double	angle;
//	double 	one_angle;
//	double 	player_angle;
//	double	center_y;
//
//	i = -1;
//	center_x = player.player_pos_x + (player.player_width >> 1);
//	center_y = player.player_pos_y + (player.player_heigth >> 1);
////	one_angle = player.fov / my_union.win_x * RAD;
////	player_angle = (player.view_direction - 30) * RAD;
//	one_angle = player.fov / my_union.win_x;
//	player_angle = (player.view_direction - 30);
//	while (++i < my_union.win_x) {
//
//		my_union.flag = 0;
//		angle = one_angle * i + player_angle;
//		if (angle < 0)
//			angle = (360 + angle);
//		if (angle >= 360)
//			angle = (angle - 360);
//		angle *= RAD;
//		my_union.ray_x = (center_x + (player.radius * cos(angle)));
//		my_union.ray_y = (center_y + (player.radius * sin(angle)));
//		trace_ray(&my_union, map, center_x, center_y, my_union.ray_x, my_union.ray_y, angle);
////		hor_intersect(&my_union, player, map, angle);
////		vert_intersect(&my_union, player, map, angle);
//		calc_line(&my_union, angle - player.view_direction * RAD);
//		if (my_union.flag/* && (my_union.end - my_union.start > 64)*/)
//		{
//			SDL_SetRenderDrawColor(my_union.renderer, 66, 152, 244, 255);
//			SDL_RenderDrawLine(my_union.renderer, i, my_union.start, i, my_union.end);
////			draw_line(my_union, (int)i, (int)my_union.start, (int)my_union.end);
////			printf("y1 - %d, y2 - %d\n", (int)my_union.start, (int)my_union.end);
//		}
//		SDL_SetRenderDrawColor(my_union.renderer, 244, 244, 66, 255);
//		SDL_RenderDrawLine(my_union.renderer, (int) center_x >> 2, (int)center_y >> 2, (int)my_union.ray_x >> 2, (int)my_union.ray_y >> 2);
//	}
//}

void	draw_rays(t_union my_union, t_player player, t_map map)
{
	int		i;
	int 	step_x;
	int 	step_y;
	int 	collis;
	int 	line_heigth;
	int 	start;
	int 	end;
	int 	wall_side;
	double	cam;
	double	ray_x;
	double	ray_y;
	int 	square_x;
	int 	square_y;
	double 	side_distance_x;
	double 	side_distance_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double 	wall_dist;



	i = -1;
	SDL_SetRenderDrawColor(my_union.renderer, 130, 130, 130, 255);
	while (++i < my_union.win_x)
	{
		cam = 2 * i / (double)my_union.win_x - 1;
		ray_x = player.dirX + player.planeX * cam;
		ray_y = player.dirY + player.planeY * cam;

		square_x = (int)player.player_pos_x;
		square_y = (int)player.player_pos_y;

		delta_dist_x = fabs(1 / ray_x);
		delta_dist_y = fabs(1 / ray_y);

		collis = 0;
		if (ray_x < 0)
		{
			step_x = -1;
			side_distance_x = (player.player_pos_x - square_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_distance_x = (square_x + 1.0 - player.player_pos_x) * delta_dist_x;
		}
		if (ray_y < 0)
		{
			step_y = -1;
			side_distance_y = (player.player_pos_y - square_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_distance_y = (square_y + 1.0 - player.player_pos_y) * delta_dist_y;
		}

		while (!collis)
		{
			if (side_distance_x < side_distance_y)
			{
				side_distance_x += delta_dist_x;
				square_x += step_x;
				wall_side = 0;
			}
			else
			{
				side_distance_y += delta_dist_y;
				square_y += step_y;
				wall_side = 1;
			}
			if (square_x >= map.size_x || square_y >= map.size_y || map.map[square_y][square_x] > 0)
				collis = 1;
		}
			if (!wall_side)
				wall_dist = (square_x - player.player_pos_x + (double)(1 - step_x) / 2) / ray_x;
			else
				wall_dist = (square_y - player.player_pos_y + (double)(1 - step_y) / 2) / ray_y;

			line_heigth = (int)(my_union.win_y / wall_dist);
			start = -line_heigth / 2 + my_union.win_y / 2;
			if (start < 0)
				start = 0;
			end = line_heigth / 2 + my_union.win_y / 2;
			if (end >= my_union.win_y)
				end = my_union.win_y - 1;

			SDL_RenderDrawLine(my_union.renderer, i,
							   start, i, end);


//			SDL_RenderDrawLine(my_union.renderer, player.player_pos_x + (player.player_width >> 1),
//							   player.player_pos_y + (player.player_heigth >> 1), ray_x, ray_y);



	}
}

void	draw_scene(t_union my_union, t_map map)
{
	int			x;
	int			y;
	SDL_Rect	wall;

	SDL_SetRenderDrawColor(my_union.renderer, 255, 50, 255, 255);
	y = -1;
	while (++y < map.size_y)
	{
		x = -1;
		while (++x < map.size_x)
		{
			wall.x = x * (BLOCK_SIZE >> 2);
			wall.y = y * (BLOCK_SIZE >> 2);
			wall.h = (BLOCK_SIZE >> 2);
			wall.w = (BLOCK_SIZE >> 2);
			if (map.map[y][x] != 0)
				SDL_RenderFillRect(my_union.renderer, &wall);
		}
	}
}

int 	check_wall(double cur_x, double cur_y, t_map map)
{
	if (cur_x >= map.size_x * BLOCK_SIZE || cur_x < 0 ||
			cur_y >= map.size_y * BLOCK_SIZE || cur_y < 0 ||
			map.map[(int)cur_y / BLOCK_SIZE][(int)cur_x / BLOCK_SIZE])
		return (1);
	return (0);
}

int 	check_bound(double	x, double y, t_map map)
{
	if (x < 0 || x > map.size_x * BLOCK_SIZE || y < 0 || y > map.size_y * BLOCK_SIZE)
		return (0);
	return (1);
}

int		draw_vert_line(t_union my_union, int x, int y1, int y2)
{
	int	sign_y;

	sign_y = y1 < y2 ? 1 : -1;
	SDL_RenderDrawPoint(my_union.renderer, x, y2);
	while (y1 != y2)
	{
		SDL_RenderDrawPoint(my_union.renderer, x, y1);
		y1 += sign_y;
	}
}

//int		draw_line(t_union my_union, double x, double y1, double y2)
//{
//	double	delta_x;
//	double	delta_y;
//	double	step;
//	double	increm_x;
//	double	increm_y;
//	double	cur_x;
//	double	cur_y;
//	int		i;
//
//	delta_y = y2 - y1;
//	step = fabs(delta_y);
//	increm_y = delta_y / (double)step;
//	cur_y = y1;
//	i = -1;
//	while (++i <= step)
//	{
//		SDL_RenderDrawPoint(my_union.renderer, x, (int)cur_y);
//		cur_y += increm_y;
//	}
//}

void	hor_distance(t_union *my_union, t_player player, t_map map, t_ray *ray, double alpha)
{
	double	first_intersect_y;
	double	first_intersect_x;
	double 	step_y;
	double 	step_x;
	double 	cur_point_x;
	double 	cur_point_y;

	if (sin(alpha) < 0)
	{
		first_intersect_y = ((int)player.player_pos_y & 0xffc0) - 0.001;
		step_y = -BLOCK_SIZE;
	}
	else if (sin(alpha) > 0)
	{
		first_intersect_y = ((int)player.player_pos_y & 0xffc0) + 64.001;
		step_y = BLOCK_SIZE;
	}
	else
	{
		ray->hor_distance = 99999;
		return;
	}
	first_intersect_x = player.player_pos_x + (first_intersect_y - player.player_pos_y) /
											  tan(alpha);
	step_x = -step_y / tan(-alpha);
	cur_point_x = first_intersect_x;
	cur_point_y = first_intersect_y;
	while (check_bound(cur_point_x, cur_point_y, map) && !check_wall(cur_point_x,
			cur_point_y, map))
	{
		cur_point_x += step_x;
		cur_point_y += step_y;
	}
	ray->end_hor_x = cur_point_x;
	ray->end_hor_y = cur_point_y;
	ray->hor_distance = fabs((player.player_pos_y - cur_point_y) / sin(alpha));
}

void	vert_distance(t_union *my_union, t_player player, t_map map, t_ray *ray, double alpha)
{
	double	first_intersect_y;
	double	first_intersect_x;
	double 	step_y;
	double 	step_x;
	double 	cur_point_x;
	double 	cur_point_y;

	if (cos(alpha) < 0)
	{
		first_intersect_x = ((int)player.player_pos_x & 0xffc0) - 0.001;
		step_x = -BLOCK_SIZE;
	}
	else if (cos(alpha) > 0)
	{
		first_intersect_x = ((int)player.player_pos_x & 0xffc0) + 64.001;
		step_x = BLOCK_SIZE;
	}
	else
	{
		ray->vert_distance = 99999;
		return;
	}
	first_intersect_y = player.player_pos_y + (first_intersect_x - player.player_pos_x) *
											  tan(alpha);
	step_y = -step_x * tan(-alpha);
	cur_point_x = first_intersect_x;
	cur_point_y = first_intersect_y;
	while (check_bound(cur_point_x, cur_point_y, map) && !check_wall(cur_point_x,
			cur_point_y, map))
	{
		cur_point_x += step_x;
		cur_point_y += step_y;
	}
	ray->end_vert_x = cur_point_x;
	ray->end_vert_y = cur_point_y;
	ray->vert_distance = fabs((player.player_pos_x - cur_point_x) / cos(alpha));
}

void	trace_ray(t_union *my_union, t_map map, double x1, double y1, double x2, double y2, double alpha)
{
	double	delta_x;
	double	delta_y;
	double	step;
	double	increm_x;
	double	increm_y;
	double	cur_x;
	double	cur_y;
	int		i;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	if (fabs(delta_x) > fabs(delta_y))
		step = fabs(delta_x);
	else
		step = fabs(delta_y);
	increm_x = delta_x / (double)step;
	increm_y = delta_y / (double)step;
	cur_x = x1;
	cur_y = y1;
	i = -1;
	while (++i <= step)
	{
		cur_x += increm_x;
		cur_y += increm_y;
		if (check_wall(cur_x, cur_y, map))
		{
			my_union->flag = 1;
			my_union->ray_x = cur_x;
			my_union->ray_y = cur_y;
			break;
		}
	}

	if (my_union->flag)
		my_union->distance = sqrt((x1 - cur_x) * (x1 - cur_x) + (y1 - cur_y) * (y1 - cur_y));

}
