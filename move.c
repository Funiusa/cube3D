/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 19:24:37 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:11:04 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	forvard_back(int keycode, t_vbls *vbls, double speed)
{
	if (keycode == 13 || keycode == 1)
	{
		if (keycode == 1)
			speed *= -1;
		if (vbls->map[(int)(vbls->ply)][(int)(vbls->plx + vbls->dir_x * speed)]
		== '0'
		|| vbls->map[(int)(vbls->ply)][(int)(vbls->plx + vbls->dir_x * speed)]
		== '2')
			vbls->plx = vbls->plx + vbls->dir_x * speed;
		if (vbls->map[(int)(vbls->ply + vbls->dir_y * speed)][(int)
				(vbls->plx)] == '0'
		|| vbls->map[(int)(vbls->ply + vbls->dir_y * speed)][(int)
				(vbls->plx)] == '2')
			vbls->ply = vbls->ply + vbls->dir_y * speed;
	}
}

void	right_left(int keycode, t_vbls *vbls, double speed)
{
	if (keycode == 2 || keycode == 0)
	{
		if (keycode == 0)
			speed *= -1;
		if (vbls->map[(int)(vbls->ply)]
		[(int)(vbls->plx + vbls->plane_x * speed)] == '0'
		|| vbls->map[(int)(vbls->ply)]
					[(int)(vbls->plx + vbls->plane_x * speed)] == '2')
			vbls->plx = vbls->plx + vbls->plane_x * speed;
		if (vbls->map[(int)(vbls->ply + vbls->plane_y * speed)]
											[(int)(vbls->plx)] == '0'
		|| vbls->map[(int)(vbls->ply + vbls->plane_y * speed)]
											[(int)(vbls->plx)] == '2')
			vbls->ply = vbls->ply + vbls->plane_y * speed;
	}
}

void	rotation(t_vbls *vbls, int keycode)
{
	double	rot_speed;
	double	old_dirx;
	double	old_planex;

	old_dirx = vbls->dir_x;
	old_planex = vbls->plane_x;
	rot_speed = 0.066;
	if (keycode == 123)
		rot_speed *= -1;
	vbls->dir_x = vbls->dir_x * cos(rot_speed) - vbls->dir_y * sin(rot_speed);
	vbls->dir_y = old_dirx * sin(rot_speed) + vbls->dir_y * cos(rot_speed);
	vbls->plane_x = vbls->plane_x * cos(rot_speed)
					- vbls->plane_y * sin(rot_speed);
	vbls->plane_y = old_planex * sin(rot_speed) +
											vbls->plane_y * cos(rot_speed);
}

int		move_and_destroy(int keycode, t_vbls *vbls)
{
	vbls->speed = 0.33;
	if (keycode == 13 || keycode == 1 || keycode == 57)
		forvard_back(keycode, vbls, vbls->speed);
	else if (keycode == 2 || keycode == 0)
		right_left(keycode, vbls, vbls->speed);
	else if (keycode == 123 || keycode == 124)
		rotation(vbls, keycode);
	else if (keycode == 53)
	{
		mlx_destroy_window(vbls->win->mlx, vbls->win->win_mlx);
		free(vbls->z_buf);
		exit(0);
	}
	vbls->draw = 1;
	return (0);
}
