/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:22:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/08 19:16:34 by hdwarven         ###   ########.fr       */
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
	double		elapsedMS;
	Uint64		start;
	Uint64		end;

	start = 0;
	if (argc == 2)
	{
		if (!val_set(argv[1], &map))
			exit(0);
		struct_initial(&my_union, &map, &player);
		initialize_SDL(&my_union);
		key = SDL_GetKeyboardState(NULL);
		while (1)
		{
//			start = SDL_GetPerformanceCounter();
			SDL_PollEvent(&event);
			if(event.type == SDL_QUIT)
				break;
			check_event(&my_union, &map, &player, key);
			clear_window(my_union);
//			draw_scene(my_union, map);
//			draw_player(my_union, player, map);
			draw_rays(my_union, player, map);

//			end = SDL_GetPerformanceCounter();
//			end = SDL_GetTicks();
			end = start;
			start = SDL_GetTicks();
			my_union.time = (start - end) / 1000.0f;
			change_speed(&my_union, &player);
//			elapsedMS = (end - start) / /*(float)SDL_GetPerformanceFrequency() **/ 1000.0f;
			SDL_RenderPresent(my_union.renderer);
//			if (elapsedMS < 15.8)
//				SDL_Delay(floor(16.666f - elapsedMS));
			printf("FPS: %f\n", 1.0 / my_union.time/*"%f - FLOOR, %f ELAPSE\n", floor(16.666f - elapsedMS), elapsedMS*/);
		}
	}
	else
		usage();
	return (0);
}
