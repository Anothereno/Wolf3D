/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:07:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/26 17:46:22 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//РАССЧИТЫВАЕТ СКОРОСТЬ ПЕРЕДВИЖЕНИЯ И ПОВОРОТА В ЗАВИСИМОСТИ ОТ ФРЭЙМРЭЙТА
void	change_speed(t_union *my_union, t_player *player)
{
	player->speed_move = my_union->time * 5.0;
	player->speed_rotate = my_union->time * 3.0;
}

//ИНИЦИАЛИЗИРУЕТ СДЛ ПЕРЕМЕННЫЕ
void	initialize_SDL(t_union *my_union) {
	int i;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("error\n");
		exit(0);
	}
	my_union->win = SDL_CreateWindow("Wolf3D",/*SDL_WINDOWPOS_CENTERED*/
									 200, /*SDL_WINDOWPOS_CENTERED*/200,
									 my_union->win_x, my_union->win_y, 0);
	my_union->renderer = SDL_CreateRenderer(my_union->win, 0,
											SDL_RENDERER_SOFTWARE);
	my_union->pixel_array = (Uint32 *) malloc(
			sizeof(Uint32) * my_union->win_x * my_union->win_y);
	my_union->main_window_texture = SDL_CreateTexture(my_union->renderer,
													  SDL_PIXELFORMAT_ARGB8888,
													  SDL_TEXTUREACCESS_STATIC,
													  my_union->win_x,
													  my_union->win_y);
	my_union->wall_surfaces_array = (SDL_Surface **) malloc(
			sizeof(SDL_Surface *) * 10);
	my_union->weapons_mini_array = (SDL_Surface **) malloc(
			sizeof(SDL_Surface *) * 3);
	my_union->weapons_surfaces = (SDL_Surface ***) malloc(
			sizeof(SDL_Surface **) * 3);
	i = -1;
	while (++i < 3) {
		if (!i)
			my_union->weapons_surfaces[i] = (SDL_Surface **) malloc(
					sizeof(SDL_Surface *) * 5);
		else
			my_union->weapons_surfaces[i] = (SDL_Surface **) malloc(
					sizeof(SDL_Surface *) * 10);

	}
}

//ГОТОВИТ МАССИВ ПРЯУГОЛЬНИКОВ ДЛЯ СТАТИСТИКИ В ХУДЕ
void    init_stats_rects(t_union *my_union) {
	int i;

	my_union->stat_rects = (SDL_Rect *) malloc(sizeof(SDL_Rect) * 8);
	i = -1;
	while (++i < 7) {
		my_union->stat_rects[i].h = my_union->hud_rect.h - 20;
		my_union->stat_rects[i].y = my_union->hud_rect.y + 20;
	}
	my_union->stat_rects[0].x = my_union->hud_rect.x + 50;
	my_union->stat_rects[0].w = my_union->stat_rects[0].h >> 1;
	my_union->stat_rects[1].x = my_union->hud_rect.x + 165;
	my_union->stat_rects[1].w = my_union->stat_rects[1].h << 1;
	my_union->stat_rects[2].x = my_union->hud_rect.x + 440;
	my_union->stat_rects[2].w = my_union->stat_rects[2].h >> 1;
	my_union->stat_rects[3].x = my_union->hud_rect.x + 670;
	my_union->stat_rects[3].w = (my_union->stat_rects[3].h << 1) - 50;
	my_union->stat_rects[4].x = my_union->hud_rect.x + 840;
	my_union->stat_rects[4].w = (my_union->stat_rects[4].h >> 1);
	my_union->stat_rects[5].x = my_union->hud_rect.x + 1050;
	my_union->stat_rects[5].w = my_union->stat_rects[4].h << 1;
	my_union->stat_rects[5].y -= 5;
	my_union->stat_rects[6].x =
			my_union->stat_rects[4].x + my_union->stat_rects[4].w;
	my_union->stat_rects[6].w = my_union->stat_rects[6].h - 20;


	my_union->stat_rects[7].h = 40;
	my_union->stat_rects[7].w = 40;
	my_union->stat_rects[7].x = 0;
	my_union->stat_rects[7].y = -10;
}

// ИНИЦИАЛИЗИРУЕТ ТТФ
void    initialize_TTF(t_union *my_union)
{
    if (TTF_Init() == -1)
    {
        printf("Unable to init SDL_TTF: %s", TTF_GetError());
    }
    my_union->font = TTF_OpenFont("resources/fonts/ui_font.ttf", 16);
    if (my_union->font == NULL)
        printf("Unable to load font: %s", TTF_GetError());
    init_stats_rects(my_union);
    my_union->font_color.r = 255;
    my_union->font_color.g = 255;
    my_union->font_color.b = 255;
    my_union->font_color.a = 255;
}

//ГОТОВИТ ГЛАВНУЮ СТРУКТУРУ
void	init_union(t_union *my_union)
{
	my_union->load_mark = 0;
	my_union->win_x = 1280;
	my_union->win_y = 720;
	my_union->half_win_y = my_union->win_y >> 1;
	my_union->half_win_x = my_union->win_x >> 1;
	my_union->door_timer_end = 0;
	my_union->escape_timer = 0;
	my_union->sens = 2.4;
	my_union->mouse_x = my_union->half_win_x;
	my_union->mouse_y = my_union->half_win_y;
	my_union->rel_mouse_mode_timer = 0;
	my_union->font = NULL;
	my_union->weapon_down_mode = 0;
	my_union->menu_mode = 1;
	my_union->menu_tick = 0;
	my_union->shoot_timer = 0;
	my_union->reload_timer = 0;
	my_union->weapon_down_timer = 0;
	my_union->go_to_menu = 0;
	my_union->menu_frame = 0;
	my_union->change_weapon_mode = 0;
	srand(time(NULL));
}

//ГОТОВИТ СТРУКТУРУ ДЛЯ ИГРОКА
void	init_player(t_union *my_union, t_player *player)
{
	player->player_heigth = 1;
	player->direct_x = 1;
	player->direct_y = 0;
	player->player_width = 1;
	player->radius = /*BLOCK_SIZE << 2;//200;//MAX(my_union->win_x, my_union->win_y)*/my_union->win_x * my_union->win_x;
	player->view_direction = 0;
	player->view_direction_rad = player->view_direction * RAD;
	player->speed = BLOCK_SIZE >> 3;
	player->strafe_speed = (BLOCK_SIZE >> 4) + 1;
	player->planeX = 0;
	player->planeY = 0.66;
	player->dirX = 0;
	player->dirY = 0;
	player->move_indicate = 0;
	player->rotate_angle = 3;
	player->time = 0;
	player->oldTime = 0;
	player->fov = 60;
	player->half_fov = player->fov * 0.5;

	player->score = 7200;
	player->level = 2;
	player->lives = 3;
	player->health = 100;
	player->ammo = (int*)malloc(sizeof(int) * 3);
	player->clip_volume = (int*)malloc(sizeof(int) * 3);
	player->clip = (int*)malloc(sizeof(int) * 3);
	player->ammo[0] = 1;
	player->ammo[1] = 40;
	player->ammo[2] = 80;
	player->clip_volume[0] = 1;
	player->clip_volume[1] = 7;
	player->clip_volume[2] = 20;
	player->clip[0] = player->clip_volume[0];
	player->clip[1] = player->clip_volume[1];
	player->clip[2] = player->clip_volume[2];
	player->weapon = 1;
	player->weapon_frame = 1;

	player->shoot_mode = 0;
}

//ГОТОВИТ СТРУКТУРУ ДЛЯ ОРУЖИЯ
void	init_weapon(t_union *my_union)
{
	my_union->weapon_place.w = my_union->win_x * 0.4;
	my_union->weapon_place.h = my_union->weapon_place.w;
	my_union->weapon_place.x = my_union->half_win_x - (my_union->weapon_place.w >> 1);//my_union->win_x * 0.25;
	my_union->weapon_place.y = (my_union->half_win_y >> 1) - 50;//
	// my_union->half_win_y;
	my_union->weapon_plce.y_start = my_union->half_win_y - 100;
	my_union->weapon_plce.y_end = my_union->hud_start;
	my_union->weapon_plce.width = my_union->weapon_plce.y_end - my_union->weapon_plce.y_start;
	my_union->weapon_plce.x_start = my_union->half_win_x - (my_union->weapon_plce.width >> 1)
			;//(my_union->half_win_y >> 1);
	my_union->weapon_plce.x_end = my_union->half_win_x + (my_union->weapon_plce.width >> 1);//(my_union->half_win_y >> 1);
	my_union->weapon_plce.scale = (float)BLOCK_SIZE / my_union->weapon_plce.width;
	my_union->weapon_plce.cur_x = 0;
	my_union->weapon_plce.changing_flag = 0;
}

//ГОТОВИТ ОКНО ДЛЯ ХУДА
void	init_HUD(t_union *my_union)
{
	my_union->hud_rect.w = my_union->win_x;
	my_union->hud_rect.h = my_union->win_y / 6;
	my_union->hud_rect.x = 0;
	my_union->hud_rect.y = my_union->win_y - my_union->hud_rect.h;//my_union->hud_start;
	my_union->hud_start = my_union->hud_rect.y;//my_union->win_y - (my_union->hud_surface->h * (my_union->win_x / my_union->hud_surface->w));
	my_union->hud_texture = SDL_CreateTextureFromSurface(my_union->renderer, my_union->hud_surface);
}

//ИНИЦИАЛИЗИРУЕТ ПЕРЕМЕННЫЕ СТРУКТУРЫ
void	init(t_union *my_union, t_map *map, t_player *player, t_map *objects) {
	char *message;

	init_union(my_union);
	init_player(my_union, player);
	my_union->dist = my_union->win_x / (tan(player->half_fov) * 2) * -360;
	initialize_SDL(my_union);
	if ((message = load_menu(my_union)) ||
		(message = load_wall_surfaces(my_union)) ||
		(message = load_weapons(my_union)) ||
		(message = load_HUD(my_union)) ||
		(message = load_weapons_minimize(my_union)))
	{
		ft_putstr(message);
		complete_work(my_union, map, objects, player);
	}
	init_HUD(my_union);
	init_weapon(my_union);
	initialize_TTF(my_union);
}

