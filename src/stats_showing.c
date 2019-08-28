/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 18:07:46 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/28 19:32:47 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_level(t_union *my_union, t_player *player)
{
	put_surface_to_render(my_union, ft_itoa(player->level), 0);
}

void	print_score(t_union *my_union, t_player *player)
{
	put_surface_to_render(my_union, ft_itoa(player->score), 1);
}

void	print_lives(t_union *my_union, t_player *player)
{
	put_surface_to_render(my_union, ft_itoa(player->lives), 2);
}

void	print_health(t_union *my_union, t_player *player)
{
	put_surface_to_render(my_union, ft_strcat(ft_itoa(player->health), "%"), 3);
}

void	show_stats(t_union *my_union, t_map *map, t_player *player)
{
	print_level(my_union, player);
	print_score(my_union, player);
	print_lives(my_union, player);
	print_health(my_union, player);
	print_ammo_in_clip(my_union, player);
	print_ammo_in_stock(my_union, player);
	print_fps(my_union);
	show_weapon_image(my_union, player);
}
