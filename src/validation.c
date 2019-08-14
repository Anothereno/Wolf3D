/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:27:15 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/14 18:11:19 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"



// Получаю размер поля
void	take_size(t_map *map, char *map_coordinates)
{
	char	*str;
	int		size_x;

	size_x = 0;
	map->size_x = 0;
	map->size_y = 0;
	str = map_coordinates;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '.' && *str != ' ' &&
				*str != '\n' && !ft_is_uppercase(*str))
		{
			ft_putstr("Not a valid file\n");
			exit(0);
		}
		if (*str == '\n')
		{
			map->size_y++;
			if (size_x > map->size_x)
				map->size_x = size_x;
			size_x = 0;
		}
		if (*str != ' ' && *str != '\n')
			size_x++;
		str++;
	}
	if (*str == '\0')
		map->size_y++;
}

int 	get_size(char *string)
{
	char	*str;
	int		size_x;

	size_x = 0;
	str = string;
	while (*str)
	{
		if (*str != ' ' && *str != '\n')
			size_x++;
		str++;
	}
	return (size_x);
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
	y = -1;
	res = ft_strsplit(map_coordinates, '\n');
	while (++y < map->size_y)
	{
		x = -1;
		size_string = get_size(res[y]);
        tmp = ft_strsplit(res[y], ' ');
        while (++x < map->size_x)
		{
//        	if (x + 1 < map->size_x)
			if (x >= size_string) {
				set_map_and_objects(2, 3,
									&map->map[y][x], &objects->map[y][x]);
				continue;
			}
            if (tmp[x][0] == '.')
            	set_map_and_objects(0, 0,
            			&map->map[y][x], &objects->map[y][x]);
            else if (ft_isdigit(tmp[x][0]))
				set_map_and_objects(ft_atoi(tmp[x]), 0,
						&map->map[y][x], &objects->map[y][x]);
            else
            {
                if (set_doors(map, objects, tmp[x][0], x, y))
                    continue;
                else if (set_player(map, objects, tmp[x][0], x, y, player))
                    continue;
                else
                	set_map_and_objects(0, tmp[x][0],
							&map->map[y][x], &objects->map[y][x]);
            }
		}
	}
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
	ft_putstr("Wrong file\n");
	return (NULL);
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
	set_array(map, map_coordinates, objects, player);
	if (player->player_pos_x == -1 || player->player_pos_y == -1)
	{
        ft_putstr("Not set player position");
        return (0);
    }
	return (1);
}