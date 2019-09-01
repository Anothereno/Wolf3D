/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:22:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/01 18:50:37 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(int argc, char **argv)
{
	t_union		my_union;
	t_map		map;
	t_map		objects;
	t_player	player;

	my_union.start_tick = 0;
	if (argc == 2)
	{
		if (!val_set(argv[1], &map, &objects, &player))
			exit(0);
		init(&my_union, &map, &player, &objects);
		my_union.key_menu = SDL_GetKeyboardState(NULL);
		if (my_union.fullscreen_mode)
			SDL_SetWindowFullscreen(my_union.win, -1);
		main_loop(my_union, map, objects, player);
	}
	else
		usage();
	return (0);
}
