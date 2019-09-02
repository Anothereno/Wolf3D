/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:27:15 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/02 13:54:52 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		set_player(t_map *map, t_map *objects, t_player *player,
			t_obj_on_map obj_on_map)
{
	if (obj_on_map.ch == 'P')
	{
		player->player_pos_x = (obj_on_map.x << 6) + 10;
		player->player_pos_y = (obj_on_map.y << 6) + 10;
		map->map[obj_on_map.y][obj_on_map.x] = 0;
		objects->map[obj_on_map.y][obj_on_map.x] = 0;
		return (1);
	}
	return (0);
}

void	set_array(t_map *map, char *map_coordinates, t_map *objects,
		t_player *player)
{
	char			**res;

	map->obj_map.y = -1;
	take_size(map, map_coordinates);
	map->map = (int**)malloc(sizeof(int*) * map->size_y);
	objects->map = (int**)malloc(sizeof(int*) * map->size_y);
	while (++map->obj_map.y < map->size_y)
	{
		map->map[map->obj_map.y] = (int*)malloc(sizeof(int)
												* map->size_x);
		objects->map[map->obj_map.y] = (int*)malloc(sizeof(int)
													* map->size_x);
	}
	map->obj_map.y = 0;
	set_edges(map, objects);
	res = ft_strsplit(map_coordinates, '\n');
	map_processing(map, res, objects, player);
	ft_clear_string_array(res, map->size_y - 2);
	ft_strdel(&map_coordinates);
}

char	*reading(int fd)
{
	char	buff[1000001];
	char	*res;
	char	*tmp;
	int		ret;

	res = ft_strdup("");
	if (read(fd, NULL, 0) >= 0)
	{
		while ((ret = read(fd, buff, 1000000)))
		{
			buff[ret] = '\0';
			tmp = res;
			res = ft_strjoin((const char *)res, (const char *)buff);
			ft_strdel(&tmp);
		}
		close(fd);
		return (res);
	}
	error_quit("Wrong file", 0, NULL, NULL);
	return (NULL);
}

int		find_place_for_player(t_player *player, t_map *map, t_map *objects)
{
	int i;
	int j;

	i = 0;
	while (++i < map->size_y - 1)
	{
		j = 0;
		while (++j < map->size_x - 1)
		{
			if (map->map[i][j] == 0 && objects->map[i][j] == 0)
			{
				player->player_pos_x = (j << 6) + 32;
				player->player_pos_y = (i << 6) + 32;
				return (1);
			}
		}
	}
	return (0);
}

int		val_set(char *file, t_map *map, t_map *objects, t_player *player)
{
	int		fd;
	char	*map_coordinates;

	if ((fd = open(file, O_RDONLY)) < 3)
	{
		usage();
		return (0);
	}
	player->player_pos_y = -1;
	player->player_pos_x = -1;
	map_coordinates = reading(fd);
	if (ft_strequ(map_coordinates, ""))
		error_quit("Empty map", 0, NULL, NULL);
	set_array(map, map_coordinates, objects, player);
	if (player->player_pos_x == -1 || player->player_pos_y == -1)
	{
		if (!find_place_for_player(player, map, objects))
		{
			error_quit("Not set player position", 1, map, objects);
			return (0);
		}
	}
	return (1);
}
