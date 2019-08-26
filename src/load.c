/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:21:09 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/26 17:19:25 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface		*get_color_key(t_union *my_union, char *path)
{
	my_union->surface = SDL_LoadBMP(path);
	SDL_SetColorKey(my_union->surface, SDL_TRUE,
			SDL_MapRGB(my_union->surface->format, 152, 0, 136));
	return my_union->surface;
}

//ЗАГРУЖАЕТ САРФЭЙСЫ ПИСТОЛЕТА
char	*load_pistol(t_union *my_union)
{
	int i;

	i = -1;
	my_union->weapons_surfaces[1][0] = get_color_key(my_union,"resources/pictures/weapons/pistol/pistol1.bmp");
	my_union->weapons_surfaces[1][1] = get_color_key(my_union,"resources/pictures/weapons/pistol/pistol2.bmp");
	my_union->weapons_surfaces[1][2] = get_color_key(my_union,"resources/pictures/weapons/pistol/pistol3.bmp");
	my_union->weapons_surfaces[1][3] = get_color_key(my_union,"resources/pictures/weapons/pistol/pistol4.bmp");
	my_union->weapons_surfaces[1][4] = get_color_key(my_union,"resources/pictures/weapons/pistol/pistol5.bmp");
	my_union->weapons_surfaces[1][5] = get_color_key(my_union,"resources/pictures/weapons/pistol/pistol6.bmp");
	my_union->weapons_surfaces[1][6] = get_color_key(my_union,"resources/pictures/weapons/pistol/pistol7.bmp");
	my_union->weapons_surfaces[1][7] = get_color_key(my_union,"resources/pictures/weapons/pistol/pistol8.bmp");
	my_union->weapons_surfaces[1][8] = get_color_key(my_union,"resources/pictures/weapons/pistol/pistol9.bmp");
	my_union->weapons_surfaces[1][9] = get_color_key(my_union,"resources/pictures/weapons/pistol/pistol10.bmp");
	while (++i < 10)
		if (!my_union->weapons_surfaces[1][i])
			return ("Pistol surface not loaded\n");
	return (NULL);
}

//ЗАГРУЖАЕТ САРФЭЙСЫ НОЖА
char	*load_knife(t_union *my_union)
{
	int i;

	i = -1;
	my_union->weapons_surfaces[0][0] = SDL_LoadBMP("resources/pictures/weapons/knife/old knife1.bmp");
	my_union->weapons_surfaces[0][1] = SDL_LoadBMP("resources/pictures/weapons/knife/old knife2.bmp");
	my_union->weapons_surfaces[0][2] = SDL_LoadBMP("resources/pictures/weapons/knife/old knife3.bmp");
	my_union->weapons_surfaces[0][3] = SDL_LoadBMP("resources/pictures/weapons/knife/old knife4.bmp");
	my_union->weapons_surfaces[0][4] = SDL_LoadBMP("resources/pictures/weapons/knife/old knife5.bmp");
	while (++i < 5)
		if (!my_union->weapons_surfaces[0][i])
//			ft_putstr("Knife surface not loaded\n");
			return ("Knife surface not loaded\n");
	return (NULL);
}

//ЗАГРУЖАЕТ САРФЭЙСЫ АВТОМАТА
char	*load_auto(t_union *my_union)
{
	int i;

	i = -1;
	my_union->weapons_surfaces[2][0] = get_color_key(my_union, "resources/pictures/weapons/auto/auto1.bmp");
	my_union->weapons_surfaces[2][1] = get_color_key(my_union,"resources/pictures/weapons/auto/auto2.bmp");
	my_union->weapons_surfaces[2][2] = get_color_key(my_union,"resources/pictures/weapons/auto/auto3.bmp");
	my_union->weapons_surfaces[2][3] = get_color_key(my_union,"resources/pictures/weapons/auto/auto4.bmp");
	my_union->weapons_surfaces[2][4] = get_color_key(my_union,"resources/pictures/weapons/auto/auto5.bmp");
	my_union->weapons_surfaces[2][5] = get_color_key(my_union,"resources/pictures/weapons/auto/auto6.bmp");
	my_union->weapons_surfaces[2][6] = get_color_key(my_union,"resources/pictures/weapons/auto/auto7.bmp");
	my_union->weapons_surfaces[2][7] = get_color_key(my_union,"resources/pictures/weapons/auto/auto8.bmp");
	my_union->weapons_surfaces[2][8] = get_color_key(my_union,"resources/pictures/weapons/auto/auto9.bmp");
	my_union->weapons_surfaces[2][9] = get_color_key(my_union,"resources/pictures/weapons/auto/auto10.bmp");
	while (++i < 10)
		if (!my_union->weapons_surfaces[2][i])
//			ft_putstr("Auto surface not loaded\n");
			return ("Auto surface not loaded\n");
	return (NULL);

}

//ЗАГРУЖАЕТ ОРУЖИЕ
char	*load_weapons(t_union *my_union)
{
	char *message;

	if ((message = load_pistol(my_union)) ||
			(message = load_auto(my_union)) ||
			(message = load_knife(my_union)))
		return (message);
	my_union->load_mark++;
	return (NULL);
}

//ЗАГРУЖАЕТ ИКОНКИ ОРУЖИЯ ДЛЯ ХУДА
char	*load_weapons_minimize(t_union *my_union)
{
	int i;

	i = -1;
	my_union->weapons_mini_array[2] = SDL_LoadBMP("resources/pictures/weapon_img/auto.bmp");
	my_union->weapons_mini_array[1] = SDL_LoadBMP("resources/pictures/weapon_img/pistol.bmp");
	my_union->weapons_mini_array[0] = SDL_LoadBMP("resources/pictures/weapon_img/knife.bmp");
	while (++i < 3)
		if (!my_union->weapons_mini_array[i])
//			ft_putstr("Weapon minimize surface not loaded\n");
			return ("Weapon minimize surface not loaded\n");
	my_union->load_mark++;
	return (NULL);

}

//ЗАГРУЖАЕТ САРФЭЙС ХУДА
char	*load_HUD(t_union *my_union)
{
	my_union->hud_surface = SDL_LoadBMP("resources/pictures/HUD/HUD.bmp");
	if (!my_union->surface)
//		ft_putstr("HUD surface not loaded\n");
		return ("HUD surface not loaded\n");
	my_union->load_mark++;
	return (NULL);
}

//ЗАГРУЖАЕТ ТЕКСТУРЫ В МАССИВ
char	*load_wall_surfaces(t_union *my_union)
{
	int	i;

	i = -1;
	my_union->wall_surfaces_array[0] = SDL_LoadBMP("resources/pictures/WALLS/WALL56.bmp");
	my_union->wall_surfaces_array[1] = SDL_LoadBMP("resources/pictures/WALLS/WALL57.bmp");
	my_union->wall_surfaces_array[2] = SDL_LoadBMP("resources/pictures/WALLS/WALL56.bmp");
	my_union->wall_surfaces_array[3] = SDL_LoadBMP("resources/pictures/WALLS/WALL57.bmp");
	my_union->wall_surfaces_array[4] = SDL_LoadBMP("resources/pictures/WALLS/WALL90.bmp");
	my_union->wall_surfaces_array[5] = SDL_LoadBMP("resources/pictures/WALLS/WALL91.bmp");
	my_union->wall_surfaces_array[6] = SDL_LoadBMP("resources/pictures/WALLS/WALL90.bmp");
	my_union->wall_surfaces_array[7] = SDL_LoadBMP("resources/pictures/WALLS/WALL91.bmp");
	my_union->wall_surfaces_array[8] = SDL_LoadBMP("resources/pictures/WALLS/WALL98.bmp");
	my_union->wall_surfaces_array[9] = SDL_LoadBMP("resources/pictures/WALLS/WALL98.bmp");
	while (++i < 10)
		if (!my_union->wall_surfaces_array[i])
//			ft_putstr("Walls surface not loaded\n");
			return ("Walls surface not loaded\n");
	my_union->load_mark++;
	return (NULL);
}

//ЗАГРУЖАЕТ САРФЭЙС МЕНЮ
char	*load_menu(t_union *my_union)
{
	int i;

	i = -1;
	my_union->menu_array = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 4);
	my_union->menu_array[0] = SDL_LoadBMP("resources/pictures/menu/menu_new_game.bmp");
	my_union->menu_array[1] = SDL_LoadBMP("resources/pictures/menu/menu_sound.bmp");
	my_union->menu_array[2] = SDL_LoadBMP("resources/pictures/menu/menu_control.bmp");
	my_union->menu_array[3] = SDL_LoadBMP("resources/pictures/menu/menu_quit.bmp");
	while (++i < 4)
		if (!my_union->menu_array[i]) {
//			ft_putstr("Menu surface not loaded\n");
			return ("Menu surface not loaded\n");
		}
	my_union->load_mark++;
	return (NULL);
}
