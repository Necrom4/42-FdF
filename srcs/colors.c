/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:28:17 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/14 14:25:16 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

int	get_default_color(int z, t_fdf *fdf)
{
	if (!z)
		return (0xA00000);
	if ((z - fdf->map->z_min) * 100 / (fdf->map->z_max - fdf->map->z_min) < 20)
		return (0xA00000);
	if ((z - fdf->map->z_min) * 100 / (fdf->map->z_max - fdf->map->z_min) < 40)
		return (0xB50000);
	if ((z - fdf->map->z_min) * 100 / (fdf->map->z_max - fdf->map->z_min) < 60)
		return (0xC00000);
	if ((z - fdf->map->z_min) * 100 / (fdf->map->z_max - fdf->map->z_min) < 80)
		return (0xD40000);
	else
		return (0xFF0000);
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(t_point current, t_point start, t_point end, t_point delta)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	red = get_light((start.color >> 16) & 0xFF,
			(end.color >> 16) & 0xFF, percentage);
	green = get_light((start.color >> 8) & 0xFF,
			(end.color >> 8) & 0xFF, percentage);
	blue = get_light(start.color & 0xFF,
			end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

int	get_stack_color(char **strs)
{
	int		res;
	int		i;
	char	str[11];

	res = 0;
	i = 2;
	if (strs[1])
	{
		while (strs[1][i])
		{
			str[i - 2] = strs[1][i];
			i++;
		}
		if (str[0])
			res = ft_atoi_base(str, 16);
	}
	else
		res = 0;
	return (res);
}
