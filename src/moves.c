/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:27:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/26 14:31:33 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int 	in_wall(t_player *player, t_map *map)
{
	if (map->map[(int)player->player_pos_y / BLOCK_SIZE][(int)player->player_pos_x / BLOCK_SIZE])
		return (1);
	return (0);
}

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

void	check_event(t_union *my_union, t_map *map, t_player *player, const Uint8	*key)
{
	double 	old_dir_x;
	double 	old_plane_x;
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
//		player->player_pos_x -= 4;
//		old_dir_x = player->dirX;
//		old_plane_x = player->planeX;
//		player->dirX = player->dirX * cos(player->speed_rotate) - player->dirY * sin(player->speed_rotate);
//		player->dirY = old_dir_x * sin(player->speed_rotate) + player->dirY * cos(player->speed_rotate);
//		player->planeX = player->planeX * cos(player->speed_rotate) - player->planeY * sin(player->speed_rotate);
//		player->planeY = old_plane_x * sin(player->speed_rotate) + player->planeY * cos(player->speed_rotate);
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
//		player->player_pos_x += 4;
//		old_dir_x = player->dirX;
//		old_plane_x = player->planeX;
//		player->dirX = player->dirX * cos(-player->speed_rotate) - player->dirY * sin(-player->speed_rotate);
//		player->dirY = old_dir_x * sin(-player->speed_rotate) + player->dirY * cos(-player->speed_rotate);
//		player->planeX = player->planeX * cos(-player->speed_rotate) - player->planeY * sin(-player->speed_rotate);
//		player->planeY = old_plane_x * sin(-player->speed_rotate) + player->planeY * cos(-player->speed_rotate);

	}
	if (key[SDL_SCANCODE_UP])
	{

//		player->player_pos_x += player->direct_x * player->speed;
//		player->player_pos_y += player->direct_y * player->speed;
//		if (!map->map[(int)(player->player_pos_y +
//				player->dirY * player->speed_move)][(int)player->player_pos_x])
//			player->player_pos_y += player->dirY * player->speed_move;
//		if (!map->map[(int)player->player_pos_y][(int)(player->player_pos_x +
//				player->dirX * player->speed_move)])
//			player->player_pos_x += player->dirX * player->speed_move;
		view_follow(player, map);
	}
	if (key[SDL_SCANCODE_DOWN])
	{
//		if (!map->map[(int)(player->player_pos_y -
//							player->dirY * player->speed_move)][(int)player->player_pos_x])
//			player->player_pos_y -= player->dirY * player->speed_move;
//		if (!map->map[(int)player->player_pos_y][(int)(player->player_pos_x -
//													   player->dirX * player->speed_move)])
//			player->player_pos_x -= player->dirX * player->speed_move;
//
//		player->player_pos_y += 4;
	}
	if (key[SDL_SCANCODE_Q])
	{
//		player->view_direction -= 2;
	}
	if (key[SDL_SCANCODE_E])
	{
//		player->view_direction += 2;
	}
}