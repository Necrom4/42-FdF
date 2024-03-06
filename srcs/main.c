/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:43:19 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/15 09:53:28 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_fdf	*fdf;

	if (argc == 2)
	{
		fd = 0;
		fdf = malloc(sizeof(t_fdf));
		fdf_init(fdf);
		stack_filler(fdf, fd, argv[1]);
		cam_init(fdf);
		mouse_init(fdf);
		draw(fdf);
		action_sensor(fdf);
		mlx_loop(fdf->mlx);
	}
	print_err("Must use one *.fdf file only");
	return (0);
}

int	print_err(char	*msg)
{
	ft_printf("%s\n", msg);
	exit(1);
}
