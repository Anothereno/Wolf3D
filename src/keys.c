/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:27:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/26 19:32:27 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ПЕРЕДВИЖЕНИЕ В СТОРОНУ ВЗГЛЯДА
void	view_follow(t_player *player, t_map *map, int mode)
{
	double center_x;
	double center_y;
	double pos_x;
	double pos_y;
	double angle;

	angle = player->view_direction * RAD;
    player->move_indicate = 5;
	center_x = player->player_pos_x + (player->player_width >> 1);
	center_y = player->player_pos_y + (player->player_heigth >> 1);
	pos_x = (center_x + (player->speed * mode *
			cos(angle))) - (player->player_width >> 1);
	pos_y = (center_y + (player->speed * mode *
			sin(angle))) - (player->player_width >> 1);
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

void    mouse_handling(t_union *my_union, t_map *map, t_player *player, t_map *objects)
{
    int x;
    int y;

    x = my_union->event.motion.x;
    y = my_union->event.motion.y;
    if (x < my_union->mouse_x)
    {
        player->view_direction -= (int)((my_union->mouse_x - x) * my_union->sens);
        my_union->mouse_x = x;
    }
    else if (x > my_union->mouse_x)
    {
        player->view_direction += (int)((x - my_union->mouse_x) * my_union->sens);
        my_union->mouse_x = x;
    }

}

//ПОЛУЧАЕТ НАЖАТИЯ КЛАВИШ
void	check_event(t_union *my_union, t_map *map, t_player *player, t_map *objects, const Uint8	*key)
{
	int		temp;


    if (my_union->event.type == SDL_MOUSEMOTION)
        mouse_handling(my_union, map, player, objects);
    if (key[SDL_SCANCODE_ESCAPE])
	{
		exit(0);
	}
	if (key[SDL_SCANCODE_Q])
	{
		if (player->view_direction - player->rotate_angle >= 0)
			player->view_direction -= player->rotate_angle;
		else
		{
			temp = 360 + player->view_direction - player->rotate_angle;
			player->view_direction = temp;
		}
	}
	if (key[SDL_SCANCODE_E])
	{
		if (player->view_direction + player->rotate_angle < 360)
			player->view_direction += player->rotate_angle;
		else
		{
			temp = 360 - player->view_direction - player->rotate_angle;
			player->view_direction = -temp;
		}
	}
	if (key[SDL_SCANCODE_W])
		view_follow(player, map, 1);
	if (key[SDL_SCANCODE_S])
		view_follow(player, map, -1);
	if (key[SDL_SCANCODE_A])
        strafe(player, map, -1);
	if (key[SDL_SCANCODE_D])
	    strafe(player, map, 1);
	if (key[SDL_SCANCODE_SPACE])
	    check_door(map, objects, player, my_union);

}