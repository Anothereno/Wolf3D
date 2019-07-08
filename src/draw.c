/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:50:14 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/08 19:52:02 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ПОЛУЧАЕТ НАПРАВЛЕНИЕ ВЗГЛЯДА
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

//РАССЧИТЫВАЕТ ВЫСОТУ СТЕНЫ И КОРРЕКТИРУЕТ РЫБИЙ ГЛАЗ
void	calc_line(t_union *my_union, t_ray ray, double betta)
{
	ray.res_distance = ray.res_distance * cos(betta);
	my_union->wall_heigth = (BLOCK_SIZE << (int)(my_union->win_x / 640)) / ray.res_distance * 277;
	my_union->start = -my_union->wall_heigth / 2 + my_union->win_y / 2;
	if (my_union->start < 0)
		my_union->start = 0;
	my_union->end = my_union->wall_heigth / 2 + my_union->win_y / 2;
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

//ВЫБИРАЕТ ПРАИВЛЬНЫЙ ЛУЧ ПО КРАТЧАЙШЕЙ ДИСТАНЦИИ
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

//ЗАКОЛЬЦОВЫВАЕТ УГОЛ В РЭНДЖЕ [0 : 360] ГРАДУСОВ
double take_range_angle(double angle)
{
	if (angle < 0)
		angle = (360 + angle);
	if (angle >= 360)
		angle = (angle - 360);
	return angle;

}

//ОЧИЩАЕТ ТЕКСТУРУ
void	clear_texture(t_union *my_union)
{
	int i;
	int j;

	i = -1;
	while (++i < my_union->win_y)
	{
		j = -1;
		while (++j < my_union->win_x)
			put_black_pixel(my_union, j, i);
	}
	SDL_UpdateTexture(my_union->texture, NULL, my_union->pixel_array, my_union->win_x * sizeof(Uint32));
	SDL_RenderCopy(my_union->renderer, my_union->texture, NULL, NULL);

}

//ВОЗВРАЩАЕТ ВЕРТИКАЛЬНУЮ ЛИНИЮ ДЛЯ ОТРИСОВКИ СПРАЙТА В ЗАВИСИМОСТИ ОТ ГОР/ВЕРТ СТОЛКНОВЕНИЯ
int	take_textures_offset(t_ray ray)
{
	if (!ray.mode)
		return ((int)ray.x % BLOCK_SIZE);
	else
		return ((int)ray.y % BLOCK_SIZE);
}

//ПРОВОДИТ РЭЙКАСТ
void	raycast(t_union my_union, t_map map, t_player player, t_ray ray)
{
	int		x;
	double	center_x;
	double	angle;
	double 	one_angle;
	double 	begin_angle;
	double	center_y;

	x = -1;
	clear_texture(&my_union);
//	center_x = player.player_pos_x + (player.player_width >> 1);
//	center_y = player.player_pos_y + (player.player_heigth >> 1);
	one_angle = player.fov / my_union.win_x;
	begin_angle = (player.view_direction - (player.fov / 2));
	angle = begin_angle;
	while (++x < my_union.win_x) {
		my_union.flag = 0;
		angle = take_range_angle(angle);
		hor_distance(&my_union, player, map, &ray, angle * RAD);
		vert_distance(&my_union, player, map, &ray, angle * RAD);
		choose_distance(&ray);
		calc_line(&my_union, ray, angle * RAD - player.view_direction * RAD);
//		change_walls_color(my_union, ray, player);
		ray.offset = take_textures_offset(ray);
		choose_surface(&my_union, ray, map);
		draw_line(&my_union, ray, x, map);
		draw_floor(my_union, ray, x, map, angle * RAD, player);
//		draw_floor(my_union, ray, x, map, angle * RAD);
//		draw_ceiling_and_floor(my_union);
//		draw_line(my_union, ray, x, my_union.start, my_union.end);
//		SDL_SetRenderDrawColor(my_union.renderer, 155, 155, 155, 255);
//		draw_vert_line(my_union, (int)i, (int)my_union.start, (int)my_union.end); //Отрисовка вертикальных линий ДДА
//		SDL_RenderDrawLine(my_union.renderer, x, my_union.start, x, my_union.end); // Отрисовка линий СДЛ
//		SDL_SetRenderDrawColor(my_union.renderer, 244, 244, 66, 255);
//		SDL_RenderDrawLine(my_union.renderer, (int) center_x >> 2, (int)center_y >> 2, (int)ray.x >> 2, (int)ray.y >> 2);
		angle += one_angle;
	}
	SDL_UpdateTexture(my_union.texture, NULL, my_union.pixel_array, my_union.win_x * sizeof(Uint32));
	SDL_RenderCopy(my_union.renderer, my_union.texture, NULL, NULL);
}

void	draw_floor(t_union my_union, t_ray ray, int x, t_map map, double angle, t_player player)
{
	double		dist;
	double 		cur_dist;
	int			y;
	SDL_Color	color;
	double		cur_x;
	double		cur_y;

	y = my_union.end;
	dist = (my_union.win_x / (tan(player.fov / 2) * 2));
	while (++y < my_union.win_y) {
		cur_dist = dist * -360 / (y - my_union.win_y / 2);
		cur_x = (cur_dist * cos(angle) + player.player_pos_x);
		cur_y = (cur_dist * sin(angle) + player.player_pos_y);
		choose_surface_floor_and_ceiling(&my_union, 'f');
//		printf("%f, %f\n", cur_x, cur_y);
		get_surface_pixel(&my_union, cur_x, cur_y, &color, ray);
		if (check_bound(x, y, map))
			put_pixel(&my_union, x, y, &color);
		choose_surface_floor_and_ceiling(&my_union, 'c');
		get_surface_pixel(&my_union, (int)cur_x, (int)(cur_y), &color, ray);
		if (check_bound(x, my_union.win_y - y, map))
			put_pixel(&my_union, x, my_union.win_y - y, &color);
	}
}

//void	draw_floor(t_union my_union, t_ray ray, int x, t_map map, double angle)
//{
//	int			cur_dist;
//	double		weight;
//	int			y;
//	SDL_Color	color;
//	double		cur_x;
//	double		cur_y;
//
//	y = my_union.end;
//	while (++y < my_union.win_y) {
//		cur_dist = my_union.win_y / (2 * y - my_union.win_y);
//		weight = cur_dist / ray.res_distance;
////		cur_x = (weight *
//		cur_x = x * cos(angle);
//		cur_y = y * sin(angle);
//		choose_surface_floor_and_ceiling(&my_union, 'f');
//		get_surface_pixel(&my_union, cur_x, cur_y, &color, ray);
//		if (check_bound(x, y, map))
//			put_pixel(&my_union, x, y, &color);
//		choose_surface_floor_and_ceiling(&my_union, 'c');
//		get_surface_pixel(&my_union, x, my_union.win_y - y, &color, ray);
//		if (check_bound(x, my_union.win_y - y, map))
//			put_pixel(&my_union, x, my_union.win_y - y, &color);
//	}
//}

//ОТРИСОВЫВАЕТ ПОЛ И ПОТОЛОК
void	draw_ceiling_and_floor(t_union my_union)
{
	SDL_Rect rect;

	rect.x = 0;
	rect.y = my_union.win_y / 2;
	rect.w = my_union.win_x;
	rect.h = rect.y;

	SDL_SetRenderDrawColor(my_union.renderer, 45, 161, 53, 255);
	SDL_RenderFillRect(my_union.renderer, &rect);
}

//ВОЗВРАЩАЕТ РАЗНИЦУ МЕЖДУ РЕАЛЬНОЙ СТЕНОЙ И ОТРИСОВАННОЙ (ЕСЛИ СТЕНА БОЛЬШЕ, ЧЕМ win_y)
int 	get_start_draw(t_union my_union)
{
	if (my_union.wall_heigth >= my_union.win_y)
		return (my_union.wall_heigth / 2 - my_union.win_y / 2);
	return 0;
}

//ОТРИСОВЫВАЕТ ВЕРТИКАЛЬНУЮ СТОЛБЕЦ СПРАЙТА
void	draw_line(t_union *my_union, t_ray ray, int x, t_map map)
{
	int			start;
	int			y;
	double		wall_scale;
	SDL_Color	color;

	start = my_union->start - 1;
	y = get_start_draw(*my_union);
	wall_scale = (float)BLOCK_SIZE / my_union->wall_heigth;;
	while (++start < my_union->end)
	{
		get_surface_pixel(my_union, ray.offset, y * wall_scale, &color, ray);
		if (check_bound(x, start, map))
			put_pixel(my_union, x, start, &color);
		y++;
	}
}

//ОТРИСОВЫВАЕТ МИНИКАРТУ
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

//ПРОВЕРЯЕТ СТОЛКНОВЕНИЕ ПО КООРДИНАТАМ
int 	check_wall(double cur_x, double cur_y, t_map map)
{
	if (cur_x >= map.size_x * BLOCK_SIZE || cur_x < 0 ||
			cur_y >= map.size_y * BLOCK_SIZE || cur_y < 0 ||
			map.map[(int)cur_y >> 6][(int)cur_x >> 6])
		return (1);
	return (0);
}

//ПРОВЕРЯЕТ, ЧТО ПЕРЕДАННЫЕ Х И У НАХОДЯТСЯ В ПРЕДЕЛАХ КАРТЫ
int 	check_bound(double	x, double y, t_map map)
{
	if (x < 0 || x > map.size_x * BLOCK_SIZE || y < 0 || y > map.size_y * BLOCK_SIZE)
		return (0);
	return (1);
}

//ДДА ДЛЯ ВЕРТИКАЛЬНОЙ ЧЕРТЫ
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

//РАССЧИТЫВАЕТ ГОРИЗОНТАЛЬНОЕ ПЕРЕСЕЧЕНИЕ СО СТЕНОЙ
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

//РАССЧИТЫВАЕТ ВЕРТИКАЛЬНОЕ ПЕРЕСЕЧЕНИЕ СО СТЕНОЙ
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

//БУДЕТ ВЫВОДИТЬ ПЕРЕКРЕСТЬЕ ПРИЦЕЛА))
//void	put_cross(t_map *my_union)
//{
//	int i;
//
//	i = 0;
//	set_pixel(my_union, my_union->win_y / 2, my_union->win_x / 2,
//			  my_union->max_iter);
//	while (++i < 10)
//	{
//		set_pixel(my_union, my_union->win_y / 2,
//				  my_union->win_x / 2 + i, my_union->max_iter);
//		set_pixel(my_union, my_union->win_y / 2,
//				  my_union->win_x / 2 - i, my_union->max_iter);
//		set_pixel(my_union, my_union->win_y / 2 + i,
//				  my_union->win_x / 2, my_union->max_iter);
//		set_pixel(my_union, my_union->win_y / 2 - i,
//				  my_union->win_x / 2, my_union->max_iter);
//	}
//}