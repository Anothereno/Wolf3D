/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:27:15 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/01 15:38:11 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// Получаю размер поля
void	take_size(t_map *map, char *map_coordinates)
{
	char	*str;

	map->size_x = 0;
	map->size_y = 0;
	str = map_coordinates;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != ' ' && *str != '\n')
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
void	set_array(t_map *map, char *map_coordinates)
{
	int		y;
	int		x;
	char	**res;
	char 	**tmp;

	y = -1;
	take_size(map, map_coordinates);
	map->map = (int**)malloc(sizeof(int*) * map->size_y);
	while (++y < map->size_y)
		map->map[y] = (int*)malloc(sizeof(int) * map->size_x);
	y = -1;
	res = ft_strsplit(map_coordinates, '\n');
	while (++y < map->size_y)
	{
		x = -1;
		while (++x < map->size_x)
		{
			tmp = ft_strsplit(res[y], ' ');
			map->map[y][x] = ft_atoi(tmp[x]);
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
int		val_set(char *file, t_map *map)
{
	int		fd;
	char	*map_coordinates;

	if ((fd = open(file, O_RDONLY)) < 3)
	{
		usage();
		return (0);
	}
	map_coordinates = reading(fd);
	set_array(map, map_coordinates);
	return (1);
}