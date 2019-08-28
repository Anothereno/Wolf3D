/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_weapon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:29:16 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/28 19:33:25 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_surface_to_render(t_union *my_union, char *info, int i)
{
	my_union->stats_surface = TTF_RenderText_Solid(my_union->font,
			info, my_union->font_color);
	my_union->stats_texture = SDL_CreateTextureFromSurface(
			my_union->renderer, my_union->stats_surface);
	SDL_FreeSurface(my_union->stats_surface);
	SDL_RenderCopy(my_union->renderer, my_union->stats_texture,
			NULL, &my_union->stat_rects[i]);
	SDL_DestroyTexture(my_union->stats_texture);
	free(info);
}

void	print_ammo_in_clip(t_union *my_union, t_player *player)
{
	put_surface_to_render(my_union, ft_strcat(
			ft_itoa(player->clip[player->weapon]), "/"), 4);
}

void	print_ammo_in_stock(t_union *my_union, t_player *player)
{
	put_surface_to_render(my_union, ft_itoa(player->ammo[player->weapon]), 6);
}

void	show_weapon_image(t_union *my_union, t_player *player)
{
	my_union->stats_texture = SDL_CreateTextureFromSurface(
			my_union->renderer, my_union->weapons_mini_array[player->weapon]);
	SDL_RenderCopy(my_union->renderer, my_union->stats_texture,
			NULL, &my_union->stat_rects[5]);
	SDL_DestroyTexture(my_union->stats_texture);
}

void	print_fps(t_union *my_union)
{
	put_surface_to_render(my_union, ft_itoa(my_union->FPS), 7);
}
