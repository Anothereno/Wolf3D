/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_surfaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 15:26:12 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/08 17:02:28 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_weapon(t_union *my_union, t_player *player, t_map *map)
{
	my_union->weapon_texture = SDL_CreateTextureFromSurface(my_union->renderer,
			my_union->weapons_surfaces[player->weapon][0]);
	SDL_RenderCopy(my_union->renderer, my_union->weapon_texture, NULL, &my_union->weapon_place);
	SDL_DestroyTexture(my_union->weapon_texture);
}