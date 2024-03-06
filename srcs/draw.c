/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:47:12 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/15 10:05:18 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
	{
		dst = fdf->addr + (y * fdf->line_length + x
				* (fdf->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	line_modif(t_point *delta, t_point *sign, t_point *cur, int *error)
{
	error[1] = error[0] * 2;
	if (error[1] > -delta->y)
	{
		error[0] -= delta->y;
		cur->x += sign->x;
	}
	if (error[1] < delta->x)
	{
		error[0] += delta->x;
		cur->y += sign->y;
	}
}

void	draw_line(t_point a, t_point b, t_fdf *fdf)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		error[2];

	delta.x = abs(b.x - a.x);
	delta.y = abs(b.y - a.y);
	if (a.x < b.x)
		sign.x = 1;
	else
		sign.x = -1;
	if (a.y < b.y)
		sign.y = 1;
	else
		sign.y = -1;
	error[0] = delta.x - delta.y;
	cur = a;
	while (cur.x != b.x || cur.y != b.y)
	{
		pixel_put(fdf, cur.x, cur.y, get_color(cur, a, b, delta));
		line_modif(&delta, &sign, &cur, error);
	}
}

void	print_menu(t_fdf *fdf)
{
	int		y;

	y = 0;
	mlx_string_put(fdf->mlx, fdf->win, 15, y += 20, 0xFF0000, "CONTROLS");
	mlx_string_put(fdf->mlx, fdf->win, 15, y += 20, 0xFF0000,
		"Mode: Mouse middle click");
	mlx_string_put(fdf->mlx, fdf->win, 15, y += 20, 0xFF0000,
		"Move: Left click or Arrows");
	mlx_string_put(fdf->mlx, fdf->win, 15, y += 20, 0xFF0000,
		"Zoom: Mode 1 scroll or +/-");
	mlx_string_put(fdf->mlx, fdf->win, 15, y += 20, 0xFF0000,
		"Rotate: Right click or");
	mlx_string_put(fdf->mlx, fdf->win, 30, y += 20, 0xFF0000, "    ^");
	mlx_string_put(fdf->mlx, fdf->win, 30, y += 20, 0xFF0000, "^   |   ^");
	mlx_string_put(fdf->mlx, fdf->win, 30, y += 20, 0xFF0000, " \\7 8 9/");
	mlx_string_put(fdf->mlx, fdf->win, 30, y += 20, 0xFF0000, "<-4(5)6->");
	mlx_string_put(fdf->mlx, fdf->win, 30, y += 20, 0xFF0000, " (1)2(3)");
	mlx_string_put(fdf->mlx, fdf->win, 30, y += 20, 0xFF0000, "    |");
	mlx_string_put(fdf->mlx, fdf->win, 30, y += 20, 0xFF0000, "    V");
	mlx_string_put(fdf->mlx, fdf->win, 15, y += 20, 0xFF0000,
		"Altitude: Mode 2 scroll or 1/3");
	mlx_string_put(fdf->mlx, fdf->win, 15, y += 20, 0xFF0000,
		"Projection: Num Pad 5");
	mlx_string_put(fdf->mlx, fdf->win, 15, y += 20, 0xFF0000,
		"Reset: Num Pad 0/Clear/Delete");
}

void	draw(t_fdf *fdf)
{
	int	x;
	int	y;

	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img,
			&fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x != fdf->map->width - 1)
				draw_line(project(x, y, fdf),
					project(x + 1, y, fdf), fdf);
			if (y != fdf->map->height - 1)
				draw_line(project(x, y, fdf),
					project(x, y + 1, fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	print_menu(fdf);
}
