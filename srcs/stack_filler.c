/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_filler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:49:08 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/14 15:30:51 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	get_wh(t_fdf *fdf, char *file)
{
	int		fd;
	char	*str;
	char	**strs;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_err("*.fdf error at opening");
	str = get_next_line(fd);
	if (!str)
		print_err("*.fdf empty");
	strs = ft_split(str, ' ');
	while (strs[fdf->map->width])
	{
		free(strs[fdf->map->width]);
		fdf->map->width++;
	}
	while (str)
	{
		free(str);
		fdf->map->height++;
		str = get_next_line(fd);
	}
	free(str);
	free(strs);
	close (fd);
}

void	negatives_neutralizer(t_fdf *fdf, char *str)
{
	int	x;
	int	y;
	int	mean;

	free(str);
	x = 0;
	y = 0;
	mean = (fdf->coords[0][0].z + fdf->coords[0][fdf->map->width - 1].z
			+ fdf->coords[fdf->map->height - 1][0].z
			+ fdf->coords[fdf->map->height - 1][fdf->map->width - 1].z) / 4;
	if (mean > 0)
		mean = -mean;
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			fdf->coords[y][x].z += mean;
			get_z_min_max(fdf->coords[y][x].z, fdf);
			x++;
		}
		y++;
	}
}

void	string_sep(t_fdf *fdf, char **sep_strs, int i, int *j)
{
	char	**new_str;

	new_str = ft_split(sep_strs[*j], ',');
	fdf->coords[i][*j].z = ft_atoi(new_str[0]);
	fdf->coords[i][*j].color = get_stack_color(new_str);
	free(sep_strs[*j]);
	free(new_str[0]);
	free(new_str[1]);
	free(new_str);
}

void	stack_filler(t_fdf *fdf, int fd, char *file)
{
	int		i;
	int		j;
	char	*str;
	char	**sep_strs;

	get_wh(fdf, file);
	fdf->coords = malloc(fdf->map->height * sizeof(int *));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_err("*.fdf error at opening");
	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		sep_strs = ft_split(str, ' ');
		j = -1;
		fdf->coords[i] = malloc(fdf->map->width * 2 * sizeof(int));
		while (sep_strs[++j])
			string_sep(fdf, sep_strs, i, &j);
		free(str);
		free(sep_strs);
		i++;
		str = get_next_line(fd);
	}
	negatives_neutralizer(fdf, str);
}
