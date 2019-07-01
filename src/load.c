/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:21:09 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/01 19:27:03 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_texture(t_union *my_union)
{
	my_union->surface = SDL_LoadBMP("pics/WALL92.bmp");
	if (!my_union->surface)
		ft_putstr("Surface not loaded\n");
	printf("%d, %d\n", my_union->surface->w, my_union->surface->h);
}