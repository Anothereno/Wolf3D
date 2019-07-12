/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:27:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/12 18:26:20 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ВОЗВРАЩАЕТ 1, ЕСЛИ ИГРОК ОКАЗАЛСЯ В СТЕНЕ
int 	in_wall(t_player *player, t_map *map)
{
	if (map->map[(int)player->player_pos_y / BLOCK_SIZE][(int)player->player_pos_x / BLOCK_SIZE])
		return (1);
	return (0);
}

//ПЕРЕДВИЖЕНИЕ В СТОРОНУ ВЗГЛЯДА
void	view_follow(t_player *player, t_map *map)
{
	double center_x;
	double center_y;
	double old_pos_x;
	double old_pos_y;
	double rad;

	rad = 0.0174533;
	old_pos_x = player->player_pos_x;
	old_pos_y = player->player_pos_y;
	center_x = player->player_pos_x + (player->player_width >> 1);
	center_y = player->player_pos_y + (player->player_heigth >> 1);
	player->player_pos_x = (center_x + (player->speed *
			cos(player->view_direction * rad))) - (player->player_width >> 1);
	player->player_pos_y = (center_y + (player->speed *
			sin(player->view_direction * rad))) - (player->player_width >> 1);
	if (in_wall(player, map))
	{
		player->player_pos_x = old_pos_x;
		player->player_pos_y = old_pos_y;
	}

}

//void    strafe()

//ПОЛУЧАЕТ НАЖАТИЯ КЛАВИШ
void	check_event(t_union *my_union, t_map *map, t_player *player, t_map *objects, const Uint8	*key)
{
	int		temp;

	if (key[SDL_SCANCODE_ESCAPE])
	{
		exit(0);
	}
	if (key[SDL_SCANCODE_LEFT])
	{
		if (player->view_direction - player->rotate_angle >= 0)
			player->view_direction -= player->rotate_angle;
		else
		{
			temp = 360 + player->view_direction - player->rotate_angle;
			player->view_direction = temp;
		}
	}
	if (key[SDL_SCANCODE_RIGHT])
	{
		if (player->view_direction + player->rotate_angle < 360)
			player->view_direction += player->rotate_angle;
		else
		{
			temp = 360 - player->view_direction - player->rotate_angle;
			player->view_direction = -temp;
		}
	}
	if (key[SDL_SCANCODE_UP])
	{
		player->speed = BLOCK_SIZE >> 3;
		player->move_indicate = 5;
		view_follow(player, map);
	}
	if (key[SDL_SCANCODE_DOWN])
	{
		player->speed = -(BLOCK_SIZE >> 3);
        player->move_indicate = 5;
		view_follow(player, map);
	}
	if (key[SDL_SCANCODE_SPACE])
	    check_door(map, objects, player, my_union);

}