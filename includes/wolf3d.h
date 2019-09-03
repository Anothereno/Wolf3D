/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:03:11 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 12:52:21 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <SDL.h>
# include <SDL_ttf.h>
# define BLOCK_SIZE	64
# define RAD 0.0174533

typedef struct	s_point
{
	float	first_intersect_y;
	float	first_intersect_x;
	float	step_y;
	float	step_x;
	float	cur_point_x;
	float	cur_point_y;

}				t_point;

typedef struct	s_weapon
{
	int		x_start;
	int		x_end;
	int		y_start;
	int		y_end;
	int		width;
	double	scale;
	int		cur_x;
	int		changing_flag;
}				t_weapon;

typedef struct	s_obj_on_map
{
	char	ch;
	int		x;
	int		y;
}				t_obj_on_map;

typedef struct	s_union
{
	char			*image_data;
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*main_window_texture;
	SDL_Texture		*weapon_texture;
	SDL_Texture		*hud_texture;
	SDL_Surface		*surface;
	SDL_Surface		*stats_surface;
	SDL_Texture		*stats_texture;
	SDL_Surface		*hud_surface;
	SDL_Surface		**wall_surfaces_array;
	SDL_Surface		**weapons_mini_array;
	SDL_Surface		*pistol;
	SDL_Surface		**menu_array;
	SDL_Surface		***weapons_surfaces;
	Uint32			*pixel_array;
	float			time;
	int				menu_mode;
	int				change_weapon_mode;
	int				menu_frame;
	int				cur_win_x;
	int				cur_win_y;
	int				full_win_x;
	int				full_win_y;
	int				window_win_x;
	int				window_win_y;
	int				mouse_handling;
	int				fullscreen_mode;
	int				submenu_mode;
	int				hud_start;
	int				start_for_draw;
	int				half_win_y;
	int				half_win_x;
	int				mouse_state;
	int				go_to_menu;
	int				temp_int;
	float			sens;
	float			fps;
	int				load_mark;
	int				mouse_x;
	int				mouse_y;
	SDL_Event		event;
	const Uint8		*key_menu;
	const Uint8		*key_game;
	Uint32			*pixels;
	Uint64			start_tick;
	Uint64			menu_tick;
	Uint64			end_tick;
	Uint64			rel_mouse_mode_timer;
	Uint64			door_timer_end;
	Uint64			escape_timer;
	Uint64			shoot_timer;
	Uint64			reload_timer;
	Uint64			weapon_down_timer;
	Uint64			return_timer;
	int				wall_heigth;
	int				wall_height_cof;
	float			dist;
	int				start;
	int				end;
	int				weapon_down_mode;
	SDL_Rect		hud_rect;
	SDL_Rect		*stat_rects;
	SDL_Rect		weapon_place;
	int				flag;
	FILE			*file;
	SDL_Color		font_color;
	SDL_Color		texturing;
	TTF_Font		*font;
	t_weapon		weapon_plce;

}				t_union;

typedef struct	s_map
{
	int				size_x;
	int				size_y;
	int				**map;
	t_obj_on_map	obj_map;
}				t_map;

typedef struct	s_ray
{
	float	vert_distance;
	float	hor_distance;
	float	end_hor_x;
	float	end_hor_y;
	float	end_vert_x;
	float	end_vert_y;
	int		mode;
	int		offset;
	float	x;
	float	y;
	float	res_distance;
	float	sin_alpha;
	float	cos_alpha;
}				t_ray;

typedef struct	s_player
{
	float	player_pos_x;
	float	player_pos_y;
	float	rotate_angle;
	int		move_indicate;

	int		score;
	int		level;
	int		lives;
	int		health;
	int		*ammo;
	int		*clip_volume;
	int		*clip;
	int		new_weapon;
	int		weapon;
	int		weapon_frame;
	int		shoot_mode;

	float	fov;
	float	half_fov;
	float	speed;
	float	strafe_speed;
	float	view_direction;
	float	view_direction_rad;
}				t_player;

typedef struct	s_ceil_floor
{
	float		cos_angle;
	float		sin_angle;
	int			diff;
	int			x;
	int			y;
}				t_ceil_floor;

void			set_edges(t_map *map, t_map *objects);
void			map_processing(t_map *map, char **res, t_map *objects, t_player
		*player);
void			take_size(t_map *map, char *map_coordinates);
int				get_size(char *string);
int				set_player(t_map *map, t_map *objects, t_player *player,
		t_obj_on_map obj_on_map);
int				set_doors(t_map *map, t_map *objects, t_obj_on_map obj_on_map);
int				check_on_edge(t_map *map, int x, int y);
void			parse_string(char *str, t_map *map, int *size_x);
void			main_loop(t_union my_union, t_map map, t_map objects,
		t_player player);
void			zeroing_timers(t_union *my_union, t_player *player);
void			calc_time_fps(t_union *my_union);
void			check_intersection(t_map map, t_point *points);
void			draw_hud(t_union *my_union, t_player *player);
int				get_start_draw(t_union my_union);
void			calc_line(t_union *my_union, t_ray ray, float betta);
int				take_textures_offset(t_ray ray);
void			draw_ceiling_floor(t_union *my_union, t_player player,
		float angle, int x);
void			stat_rects_fullscreen(t_union *my_union);
void			stat_rects_windowed(t_union *my_union);
void			weapon_to_fullscreen(t_union *my_union);
void			change_resolution(t_union *my_union);
void			change_weapon_rect(t_union *my_union);
void			change_stat_rects(t_union *my_union);
void			change_hud_rect(t_union *my_union);
void			show_weapon_image(t_union *my_union, t_player *player);
void			print_ammo_in_stock(t_union *my_union, t_player *player);
void			print_ammo_in_clip(t_union *my_union, t_player *player);
void			put_surface_to_render(t_union *my_union, char *info, int i);
int				check_loaded(t_union *my_union, int index, int size,
		int dimension);
void			check_weapons_and_quit(t_union *my_union, t_map *map,
		t_player *player, t_map *objects);
void			mouse_relative_handling(t_union *my_union, t_player *player);
void			check_rotates_keys(t_union *my_union, t_player *player);
void			check_movement_shooting_keys(t_union *my_union,
		t_map *map, t_player *player);
void			strafe(t_player *player, t_map *map, float mode);
void			change_weapon(t_player *player, const Uint8 *key,
		t_union *my_union);
void			choice_menu(t_union *my_union);
void			change_menu_choice(t_union *my_union, char mode);
void			init_weapon_arrays(t_union *my_union);
void			weapon_to_windowed(t_union *my_union);
void			init_stats_rects(t_union *my_union);
void			init_union(t_union *my_union);
void			init_hud(t_union *my_union);
void			init_player(t_player *player);
void			msg(char *message);
void			free_font(t_union *my_union);
void			free_player(t_player *player);
void			free_stat_hud_rects(t_union *my_union);
void			free_map_and_objects(t_map *map, t_map *objects);
void			free_sdl(t_union *my_union);
void			free_map_and_objects(t_map *map, t_map *objects);
void			error_quit(char *msg, int i, t_map *map, t_map *objects);
void			weapon_down(t_union *my_union, t_player *player);
void			reload(t_union *my_union, t_player *player);
int				check_invisible_pixels(SDL_Color *color);
void			draw_weapon(t_union *my_union, t_player *player);
void			print_fps(t_union *my_union);
void			check_event_menu(t_union *my_union, t_map *map,
		t_player *player, t_map *objects);
void			start_game(t_union my_union, t_map map, t_player player,
		t_map objects);
void			show_menu(t_union my_union);
char			*load_menu(t_union *my_union);
char			*load_hud(t_union *my_union);
char			*load_weapons(t_union *my_union);
char			*load_weapons_minimize(t_union *my_union);
void			choose_surface_floor_ceiling_hud(t_union *my_union, char mode);
void			choose_surface_wall(t_union *my_union, t_ray ray, t_map map);
void			put_pixel(t_union *my_union, int x, int y, SDL_Color *color);
void			get_surface_pixel(t_union *my_union, int x, int y,
		SDL_Color *color);
void			draw_walls(t_union *my_union, t_ray ray, int x, t_map map);
char			*load_wall_surfaces(t_union *my_union);
int				check_bound(float x, float y, t_map map);
void			vert_distance(t_player player, t_map map, t_ray *ray,
		float alpha);
void			raycast(t_union *my_union, t_map *map, t_player *player,
		t_ray *ray);
void			hor_distance(t_player player, t_map map, t_ray *ray,
		float alpha);
void			move_forward(t_player *player, t_map *map, float mode);
void			check_event_game(t_union *my_union, t_map *map,
		t_player *player, t_map *objects);
void			initialize_sdl(t_union *my_union);
int				val_set(char *argv, t_map *my_union, t_map *objects,
		t_player *player);
void			usage(void);
void			init(t_union *my_union, t_map *map, t_player *player,
		t_map *objects);
void			put_cross(t_union *my_union, t_player *player);
void			check_door(t_map *map, t_map *objects, t_player *player,
		t_union *my_union);
int				check_wall(float cur_x, float cur_y, t_map map);
float			take_range_angle(float angle);
void			choose_distance(t_ray *ray);
void			show_stats(t_union *my_union, t_player *player);
void			complete_work(t_union *my_union, t_map *map, t_map *objects,
		t_player *player);

#endif
