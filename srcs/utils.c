/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:09:48 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/15 10:08:07 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

int	ft_close(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map->height)
		free(fdf->coords[i++]);
	free(fdf->coords);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_image(fdf->mlx, fdf->img);
	free(fdf->map);
	free(fdf->cam);
	free(fdf->mouse);
	free(fdf);
	exit(0);
}

void	reset(t_fdf *fdf)
{
	fdf->cam->zoom = ft_min(WIDTH / fdf->map->width / 2,
			HEIGHT / fdf->map->height / 2);
	fdf->cam->x_angle = 0;
	fdf->cam->y_angle = 0;
	fdf->cam->z_angle = 0;
	fdf->cam->x_offset = 0;
	fdf->cam->y_offset = 0;
	fdf->cam->z_offset = 10;
	fdf->cam->projection = 1;
	fdf->mouse->mode = 0;
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	else
		return (placement / distance);
}

void	get_z_min_max(int z, t_fdf *fdf)
{
	if (z < fdf->map->z_min)
		fdf->map->z_min = z;
	else if (z > fdf->map->z_max)
		fdf->map->z_max = z;
}
