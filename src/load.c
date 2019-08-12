/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:21:09 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/12 19:44:58 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//ЗАГРУЖАЕТ САРФЭЙСЫ ПИСТОЛЕТА
void	load_pistol(t_union *my_union)
{
	int i;

	i = -1;
	my_union->weapons_surfaces[1][0] = SDL_LoadBMP("resources/pictures/weapons/pistol/pistol1.bmp");
	my_union->weapons_surfaces[1][1] = SDL_LoadBMP("resources/pictures/weapons/pistol/pistol2.bmp");
	my_union->weapons_surfaces[1][2] = SDL_LoadBMP("resources/pictures/weapons/pistol/pistol3.bmp");
	my_union->weapons_surfaces[1][3] = SDL_LoadBMP("resources/pictures/weapons/pistol/pistol4.bmp");
	my_union->weapons_surfaces[1][4] = SDL_LoadBMP("resources/pictures/weapons/pistol/pistol5.bmp");
	my_union->weapons_surfaces[1][5] = SDL_LoadBMP("resources/pictures/weapons/pistol/pistol6.bmp");
	my_union->weapons_surfaces[1][6] = SDL_LoadBMP("resources/pictures/weapons/pistol/pistol7.bmp");
	my_union->weapons_surfaces[1][7] = SDL_LoadBMP("resources/pictures/weapons/pistol/pistol8.bmp");
	my_union->weapons_surfaces[1][8] = SDL_LoadBMP("resources/pictures/weapons/pistol/pistol9.bmp");
	my_union->weapons_surfaces[1][9] = SDL_LoadBMP("resources/pictures/weapons/pistol/pistol10.bmp");
	while (++i < 10)
	{
		if (!my_union->weapons_surfaces[1][i])
			ft_putstr("Pistol surface not loaded\n");
	}
}

//ЗАГРУЖАЕТ САРФЭЙСЫ НОЖА
void	load_knife(t_union *my_union)
{
	int i;

	i = -1;
	my_union->weapons_surfaces[2][0] = SDL_LoadBMP("resources/pictures/weapons/knife/knife1.bmp");
	my_union->weapons_surfaces[2][1] = SDL_LoadBMP("resources/pictures/weapons/knife/knife2.bmp");
	my_union->weapons_surfaces[2][2] = SDL_LoadBMP("resources/pictures/weapons/knife/knife3.bmp");
	my_union->weapons_surfaces[2][3] = SDL_LoadBMP("resources/pictures/weapons/knife/knife4.bmp");
	my_union->weapons_surfaces[2][4] = SDL_LoadBMP("resources/pictures/weapons/knife/knife5.bmp");
	while (++i < 5)
	{
		if (!my_union->weapons_surfaces[0][i])
			ft_putstr("Knife surface not loaded\n");
	}
}

//ЗАГРУЖАЕТ САРФЭЙСЫ АВТОМАТА
void	load_auto(t_union *my_union)
{
	int i;

	i = -1;
	my_union->weapons_surfaces[0][0] = SDL_LoadBMP("resources/pictures/weapons/auto/auto1.bmp");
	my_union->weapons_surfaces[0][1] = SDL_LoadBMP("resources/pictures/weapons/auto/auto2.bmp");
	my_union->weapons_surfaces[0][2] = SDL_LoadBMP("resources/pictures/weapons/auto/auto3.bmp");
	my_union->weapons_surfaces[0][3] = SDL_LoadBMP("resources/pictures/weapons/auto/auto4.bmp");
	my_union->weapons_surfaces[0][4] = SDL_LoadBMP("resources/pictures/weapons/auto/auto5.bmp");
	my_union->weapons_surfaces[0][5] = SDL_LoadBMP("resources/pictures/weapons/auto/auto6.bmp");
	my_union->weapons_surfaces[0][6] = SDL_LoadBMP("resources/pictures/weapons/auto/auto7.bmp");
	my_union->weapons_surfaces[0][7] = SDL_LoadBMP("resources/pictures/weapons/auto/auto8.bmp");
	my_union->weapons_surfaces[0][8] = SDL_LoadBMP("resources/pictures/weapons/auto/auto9.bmp");
	my_union->weapons_surfaces[0][9] = SDL_LoadBMP("resources/pictures/weapons/auto/auto10.bmp");
	while (++i < 10)
	{
		if (!my_union->weapons_surfaces[0][i])
			ft_putstr("Auto surface not loaded\n");
	}
}

//ЗАГРУЖАЕТ ОРУЖИЕ
void	load_weapons(t_union *my_union)
{
	load_pistol(my_union);
	load_auto(my_union);
	load_knife(my_union);
}

//ЗАГРУЖАЕТ ИКОНКИ ОРУЖИЯ ДЛЯ ХУДА
void	load_weapons_minimize(t_union *my_union)
{
	int i;

	i = -1;
	my_union->weapons_mini_array[0] = SDL_LoadBMP("resources/pictures/weapon_img/auto.bmp");
	my_union->weapons_mini_array[1] = SDL_LoadBMP("resources/pictures/weapon_img/pistol.bmp");
	my_union->weapons_mini_array[2] = SDL_LoadBMP("resources/pictures/weapon_img/knife.bmp");
	while (++i < 3)
		if (!my_union->weapons_mini_array[i])
			ft_putstr("Weapon minimize surface not loaded\n");
}

//ЗАГРУЖАЕТ САРФЭЙС ХУДА
void	load_HUD(t_union *my_union)
{
	my_union->hud_surface = SDL_LoadBMP("resources/pictures/HUD/HUD.bmp");
	if (!my_union->surface)
		ft_putstr("HUD surface not loaded\n");
}

//ЗАГРУЖАЕТ ТЕКСТУРЫ В МАССИВ
void	load_wall_textures(t_union *my_union)
{
	int	i;

	i = -1;
	my_union->surface = SDL_LoadBMP("resources/pictures/WALLS/WALL14.bmp");
	if (!my_union->surface)
		ft_putstr("Surface not loaded\n");
	my_union->surface_array[0] = SDL_LoadBMP("resources/pictures/WALLS/WALL56.bmp");
	my_union->surface_array[1] = SDL_LoadBMP("resources/pictures/WALLS/WALL57.bmp");
	my_union->surface_array[2] = SDL_LoadBMP("resources/pictures/WALLS/WALL56.bmp");
	my_union->surface_array[3] = SDL_LoadBMP("resources/pictures/WALLS/WALL57.bmp");
	my_union->surface_array[4] = SDL_LoadBMP("resources/pictures/WALLS/WALL90.bmp");
	my_union->surface_array[5] = SDL_LoadBMP("resources/pictures/WALLS/WALL91.bmp");
	my_union->surface_array[6] = SDL_LoadBMP("resources/pictures/WALLS/WALL90.bmp");
	my_union->surface_array[7] = SDL_LoadBMP("resources/pictures/WALLS/WALL91.bmp");
	my_union->surface_array[8] = SDL_LoadBMP("resources/pictures/WALLS/WALL98.bmp");
	my_union->surface_array[9] = SDL_LoadBMP("resources/pictures/WALLS/WALL98.bmp");
	while (++i < 10)
		if (!my_union->surface_array[i])
			ft_putstr("Walls surface not loaded\n");
}

//ЗАГРУЖАЕТ САРФЭЙС МЕНЮ
void	load_menu(t_union *my_union)
{
	int i;

	i = -1;
	my_union->menu_array = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 4);
	my_union->menu_array[0] = SDL_LoadBMP("resources/pictures/menu/menu_new_game.bmp");
	my_union->menu_array[1] = SDL_LoadBMP("resources/pictures/menu/menu_sound.bmp");
	my_union->menu_array[2] = SDL_LoadBMP("resources/pictures/menu/menu_control.bmp");
	my_union->menu_array[3] = SDL_LoadBMP("resources/pictures/menu/menu_quit.bmp");
	while (++i < 4)
		if (!my_union->menu_array[i])
			ft_putstr("Menu surface not loaded\n");
}
