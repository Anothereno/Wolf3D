/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:03:11 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/30 11:21:20 by hdwarven         ###   ########.fr       */
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
	Uint32 			*pixel_array;
	double 			time;
	int				win_y;
	SDL_Event		event;
	const Uint8		*key;
	Uint64			start_tick;
	Uint64			end_tick;
	int 			wall_heigth;
	int				save_fdf;
	int 			line_length;
	double 			distance;
	double 			delta_x;
	double 			ray_x;
	double 			ray_y;
	int 			start;
	int 			end;
	int				flag;
	double			delta_y;
	int				sl;
	FILE			*file;
	t_int			*ints;
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

	double 	distanse;
	double	fov;
	int		speed;
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
void			view_follow(t_player *player, t_map *map);
void			check_event(t_union *my_union, t_map *map, t_player *player, const Uint8	*key);
void			draw_player(t_union my_union, t_player player, t_map map);
void			draw_scene(t_union my_union, t_map map);
void			clear_window(t_union my_union);
void			initialize_SDL(t_union *my_union);
void			msg(char *message, t_map *my_union);
int				val_set(char *argv, t_map *my_union);
void			create_fdf(t_map *my_union);
void			pixel_fdf(t_map *my_union, int n);
void			ship(t_map *my_union, int x, int y);
void			put_cross(t_map *my_union);
void			mandelbrot(t_map *my_union, int x, int y);
int				mouse_move(int x, int y, t_map *param);
int				mouse_press(int key, int x, int y, t_map *param);
void			julia(t_map *my_union, int x, int y);
void			set_pixel(t_union *my_union, int y, int x, int num);
void			image_init(t_union *my_union);
void			change_mode(t_map *my_union);
void			shift_x(int key, t_map *my_union);
void			shift_y(int key, t_map *my_union);
void			zoom(int key, t_map *my_union);
int				exit_(t_map *my_union);
void			plot(t_union *my_union, t_map *map);
int				deal_key(int key, t_map *param);
void			usage(void);
void			struct_initial(t_union *my_union, t_map *map, t_player *player);

#endif
