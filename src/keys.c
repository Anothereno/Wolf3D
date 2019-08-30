/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:27:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/30 15:51:53 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	enter_in_submenu(t_union *my_union)
{
	if (my_union->menu_frame == 4)
	{
		my_union->menu_frame = 5;
		my_union->mouse_handling = 0;
	}
	else if (my_union->menu_frame == 5)
	{
		my_union->menu_frame = 4;
		my_union->mouse_handling = 1;
	}
	else if (my_union->menu_frame == 6)
	{
		my_union->menu_frame = 7;
		change_resolution(my_union);
	}
	else if (my_union->menu_frame == 7)
	{
		my_union->menu_frame = 6;
		change_resolution(my_union);
	}
}

void	escape_event(t_union *my_union, t_map *map, t_player *player,
		t_map *objects)
{
	if (!my_union->escape_timer && my_union->submenu_mode &&
		my_union->key_menu[SDL_SCANCODE_ESCAPE])
	{
		my_union->escape_timer = SDL_GetTicks();
		my_union->submenu_mode = 0;
		my_union->menu_frame = 0;
	}
	else if (!my_union->escape_timer && !my_union->submenu_mode &&
		my_union->key_menu[SDL_SCANCODE_ESCAPE])
	{
		my_union->escape_timer = SDL_GetTicks();
		if (!my_union->go_to_menu && my_union->menu_mode)
			complete_work(my_union, map, objects, player);
		my_union->go_to_menu = 0;
	}
}

void	check_event_menu(t_union *my_union, t_map *map, t_player *player,
		t_map *objects)
{
	if (my_union->menu_mode && !my_union->submenu_mode &&
	!my_union->return_timer && my_union->key_menu[SDL_SCANCODE_RETURN])
	{
		my_union->return_timer = SDL_GetTicks();
		choice_menu(my_union);
	}
	else if (my_union->menu_mode && my_union->submenu_mode &&
			!my_union->return_timer && my_union->key_menu[SDL_SCANCODE_RETURN])
	{
		my_union->return_timer = SDL_GetTicks();
		enter_in_submenu(my_union);
	}
	if (!my_union->submenu_mode && my_union->key_menu[SDL_SCANCODE_UP])
		change_menu_choice(my_union, 'u');
	if (!my_union->submenu_mode && my_union->key_menu[SDL_SCANCODE_DOWN])
		change_menu_choice(my_union, 'd');
	if (my_union->key_menu[SDL_SCANCODE_ESCAPE])
		escape_event(my_union, map, player, objects);
}

void	change_resolution(t_union *my_union)
{
	if (my_union->fullscreen_mode)
	{
		SDL_SetWindowFullscreen(my_union->win, 0);
		SDL_RestoreWindow(my_union->win);
		SDL_SetWindowSize(my_union->win, my_union->cur_win_x,
				my_union->cur_win_y);
		SDL_SetWindowPosition(my_union->win, SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED);
		my_union->fullscreen_mode = 0;
		change_hud_rect(my_union);
		change_stat_rects(my_union);
		change_weapon_rect(my_union);
	}
	else if (!my_union->fullscreen_mode)
	{
		SDL_SetWindowFullscreen(my_union->win, -1);
		my_union->fullscreen_mode = 1;
		change_hud_rect(my_union);
		change_stat_rects(my_union);
		change_weapon_rect(my_union);
	}
}

void	check_event_game(t_union *my_union, t_map *map, t_player *player,
	t_map *objects)
{
	check_weapons_and_quit(my_union, map, player, objects);
	check_rotates_keys(my_union, player);
	check_movement_shooting_keys(my_union, map, player);
}
