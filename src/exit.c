/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:05:13 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	error_quit(char *msg, int i, t_map *map, t_map *objects)
{
	ft_putstr(msg);
	if (!i)
		exit(0);
	else if (i == 1)
		free_map_and_objects(map, objects);
}

void	free_menu(t_union *my_union)
{
	int i;

	i = 8;
	while (--i > -1)
		SDL_FreeSurface(my_union->menu_array[i]);
	free(my_union->menu_array);
}

void	free_inside_arrays(t_union *my_union)
{
	int i;
	int j;

	i = 3;
	while (--i > -1)
	{
		if (my_union->load_mark > 4 && my_union->weapons_mini_array[i])
			SDL_FreeSurface(my_union->weapons_mini_array[i]);
		j = 10;
		while (--j > -1)
		{
			if (i == 0 && j > 4)
				continue;
			if (my_union->load_mark > 2 && my_union->weapons_surfaces[i][j])
				SDL_FreeSurface(my_union->weapons_surfaces[i][j]);
		}
		free(my_union->weapons_surfaces[i]);
	}
}

void	free_sdl(t_union *my_union)
{
	int i;

	free(my_union->pixel_array);
	SDL_DestroyTexture(my_union->main_window_texture);
	i = 10;
	while (--i > -1)
		if (my_union->load_mark > 1 && my_union->wall_surfaces_array[i])
			SDL_FreeSurface(my_union->wall_surfaces_array[i]);
	free(my_union->wall_surfaces_array);
	free_inside_arrays(my_union);
	free(my_union->weapons_mini_array);
	free(my_union->weapons_surfaces);
	SDL_DestroyRenderer(my_union->renderer);
	SDL_DestroyWindow(my_union->win);
}

void	complete_work(t_union *my_union, t_map *map, t_map *objects,
		t_player *player)
{
	free_sdl(my_union);
	if (my_union->load_mark > 4)
		free_stat_hud_rects(my_union);
	free_player(player);
	free_map_and_objects(map, objects);
	free_font(my_union);
	free_menu(my_union);
	SDL_Quit();
	TTF_Quit();
	exit(0);
}
