/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:46:38 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/28 16:53:17 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

void	free_stat_hud_rects(t_union *my_union)
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

void	free_font(t_union *my_union)
{
	TTF_CloseFont(my_union->font);
}
