/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:06:04 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/05 17:33:30 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//void	set_pixel(t_union *my_union, int y, int x, int num)
//{
//	int point;
//
//	point = x * 4 + my_union->sl * y;
//	if (num != 0)
//	{
//		my_union->image_data[point] = 0;
//		my_union->image_data[point + 1] = 255;
//		my_union->image_data[point + 2] = 0;
//	}
//	else
//	{
//		my_union->image_data[point] = 255;
//		my_union->image_data[point + 1] = 255;
//		my_union->image_data[point + 2] = 255;
//	}
//}
//
//void	change_walls_color(t_union my_union, t_ray ray, t_player player)
//{
//	if (!ray.mode)
//		SDL_SetRenderDrawColor(my_union.renderer, 61, 64, 252, 255);
//	else
//		SDL_SetRenderDrawColor(my_union.renderer, 117, 34, 130, 255);
//}

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
	my_union->pixel_array[shift] = ((Uint32)((color->r << 16) +
			(color->g << 8) + color->b));
}

//ЗАКРАШИВАЕТ ПИКСЕЛЬ ЧЕРНЫМ ЦВЕТОМ (ДЛЯ ОЧИЩЕНИЯ ТЕКСТУРЫ)
void		put_black_pixel(t_union *my_union, int x, int y)
{
	int shift;

	shift = y * my_union->win_x + x;
	my_union->pixel_array[shift] = 0;
}