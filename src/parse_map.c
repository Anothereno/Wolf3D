/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 13:55:00 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 11:38:30 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	parse_string(char *str, t_map *map, int *size_x)
{
	if (!ft_isdigit(*str) && *str != '.' && *str != ' ' &&
		*str != '\n' && !ft_is_uppercase(*str))
		error_quit("Not a valid file", 0, NULL, NULL);
	if (*str == '\n')
	{
		map->size_y++;
		if (*size_x + 2 > map->size_x)
			map->size_x = *size_x + 2;
		*size_x = 0;
	}
}

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
		parse_string(str, map, &size_x);
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

int		get_size(char *string)
{
	char	*str;
	int		size_x;
	int		flag;

	if (!string)
		msg("Not a valid map\n");
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

int		set_doors(t_map *map, t_map *objects, t_obj_on_map obj_on_map)
{
	if (obj_on_map.ch == 'D')
	{
		map->map[obj_on_map.y][obj_on_map.x] = 2;
		objects->map[obj_on_map.y][obj_on_map.x] = obj_on_map.ch;
		return (1);
	}
	return (0);
}
