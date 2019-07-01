/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:06:04 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/01 17:41:51 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	set_pixel(t_union *my_union, int y, int x, int num)
{
	int point;

	point = x * 4 + my_union->sl * y;
	if (num != 0)
	{
		my_union->image_data[point] = 0;
		my_union->image_data[point + 1] = 255;
		my_union->image_data[point + 2] = 0;
	}
	else
	{
		my_union->image_data[point] = 255;
		my_union->image_data[point + 1] = 255;
		my_union->image_data[point + 2] = 255;
	}
}

void	change_walls_color(t_union my_union, t_ray ray, t_player player)
{
	if (!ray.mode)
		SDL_SetRenderDrawColor(my_union.renderer, 61, 64, 252, 255);
	else
		SDL_SetRenderDrawColor(my_union.renderer, 117, 34, 130, 255);
}

void	get_surface_pixel(t_union *my_union, int x, int y)
{
	Uint8		*pixel;

	x %= 64;
	y %= 64;
	pixel = my_union->surface->pixels + y * my_union->surface->pitch + x
			* my_union->surface->format->BytesPerPixel;
	SDL_GetRGB((Uint32)pixel, my_union->surface->format,
			&my_union->color.r, &my_union->color.g, &my_union->color.b);
}

void		put_pixel(t_union *my_union, int x, int y)
{
	int shift;

	shift = y * my_union->win_x + x;
	my_union->pixel_array[shift] = ((Uint32)((my_union->color.r << 16) +
			(my_union->color.g << 8) + my_union->color.b));
}

void		put_black_pixel(t_union *my_union, int x, int y)
{
	int shift;

	shift = y * my_union->win_x + x;
	my_union->pixel_array[shift] = (Uint32)0;
}

/*
void	pixel_fdf(t_map *my_union, int n)
{
	int		color_red;
	int		color_green;
	int		color_blue;
	char	color_string[9];

	color_string[0] = '0';
	color_string[1] = 'x';
	color_string[8] = '\0';
	color_blue = color_func(my_union->max_iter, my_union->scale * 0.0025);
	color_green = color_func(my_union->max_iter, n + my_union->scale * 0.0025);
	color_red = color_func(my_union->max_iter, 0.5 *
		n + my_union->scale * 0.0025);
	write2map(color_red, color_string, 2);
	write2map(color_green, color_string, 4);
	write2map(color_blue, color_string, 6);
	fprintf(my_union->file, "%d,%s ", n, color_string);
}
*/