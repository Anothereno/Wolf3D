/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:03:11 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/17 16:39:12 by hdwarven         ###   ########.fr       */
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
# include <SDL_image.h>
# define NUM_OF_THR 200
# define BLOCK_SIZE	64
# define RAD 0.0174533

typedef struct	s_int
{
	int			i;
	int			j;
}				t_int;

typedef struct	s_union
{
	char			*image_data;
	int				win_x;
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Texture     *hud_texture;
	SDL_Surface		*surface;
	SDL_Surface     *hud_surface;
	SDL_Surface		**surface_array;
	Uint32 			*pixel_array;
	double 			time;
	int				win_y;
	int             hud_start;
	int             half_win_y;
	int             half_win_x;
	int             mouse_x;
	double          sens;
	int             mouse_y;
	SDL_Event		event;
	const Uint8		*key;
	Uint32 			*pixels;
	Uint64			start_tick;
	Uint64			end_tick;
	Uint64          door_timer_start;
	Uint64          door_timer_end;
	int 			wall_heigth;
	double          dist;
	int 			start;
	int 			end;
	SDL_Rect        hud_rect;
	int             flag;
	FILE			*file;
	t_int			*ints;
	SDL_Color		*color;
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
	double	player_pos_x;
	double	player_pos_y;
	int		player_heigth;
	int		player_width;
	double	direct_x;
	double	direct_y;
	int 	rotate_angle;
	int     move_indicate;

	double 	distanse;
	double	fov;
	double  half_fov;
	int		speed;
	int     strafe_speed;
	int		radius;
	int		view_direction;
	double 	speed_move;
	double 	speed_rotate;


	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldTime;
}				t_player;

void			draw_ceiling(t_union my_union, t_ray ray, int x, t_map map, double angle, t_player player);

//void			draw_floor(t_union my_union, t_ray ray, int x, t_map map, double angle);
void			draw_floor(t_union my_union, t_ray ray, int x, t_map map, double angle, t_player player);
void			choose_surface_floor_ceiling_hud(t_union *my_union, char mode);
void			choose_surface_wall(t_union *my_union, t_ray ray, t_map map);
void			put_black_pixel(t_union *my_union, int x, int y);
void			init_texture(t_union *my_union);
void			put_pixel(t_union *my_union, int x, int y, SDL_Color *color);
void            get_surface_pixel(t_union *my_union, int x, int y, SDL_Color *color);
void			draw_line(t_union *my_union, t_ray ray, int x, t_map map, t_player player, double angle);
//void			draw_line(t_union *my_union, t_ray ray, int x, t_map map);
void			draw_ceiling_and_floor(t_union my_union);
void			load_textures(t_union *my_union);
void			change_walls_color(t_union my_union, t_ray ray, t_player player);
int 			check_bound(double	x, double y, t_map map);
void			take_vector_of_view(t_player *player);
void			vert_distance(t_union *my_union, t_player player, t_map map, t_ray *ray, double alpha);
void			raycast(t_union my_union, t_map map, t_player player, t_ray ray);
void			hor_distance(t_union *my_union, t_player player, t_map map, t_ray *ray, double alpha);
void			trace_ray(t_union *my_union, t_map map, double x1, double y1, double x2, double y2, double alpha);
int				draw_vert_line(t_union my_union, int x, int y1, int y2);
//int				draw_line(t_union my_union, double x1, double y1, double y2);
void			draw_rays(t_union my_union, t_player player, t_map map);
void			change_speed(t_union *my_union, t_player *player);
void			view_follow(t_player *player, t_map *map, int mode);
void			check_event(t_union *my_union, t_map *map, t_player *player, t_map *objects, const Uint8	*key);
void			draw_player(t_union my_union, t_player player, t_map map);
void			draw_scene(t_union my_union, t_map map);
void			clear_window(t_union my_union);
void			initialize_SDL(t_union *my_union);
void			msg(char *message, t_map *my_union);
int				val_set(char *argv, t_map *my_union, t_map *objects, t_player *player);
void			usage(void);
void			struct_initial(t_union *my_union, t_map *map, t_player *player, t_map *objects);
void	        put_cross(t_union *my_union, t_player *player);
void            check_door(t_map *map, t_map *objects, t_player *player, t_union *my_union);
int 	        check_wall(double cur_x, double cur_y, t_map map);
double          take_range_angle(double angle);
void	        choose_distance(t_ray *ray);

#endif
