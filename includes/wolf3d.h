/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:03:11 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/07 13:53:39 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FRACTOL_H
# define __FRACTOL_H
# define SQR(x) x * x
# include "/usr/local/include/mlx.h"
# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <SDL.h>

# define NUM_OF_THR 200
# define BLOCK_SIZE	64

typedef struct	s_line
{
	int			dx;
	int			dy;
	int			inclinex;
	int			incliney;
	int			signx;
	int			signy;
	int			error;
	int			longline;
	int			shortline;
	int			i;
}				t_line;

typedef struct	s_int
{
	int			i;
	int			j;
}				t_int;

typedef struct	s_union
{
	void			*image_ptr;
	void			*mlx_ptr;
	char			*image_data;
	void			*win_ptr;
	double			scale;
	int				win_x;
	char			delta;
	double			shift_x;
	int				max_iter;
	double			cur_real;
	double			cur_imag;
	int				zoom_num;
	double			temp_real;
	double			half_win_x;
	double			half_win_y;
	int				cross;
	double			var_x;
	double			var_y;
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	char			mode;
	double			shift_y;
	int				win_y;
	int				bpp;
	int				save_fdf;
	int				endian;
	int				sl;
	FILE			*file;
	t_line			*line;
	t_int			*ints;
}				t_union;


typedef struct 	s_map
{
	int size_x;
	int size_y;
	int	**map;
}				t_map;

typedef struct	s_player
{
	int player_pos_x;
	int player_pos_y;
	int player_heigth;
	int player_width;

}				t_player;

void			check_event(t_union *my_union, t_map *map, t_player *player, const Uint8	*key);
void			draw_player(t_union my_union, t_player player);
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
