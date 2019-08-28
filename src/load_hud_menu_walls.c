/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_hud_and_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:19:00 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/28 19:21:11 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char			*load_hud(t_union *my_union)
{
	my_union->hud_surface = SDL_LoadBMP(
			"resources/pictures/HUD/HUD.bmp");
	if (!my_union->surface)
		return ("HUD surface not loaded\n");
	my_union->load_mark++;
	return (NULL);
}

char			*load_menu(t_union *my_union)
{
	int i;

	i = -1;
	my_union->menu_array =
			(SDL_Surface**)malloc(sizeof(SDL_Surface*) * 4);
	my_union->menu_array[0] = SDL_LoadBMP(
			"resources/pictures/menu/menu_new_game.bmp");
	my_union->menu_array[1] = SDL_LoadBMP(
			"resources/pictures/menu/menu_sound.bmp");
	my_union->menu_array[2] = SDL_LoadBMP(
			"resources/pictures/menu/menu_control.bmp");
	my_union->menu_array[3] = SDL_LoadBMP(
			"resources/pictures/menu/menu_quit.bmp");
	while (++i < 4)
		if (!my_union->menu_array[i])
			return ("Menu surface not loaded\n");
	my_union->load_mark++;
	return (NULL);
}

char			*load_weapons_minimize(t_union *my_union)
{
	int i;

	i = -1;
	my_union->weapons_mini_array[2] = SDL_LoadBMP(
			"resources/pictures/weapon_img/auto.bmp");
	my_union->weapons_mini_array[1] = SDL_LoadBMP(
			"resources/pictures/weapon_img/pistol.bmp");
	my_union->weapons_mini_array[0] = SDL_LoadBMP(
			"resources/pictures/weapon_img/knife.bmp");
	while (++i < 3)
		if (!my_union->weapons_mini_array[i])
			return ("Weapon minimize surface not loaded\n");
	my_union->load_mark++;
	return (NULL);
}

char			*load_wall_surfaces(t_union *my_union)
{
	my_union->wall_surfaces_array[0] = SDL_LoadBMP(
			"resources/pictures/WALLS/WALL56.bmp");
	my_union->wall_surfaces_array[1] = SDL_LoadBMP(
			"resources/pictures/WALLS/WALL57.bmp");
	my_union->wall_surfaces_array[2] = SDL_LoadBMP(
			"resources/pictures/WALLS/WALL56.bmp");
	my_union->wall_surfaces_array[3] = SDL_LoadBMP(
			"resources/pictures/WALLS/WALL57.bmp");
	my_union->wall_surfaces_array[4] = SDL_LoadBMP(
			"resources/pictures/WALLS/WALL90.bmp");
	my_union->wall_surfaces_array[5] = SDL_LoadBMP(
			"resources/pictures/WALLS/WALL91.bmp");
	my_union->wall_surfaces_array[6] = SDL_LoadBMP(
			"resources/pictures/WALLS/WALL90.bmp");
	my_union->wall_surfaces_array[7] = SDL_LoadBMP(
			"resources/pictures/WALLS/WALL91.bmp");
	my_union->wall_surfaces_array[8] = SDL_LoadBMP(
			"resources/pictures/WALLS/WALL98.bmp");
	my_union->wall_surfaces_array[9] = SDL_LoadBMP(
			"resources/pictures/WALLS/WALL98.bmp");
	if (!check_loaded(my_union, 0, 10, 1))
		return ("Walls surface not loaded\n");
	my_union->load_mark++;
	return (NULL);
}

int				check_loaded(t_union *my_union, int index,
								int size, int dimension)
{
	int i;

	i = -1;
	while (++i < size)
		if ((dimension == 1 && !my_union->wall_surfaces_array[i]) ||
			(dimension == 2 && !my_union->weapons_surfaces[index][i]))
			return (0);
	return (1);
}
