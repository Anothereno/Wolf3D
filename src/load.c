/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:21:09 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/30 13:12:54 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_texture(t_union *my_union)
{
	SDL_Surface	*surface = IMG_Load("pics/purplestone.png");
	if (!surface)
		ft_putstr("Image not loaded\n");
	else
	{
		my_union->texture = SDL_CreateTextureFromSurface(my_union->renderer, surface);
		if (!my_union->texture)
			ft_putstr("Texture not created");
		SDL_FreeSurface(surface);
	}
}