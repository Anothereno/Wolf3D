/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:27:15 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/26 19:39:50 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"



// Получаю размер поля
void	take_size(t_map *map, char *map_coordinates)
{
	char	*str;
	int		size_x;

	size_x = 0;
	map->size_x = 2;
	map->size_y = 2;
	str = map_coordinates;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '.' && *str != ' ' &&
				*str != '\n' && !ft_is_uppercase(*str))
			error_quit("Not a valid file", 0, NULL, NULL);
		if (*str == '\n')
		{
			map->size_y++;
			if (size_x + 2 > map->size_x)
				map->size_x = size_x + 2;
			size_x = 0;
		}
		if (*str != ' ' && *str != '\n')
			size_x++;
		if (*str == '\n' && *(str + 1) == '\0')
			map->size_y--;
		str++;
	}
	if (*str == '\0')
	{
		if (size_x + 2 > map->size_x)
			map->size_x = size_x + 2;
		map->size_y++;
	}
}

int 	get_size(char *string)
{
	char	*str;
	int		size_x;
	int		flag;

	flag = 1;
	size_x = 0;
	str = string;
	while (str && *str)
	{
		if (*str == ' ')
			flag++;
		if (flag && *str != ' ' && *str != '\n')
		{
			size_x++;
			flag = 0;
		}
		str++;
	}
	return (size_x);
}

int		check_on_edge(t_map *map, int x, int y)
{
	if (x == 0 || x == map->size_x - 1 || y == 0 || y == map->size_y - 1)
		return (1);
	return (0);
}

//УСТАНАВЛИВАЕТ ДВЕРИ
int    set_doors(t_map *map, t_map *objects, char ch, int x, int y)
{
    if (ch == 'D')
    {
		map->map[y][x] = 9;
		objects->map[y][x] = ch;
    	return (1);
    }
    return (0);
}

//УСТАНАВЛИВАЕТ ИГРОКА
int    set_player(t_map *map, t_map *objects, char ch, int x, int y, t_player *player)
{
    if (ch == 'P')
    {
        player->player_pos_x = (x << 6) + 10;
        player->player_pos_y = (y << 6) + 10;
        map->map[y][x] = 0;
        objects->map[y][x] = 0;
        return (1);
    }
    return (0);
}

void	set_map_and_objects(int map_num, int objects_num, int *map, int *objects)
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
				set_map_and_objects(1 + rand() % 6, 0,
									&map->map[y][x], &objects->map[y][x]);
	}
}

// Инициализирую массив с координатами карты
void	set_array(t_map *map, char *map_coordinates, t_map *objects, t_player *player)
{
	int		y;
	int		x;
	int 	size_string;
	char	**res;
	char 	**tmp;

	y = -1;
	take_size(map, map_coordinates);
	map->map = (int**)malloc(sizeof(int*) * map->size_y);
	objects->map = (int**)malloc(sizeof(int*) * map->size_y);
	while (++y < map->size_y)
    {
        map->map[y] = (int*)malloc(sizeof(int) * map->size_x);
        objects->map[y] = (int*)malloc(sizeof(int) * map->size_x);
    }
	y = 0;
	set_edges(map,objects);
	res = ft_strsplit(map_coordinates, '\n');
	while (++y < map->size_y - 1)
	{
		x = 0;
		size_string = get_size(res[y - 1]);
        tmp = ft_strsplit(res[y - 1], ' ');
        while (++x < map->size_x - 1)
		{
        	if (x > size_string)
        	{
				set_map_and_objects(1 + rand() % 6, 0,
									&map->map[y][x], &objects->map[y][x]);
				continue;
			}
            else if (tmp[x - 1][0] == '.')
            	set_map_and_objects(0, 0,
            			&map->map[y][x], &objects->map[y][x]);
            else if (ft_isdigit(tmp[x - 1][0]))
				set_map_and_objects(ft_atoi(tmp[x - 1]), 0,
						&map->map[y][x], &objects->map[y][x]);
            else
            {
                if (set_doors(map, objects, tmp[x - 1][0], x, y) ||
                		set_player(map, objects, tmp[x - 1][0], x, y, player))
                    continue;
                else
                	set_map_and_objects(0, tmp[x - 1][0],
							&map->map[y][x], &objects->map[y][x]);
            }
		}
        ft_clear_string_array(tmp, size_string);
	}
	ft_clear_string_array(res, map->size_y - 2);
	ft_strdel(&map_coordinates);
}

// Читаю карту из файла
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

int 	find_place_for_player(t_player *player, t_map *map, t_map *objects)
{
	int i;
	int j;

	i = 0;
	while (++i < map->size_y - 1)
	{
		j = 0;
		while (++j < map->size_x - 1) {
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

// Открываю карту на чтение
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