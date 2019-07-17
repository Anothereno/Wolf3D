/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:51:14 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/17 16:24:08 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ЧЕКАЕТ ДВЕРЬ
//void    check_door(t_map *map, t_map *objects, t_player *player, t_union *my_union) {
//    double angle_rad;
//    double angle;
//    t_ray ray;
//
//    angle = player->view_direction;
//    my_union->flag = 0;
//    angle = take_range_angle(angle);
//    angle_rad = angle * RAD;
//    hor_distance(my_union, *player, *map, &ray, angle_rad);
//    vert_distance(my_union, *player, *map, &ray, angle_rad);
//    choose_distance(&ray);
//    printf("%c, %d\n", objects->map[(int) ray.y >> 6][(int) ray.x >> 6], map->map[(int) ray.y >> 6][(int) ray.x >> 6]);
//    if (objects->map[(int) ray.y >> 6][(int) ray.x >> 6] == 'D' && ray.res_distance <= BLOCK_SIZE << 1)
//    {
//        if (map->map[(int) ray.y >> 6][(int) ray.x >> 6] != 0)
//            map->map[(int) ray.y >> 6][(int) ray.x >> 6] = 0;
//        else
//            map->map[(int) ray.y >> 6][(int) ray.x >> 6] = 9;
//    }
//}

void    open_close_door(t_map *objects, t_map *map, int j, int i)
{
    if (objects->map[j][i] == 'D')
    {
        if (map->map[j][i] != 0)
            map->map[j][i] = 0;
        else
            map->map[j][i] = 9;
    }
}

void    check_door(t_map *map, t_map *objects, t_player *player, t_union *my_union)
{
    int pos_x;
    int pos_y;
    int i;
    int j;

    if (!my_union->door_timer_end)
    {
        my_union->door_timer_end = SDL_GetTicks();
        pos_x = (int) player->player_pos_x >> 6;
        pos_y = (int) player->player_pos_y >> 6;
        j = pos_y - 2;
        while (++j <= pos_y + 1)
        {
            i = pos_x - 2;
            while (++i <= pos_x + 1)
            {
                if (!check_bound(i, j, *map))
                    continue;
                open_close_door(objects, map, j, i);
            }
        }
    }
}