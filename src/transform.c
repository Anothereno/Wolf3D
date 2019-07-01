/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 17:38:12 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/01 17:37:02 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
/*
void	change_mode(t_map *my_union)
{
	if (my_union->mode == 'f')
		my_union->mode = 'j';
	else
		my_union->mode = 'f';
	plot(my_union);
}

void	shift_y(int key, t_map *my_union)
{
	if (key == 126)
		my_union->shift_y -= 0.0008 * my_union->zoom_num / my_union->scale;
	if (key == 125)
		my_union->shift_y += 0.0008 * my_union->zoom_num / my_union->scale;
	plot(my_union);
}

void	shift_x(int key, t_map *my_union)
{
	if (key == 123)
		my_union->shift_x -= 0.0008 * my_union->zoom_num / my_union->scale;
	if (key == 124)
		my_union->shift_x += 0.0008 * my_union->zoom_num / my_union->scale;
	plot(my_union);
}

void	zoom(int key, t_map *my_union)
{
	double old;

	old = my_union->scale;
	if (key == 4 && my_union->zoom_num < 260)
	{
		my_union->scale *= pow(1.001, my_union->zoom_num + 1);
		if (my_union->scale < 0)
		{
			my_union->scale = old;
			return ;
		}
		if (my_union->zoom_num % 5 == 0)
			my_union->max_iter += 2;
		my_union->zoom_num++;
	}
	else if (key == 5 && my_union->zoom_num != 1)
	{
		my_union->scale /= pow(1.001, my_union->zoom_num + 1);
		if (my_union->zoom_num % 5 == 0)
			my_union->max_iter -= 2;
		my_union->zoom_num--;
	}
	plot(my_union);
}

void	put_cross(t_map *my_union)
{
	int i;

	i = 0;
	set_pixel(my_union, my_union->win_y / 2, my_union->win_x / 2,
		my_union->max_iter);
	while (++i < 10)
	{
		set_pixel(my_union, my_union->win_y / 2,
			my_union->win_x / 2 + i, my_union->max_iter);
		set_pixel(my_union, my_union->win_y / 2,
			my_union->win_x / 2 - i, my_union->max_iter);
		set_pixel(my_union, my_union->win_y / 2 + i,
			my_union->win_x / 2, my_union->max_iter);
		set_pixel(my_union, my_union->win_y / 2 - i,
			my_union->win_x / 2, my_union->max_iter);
	}
}
*/