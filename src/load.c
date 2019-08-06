/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:21:09 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/06 17:23:09 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ЗАГРУЖАЕТ ТЕКСТУРЫ В МАССИВ
void	load_wall_textures(t_union *my_union)
{
	int	i;

	i = -1;
	my_union->surface = SDL_LoadBMP("resources/pictures/WALLS/WALL14.bmp");
	if (!my_union->surface)
		ft_putstr("Surface not loaded\n");
	my_union->hud_surface = SDL_LoadBMP("resources/pictures/HUD/HUD.bmp");
	my_union->surface_array[0] = SDL_LoadBMP("resources/pictures/WALLS/WALL56.bmp");
	my_union->surface_array[1] = SDL_LoadBMP("resources/pictures/WALLS/WALL57.bmp");
	my_union->surface_array[2] = SDL_LoadBMP("resources/pictures/WALLS/WALL56.bmp");
	my_union->surface_array[3] = SDL_LoadBMP("resources/pictures/WALLS/WALL57.bmp");
	my_union->surface_array[4] = SDL_LoadBMP("resources/pictures/WALLS/WALL90.bmp");
	my_union->surface_array[5] = SDL_LoadBMP("resources/pictures/WALLS/WALL91.bmp");
	my_union->surface_array[6] = SDL_LoadBMP("resources/pictures/WALLS/WALL90.bmp");
	my_union->surface_array[7] = SDL_LoadBMP("resources/pictures/WALLS/WALL91.bmp");
	my_union->surface_array[8] = SDL_LoadBMP("resources/pictures/WALLS/WALL98.bmp");
	my_union->surface_array[9] = SDL_LoadBMP("resources/pictures/WALLS/WALL98.bmp");
	while (++i < 10)
		if (!my_union->surface_array[i])
			ft_putstr("Surface not loaded\n");
}

void	load_weapon_images(t_union *my_union)
{

}
