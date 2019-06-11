/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:50:14 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/11 13:43:25 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	clear_window(t_union my_union)
{
	SDL_SetRenderDrawColor(my_union.renderer, 0, 0, 0, 255);
	SDL_RenderClear(my_union.renderer);
}

//void	draw_raycast()

void	take_vector_of_view(t_player *player)
{
	double center_x;
	double center_y;
	double rad;

	rad = 0.0174533;
	center_x = player->player_pos_x + (player->player_width >> 1);
	center_y = player->player_pos_y + (player->player_heigth >> 1);
	player->direct_x = (center_x + (player->radius * cos(player->degree * rad)));
	player->direct_y = (center_y + (player->radius * sin(player->degree * rad)));
}

void	raycast(t_union my_union, t_map map, t_player player)
{
	int		i;
	double	center_x;
	double	ray_x;
	double	ray_y;
	double	angle;
	double 	prev_angle;
	double 	player_angle;
	double	center_y;
	double	rad;

	rad = 0.0174533;
	i = -1;
	center_x = player.player_pos_x + (player.player_width >> 1);
	center_y = player.player_pos_y + (player.player_heigth >> 1);
	prev_angle = player.fov / my_union.win_x * rad;
	player_angle = player.degree * rad;

	while (++i < my_union.win_x / 2)
	{
		angle = prev_angle * i;
		ray_x = (center_x + (player.radius * cos(player_angle + angle)));
		ray_y = (center_y + (player.radius * sin(player_angle + angle)));
		draw_line(my_union, map, center_x, center_y, ray_x, ray_y);
		ray_x = (center_x + (player.radius * cos(player_angle - angle)));
		ray_y = (center_y + (player.radius * sin(player_angle - angle)));
		draw_line(my_union, map, center_x, center_y, ray_x, ray_y);

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

void	draw_player(t_union my_union, t_player player, t_map map)
{
	SDL_Rect player_body;

	player_body.x = (int)player.player_pos_x;
	player_body.y = (int)player.player_pos_y;
	player_body.h = player.player_heigth;
	player_body.w = player.player_width;
	take_vector_of_view(&player);
	SDL_SetRenderDrawColor(my_union.renderer, 50, 255, 255, 255);
	SDL_RenderFillRect(my_union.renderer, &player_body);
//	draw_line(my_union, map, player.player_pos_x + (player.player_width >> 1),
//					   player.player_pos_y + (player.player_heigth >> 1), player.direct_x,
//					   player.direct_y);
	raycast(my_union, map, player);
	//draw_rays(my_union, player, map);

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
			wall.x = x * BLOCK_SIZE;
			wall.y = y * BLOCK_SIZE;
			wall.h = BLOCK_SIZE;
			wall.w = BLOCK_SIZE;
			if (map.map[y][x] != 0)
			{
				SDL_RenderFillRect(my_union.renderer, &wall);
			}
//			else
//			{
//				SDL_RenderDrawRect(my_union.renderer, &wall);
//			}
		}
	}
}

int 	check_wall(double cur_x, double cur_y, t_map map)
{
	if (map.map[(int)cur_y >> 5][(int)cur_x >> 5])
		return (1);
	return (0);
}

void	draw_line(t_union my_union, t_map map, double x1, double y1, double x2, double y2)
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
		if (check_wall(cur_x, cur_y, map))
			break;
		SDL_RenderDrawPoint(my_union.renderer, (int)cur_x, (int)cur_y);
		cur_x += increm_x;
		cur_y += increm_y;

	}
}
