/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:27:15 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/10 10:16:52 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int     ft_is_uppercase(char c)
{
    if (ft_isalpha(c) && c >= 'A' && c <='Z')
        return (1);
    return (0);
}

// Получаю размер поля
void	take_size(t_map *map, char *map_coordinates)
{
	char	*str;

	map->size_x = 0;
	map->size_y = 0;
	str = map_coordinates;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ' ' && *str != '\n' && !ft_is_uppercase(*str))
		{
			ft_putstr("Not a valid file\n");
			exit(0);
		}
		if (*str == '\n')
			map->size_y++;
		if (!map->size_y && *str != ' ' && *str != '\n')
			map->size_x++;
		str++;
	}
	if (*str == '\0')
		map->size_y++;
}

// Инициализирую массив с координатами карты
void	set_array(t_map *map, char *map_coordinates, t_map *objects)
{
	int		y;
	int		x;
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
        tmp = ft_strsplit(res[y], ' ');
        while (++x < map->size_x)
		{
            if (ft_isdigit(tmp[x][0]))
            {
                map->map[y][x] = ft_atoi(tmp[x]);
                objects->map[y][x] = 0;
            }
            else
            {
                if (tmp[x][0] == 'D')
                {
                    map->map[y][x] = 9;
                    objects->map[y][x] = tmp[x][0];
                }
                else
                {
                    map->map[y][x] = 0;
                    objects->map[y][x] = tmp[x][0];
                }

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
int		val_set(char *file, t_map *map, t_map *objects)
{
	int		fd;
	char	*map_coordinates;

	if ((fd = open(file, O_RDONLY)) < 3)
	{
		usage();
		return (0);
	}
	map_coordinates = reading(fd);
	set_array(map, map_coordinates, objects);
	return (1);
}