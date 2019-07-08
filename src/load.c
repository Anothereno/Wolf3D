/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:21:09 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/08 13:50:31 by hdwarven         ###   ########.fr       */
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
	my_union->surface_array[0] = SDL_LoadBMP("pics/WALL20.bmp");
	my_union->surface_array[1] = SDL_LoadBMP("pics/WALL12.bmp");
	my_union->surface_array[2] = SDL_LoadBMP("pics/WALL24.bmp");
	my_union->surface_array[3] = SDL_LoadBMP("pics/WALL46.bmp");
	my_union->surface_array[4] = SDL_LoadBMP("pics/WALL69.bmp");
	my_union->surface_array[5] = SDL_LoadBMP("pics/WALL38.bmp");
	my_union->surface_array[6] = SDL_LoadBMP("pics/WALL18.bmp");
	my_union->surface_array[7] = SDL_LoadBMP("pics/WALL64.bmp");
	my_union->surface_array[8] = SDL_LoadBMP("pics/WALL54.bmp");
	my_union->surface_array[9] = SDL_LoadBMP("pics/WALL36.bmp");
	while (++i < 10)
		if (!my_union->surface_array[i])
			ft_putstr("Surface not loaded\n");
}
