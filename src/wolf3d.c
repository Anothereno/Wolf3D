/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:22:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/07 13:53:48 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	usage(void)
{
	ft_putstr("usage: ./wolf3d <argument>\n");
}

int		main(int argc, char **argv)
{
	t_union		my_union;
	t_map		map;
	t_player	player;
	SDL_Event	event;
	const Uint8	*key;
	float		elapsedMS;
	Uint64		start;
	Uint64		end;

	if (argc == 2)
	{
		if (!val_set(argv[1], &map))
			exit(0);
		struct_initial(&my_union, &map, &player);
		initialize_SDL(&my_union);
		key = SDL_GetKeyboardState(NULL);
		while (1)
		{
			SDL_PollEvent(&event);
			if(event.type == SDL_QUIT)
				break;
			check_event(&my_union, &map, &player, key);
			start = SDL_GetPerformanceCounter();
			clear_window(my_union);
			draw_scene(my_union, map);
			draw_player(my_union, player);
			SDL_RenderPresent(my_union.renderer);
			end = SDL_GetPerformanceCounter();
			elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
//			SDL_Delay(floor(16.666f - elapsedMS));
		}
	}
	else
		usage();
	return (0);
}
