/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:06:04 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/12 18:08:42 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ПОЛУЧАЕТ ЦВЕТ ПИКСЕЛЯ ИЗ СПРАЙТА
void get_surface_pixel(t_union *my_union, int x, int y, SDL_Color *color)
{
	Uint8		*pixel;

	pixel = my_union->surface->pixels + y * my_union->surface->pitch;
	pixel += x * my_union->surface->format->BytesPerPixel;
	SDL_GetRGB(*pixel, my_union->surface->format,
			&color->r, &color->g, &color->b);
}

//ПРОВЕРЯЕТ ПИКСЕЛЬ НА ФИОЛЕТОВЫЙ ЦВЕТ
int 		check_invisible_pixels(SDL_Color *color)
{
//	printf("r = %d, g = %d, b = %d\n", color->r, color->g, color->b);
	if ((color->r >= 130 && color->r <= 160) &&
			(color->g >= 0 && color->g <= 35) &&
			(color->b >= 125 && color->b <= 140))
		return (1);
	return (0);
}

//УСТАНАВЛИВАЕТ ПИКСЕЛЬ В ЗАДАННЫЙ ЦВЕТ
void		put_pixel(t_union *my_union, int x, int y, SDL_Color *color)
{
	int shift;


	shift = y * my_union->win_x + x;
	my_union->pixel_array[shift] = (Uint32) ((color->r << 16) +
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
void		choose_surface_wall(t_union *my_union, t_ray ray, t_map map)
{
	int wall;

	wall = map.map[(int)ray.y >> 6][(int)ray.x >> 6];
	my_union->surface = my_union->surface_array[wall - ray.mode];
}

//ВЫБИРАЕТ САРФЭЙС ИЗ МАССИВА СПРАЙТОВ
void		choose_surface_floor_ceiling_hud(t_union *my_union, char mode)
{
	if (mode =='c')
		my_union->surface = my_union->surface_array[7];
	else if (mode == 'h')
	    my_union->surface = my_union->hud_surface;
	else
		my_union->surface = my_union->surface_array[6];
}