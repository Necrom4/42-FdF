/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:38:32 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/14 11:05:55 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	zoom(int keycode, t_fdf *fdf)
{
	if (keycode == 24 || keycode == 69)
		fdf->cam->zoom++;
	else if (keycode == 27 || keycode == 78)
		fdf->cam->zoom--;
	if (fdf->cam->zoom < 1)
		fdf->cam->zoom = 1;
	if (fdf->cam->zoom > 100)
		fdf->cam->zoom = 100;
}

void	rotate(int keycode, t_fdf *fdf)
{
	if (keycode == 91 || keycode == 13)
		fdf->cam->x_angle -= 0.05;
	else if (keycode == 84 || keycode == 1)
		fdf->cam->x_angle += 0.05;
	else if (keycode == 86 || keycode == 0)
		fdf->cam->y_angle -= 0.05;
	else if (keycode == 88 || keycode == 2)
		fdf->cam->y_angle += 0.05;
	else if (keycode == 89 || keycode == 12)
		fdf->cam->z_angle -= 0.05;
	else if (keycode == 92 || keycode == 14)
		fdf->cam->z_angle += 0.05;
}

void	move(int keycode, t_fdf *fdf)
{
	if (keycode == 126)
		fdf->cam->y_offset -= 15;
	else if (keycode == 125)
		fdf->cam->y_offset += 15;
	else if (keycode == 123)
		fdf->cam->x_offset -= 15;
	else if (keycode == 124)
		fdf->cam->x_offset += 15;
}

void	z_threshold(int keycode, t_fdf *fdf)
{
	if (keycode == 43 || keycode == 83)
		fdf->cam->z_offset *= 1.1;
	else if (keycode == 47 || keycode == 85)
		fdf->cam->z_offset /= 1.1;
	if (fdf->cam->z_offset > 50)
		fdf->cam->z_offset = 50;
	else if (fdf->cam->z_offset < 2)
		fdf->cam->z_offset = 2;
}

void	projection_change(t_fdf *fdf)
{
	fdf->cam->x_angle = 0;
	fdf->cam->y_angle = 0;
	fdf->cam->z_angle = 0;
	if (fdf->cam->projection)
		fdf->cam->projection = 0;
	else
		fdf->cam->projection = 1;
}
