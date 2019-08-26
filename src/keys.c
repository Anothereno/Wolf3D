/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:27:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/26 12:38:45 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ПЕРЕДВИЖЕНИЕ В СТОРОНУ ВЗГЛЯДА
void	view_follow(t_player *player, t_map *map, int mode, t_union *my_union)
{
	double center_x;
	double center_y;
	double pos_x;
	double pos_y;

    player->move_indicate = 5;
	center_x = player->player_pos_x + (player->player_width >> 1);
	center_y = player->player_pos_y + (player->player_heigth >> 1);
	pos_x = (center_x + (player->speed * mode *
			cos(player->view_direction_rad))) - (player->player_width >> 1);
	pos_y = (center_y + (player->speed * mode *
			sin(player->view_direction_rad))) - (player->player_width >> 1);
	if (!check_wall(pos_x, pos_y, *map))
	{
		player->player_pos_x = pos_x;
		player->player_pos_y = pos_y;
	}
}

//СТРЭЙФ ВПРАВО И ВЛЕВО
void    strafe(t_player *player, t_map *map, int mode)
{
    double center_x;
    double center_y;
    double angle;
    double pos_x;
    double pos_y;

    player->move_indicate = 5;
    angle = (player->view_direction + (90 * mode)) * RAD;
    center_x = player->player_pos_x + (player->player_width >> 1);
    center_y = player->player_pos_y + (player->player_heigth >> 1);
    pos_x = (center_x + (player->strafe_speed *
                         cos(angle))) - (player->player_width >> 1);
    pos_y = (center_y + (player->strafe_speed *
                         sin(angle))) - (player->player_width >> 1);
    if (!check_wall(pos_x, pos_y, *map))
    {
        player->player_pos_x = pos_x;
        player->player_pos_y = pos_y;
    }
}

//ОБРАБАТЫВАЕТ ПОВЕДЕНИЕ МЫШИ, ЕСЛИ КУРСОР ВКЛЮЧЕН
void    mouse_handling(t_union *my_union, t_map *map, t_player *player, t_map *objects)
{
    int x;
    int y;

    SDL_GetMouseState(&x, &y);
//    printf("%d, %d\n", x, y);
    if (x < 0)
    {
        player->view_direction -= ((my_union->half_win_x - x) * my_union->sens);
        my_union->mouse_x = x;
    }
    else if (x > 0)
    {
        player->view_direction += ((x - my_union->half_win_x) * my_union->sens);
        my_union->mouse_x = x;
    }
//    SDL_WarpMouseInWindow(my_union->win, my_union->half_win_x, my_union->half_win_y);

}

// МЕНЯЕТ ОРУЖИЕ
void change_weapon(t_player *player, const Uint8 *key, t_union *my_union)
{
	if (key[SDL_SCANCODE_1] && player->weapon != 0)
	{
		weapon_down(my_union, player);
		my_union->change_weapon_mode = 1;
		player->new_weapon = 0;
	}
	else if (key[SDL_SCANCODE_2] && player->weapon != 1)
	{
		weapon_down(my_union, player);
		my_union->change_weapon_mode = 1;
		player->new_weapon = 1;
	}
	else if (key[SDL_SCANCODE_3] && player->weapon != 2)
	{
		weapon_down(my_union, player);
		my_union->change_weapon_mode = 1;
		player->new_weapon = 2;
	}
}

//ОБРАБАТЫВАЕТ ПОВЕДЕНИЕ МЫШИ, ЕСЛИ КУРСОР ВЫКЛЮЧЕН
void    mouse_relative_handling(t_union *my_union, t_map *map, t_player *player, t_map *objects)
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

//ПОЗВОЛЯЕТ ВЫБИРАТЬ ПУНКТЫ МЕНЮ
void	change_menu_choise(t_union *my_union, char mode)
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

//ДЕЛАЕТ ВЫБОРА ОПРЕДЕЛЕНОГО ПУНКТА МЕНЮ
void	choise_menu(t_union *my_union, t_map *map, t_player *player, t_map *objects)
{
	if (my_union->menu_frame == 0)
		my_union->menu_mode = 0;
	else if (my_union->menu_frame == 3)
		exit(0);
}

//ОТЛАВЛИВАЕТ ИВЕНТЫ В МЕНЮ
void	check_event_menu(t_union *my_union, t_map *map, t_player *player, t_map *objects, const Uint8	*key)
{
	if (my_union->menu_mode && key[SDL_SCANCODE_RETURN])
		choise_menu(my_union, map, player, objects);
	if (key[SDL_SCANCODE_UP])
		change_menu_choise(my_union, 'u');
	if (key[SDL_SCANCODE_DOWN])
		change_menu_choise(my_union, 'd');
	if (key[SDL_SCANCODE_ESCAPE])
	{
		if (!my_union->escape_timer) {
			my_union->escape_timer = SDL_GetTicks();
			if (!my_union->go_to_menu && my_union->menu_mode)
				complete_work(my_union,map, objects, player);
			my_union->go_to_menu = 0;
		}
	}
}

//ОТЛАВЛИВАЕТ ИВЕНТЫ В ИГРЕ
void	check_event_game(t_union *my_union, t_map *map, t_player *player, t_map *objects, const Uint8	*key) {
	int temp;

	if (my_union->event.type == SDL_MOUSEMOTION) {
//        if (my_union->mouse_state)
//            mouse_handling(my_union, map, player, objects);
//        else
		mouse_relative_handling(my_union, map, player, objects);
	}
	if (!my_union->escape_timer && key[SDL_SCANCODE_ESCAPE]) {
		my_union->escape_timer = SDL_GetTicks();
		my_union->go_to_menu = 1;
	}
	if (!my_union->rel_mouse_mode_timer && key[SDL_SCANCODE_BACKSPACE]) {
		my_union->rel_mouse_mode_timer = SDL_GetTicks();
		my_union->mouse_state = (my_union->mouse_state == 0) ? 1 : 0;
		SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
	}
	if (!my_union->weapon_down_mode && !my_union->shoot_timer &&
		key[SDL_SCANCODE_KP_ENTER]
		&& !player->shoot_mode && player->clip[player->weapon]) {
		if (player->weapon)
			player->clip[player->weapon]--;
		my_union->shoot_timer = SDL_GetTicks();
		player->shoot_mode = 1;
	}
	if (key[SDL_SCANCODE_Q]) {
		if (player->view_direction - player->rotate_angle >= 0)
			player->view_direction -= player->rotate_angle;
		else {
			temp = 360 + player->view_direction - player->rotate_angle;
			player->view_direction = temp;
		}
		player->view_direction_rad = player->view_direction * RAD;
	}
	if (key[SDL_SCANCODE_E]) {
		if (player->view_direction + player->rotate_angle < 360)
			player->view_direction += player->rotate_angle;
		else {
			temp = 360 - player->view_direction - player->rotate_angle;
			player->view_direction = -temp;
		}
		player->view_direction_rad = player->view_direction * RAD;
	}
	if (key[SDL_SCANCODE_W])
		view_follow(player, map, 1, my_union);
	if (key[SDL_SCANCODE_S])
		view_follow(player, map, -1, my_union);
	if (key[SDL_SCANCODE_A])
		strafe(player, map, -1);
	if (key[SDL_SCANCODE_D])
		strafe(player, map, 1);
	if (key[SDL_SCANCODE_SPACE])
		check_door(map, objects, player, my_union);
	if (!player->shoot_mode && (key[SDL_SCANCODE_1] || key[SDL_SCANCODE_2] ||
	key[SDL_SCANCODE_3]))
	{
		my_union->change_weapon_mode = 1;
		change_weapon(player, key, my_union);
	}
	if (!my_union->reload_timer && key[SDL_SCANCODE_R])
	{
		my_union->reload_timer = SDL_GetTicks();
		reload(my_union, player);
	}
	//FOR DEBUG
//	if (key[SDL_SCANCODE_KP_PLUS])
//	{
//		player->score += 100;
//		player->health += 10;
//		player->ammo += 10;
//		player->lives++;
//		player->level++;
//	}
//	if (key[SDL_SCANCODE_KP_MINUS])
//	{
//		player->score -= 100;
//		player->health -= 10;
//		player->ammo -= 10;
//		player->lives--;
//		player->level--;
//	}
}