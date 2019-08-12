/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 18:07:46 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/12 15:31:21 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ПОМЕЩАЕТ САРФЭЙС В ОКНО
void	put_surface_to_render(t_union *my_union, char *info, int i)
{
	my_union->stats_surface = TTF_RenderText_Solid(my_union->font,
			info, my_union->font_color);
	my_union->stats_texture = SDL_CreateTextureFromSurface(
			my_union->renderer, my_union->stats_surface);
	free(my_union->stats_surface);
	SDL_RenderCopy(my_union->renderer, my_union->stats_texture,
				   NULL, &my_union->stat_rects[i]);
	SDL_DestroyTexture(my_union->stats_texture);
}

void    print_level(t_union *my_union, t_player *player)
{
    put_surface_to_render(my_union, ft_itoa(player->level), 0);
}

void    print_score(t_union *my_union, t_player *player)
{
	put_surface_to_render(my_union, ft_itoa(player->score), 1);
}

void    print_lives(t_union *my_union, t_player *player)
{
	put_surface_to_render(my_union, ft_itoa(player->lives), 2);
}

void    print_health(t_union *my_union, t_player *player)
{
	put_surface_to_render(my_union, ft_strcat(ft_itoa(player->health), "%"), 3);
}

void    print_ammo(t_union *my_union, t_player *player)
{
	put_surface_to_render(my_union, ft_itoa(player->ammo), 4);
}

//ОРТИСОВЫВАЕТ МИНИМАЙЗ КАРТИНКИ
void	show_weapon_image(t_union *my_union, t_player *player)
{
	my_union->stats_texture = SDL_CreateTextureFromSurface(
			my_union->renderer, my_union->weapons_mini_array[player->weapon]);
	SDL_RenderCopy(my_union->renderer, my_union->stats_texture,
			NULL, &my_union->stat_rects[5]);
}

void	print_FPS(t_union *my_union)
{
	put_surface_to_render(my_union, ft_itoa(my_union->FPS), 6);
}

//ОТРИСОВАЕТ СТАТЫ
void    show_stats(t_union *my_union, t_map *map, t_player *player)
{
    print_level(my_union, player);
    print_score(my_union, player);
    print_lives(my_union, player);
    print_health(my_union, player);
    print_ammo(my_union, player);
	print_FPS(my_union);
	show_weapon_image(my_union, player);
}


