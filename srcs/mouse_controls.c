/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:53:51 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/15 10:07:58 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fdf.h"

void	zoom_mouse(int mousecode, t_fdf *fdf)
{
	if (mousecode == 4)
		fdf->cam->zoom += 2;
	else if (mousecode == 5)
		fdf->cam->zoom -= 2;
	if (fdf->cam->zoom < 1)
		fdf->cam->zoom = 1;
	if (fdf->cam->zoom > 100)
		fdf->cam->zoom = 100;
}

void	z_threshold_mouse(int mousecode, t_fdf *fdf)
{
	if (mousecode == 5)
		fdf->cam->z_offset *= 1.1;
	else if (mousecode == 4)
		fdf->cam->z_offset /= 1.1;
	if (fdf->cam->z_offset > 50)
		fdf->cam->z_offset = 50;
	else if (fdf->cam->z_offset < 2)
		fdf->cam->z_offset = 2;
}
