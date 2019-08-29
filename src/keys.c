/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:27:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/29 18:24:11 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	mouse_relative_handling(t_union *my_union, t_player *player)
{
	int x;
	int y;

	SDL_GetRelativeMouseState(&x, &y);
	if (x)
	{
		player->view_direction += (x * my_union->sens * my_union->time);
		player->view_direction_rad = player->view_direction * RAD;
		my_union->mouse_x = x;
	}
}

void	check_event_menu(t_union *my_union, t_map *map, t_player *player,
	t_map *objects)
{
	if (my_union->menu_mode && my_union->key_menu[SDL_SCANCODE_RETURN])
		choice_menu(my_union);
	if (my_union->key_menu[SDL_SCANCODE_UP])
		change_menu_choice(my_union, 'u');
	if (my_union->key_menu[SDL_SCANCODE_DOWN])
		change_menu_choice(my_union, 'd');
	if (my_union->key_menu[SDL_SCANCODE_ESCAPE])
	{
		if (!my_union->escape_timer)
		{
			my_union->escape_timer = SDL_GetTicks();
			if (!my_union->go_to_menu && my_union->menu_mode)
				complete_work(my_union, map, objects, player);
			my_union->go_to_menu = 0;
		}
	}
	if (my_union->fullscreen_mode && my_union->key_menu[SDL_SCANCODE_BACKSPACE])
	{
		SDL_SetWindowFullscreen(my_union->win,0);
		SDL_RestoreWindow(my_union->win);
		SDL_SetWindowSize(my_union->win, my_union->cur_win_x, my_union->cur_win_y);
		SDL_SetWindowPosition(my_union->win, SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED);
		my_union->fullscreen_mode = 0;
		change_hud_rect(my_union);
	}
	if (!my_union->fullscreen_mode && my_union->key_menu[SDL_SCANCODE_BACKSPACE])
	{
		SDL_SetWindowFullscreen(my_union->win,-1);
		my_union->fullscreen_mode = 1;
		change_hud_rect(my_union);
	}
}

void	check_event_game(t_union *my_union, t_map *map, t_player *player,
	t_map *objects)
{
	if (my_union->fullscreen_mode && my_union->key_game[SDL_SCANCODE_BACKSPACE])
	{
		SDL_SetWindowFullscreen(my_union->win,0);
		SDL_RestoreWindow(my_union->win);
		SDL_SetWindowSize(my_union->win, my_union->cur_win_x, my_union->cur_win_y);
		SDL_SetWindowPosition(my_union->win, SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED);
		my_union->fullscreen_mode = 0;
		change_hud_rect(my_union);
	}
	if (!my_union->fullscreen_mode && my_union->key_game[SDL_SCANCODE_BACKSPACE])
	{
		SDL_SetWindowFullscreen(my_union->win,-1);
		my_union->fullscreen_mode = 1;
		change_hud_rect(my_union);
	}
	check_weapons_and_quit(my_union, map, player, objects);
	check_rotates_keys(my_union, player);
	check_movement_shooting_keys(my_union, map, player);
}
