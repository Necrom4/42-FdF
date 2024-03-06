/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:06:07 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/15 10:08:52 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/incs/libft.h"

//DEFINITIONS:

# define WIDTH	1920
# define HEIGHT	1080

//STRUCTURES

typedef struct s_stack
{
	int		z;
	int		color;
}	t_stack;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}	t_point;

typedef struct s_cam
{
	int		zoom;
	float	x_angle;
	float	y_angle;
	float	z_angle;
	int		x_offset;
	int		y_offset;
	float	z_offset;
	int		projection;
}	t_cam;

typedef struct s_map
{
	int		width;
	int		height;
	int		z_min;
	int		z_max;
}	t_map;

typedef struct s_mouse
{
	int		button;
	int		x;
	int		y;
	int		prev_x;
	int		prev_y;
	int		mode;
}	t_mouse;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	*map;
	t_cam	*cam;
	t_mouse	*mouse;
	t_stack	**coords;
}	t_fdf;

//FUNCTIONS:

void	fdf_init(t_fdf *fdf);

void	cam_init(t_fdf *fdf);

void	mouse_init(t_fdf *fdf);

int		ft_close(t_fdf *fdf);

void	draw(t_fdf *fdf);

void	action_sensor(t_fdf *fdf);

void	reset(t_fdf *fdf);

t_point	project(int x, int y, t_fdf *fdf);

void	stack_filler(t_fdf *fdf, const int fd, char *file);

void	coords_to_pts(t_fdf *fdf);

void	pixel_put(t_fdf *data, int x, int y, int color);

int		print_err(char	*msg);

int		ft_min(int a, int b);

void	zoom(int keycode, t_fdf *fdf);

void	rotate(int keycode, t_fdf *fdf);

void	move(int keycode, t_fdf *fdf);

void	z_threshold(int keycode, t_fdf *fdf);

void	projection_change(t_fdf *fdf);

void	zoom_mouse(int keycode, t_fdf *fdf);

void	z_threshold_mouse(int keycode, t_fdf *fdf);

double	percent(int start, int end, int current);

int		get_stack_color(char **strs);

int		get_default_color(int z, t_fdf *fdf);

int		get_color(t_point current, t_point start, t_point end, t_point delta);

void	get_z_min_max(int z, t_fdf *fdf);

#endif
