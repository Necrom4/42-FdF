/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:01:18 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/15 10:09:21 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	rotation(t_point *point, t_fdf *fdf)
{
	int	prev_x;
	int	prev_y;

	prev_y = point->y;
	point->y = prev_y * cosf(fdf->cam->x_angle)
		+ point->z * sinf(fdf->cam->x_angle);
	point->z = -prev_y * sinf(fdf->cam->x_angle)
		+ point->z * cosf(fdf->cam->x_angle);
	prev_x = point->x;
	point->x = prev_x * cosf(fdf->cam->y_angle)
		+ point->z * sinf(fdf->cam->y_angle);
	point->z = -prev_x * sinf(fdf->cam->y_angle)
		+ point->z * cosf(fdf->cam->y_angle);
	prev_x = point->x;
	prev_y = point->y;
	point->x = prev_x * cosf(fdf->cam->z_angle)
		- prev_y * sinf(fdf->cam->z_angle);
	point->y = prev_x * sinf(fdf->cam->z_angle)
		+ prev_y * cosf(fdf->cam->z_angle);
}

void	projection(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = -z + (prev_x + prev_y) * sin(0.523599);
}

t_point	project(int x, int y, t_fdf *fdf)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = fdf->coords[y][x].z;
	point.color = fdf->coords[y][x].color;
	if (!point.color)
		point.color = get_default_color(point.z, fdf);
	point.x *= fdf->cam->zoom;
	point.y *= fdf->cam->zoom;
	point.z *= fdf->cam->zoom / fdf->cam->z_offset;
	point.x -= (fdf->map->width * fdf->cam->zoom) / 2;
	point.y -= (fdf->map->height * fdf->cam->zoom) / 2;
	rotation(&point, fdf);
	if (fdf->cam->projection == 1)
		projection(&point.x, &point.y, point.z);
	point.x += WIDTH / 2 + fdf->cam->x_offset;
	point.y += (HEIGHT + fdf->map->height / 2
			* fdf->cam->zoom) / 2 + fdf->cam->y_offset;
	return (point);
}
