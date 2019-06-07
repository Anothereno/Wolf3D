/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:07:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/06 17:37:42 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	initialize_SDL(t_union *my_union)
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("error\n");
	my_union->win = SDL_CreateWindow("Wolf3D",/*SDL_WINDOWPOS_CENTERED*/ 200, /*SDL_WINDOWPOS_CENTERED*/200, my_union->win_x, my_union->win_y, 0);
	my_union->renderer = SDL_CreateRenderer(my_union->win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void	struct_initial(t_union *my_union, t_map *map, t_player *player)
{
	my_union->win_x = map->size_x * BLOCK_SIZE;
	my_union->win_y = map->size_y * BLOCK_SIZE;
	my_union->scale = 1;
	my_union->save_fdf = 0;
	my_union->shift_y = 0;
	my_union->half_win_x = my_union->win_x * 0.5;
	my_union->half_win_y = my_union->win_y * 0.5;
	player->player_pos_x = 100;
	player->player_pos_y = 100;
	player->player_heigth = BLOCK_SIZE >> 1;
	player->player_width = BLOCK_SIZE >> 1;
}

/*
void	create_fdf(t_map *my_union)
{
	int x;
	int y;

	my_union->file = fopen("fractol.fdf", "wt");
	my_union->save_fdf = 1;
	y = -1;
	while (++y < my_union->win_y)
	{
		x = -1;
		while (++x < my_union->win_x)
		{
			if (my_union->mode == 's')
				ship(my_union, x, y);
			else if (my_union->mode == 'j' || my_union->mode == 'f')
				julia(my_union, x, y);
			else if (my_union->mode == 'm')
				mandelbrot(my_union, x, y);
		}
		fprintf(my_union->file, "\n");
	}
	fclose(my_union->file);
	my_union->save_fdf = 0;
}*/
