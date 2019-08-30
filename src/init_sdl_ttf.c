/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:07:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/30 15:17:09 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	initialize_sdl(t_union *my_union)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		msg("Erron in SDL_Init!\n");
	my_union->win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			my_union->cur_win_x, my_union->cur_win_y, 0);
	my_union->renderer = SDL_CreateRenderer(my_union->win, 0,
			SDL_RENDERER_SOFTWARE);
	my_union->pixel_array = (Uint32 *)malloc(
			sizeof(Uint32) * my_union->cur_win_x * my_union->cur_win_y);
	my_union->main_window_texture = SDL_CreateTexture(my_union->renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
			my_union->cur_win_x, my_union->cur_win_y);
	my_union->wall_surfaces_array = (SDL_Surface **)malloc(
			sizeof(SDL_Surface *) * 10);
	init_weapon_arrays(my_union);
}

void	initialize_ttf(t_union *my_union)
{
	if (TTF_Init() == -1)
	{
		ft_putstr("Unable to init SDL_TTF: %s");
		ft_putstr(TTF_GetError());
	}
	my_union->font = TTF_OpenFont("resources/fonts/ui_font.ttf", 16);
	if (my_union->font == NULL)
	{
		ft_putstr("Unable to load font: ");
		ft_putstr(TTF_GetError());
	}
	my_union->font_color.r = 255;
	my_union->font_color.g = 255;
	my_union->font_color.b = 255;
	my_union->font_color.a = 255;
}

void	init(t_union *my_union, t_map *map, t_player *player, t_map *objects)
{
	char *message;

	init_union(my_union);
	init_player(player);
	my_union->dist = my_union->cur_win_x / (tan(player->half_fov) * 2) * -360;
	initialize_sdl(my_union);
	if ((message = load_menu(my_union)) ||
		(message = load_wall_surfaces(my_union)) ||
		(message = load_weapons(my_union)) ||
		(message = load_hud(my_union)) ||
		(message = load_weapons_minimize(my_union)))
	{
		ft_putstr(message);
		complete_work(my_union, map, objects, player);
	}
	init_hud(my_union);
	change_weapon_rect(my_union);
	initialize_ttf(my_union);
}
