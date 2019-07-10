/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:06:04 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/10 09:09:31 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ПОЛУЧАЕТ ЦВЕТ ПИКСЕЛЯ ИЗ СПРАЙТА
void	get_surface_pixel(t_union *my_union, int x, int y, SDL_Color *color, t_ray ray)
{
	Uint8		*pixel;

	x %= 64;
	y %= 64;
//	printf("%d, %d\n", x, y);
//	my_union->surface = get_surface(my_union, map);
	pixel = my_union->surface->pixels + y * my_union->surface->pitch;
	pixel += x * my_union->surface->format->BytesPerPixel;
	SDL_GetRGBA(*pixel, my_union->surface->format,
			&color->r, &color->g, &color->b, &color->a);
}

//УСТАНАВЛИВАЕТ ПИКСЕЛЬ В ЗАДАННЫЙ ЦВЕТ
void		put_pixel(t_union *my_union, int x, int y, SDL_Color *color)
{
	int shift;

	shift = y * my_union->win_x + x;
	my_union->pixel_array[shift] = (Uint32)((color->r << 16) +
			(color->g << 8) + color->b);
}

//ЗАКРАШИВАЕТ ПИКСЕЛЬ ЧЕРНЫМ ЦВЕТОМ (ДЛЯ ОЧИЩЕНИЯ ТЕКСТУРЫ)
void		put_black_pixel(t_union *my_union, int x, int y)
{
	int shift;

	shift = y * my_union->win_x + x;
	my_union->pixel_array[shift] = 0;
}

//ВЫБИРАЕТ САРФЭЙС ИЗ МАССИВА СПРАЙТОВ
void		choose_surface(t_union *my_union, t_ray ray, t_map map)
{
	int wall;

	wall = map.map[(int)ray.y >> 6][(int)ray.x >> 6];
	my_union->surface = my_union->surface_array[wall - ray.mode];
}

//ВЫБИРАЕТ САРФЭЙС ИЗ МАССИВА СПРАЙТОВ
void		choose_surface_floor_and_ceiling(t_union *my_union, char mode)
{
	if (mode =='c')
		my_union->surface = my_union->surface_array[0];
	else
		my_union->surface = my_union->surface_array[1];
}