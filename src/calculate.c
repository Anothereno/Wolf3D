/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:42:02 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/01 17:41:51 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	plot(t_union *my_union, t_map *map)
{
	int x;
	int y;
	SDL_Rect rect;
	int i;
	int j;

	j = -1;
	while (++j < map->size_y)
	{
//		y = -1;
//		while (++y < BLOCK_SIZE)
//		{
			i = -1;
			while (++i < map->size_x)
			{

			}
//				x = -1;
//				while (++x < BLOCK_SIZE)
//				{
//					if (map->map[j][i] == 0)
//						set_pixel(my_union, y, x, map->map[j][i]);
//				}
//				printf("map[%d][%d] = %d\n", j, i, map->map[j][i]);
//			}
//		}
	}
//	mlx_put_image_to_window(my_union->mlx_ptr,
//				my_union->win_ptr, my_union->image_ptr, 0, 0);
}
