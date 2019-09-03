/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:21:09 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface		*get_color_key(t_union *my_union, char *path)
{
	my_union->surface = SDL_LoadBMP(path);
	if (!my_union->surface)
		return (NULL);
	SDL_SetColorKey(my_union->surface, SDL_TRUE,
			SDL_MapRGB(my_union->surface->format, 152, 0, 136));
	return (my_union->surface);
}

char			*load_pistol(t_union *my_union)
{
	my_union->weapons_surfaces[1][0] = get_color_key(my_union,
			"resources/pictures/weapons/pistol/pistol1.bmp");
	my_union->weapons_surfaces[1][1] = get_color_key(my_union,
			"resources/pictures/weapons/pistol/pistol2.bmp");
	my_union->weapons_surfaces[1][2] = get_color_key(my_union,
			"resources/pictures/weapons/pistol/pistol3.bmp");
	my_union->weapons_surfaces[1][3] = get_color_key(my_union,
			"resources/pictures/weapons/pistol/pistol4.bmp");
	my_union->weapons_surfaces[1][4] = get_color_key(my_union,
			"resources/pictures/weapons/pistol/pistol5.bmp");
	my_union->weapons_surfaces[1][5] = get_color_key(my_union,
			"resources/pictures/weapons/pistol/pistol6.bmp");
	my_union->weapons_surfaces[1][6] = get_color_key(my_union,
			"resources/pictures/weapons/pistol/pistol7.bmp");
	my_union->weapons_surfaces[1][7] = get_color_key(my_union,
			"resources/pictures/weapons/pistol/pistol8.bmp");
	my_union->weapons_surfaces[1][8] = get_color_key(my_union,
			"resources/pictures/weapons/pistol/pistol9.bmp");
	my_union->weapons_surfaces[1][9] = get_color_key(my_union,
			"resources/pictures/weapons/pistol/pistol10.bmp");
	if (!check_loaded(my_union, 1, 10, 2))
		return ("Pistol surface not loaded\n");
	return (NULL);
}

char			*load_knife(t_union *my_union)
{
	my_union->weapons_surfaces[0][0] = SDL_LoadBMP(
			"resources/pictures/weapons/knife/old knife1.bmp");
	my_union->weapons_surfaces[0][1] = SDL_LoadBMP(
			"resources/pictures/weapons/knife/old knife2.bmp");
	my_union->weapons_surfaces[0][2] = SDL_LoadBMP(
			"resources/pictures/weapons/knife/old knife3.bmp");
	my_union->weapons_surfaces[0][3] = SDL_LoadBMP(
			"resources/pictures/weapons/knife/old knife4.bmp");
	my_union->weapons_surfaces[0][4] = SDL_LoadBMP(
			"resources/pictures/weapons/knife/old knife5.bmp");
	if (!check_loaded(my_union, 0, 5, 2))
		return ("Knife surface not loaded\n");
	return (NULL);
}

char			*load_auto(t_union *my_union)
{
	my_union->weapons_surfaces[2][0] = get_color_key(my_union,
			"resources/pictures/weapons/auto/auto1.bmp");
	my_union->weapons_surfaces[2][1] = get_color_key(my_union,
			"resources/pictures/weapons/auto/auto2.bmp");
	my_union->weapons_surfaces[2][2] = get_color_key(my_union,
			"resources/pictures/weapons/auto/auto3.bmp");
	my_union->weapons_surfaces[2][3] = get_color_key(my_union,
			"resources/pictures/weapons/auto/auto4.bmp");
	my_union->weapons_surfaces[2][4] = get_color_key(my_union,
			"resources/pictures/weapons/auto/auto5.bmp");
	my_union->weapons_surfaces[2][5] = get_color_key(my_union,
			"resources/pictures/weapons/auto/auto6.bmp");
	my_union->weapons_surfaces[2][6] = get_color_key(my_union,
			"resources/pictures/weapons/auto/auto7.bmp");
	my_union->weapons_surfaces[2][7] = get_color_key(my_union,
			"resources/pictures/weapons/auto/auto8.bmp");
	my_union->weapons_surfaces[2][8] = get_color_key(my_union,
			"resources/pictures/weapons/auto/auto9.bmp");
	my_union->weapons_surfaces[2][9] = get_color_key(my_union,
			"resources/pictures/weapons/auto/auto10.bmp");
	if (!check_loaded(my_union, 2, 10, 2))
		return ("Auto surface not loaded\n");
	return (NULL);
}

char			*load_weapons(t_union *my_union)
{
	char *message;

	if ((message = load_pistol(my_union)) ||
			(message = load_auto(my_union)) ||
			(message = load_knife(my_union)))
		return (message);
	my_union->load_mark++;
	return (NULL);
}
