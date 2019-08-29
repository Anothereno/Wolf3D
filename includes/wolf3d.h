/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:03:11 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/29 18:11:04 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FRACTOL_H
# define __FRACTOL_H
# define ABS(x) x >= 0 ? x : -x
# define MAX(x,y) x >= y ? x : y
# include "/usr/local/include/mlx.h"
# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# define NUM_OF_THR 200
# define BLOCK_SIZE	64
# define RAD 0.0174533

typedef struct	s_int
{
	int			i;
	int			j;
}
t_int;

typedef struct	s_weapon
{
	int		x_start;
	int 	x_end;
	int		y_start;
	int 	y_end;
	int		width;
	double 	scale;
	int		cur_x;
	int		changing_flag;
}				t_weapon;

typedef struct	s_union
{
	char			*image_data;
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*main_window_texture;
	SDL_Texture		*weapon_texture;
	SDL_Texture     *hud_texture;
	SDL_Surface		*surface;
	SDL_Surface     *stats_surface;
	SDL_Texture     *stats_texture;
	SDL_Surface     *hud_surface;
	SDL_Surface		**wall_surfaces_array;
	SDL_Surface		**weapons_mini_array;
	SDL_Surface		*pistol;
	SDL_Surface		**menu_array;
	SDL_Surface		***weapons_surfaces;
	Uint32 			*pixel_array;
	float 			time;
	int				menu_mode;
	int				change_weapon_mode;
	int 			menu_frame;
	int				cur_win_x;
	int				cur_win_y;
	int				full_win_x;
	int				full_win_y;
	int				window_win_x;
	int				window_win_y;
	int 			mouse_handling;
	int 			fullscreen_mode;
	int             hud_start;
	int             half_win_y;
	int             half_win_x;
	int             mouse_state;
	int 			go_to_menu;
	int 			temp_int;
	float          	sens;
    float			FPS;
    int				load_mark;
    int             mouse_x;
    int             mouse_y;
	SDL_Event		event;
	const Uint8		*key_menu;
	const Uint8 	*key_game;
	Uint32 			*pixels;
	Uint64			start_tick;
	Uint64 			menu_tick;
	Uint64			end_tick;
	Uint64          rel_mouse_mode_timer;
	Uint64          door_timer_end;
	Uint64 			escape_timer;
	Uint64 			shoot_timer;
	Uint64 			reload_timer;
	Uint64			weapon_down_timer;
	int 			wall_heigth;
	int				wall_height_cof;
	double          dist;
	int 			start;
	int 			end;
	int 			weapon_down_mode;
	SDL_Rect        hud_rect;
	SDL_Rect        *stat_rects;
	SDL_Rect		weapon_place;
	int             flag;
	FILE			*file;
	t_int			*ints;
	SDL_Color		font_color;
	TTF_Font        *font;
	t_weapon		weapon_plce;
}				t_union;


typedef struct 	s_map
{
	int size_x;
	int size_y;
	int	**map;
}				t_map;



typedef struct	s_ray
{
	double	vert_distance;
	double 	hor_distance;
	double 	end_hor_x;
	double 	end_hor_y;
	double 	end_vert_x;
	double 	end_vert_y;
	int 	mode;
	int		offset;
	double 	x;
	double 	y;
	double	res_distance;
}				t_ray;

typedef struct	s_player
{
	float	player_pos_x;
	float	player_pos_y;
	int		player_heigth;
	int		player_width;
	float	direct_x;
	float	direct_y;
	float 	rotate_angle;
	int     move_indicate;

	int     score;
	int     level;
	int		lives;
	int 	health;
	int 	*ammo;
	int 	*clip_volume;
	int		*clip;
	int 	new_weapon;
	int 	weapon;
	int 	weapon_frame;
	int 	shoot_mode;

	float	fov;
	float  half_fov;
	int		speed;
	int     strafe_speed;
    float	view_direction;
    float 	view_direction_rad;
}				t_player;

void			change_hud_rect(t_union *my_union);
void			show_weapon_image(t_union *my_union, t_player *player);
void			print_ammo_in_stock(t_union *my_union, t_player *player);
void    		print_ammo_in_clip(t_union *my_union, t_player *player);
void			put_surface_to_render(t_union *my_union, char *info, int i);
int				check_loaded(t_union *my_union, int index, int size,
			int dimension);
void			check_weapons_and_quit(t_union *my_union, t_map *map, t_player *player,
			t_map *objects);
void			mouse_relative_handling(t_union *my_union, t_player *player);
void			check_rotates_keys(t_union *my_union, t_player *player);
void			check_movement_shooting_keys(t_union *my_union,
			t_map *map, t_player *player);
void			strafe(t_player *player, t_map *map, int mode);
void 			change_weapon(t_player *player, const Uint8 *key, t_union *my_union);
void			choice_menu(t_union *my_union);
void			change_menu_choice(t_union *my_union, char mode);
void			init_weapon_arrays(t_union *my_union);
void			init_weapon(t_union *my_union);
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
int 			check_invisible_pixels(SDL_Color *color);
void			draw_weapon(t_union *my_union, t_player *player, t_map *map);
void			print_fps(t_union *my_union);
void check_event_menu(t_union *my_union, t_map *map, t_player *player,
					  t_map *objects);
void 			start_game(t_union my_union, t_map map, t_player player, t_map objects);
void 			show_menu(t_union my_union);
char			*load_menu(t_union *my_union);
char			*load_hud(t_union *my_union);
char			*load_weapons(t_union *my_union);
char			*load_weapons_minimize(t_union *my_union);
void			draw_ceiling(t_union my_union, t_ray ray, int x, t_map map, double angle, t_player player);
//void			draw_floor(t_union my_union, t_ray ray, int x, t_map map, double angle);
void			draw_floor(t_union my_union, t_ray ray, int x, t_map map, double angle, t_player player);
void			choose_surface_floor_ceiling_hud(t_union *my_union, char mode);
void			choose_surface_wall(t_union *my_union, t_ray ray, t_map map);
void			put_black_pixel(t_union *my_union, int x, int y);
void			init_texture(t_union *my_union);
void			put_pixel(t_union *my_union, int x, int y, SDL_Color *color);
void            get_surface_pixel(t_union *my_union, int x, int y, SDL_Color *color);
void			draw_line_in_window(t_union *my_union, t_ray ray, int x, t_map map, t_player player, float angle);
//void			draw_line_in_window(t_union *my_union, t_ray ray, int x, t_map map);
void			draw_ceiling_and_floor(t_union my_union);
char			*load_wall_surfaces(t_union *my_union);
void			change_walls_color(t_union my_union, t_ray ray, t_player player);
int 			check_bound(double	x, double y, t_map map);
void			take_vector_of_view(t_player *player);
void vert_distance(t_player player, t_map map, t_ray *ray, float alpha);
void			raycast(t_union *my_union, t_map *map, t_player *player, t_ray *ray);
void hor_distance(t_player player, t_map map, t_ray *ray, float alpha);
void			trace_ray(t_union *my_union, t_map map, double x1, double y1, double x2, double y2, double alpha);
int				draw_vert_line(t_union my_union, int x, int y1, int y2);
//int				draw_line_in_window(t_union my_union, double x1, double y1, double y2);
void			draw_rays(t_union my_union, t_player player, t_map map);
void			change_speed(t_union *my_union, t_player *player);
void			move_forward(t_player *player, t_map *map, int mode, t_union *my_union);
void check_event_game(t_union *my_union, t_map *map, t_player *player,
					  t_map *objects);
void			draw_player(t_union my_union, t_player player, t_map map);
void			draw_scene(t_union my_union, t_map map);
void			clear_window(t_union my_union);
void			initialize_sdl(t_union *my_union);
int				val_set(char *argv, t_map *my_union, t_map *objects, t_player *player);
void			usage(void);
void			init(t_union *my_union, t_map *map, t_player *player, t_map *objects);
void	        put_cross(t_union *my_union, t_player *player);
void            check_door(t_map *map, t_map *objects, t_player *player, t_union *my_union);
int 	        check_wall(double cur_x, double cur_y, t_map map);
float take_range_angle(float angle);
void	        choose_distance(t_ray *ray);
void            show_stats(t_union *my_union, t_map *map, t_player *player);
void			complete_work(t_union *my_union, t_map *map, t_map *objects,
		t_player *player);

#endif
