/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers_game_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 18:45:55 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/01 18:58:35 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

void	zeroing_timers(t_union *my_union, t_player *player)
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
		zeroing_weapon_timer(my_union, player);
	if (my_union->start_tick - my_union->reload_timer > 600)
		my_union->reload_timer = 0;
	if (my_union->start_tick - my_union->weapon_down_timer > 600)
		my_union->weapon_down_timer = 0;
	if (my_union->start_tick - my_union->return_timer > 300)
		my_union->return_timer = 0;
}

void	calc_time_fps(t_union *my_union)
{
	my_union->end_tick = my_union->start_tick;
	my_union->start_tick = SDL_GetTicks();
	my_union->time = (my_union->start_tick - my_union->end_tick) * 0.001;
	my_union->FPS = 1.0f / my_union->time;
}

void	start_game(t_union my_union, t_map map, t_player player,
		t_map objects)
{
	t_ray		ray;

	my_union.go_to_menu = 0;
	my_union.key_game = SDL_GetKeyboardState(NULL);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (1)
	{
		SDL_PollEvent(&my_union.event);
		if (my_union.event.type == SDL_QUIT)
			break ;
		player.move_indicate = 0;
		if (my_union.go_to_menu)
			break ;
		check_event_game(&my_union, &map, &player, &objects);
		raycast(&my_union, &map, &player, &ray);
		calc_time_fps(&my_union);
		SDL_RenderPresent(my_union.renderer);
		zeroing_timers(&my_union, &player);
	}
}

void	main_loop(t_union my_union, t_map map, t_map objects, t_player player)
{
	while (1)
	{
		SDL_PollEvent(&my_union.event);
		if (my_union.event.type == SDL_QUIT)
			break ;
		check_event_menu(&my_union, &map, &player, &objects);
		if (my_union.menu_mode)
			show_menu(my_union);
		else
		{
			start_game(my_union, map, player, objects);
			my_union.menu_mode = 1;
			my_union.go_to_menu = 1;
			continue;
		}
		calc_time_fps(&my_union);
		print_fps(&my_union);
		SDL_RenderPresent(my_union.renderer);
		zeroing_timers(&my_union, &player);
	}
}
