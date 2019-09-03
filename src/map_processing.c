/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 13:51:30 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 12:49:30 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	set_map_and_objects(int map_num, int objects_num, int *map,
							int *objects)
{
	*map = map_num;
	*objects = objects_num;
}

void	set_edges(t_map *map, t_map *objects)
{
	int x;
	int y;

	y = -1;
	while (++y < map->size_y)
	{
		x = -1;
		while (++x < map->size_x)
			if (check_on_edge(map, x, y))
				set_map_and_objects(1, 0,
						&map->map[y][x], &objects->map[y][x]);
	}
}

void	doors_another_objects(t_map *map, t_map *objects, t_player *player,
		char **tmp)
{
	if ((map->obj_map.ch = tmp[map->obj_map.x - 1][0]) &&
		(set_doors(map, objects, map->obj_map)
		|| set_player(map, objects, player, map->obj_map)))
		return ;
	else
		set_map_and_objects(0,
							tmp[map->obj_map.x - 1][0],
							&map->map[map->obj_map.y][map->obj_map.x],
							&objects->map[map->obj_map.y][map->obj_map.x]);
}

int		wall_completing(t_map *map, int size_string, t_map *objects)
{
	if (map->obj_map.x > size_string)
	{
		set_map_and_objects(1, 0,
							&map->map[map->obj_map.y][map->obj_map.x],
							&objects->map[map->obj_map.y][map->obj_map.x]);
		return (1);
	}
	return (0);
}

void	map_processing(t_map *map, char **res, t_map *objects, t_player *player)
{
	int		size_string;
	char	**tmp;

	while (++map->obj_map.y < map->size_y - 1)
	{
		map->obj_map.x = 0;
		size_string = get_size(res[map->obj_map.y - 1]);
		tmp = ft_strsplit(res[map->obj_map.y - 1], ' ');
		while (++map->obj_map.x < map->size_x - 1)
		{
			if (wall_completing(map, size_string, objects))
				continue;
			else if (tmp[map->obj_map.x - 1][0] == '.')
				set_map_and_objects(0, 0,
					&map->map[map->obj_map.y][map->obj_map.x],
					&objects->map[map->obj_map.y][map->obj_map.x]);
			else if (ft_isdigit(tmp[map->obj_map.x - 1][0]))
				set_map_and_objects(1,
					0, &map->map[map->obj_map.y][map->obj_map.x],
					&objects->map[map->obj_map.y][map->obj_map.x]);
			else
				doors_another_objects(map, objects, player, tmp);
		}
		ft_clear_string_array(tmp, size_string);
	}
}
