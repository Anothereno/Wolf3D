/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:21:09 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/12 16:53:09 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ЗАГРУЖАЕТ ТЕКСТУРЫ В МАССИВ
void	load_textures(t_union *my_union)
{
	int i;

	i = -1;
	my_union->surface = SDL_LoadBMP("pics/WALL14.bmp");
	if (!my_union->surface)
		ft_putstr("Surface not loaded\n");
	my_union->hud = SDL_LoadBMP("pics/qwerty.bmp");
    if (!my_union->hud)
        ft_putstr("Surface not loaded\n");
	my_union->surface_array[0] = SDL_LoadBMP("pics/WALL77.bmp");
	my_union->surface_array[1] = SDL_LoadBMP("pics/WALL76.bmp");
	my_union->surface_array[2] = SDL_LoadBMP("pics/WALL21.bmp");
	my_union->surface_array[3] = SDL_LoadBMP("pics/WALL69.bmp");
	my_union->surface_array[4] = SDL_LoadBMP("pics/WALL69.bmp");
	my_union->surface_array[5] = SDL_LoadBMP("pics/WALL69.bmp");
	my_union->surface_array[6] = SDL_LoadBMP("pics/WALL18.bmp");
	my_union->surface_array[7] = SDL_LoadBMP("pics/WALL64.bmp");
	my_union->surface_array[8] = SDL_LoadBMP("pics/WALL98.bmp");
	my_union->surface_array[9] = SDL_LoadBMP("pics/WALL98.bmp");
	while (++i < 10)
		if (!my_union->surface_array[i])
			ft_putstr("Surface not loaded\n");
}
