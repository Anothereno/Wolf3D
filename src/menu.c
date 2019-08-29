/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:56:51 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/28 19:25:26 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	show_menu(t_union my_union)
{
	my_union.main_window_texture = SDL_CreateTextureFromSurface(
			my_union.renderer, my_union.menu_array[my_union.menu_frame]);
	SDL_RenderCopy(my_union.renderer, my_union.main_window_texture,
			NULL, NULL);
	SDL_DestroyTexture(my_union.main_window_texture);
}

void	change_menu_choice(t_union *my_union, char mode)
{
	if (my_union->menu_mode && !my_union->menu_tick)
	{
		my_union->menu_tick = SDL_GetTicks();
		if (mode == 'u')
		{
			if (my_union->menu_frame == 0)
				my_union->menu_frame = 3;
			else
				my_union->menu_frame--;
		}
		else
		{
			if (my_union->menu_frame == 3)
				my_union->menu_frame = 0;
			else
				my_union->menu_frame++;
		}
	}
}

void	choice_menu(t_union *my_union)
{
	if (my_union->menu_frame == 0)
		my_union->menu_mode = 0;
	else if (my_union->menu_frame == 3)
		exit(0);
}
