/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:35:34 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/14 14:28:10 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

int	mouse_press(int mousecode, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (mousecode == 3)
	{
		if (fdf->mouse->mode == 1)
			fdf->mouse->mode = 0;
		else
			fdf->mouse->mode++;
	}
	else if (fdf->mouse->mode == 0 && (mousecode == 4 || mousecode == 5))
		zoom_mouse(mousecode, fdf);
	else if (fdf->mouse->mode == 1 && (mousecode == 4 || mousecode == 5))
		z_threshold_mouse(mousecode, fdf);
	else if (mousecode == 1 || mousecode == 2)
	{
		fdf->mouse->button = mousecode;
		fdf->mouse->prev_x = x;
		fdf->mouse->prev_y = y;
	}
	draw(fdf);
	return (0);
}

int	mouse_release(int mousecode, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	(void)mousecode;
	fdf->mouse->button = 0;
	return (0);
}

int	mouse_move(int x, int y, t_fdf *fdf)
{
	fdf->mouse->prev_x = fdf->mouse->x;
	fdf->mouse->prev_y = fdf->mouse->y;
	fdf->mouse->x = x;
	fdf->mouse->y = y;
	if (fdf->mouse->button == 1)
	{
		fdf->cam->x_offset += x - fdf->mouse->prev_x;
		fdf->cam->y_offset += y - fdf->mouse->prev_y;
		fdf->mouse->prev_x = x;
		fdf->mouse->prev_y = y;
		draw(fdf);
	}
	else if (fdf->mouse->button == 2)
	{
		fdf->cam->y_angle += (x - fdf->mouse->prev_x) * 0.002;
		fdf->cam->x_angle += (y - fdf->mouse->prev_y) * 0.002;
		draw(fdf);
	}
	return (0);
}

int	keyhook(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		ft_close(fdf);
	else if (keycode == 24 || keycode == 69 || keycode == 27 || keycode == 78)
		zoom(keycode, fdf);
	else if (keycode == 126 || keycode == 125 || keycode == 123
		|| keycode == 124)
		move(keycode, fdf);
	else if (keycode == 91 || keycode == 13 || keycode == 84 || keycode == 1
		|| keycode == 86 || keycode == 0 || keycode == 88 || keycode == 2
		|| keycode == 89 || keycode == 12 || keycode == 92 || keycode == 14)
		rotate(keycode, fdf);
	else if (keycode == 43 || keycode == 47 || keycode == 83 || keycode == 85)
		z_threshold(keycode, fdf);
	else if (keycode == 87 || keycode == 49)
		projection_change(fdf);
	else if (keycode == 82 || keycode == 71 || keycode == 51)
		reset(fdf);
	draw(fdf);
	return (0);
}

void	action_sensor(t_fdf *fdf)
{
	mlx_do_key_autorepeaton(fdf->mlx);
	mlx_hook(fdf->win, 2, 0, keyhook, fdf);
	mlx_hook(fdf->win, 17, 0, ft_close, fdf);
	mlx_hook(fdf->win, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->win, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->win, 6, 0, mouse_move, fdf);
}
