/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:50:14 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/20 11:58:21 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	take_vector_of_view(t_player *player)
{
	double last_x;

	last_x = player->direct_x;
	player->direct_x = player->direct_x * cos(player->view_direction_rad) - player->direct_y *
			sin(player->view_direction_rad);
	player->direct_y = last_x * sin(player->view_direction_rad) +
			player->direct_y * sin(player->view_direction_rad);
}

void	calc_line(t_union *my_union, t_ray ray, double betta)
{
	ray.res_distance = ray.res_distance * cos(betta);
	my_union->wall_heigth = (BLOCK_SIZE << (int)(my_union->win_x / 640)) / ray.res_distance * 277;
	my_union->start = -my_union->wall_heigth / 2 + my_union->half_win_y;
	if (my_union->start < 0)
		my_union->start = 0;
	my_union->end = my_union->wall_heigth / 2 + my_union->half_win_y;
	if (my_union->end >= my_union->win_y)
		my_union->end = my_union->win_y - 1;
}

void	choose_distance(t_ray *ray) {
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

double take_range_angle(double angle)
{
	if (angle < 0)
		angle = (360 + angle);
	if (angle >= 360)
		angle = (angle - 360);
	return angle;

}

int	take_textures_offset(t_ray ray)
{
	if (!ray.mode)
		return ((int)ray.x % BLOCK_SIZE);
	else
		return ((int)ray.y % BLOCK_SIZE);
}

void    draw_hud(t_union *my_union, t_player *player, t_map *map)
{
    SDL_RenderCopy(my_union->renderer, my_union->hud_texture, NULL, &my_union->hud_rect);
    show_stats(my_union, map, player);
}

void	raycast(t_union *my_union, t_map *map, t_player *player, t_ray *ray)
{
	int		x;
	double	angle_rad;
	double	angle;
	double 	one_angle;
	double 	begin_angle;

	x = -1;
	one_angle = player->fov / my_union->win_x;
	begin_angle = (player->view_direction - player->half_fov);
	angle = begin_angle;
	my_union->weapon_plce.cur_x = 0;
	while (++x < my_union->win_x) {
		my_union->flag = 0;
        angle = take_range_angle(angle);
        angle_rad = angle * RAD;
        hor_distance(my_union, *player, *map, ray, angle_rad);
        vert_distance(my_union, *player, *map, ray, angle_rad);
        choose_distance(ray);
        calc_line(my_union, *ray, angle_rad - player->view_direction * RAD);
        ray->offset = take_textures_offset(*ray);
		draw_line_in_window(my_union, *ray, x, *map, *player, angle_rad);
		angle += one_angle;
	}
	put_cross(my_union, player);
    SDL_UpdateTexture(my_union->main_window_texture, NULL, my_union->pixel_array, my_union->win_x * sizeof(Uint32));
    SDL_RenderCopy(my_union->renderer, my_union->main_window_texture, NULL, NULL);
	draw_weapon(my_union, player, map);
	draw_hud(my_union, player, map);
}

int 	get_start_draw(t_union my_union)
{
	if (my_union.wall_heigth >= my_union.win_y)
		return (my_union.wall_heigth / 2 - my_union.half_win_y);
	return 0;
}

void	draw_line_in_window(t_union *my_union, t_ray ray, int x, t_map map, t_player player, double angle)
{
    int			start;
    int			y;
    int         it;
    int 		diff;
    double		wall_scale;
    double      hud_scale_width;
    double      cur_dist;
    int			cur_x;
	int			cur_y;
    double      dist;
    double      cos_angle;
    double      sin_angle;
    SDL_Color	color;

    cos_angle = cos(angle);
    sin_angle = sin(angle);
    start = 0;
    y = get_start_draw(*my_union);
    wall_scale = (float)BLOCK_SIZE / my_union->wall_heigth;
    dist = my_union->dist / cos(angle - player.view_direction * RAD);
    while (++start < my_union->win_y)
    {
        if (start >= my_union->start && start < my_union->end)
        {
            if (start > my_union->hud_start)
				continue;
			choose_surface_wall(my_union, ray, map);
			get_surface_pixel(my_union, ray.offset, y * wall_scale, &color);
            y++;
			put_pixel(my_union, x, start, &color);
        }
        else if (start > my_union->start)
        {
            cur_dist = dist / (start - my_union->half_win_y);
            cur_x = (int)(cur_dist * cos_angle + player.player_pos_x) % 64;
            cur_y = (int)(cur_dist * sin_angle + player.player_pos_y) % 64;
            if (start < my_union->hud_start) {
                choose_surface_floor_ceiling_hud(my_union, 'f');
                get_surface_pixel(my_union, cur_x, cur_y, &color);
                    put_pixel(my_union, x, start, &color);
            }
            diff = my_union->win_y - start;
            choose_surface_floor_ceiling_hud(my_union, 'c');
            get_surface_pixel(my_union, cur_x, cur_y, &color);
            put_pixel(my_union, x, diff, &color);
        }
	}
}

int 	check_wall(double cur_x, double cur_y, t_map map)
{
	if (cur_x >= map.size_x << 6 || cur_x < 0 ||
			cur_y >= map.size_y << 6 || cur_y < 0 ||
			map.map[(int)cur_y >> 6][(int)cur_x >> 6])
		return (1);
	return (0);
}

int 	check_bound(double	x, double y, t_map map)
{
	if (x < 0 || x > map.size_x << 6 || y < 0 || y > map.size_y << 6)
		return (0);
	return (1);
}

void	hor_distance(t_union *my_union, t_player player, t_map map, t_ray *ray, double alpha)
{
	double	first_intersect_y;
	double	first_intersect_x;
	double 	step_y;
	double 	step_x;
	double 	cur_point_x;
	double 	cur_point_y;
	double  sin_alpha;

	sin_alpha = sin(alpha);
	if (sin_alpha < 0)
    {
        first_intersect_y = ((int)player.player_pos_y & 0xffc0) - 0.001;
        step_y = -BLOCK_SIZE;
    }
	else if (sin_alpha > 0)
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
	ray->hor_distance = fabs((player.player_pos_y - cur_point_y) / sin_alpha);
}

//РАССЧИТЫВАЕТ ВЕРТИКАЛЬНОЕ ПЕРЕСЕЧЕНИЕ СО СТЕНОЙ
void	vert_distance(t_union *my_union, t_player player, t_map map, t_ray *ray, double alpha)
{
	double	first_intersect_y;
	double	first_intersect_x;
	double 	step_y;
	double 	step_x;
	double 	cur_point_x;
	double 	cur_point_y;
	double  cos_alpha;

	cos_alpha = cos(alpha);
	if (cos_alpha < 0)
	{
		first_intersect_x = ((int)player.player_pos_x & 0xffc0) - 0.001;
		step_x = -BLOCK_SIZE;
	}
	else if (cos_alpha > 0)
	{
		first_intersect_x = ((int)player.player_pos_x & 0xffc0) + 64.001;
		step_x = BLOCK_SIZE;
	}
	else
	{
		ray->vert_distance = 99999;
		return;
	}
	first_intersect_y = player.player_pos_y + (first_intersect_x
			- player.player_pos_x) * tan(alpha);
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
	ray->vert_distance = fabs((player.player_pos_x - cur_point_x) / cos_alpha);
}

void	put_cross(t_union *my_union, t_player *player)
{
	int         i;

	i = 3 + player->move_indicate;
	while (++i < 10 + player->move_indicate)
	{
        my_union->pixel_array[my_union->half_win_y *
        my_union->win_x + my_union->half_win_x + i] = 0xFFFFFF;
        my_union->pixel_array[my_union->half_win_y *
        my_union->win_x + my_union->half_win_x - i] = 0xFFFFFF;
        my_union->pixel_array[(my_union->half_win_y + i) *
        my_union->win_x + my_union->half_win_x] = 0xFFFFFF;
        my_union->pixel_array[(my_union->half_win_y - i) *
        my_union->win_x + my_union->half_win_x] = 0xFFFFFF;
	}
}

