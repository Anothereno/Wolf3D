/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:07:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/11 19:37:11 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	change_speed(t_union *my_union, t_player *player)
{
	player->speed_move = my_union->time * 5.0;
	player->speed_rotate = my_union->time * 3.0;
}

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
	my_union->win_x = 640;
	my_union->win_y = 480;
	my_union->save_fdf = 0;
//	player->player_pos_x = 3;
//	player->player_pos_y = 3;
	player->player_pos_x = 3 * BLOCK_SIZE;
	player->player_pos_y = 5 * BLOCK_SIZE;
	player->player_heigth = 1;
	player->player_width = 1;
	player->radius = BLOCK_SIZE * 4;//200;//MAX(my_union->win_x, my_union->win_y);
	player->degree = 45;
	player->step_length = BLOCK_SIZE >> 4;
	player->planeX = 0;
	player->planeY = 0.66;
	player->dirX = -1;
	player->dirY = 0;
	player->time = 0;
	player->oldTime = 0;
	player->fov = 60;
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
