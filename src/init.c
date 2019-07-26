/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:07:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/26 19:32:37 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//РАССЧИТЫВАЕТ СКОРОСТЬ ПЕРЕДВИЖЕНИЯ И ПОВОРОТА В ЗАВИСИМОСТИ ОТ ФРЭЙМРЭЙТА
void	change_speed(t_union *my_union, t_player *player)
{
	player->speed_move = my_union->time * 5.0;
	player->speed_rotate = my_union->time * 3.0;
}

//ИНИЦИАЛИЗИРУЕТ СДЛ ПЕРЕМЕННЫЕ
void	initialize_SDL(t_union *my_union)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("error\n");
		exit(0);
	}
	my_union->win = SDL_CreateWindow("Wolf3D",/*SDL_WINDOWPOS_CENTERED*/ 200, /*SDL_WINDOWPOS_CENTERED*/200, my_union->win_x, my_union->win_y, 0);
	my_union->renderer = SDL_CreateRenderer(my_union->win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	my_union->pixel_array = (Uint32*)malloc(sizeof(Uint32) * my_union->win_x * my_union->win_y);
	my_union->texture = SDL_CreateTexture(my_union->renderer,
										  SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
										  my_union->win_x, my_union->win_y);
	my_union->color = (SDL_Color*)malloc(sizeof(SDL_Color));
	my_union->surface_array = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 10);
}

//ИНИЦИАЛИЗИРУЕТ ПЕРЕМЕННЫЕ СТРУКТУРЫ
void	struct_initial(t_union *my_union, t_map *map, t_player *player, t_map *objects)
{
	my_union->win_x = 640;
	my_union->win_y = 480;
	my_union->half_win_y = my_union->win_y >> 1;
	my_union->half_win_x = my_union->win_x >> 1;
	my_union->door_timer_end = 0;
	my_union->sens = 0.3;
	my_union->mouse_x = my_union->half_win_x;
	my_union->mouse_y = my_union->half_win_y;
    player->player_heigth = 1;
    player->direct_x = 1;
    player->direct_y = 0;
    player->player_width = 1;
    player->radius = /*BLOCK_SIZE << 2;//200;//MAX(my_union->win_x, my_union->win_y)*/my_union->win_x * my_union->win_x;
    player->view_direction = 0;
    player->speed = BLOCK_SIZE >> 3;
    player->strafe_speed = (BLOCK_SIZE >> 4) + 1;
    player->planeX = 0;
    player->planeY = 0.66;
    player->dirX = 0;
    player->dirY = 0;
    player->move_indicate = 0;
    player->rotate_angle = 3;
    player->time = 0;
    player->oldTime = 0;
    player->fov = 60;
    player->half_fov = player->fov * 0.5;
    my_union->dist = my_union->win_x / (tan(player->half_fov) * 2) * -360;
    initialize_SDL(my_union);
    load_textures(my_union);
    my_union->hud_start = my_union->win_y - (my_union->hud_surface->h * (my_union->win_x / my_union->hud_surface->w));
    my_union->hud_rect.w = my_union->win_x;
    my_union->hud_rect.h = my_union->win_y / 6;
    my_union->hud_rect.x = 0;
    my_union->hud_rect.y = my_union->hud_start;
    my_union->hud_texture = SDL_CreateTextureFromSurface(my_union->renderer, my_union->hud_surface);

}

