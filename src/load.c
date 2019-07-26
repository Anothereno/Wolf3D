/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:21:09 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/26 19:32:37 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ЗАГРУЖАЕТ ТЕКСТУРЫ В МАССИВ
void	load_textures(t_union *my_union)
{
	int         i;

	i = -1;
	my_union->surface = SDL_LoadBMP("resourses/WALL14.bmp");
	if (!my_union->surface)
		ft_putstr("Surface not loaded\n");
	my_union->hud_surface = SDL_LoadBMP("resourses/HUD.bmp");
	my_union->surface_array[0] = SDL_LoadBMP("resourses/WALL77.bmp");
	my_union->surface_array[1] = SDL_LoadBMP("resourses/WALL76.bmp");
	my_union->surface_array[2] = SDL_LoadBMP("resourses/WALL21.bmp");
	my_union->surface_array[3] = SDL_LoadBMP("resourses/WALL69.bmp");
	my_union->surface_array[4] = SDL_LoadBMP("resourses/WALL69.bmp");
	my_union->surface_array[5] = SDL_LoadBMP("resourses/WALL69.bmp");
	my_union->surface_array[6] = SDL_LoadBMP("resourses/WALL18.bmp");
	my_union->surface_array[7] = SDL_LoadBMP("resourses/WALL64.bmp");
	my_union->surface_array[8] = SDL_LoadBMP("resourses/WALL98.bmp");
	my_union->surface_array[9] = SDL_LoadBMP("resourses/WALL98.bmp");
	while (++i < 10)
		if (!my_union->surface_array[i])
			ft_putstr("Surface not loaded\n");
}
