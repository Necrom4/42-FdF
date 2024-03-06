/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:47:33 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/14 14:48:16 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	map_init(t_fdf *fdf)
{
	fdf->map = malloc(sizeof(t_map));
	if (!fdf->map)
		print_err("Map couldn't be initialized");
	fdf->map->width = 0;
	fdf->map->height = 0;
	fdf->map->z_min = 0;
	fdf->map->z_max = 0;
}

void	cam_init(t_fdf *fdf)
{
	fdf->cam = malloc(sizeof(t_cam));
	if (!fdf->cam)
		print_err("Camera couldn't be initialized");
	fdf->cam->zoom = ft_min(WIDTH / fdf->map->width / 2,
			HEIGHT / fdf->map->height / 2);
	fdf->cam->x_angle = 0;
	fdf->cam->y_angle = 0;
	fdf->cam->z_angle = 0;
	fdf->cam->x_offset = 0;
	fdf->cam->y_offset = 0;
	fdf->cam->z_offset = 10;
	fdf->cam->projection = 1;
}

void	mouse_init(t_fdf *fdf)
{
	fdf->mouse = malloc(sizeof(t_mouse));
	if (!fdf->mouse)
		print_err("Mouse couldn't be initialized");
	fdf->mouse->mode = 0;
}

void	fdf_init(t_fdf *fdf)
{
	if (!fdf)
		print_err("FDF coulnd't be initialized");
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "fdf");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
	map_init(fdf);
}
