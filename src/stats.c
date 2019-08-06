/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 18:07:46 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/06 17:01:35 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_surface_to_render(t_union *my_union, char *info, int i)
{
	my_union->stats_surface = TTF_RenderText_Solid(my_union->font,
			info, my_union->font_color);
	my_union->stats_texture = SDL_CreateTextureFromSurface(
			my_union->renderer, my_union->stats_surface);
	SDL_RenderCopy(my_union->renderer, my_union->stats_texture,
				   NULL, &my_union->stat_rects[i]);
}

void    print_level(t_union *my_union, t_player *player)
{
	my_union->stat_rects[0].x = my_union->hud_rect.x + 50;
	my_union->stat_rects[0].w = my_union->stat_rects[0].h >> 1;
    put_surface_to_render(my_union, ft_itoa(player->level), 0);
}

void    print_score(t_union *my_union, t_player *player)
{
	my_union->stat_rects[1].x = my_union->hud_rect.x + 165;
	my_union->stat_rects[1].w = my_union->stat_rects[1].h << 1;
	put_surface_to_render(my_union, ft_itoa(player->score), 1);
}

void    print_lives(t_union *my_union, t_player *player)
{
	my_union->stat_rects[2].x = my_union->hud_rect.x + 440;
	my_union->stat_rects[2].w = my_union->stat_rects[2].h >> 1;
	put_surface_to_render(my_union, ft_itoa(player->lives), 2);
}

void    print_health(t_union *my_union, t_player *player)
{
	my_union->stat_rects[3].x = my_union->hud_rect.x + 670;
	my_union->stat_rects[3].w = (my_union->stat_rects[3].h << 1) - 50;
	put_surface_to_render(my_union, ft_strcat(ft_itoa(player->health), "%"), 3);
}

void    print_ammo(t_union *my_union, t_player *player)
{
	my_union->stat_rects[4].x = my_union->hud_rect.x + 850;
	my_union->stat_rects[4].w = my_union->stat_rects[4].h;
	put_surface_to_render(my_union, ft_itoa(player->ammo), 4);
}

void	show_weapon_image(t_union *my_union, t_player *player)
{

}

void    show_stats(t_union *my_union, t_map *map, t_player *player)
{
    print_level(my_union, player);
    print_score(my_union, player);
    print_lives(my_union, player);
    print_health(my_union, player);
    print_ammo(my_union, player);
//    show_weapon_image(my_union, player);
}


