/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:22:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/26 16:21:30 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ВЫВОДИТ ЮЗЭДЖ
void	usage(void)
{
    ft_putstr("usage: ./wolf3d <argument>\n");
}

void	zeroing_weapon_timer(t_union *my_union, t_player *player)
{
	if (player->weapon == 1 && my_union->start_tick -
			my_union->shoot_timer > 150)
		my_union->shoot_timer = 0;
	else if (player->weapon == 2 && my_union->start_tick -
			my_union->shoot_timer > 70)
		my_union->shoot_timer = 0;
	else if (player->weapon == 0 && my_union->start_tick -
			my_union->shoot_timer > 200)
		my_union->shoot_timer = 0;
}

//СБРАСЫВВАЕТ ЗАДЕРЖКИ
void    zeroing_timers(t_union *my_union, t_player *player)
{
    if (my_union->start_tick - my_union->door_timer_end > 350)
        my_union->door_timer_end = 0;
    if (my_union->start_tick - my_union->rel_mouse_mode_timer > 350)
        my_union->rel_mouse_mode_timer = 0;
    if (my_union->start_tick - my_union->menu_tick > 150)
        my_union->menu_tick = 0;
	if (my_union->start_tick - my_union->escape_timer > 350)
		my_union->escape_timer = 0;
	if (my_union->shoot_timer)
		zeroing_weapon_timer(my_union,player);
	if (my_union->start_tick - my_union->reload_timer > 600)
		my_union->reload_timer = 0;
	if (my_union->start_tick - my_union->weapon_down_timer > 600)
		my_union->weapon_down_timer = 0;
}

//РАСЧИТВАЕТ ФПС
void	calc_time_FPS(t_union *my_union)
{
	my_union->end_tick = my_union->start_tick;
	my_union->start_tick = SDL_GetTicks();
	my_union->time = (my_union->start_tick - my_union->end_tick) * 0.001;
	my_union->FPS = 1.0 / my_union->time;
}

//ЗАПУСКАЕТ ГЕЙМ ЛУП
void 	start_game(t_union my_union, t_map map, t_player player, t_map objects) {
	t_ray		ray;
	my_union.go_to_menu = 0;
	my_union.key_game = SDL_GetKeyboardState(NULL);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (1) {

		SDL_PollEvent(&my_union.event);
		if (my_union.event.type == SDL_QUIT)
			break;
		player.move_indicate = 0;
		check_event_game(&my_union, &map, &player, &objects, my_union.key_game);
		if (my_union.go_to_menu)
			break;
		take_vector_of_view(&player);
		raycast(&my_union, &map, &player, &ray);
//			draw_scene(my_union, map);
		calc_time_FPS(&my_union);
		change_speed(&my_union, &player);
		SDL_RenderPresent(my_union.renderer);
		zeroing_timers(&my_union, &player);
	}

}

int		main(int argc, char **argv)
{
	t_union		my_union;
	t_map		map;
	t_map       objects;
	t_player	player;
//	getchar(); ДЛЯ ДЕБАГА
	my_union.start_tick = 0;
	if (argc == 2)
	{
		if (!val_set(argv[1], &map, &objects, &player))
			exit(0);
		init(&my_union, &map, &player, &objects);
		my_union.key_menu = SDL_GetKeyboardState(NULL);
		while (1) {
			SDL_PollEvent(&my_union.event);
			if (my_union.event.type == SDL_QUIT)
				break;
			check_event_menu(&my_union, &map, &player, &objects, my_union.key_menu);
			if (my_union.menu_mode)
				show_menu(my_union);
			else
			{
				start_game(my_union, map, player, objects);
				my_union.menu_mode = 1;
				my_union.go_to_menu = 1;
				continue;
			}
			calc_time_FPS(&my_union);
			print_FPS(&my_union);
			SDL_RenderPresent(my_union.renderer);
			zeroing_timers(&my_union, &player);
		}
	}
	else
		usage();
	return (0);
}

