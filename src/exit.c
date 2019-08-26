/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:05:13 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/26 17:47:13 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	error_quit(char *msg, int i, t_map *map, t_map *objects)
{
	ft_putstr(msg);
	if (!i) {
		exit(0);
	}
	else if (i == 1)
	{
		free_map_and_objects(map, objects);
	}
}

void	free_SDL(t_union *my_union)
{
	int i;
	int j;

	free(my_union->pixel_array);
	SDL_DestroyTexture(my_union->main_window_texture);
	i = 10;
	while (--i > -1)
		if (my_union->load_mark > 1 && my_union->wall_surfaces_array[i])
			SDL_FreeSurface(my_union->wall_surfaces_array[i]);
	free(my_union->wall_surfaces_array);
	i = 3;
	while (--i > -1)
	{
		if (my_union->load_mark > 4 && my_union->weapons_mini_array[i])
			SDL_FreeSurface(my_union->weapons_mini_array[i]);
		j = 10;
		while (--j > -1) {
			if (i == 0 && j > 4)
				continue;
			if (my_union->load_mark > 2 && my_union->weapons_surfaces[i][j])
				SDL_FreeSurface(my_union->weapons_surfaces[i][j]);
		}
		free(my_union->weapons_surfaces[i]);
	}
	free(my_union->weapons_mini_array);
	free(my_union->weapons_surfaces);
	SDL_DestroyRenderer(my_union->renderer);
	SDL_DestroyWindow(my_union->win);
}

void	free_map_and_objects(t_map *map, t_map *objects)
{
	while (--map->size_y > -1)
	{
		free(map->map[map->size_y]);
		free(objects->map[map->size_y]);
	}
	free(map->map);
	free(objects->map);
}

void	free_stat_HUD_rects(t_union *my_union)
{
	free(my_union->stat_rects);
	SDL_DestroyTexture(my_union->hud_texture);
}

void	free_player(t_player *player)
{
	free(player->ammo);
	free(player->clip);
	free(player->clip_volume);
}

void	complete_work(t_union *my_union, t_map *map, t_map *objects, t_player
*player)
{
	free_SDL(my_union);
	if (my_union->load_mark > 3)
		free_stat_HUD_rects(my_union);
	free_player(player);
	free_map_and_objects(map, objects);

	SDL_Quit();
	exit(0);
}