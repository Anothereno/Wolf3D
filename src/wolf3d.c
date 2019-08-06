/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:22:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/06 15:26:49 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ВЫВОДИТ ЮЗЭДЖ
void	usage(void)
{
    ft_putstr("usage: ./wolf3d <argument>\n");
}

void    changing_key_states(t_union *my_union)
{
    if (my_union->start_tick - my_union->door_timer_end > 350)
        my_union->door_timer_end = 0;
    if (my_union->start_tick - my_union->rel_mouse_mode_timer > 350)
        my_union->rel_mouse_mode_timer = 0;
}

//ОСУЩЕСТВЛЯЕТ МЭЙН ЛУП
int		main(int argc, char **argv)
{
    t_union		my_union;
    t_map		map;
    t_map       objects;
    t_player	player;
    t_ray		ray;

    my_union.start_tick = 0;
    if (argc == 2)
    {
        if (!val_set(argv[1], &map, &objects, &player))
            exit(0);
        struct_initial(&my_union, &map, &player, &objects);
        my_union.key = SDL_GetKeyboardState(NULL);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        while (1) {

            SDL_PollEvent(&my_union.event);
            if (my_union.event.type == SDL_QUIT)
                break;
            player.move_indicate = 0;
            check_event(&my_union, &map, &player, &objects, my_union.key);
//			clear_window(my_union);
            take_vector_of_view(&player);
            raycast(my_union, map, player, ray);
//			draw_scene(my_union, map);
            my_union.end_tick = my_union.start_tick;
            my_union.start_tick = SDL_GetTicks();
            my_union.time = (my_union.start_tick - my_union.end_tick) * 0.001;
            change_speed(&my_union, &player);
            SDL_RenderPresent(my_union.renderer);
            changing_key_states(&my_union);
			printf("FPS: %f, Current PosX: %d, PosY: %d\n", 1.0 / my_union.time, (int)player.player_pos_x, (int)player.player_pos_y/*"%f - FLOOR, %f ELAPSE\n", floor(16.666f - elapsedMS), elapsedMS*/);
        }
    }
    else
        usage();
    return (0);
}
