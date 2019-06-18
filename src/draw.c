/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:50:14 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/18 18:03:35 by hdwarven         ###   ########.fr       */
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

void	calc_line(t_union *my_union, double betta)
{
	my_union->distance = my_union->distance * cos(betta);
	my_union->line_length = (BLOCK_SIZE << (int)(my_union->win_x / 640)) / my_union->distance * 277;
	my_union->start = -my_union->line_length / 2 + my_union->win_y / 2;
	if (my_union->start < 0)
		my_union->start = 0;
	my_union->end = my_union->line_length / 2 + my_union->win_y / 2;
	if (my_union->end >= my_union->win_y)
		my_union->end = my_union->win_y - 1;
}

void	raycast(t_union my_union, t_map map, t_player player)
{
	int		i;
	double	center_x;
	double	angle;
	double 	one_angle;
	double 	player_angle;
	double	center_y;

	i = -1;
	center_x = player.player_pos_x + (player.player_width >> 1);
	center_y = player.player_pos_y + (player.player_heigth >> 1);
//	one_angle = player.fov / my_union.win_x * RAD;
//	player_angle = (player.view_direction - 30) * RAD;
	one_angle = player.fov / my_union.win_x;
	player_angle = (player.view_direction - 30);
	while (++i < my_union.win_x) {

		my_union.flag = 0;
		angle = one_angle * i + player_angle;
		if (angle < 0)
			angle = (360 + angle);
		if (angle >= 360)
			angle = (angle - 360);
		angle *= RAD;
		my_union.ray_x = (center_x + (player.radius * cos(angle)));
		my_union.ray_y = (center_y + (player.radius * sin(angle)));
//		trace_ray(&my_union, map, center_x, center_y, my_union.ray_x, my_union.ray_y, angle);
		hor_intersect(&my_union, player, map, angle);
		vert_intersect(&my_union, player, map, angle);
		calc_line(&my_union, angle - player.view_direction * RAD);
		if (my_union.flag/* && (my_union.end - my_union.start > 64)*/)
		{
			SDL_SetRenderDrawColor(my_union.renderer, 140, 140, 140, 255);
			SDL_RenderDrawLine(my_union.renderer, i, my_union.start, i, my_union.end);
//			draw_line(my_union, (int)i, (int)my_union.start, (int)my_union.end);
//			printf("y1 - %d, y2 - %d\n", (int)my_union.start, (int)my_union.end);
		}
		SDL_SetRenderDrawColor(my_union.renderer, 40, 255, 40, 255);
		SDL_RenderDrawLine(my_union.renderer, (int) center_x >> 2, (int)center_y >> 2, (int)my_union.ray_x >> 2, (int)my_union.ray_y >> 2);
	}
}

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
	if (map.map[(int)cur_y / BLOCK_SIZE][(int)cur_x / BLOCK_SIZE])
		return (1);
	return (0);
}

int 	check_bound(int	x, int y, t_map map)
{
	if ()
}

int		draw_line(t_union my_union, int x, int y1, int y2)
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

void	hor_intersect(t_union *my_union, t_player player, t_map map, double alpha)
{
	int	first_intersect_y;
	int	first_intersect_x;
	double 	step_y;
	double 	step_x;
	double 	cur_point_x;
	double 	cur_point_y;
	int 	intersect;
	double  tan_alpha;

	intersect = 0;

	tan_alpha = tan(alpha);
	printf("pos_x - %f, pos_y - %f, player - %d, angle - %f, tan - %f\n", player.player_pos_x, player.player_pos_y,
		   player.view_direction, alpha / RAD, tan(alpha));
	if ((int) (alpha / RAD) % 360 > 180 && (int) (alpha / RAD) % 360 < 360) {
		first_intersect_y = floor(player.player_pos_y / BLOCK_SIZE) * BLOCK_SIZE - 1;
		step_y = -BLOCK_SIZE;
	} else {
		first_intersect_y = floor(player.player_pos_y / BLOCK_SIZE) * BLOCK_SIZE + 64;
		step_y = BLOCK_SIZE;
	}

	first_intersect_x = player.player_pos_x + (player.player_pos_y - first_intersect_y) /
											  tan_alpha;

	printf("x: %d, y: %d\n", (first_intersect_x), first_intersect_y);
	step_x = BLOCK_SIZE / tan_alpha;
	if (step_x < -200 || step_x > 200) {
		my_union->distance = 15000;
		return;
	}
	printf("step_x - %f\n", step_x);
	cur_point_x = first_intersect_x;
	cur_point_y = first_intersect_y;
	while (!intersect|| (cur_point_x < map.size_x && cur_point_y < map.size_y))
	{
		if (check_wall(cur_point_x, cur_point_y, map))
		{
			intersect++;
			break;
		}
		cur_point_x += step_x;
		cur_point_y += step_y;
	}
	my_union->ray_x = cur_point_x;
	my_union->ray_y = cur_point_y;
	my_union->distance = fabs(player.player_pos_x - cur_point_x) / cos(alpha);
	printf("cur_x - %f, cur_y - %f\n", cur_point_x, cur_point_y);
}

//void	hor_intersect(t_union *my_union, t_player player, t_map map, double alpha)
//{
//	int	first_intersect_y;
//	int	first_intersect_x;
//	double 	step_y;
//	double 	step_x;
//	double 	cur_point_x;
//	double 	cur_point_y;
//	int 	intersect;
//	double  tan_alpha;
//
//	intersect = 0;
//
//	if (alpha / RAD == 90 || alpha / RAD == 270) {
//		step_x = 0;
//		if (alpha / RAD == 90)
//		{
//			first_intersect_x = floor(player.player_pos_x / BLOCK_SIZE) * BLOCK_SIZE + 64;
//			step_y = BLOCK_SIZE;
//		}
//		else
//			first_intersect_x = floor(player.player_pos_x / BLOCK_SIZE) * BLOCK_SIZE - 1;
//		step_y = -BLOCK_SIZE;
//	}
//	else {
//		tan_alpha = tan(alpha);
//		printf("pos_x - %f, pos_y - %f, player - %d, angle - %f, tan - %f\n", player.player_pos_x, player.player_pos_y,
//			   player.view_direction, alpha / RAD, tan(alpha));
//		if ((int) (alpha / RAD) % 360 > 180 && (int) (alpha / RAD) % 360 < 360) {
//			first_intersect_y = floor(player.player_pos_y / BLOCK_SIZE) * BLOCK_SIZE - 1;
//			step_y = -BLOCK_SIZE;
//		} else {
//			first_intersect_y = floor(player.player_pos_y / BLOCK_SIZE) * BLOCK_SIZE + 64;
//			step_y = BLOCK_SIZE;
//		}
//
//		first_intersect_x = player.player_pos_x + (player.player_pos_y - first_intersect_y) /
//												  tan_alpha;
//
//		printf("x: %d, y: %d\n", (first_intersect_x), first_intersect_y);
//		step_x = BLOCK_SIZE / tan_alpha;
//		if (step_x < -200 || step_x > 200) {
//			my_union->distance = 15000;
//			return;
//		}
//	}
//	printf("step_x - %f\n", step_x);
//	cur_point_x = first_intersect_x;
//	cur_point_y = first_intersect_y;
//	while (!intersect|| (cur_point_x < map.size_x && cur_point_y < map.size_y))
//	{
//		if (check_wall(cur_point_x, cur_point_y, map))
//		{
//			intersect++;
//			break;
//		}
//
//			cur_point_x += step_x;
//			cur_point_y += step_y;
//	}
//	my_union->ray_x = cur_point_x;
//	my_union->ray_y = cur_point_y;
//	my_union->distance = fabs(player.player_pos_x - cur_point_x) / cos(alpha);
//	printf("cur_x - %f, cur_y - %f\n", cur_point_x, cur_point_y);
//}

void	vert_intersect(t_union *my_union, t_player player, t_map map, double alpha)
{
	int	first_intersect_y;
	int	first_intersect_x;
	double 	distance;
	double 	step_y;
	double 	step_x;
	double 	cur_point_x;
	double 	cur_point_y;
	int 	intersect;
	double  tan_alpha;

	intersect = 0;

	if (alpha / RAD == 0 || alpha / RAD == 180)
	{
		step_x = 0;
		if (alpha / RAD == 0)
		{
			first_intersect_x = floor(player.player_pos_x / BLOCK_SIZE) * BLOCK_SIZE + 64;
			step_y = BLOCK_SIZE;
		}
		else
			first_intersect_x = floor(player.player_pos_x / BLOCK_SIZE) * BLOCK_SIZE - 1;
			step_y = -BLOCK_SIZE;
	}
	else
	{
		tan_alpha = tan(alpha);
		printf("pos_x - %f, pos_y - %f, player - %d, angle - %f, tan - %f\n", player.player_pos_x, player.player_pos_y,
			   player.view_direction, alpha / RAD, tan(alpha));
		if (alpha / RAD > 90 && alpha / RAD < 270) {
			first_intersect_x = floor(player.player_pos_x / BLOCK_SIZE) * BLOCK_SIZE - 1;
			step_x = -BLOCK_SIZE;
		} else {
			first_intersect_x = floor(player.player_pos_x / BLOCK_SIZE) * BLOCK_SIZE + 64;
			step_x = BLOCK_SIZE;
		}

		first_intersect_y = player.player_pos_y + (player.player_pos_x - first_intersect_x) /
												  tan_alpha;

		printf("x: %d, y: %d\n", (first_intersect_x), first_intersect_y);
		step_y = BLOCK_SIZE / tan_alpha;
		if (step_y < -200 || step_y > 200) {
			my_union->distance = 15000;
			return;
		}
	}
	printf("step_y - %f\n", step_y);
	cur_point_x = first_intersect_x;
	cur_point_y = first_intersect_y;
	while (!intersect|| (cur_point_x < map.size_x && cur_point_x >= 0 && cur_point_y >= 0 && cur_point_y < map.size_y))
	{
		if (check_wall(cur_point_x, cur_point_y, map))
		{
			intersect++;
			break;
		}

		cur_point_x += step_x;
		cur_point_y += step_y;
	}
	distance = fabs(player.player_pos_x - cur_point_x) / cos(alpha);
	if (distance < my_union->distance)
	{
		my_union->ray_x = cur_point_x;
		my_union->ray_y = cur_point_y;
		my_union->distance = distance;
	}
	printf("cur_x - %f, cur_y - %f\n", cur_point_x, cur_point_y);
}

void	trace_ray(t_union *my_union, t_map map, double x1, double y1, double x2, double y2, double alpha)
{
	double	delta_x;
	double	delta_y;
	double	step;
	double	increm_x;
	double	increm_y;
//	double 	intersect_begin_x;
//	double 	intersect_begin_y;
//	int 	flag;
//	double 	intersect_end_x;
//	double 	intersect_end_y;
	double	cur_x;
	double	cur_y;
	int		i;

//	flag = 0;
//	intersect_begin_x = 0;
//	intersect_begin_y = 0;
//	intersect_end_x = 0;
//	intersect_end_y = 0;
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
//		if (!flag)
//		{
//			if ((int) cur_x % BLOCK_SIZE == 0)
//				intersect_begin_x = cur_x;
//			if (intersect_begin_x && (int) cur_x % BLOCK_SIZE == 0)
//				intersect_end_x = cur_x;
//			if ((int) cur_y % BLOCK_SIZE == 0)
//			{
//				increm_x = cur_x - intersect_begin_x;
//				intersect_begin_y = cur_y;
//			}
//			if (intersect_begin_y && (int) cur_y % BLOCK_SIZE == 0)
//			{
//				increm_y = cur_y - intersect_begin_y;
//				intersect_end_y = cur_y;
//			}
//			if (intersect_end_x && intersect_end_y)
//				flag++;
//		{
//			increm_x = intersect_end_x - intersect_begin_x;
//			increm_y = intersect_end_y - intersect_begin_y;
//		}

//		}
		if (check_wall(cur_x, cur_y, map))
		{
			my_union->flag = 1;
			my_union->ray_x = cur_x;
			my_union->ray_y = cur_y;
			break;
		}
	}
//	my_union->delta_x = intersect_end_x - intersect_begin_x;
//	my_union->delta_y = intersect_end_y - intersect_begin_y;
//	if (flag)
//		return (1);
//	return (0);
	if (my_union->flag)
//		if ((int)cur_x % BLOCK_SIZE == 0 && (int)cur_y % BLOCK_SIZE != 0)
//			my_union->distance = fabs(x1 - cur_x) / alpha;
			my_union->distance = sqrt((x1 - cur_x) * (x1 - cur_x) + (y1 - cur_y) * (y1 - cur_y));
//		else if ((int)cur_y % BLOCK_SIZE == 0 && (int)cur_x % BLOCK_SIZE != 0)
//			my_union->distance = sqrt((x1 - cur_x) * (x1 - cur_x) + (y1 - cur_y) * (y1 - cur_y));

}
