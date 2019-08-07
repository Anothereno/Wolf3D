/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:56:51 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/07 16:36:38 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void show_menu(t_union my_union, t_map map, t_player player, t_map objects)
{
	my_union.texture = SDL_CreateTextureFromSurface(my_union.renderer,
			my_union.menu_array[my_union.menu_frame]);
	SDL_RenderCopy(my_union.renderer, my_union.texture, NULL, NULL);
	SDL_DestroyTexture(my_union.texture);
}