/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:55:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/09 13:40:20 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ФАЙЛ ПОКА НЕ ИСПОЛЬЗУЕТСЯ

/*
int		exit_(t_map *my_union)
{
	mlx_destroy_image(my_union->mlx_ptr, my_union->image_ptr);
	mlx_destroy_window(my_union->mlx_ptr, my_union->win_ptr);
	exit(0);
}

void	max_plus(int key, t_map *my_union)
{
	if (key == 69)
		my_union->max_iter += 5;
	if (key == 78)
		my_union->max_iter -= 5;
	plot(my_union);
}

int		mouse_move(int x, int y, t_map *my_union)
{
	if (my_union->mode != 'f')
		return (0);
	else
	{
		my_union->cur_real = (double)x * 4 / my_union->win_x - 2.5;
		my_union->cur_imag = (double)y * 4 / my_union->win_y - 2.5;
		plot(my_union);
	}
	return (1);
}

int		mouse_press(int key, int x, int y, t_map *my_union)
{
	if (key == 1 && (my_union->mode == 'j' || my_union->mode == 'f'))
		change_mode(my_union);
	if (key == 5 || key == 4)
		zoom(key, my_union);
	return (x + y);
}

int		deal_key(int key, t_map *param)
{
	if (key == 53)
		exit_(param);
	if (key == 126 || key == 125)
		shift_y(key, param);
	if (key == 123 || key == 124)
		shift_x(key, param);
	if (key == 69 || key == 78)
		max_plus(key, param);
	if (key == 14)
		create_fdf(param);
	if (key == 8)
	{
		if (param->cross)
			param->cross = 0;
		else
			param->cross = 1;
		plot(param);
	}
	return (0);
}
*/