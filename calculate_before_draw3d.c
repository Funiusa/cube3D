/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_before_draw3d.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:02:51 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 18:02:55 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void		division_by_zero(t_vbls *vbls)
{
	if (vbls->ray_dir_y == 0)
		vbls->delta_dist_x = 0;
	else
		vbls->delta_dist_x =
				vbls->ray_dir_x == 0 ? 1 : fabs(1 / vbls->ray_dir_x);
	if (vbls->ray_dir_x == 0)
		vbls->delta_dist_y = 0;
	else
		vbls->delta_dist_y =
				vbls->ray_dir_y == 0 ? 1 : fabs(1 / vbls->ray_dir_y);
}

static void		euclidean_distance(t_vbls *vbls)
{
	if (vbls->ray_dir_x < 0)
	{
		vbls->step_x = -1;
		vbls->side_dst_x = (vbls->plx - vbls->map_x) * vbls->delta_dist_x;
	}
	else
	{
		vbls->step_x = 1;
		vbls->side_dst_x = (vbls->map_x + 1.0 - vbls->plx) * vbls->delta_dist_x;
	}
	if (vbls->ray_dir_y < 0)
	{
		vbls->step_y = -1;
		vbls->side_dst_y = (vbls->ply - vbls->map_y) * vbls->delta_dist_y;
	}
	else
	{
		vbls->step_y = 1;
		vbls->side_dst_y = (vbls->map_y + 1.0 - vbls->ply) * vbls->delta_dist_y;
	}
}

static int		dda_hit(t_vbls *vbls)
{
	if (vbls->side_dst_x < vbls->side_dst_y)
	{
		vbls->side_dst_x += vbls->delta_dist_x;
		vbls->map_x += vbls->step_x;
		vbls->side = 0;
	}
	else
	{
		vbls->side_dst_y += vbls->delta_dist_y;
		vbls->map_y += vbls->step_y;
		vbls->side = 1;
	}
	if (vbls->map[vbls->map_y][vbls->map_x] > '0'
		&& vbls->map[vbls->map_y][vbls->map_x] != '2')
		return (1);
	return (0);
}

static void		distance_to_wall(t_vbls *vbls)
{
	if (vbls->side == 0)
	{
		vbls->prp_wall_dist = (vbls->map_x - vbls->plx +
			(1 - (double)vbls->step_x) / 2) / vbls->ray_dir_x;
		if (vbls->ray_dir_x < 0)
			vbls->walldir = 'W';
		else
			vbls->walldir = 'E';
		vbls->img->wall_x = vbls->ply + vbls->prp_wall_dist * vbls->ray_dir_y;
	}
	else
	{
		vbls->prp_wall_dist = (vbls->map_y - vbls->ply
			+ (1 - (double)vbls->step_y) / 2) / vbls->ray_dir_y;
		if (vbls->ray_dir_y < 0)
			vbls->walldir = 'N';
		else
			vbls->walldir = 'S';
		vbls->img->wall_x = vbls->plx + vbls->prp_wall_dist * vbls->ray_dir_x;
	}
	vbls->line_hght = (int)(vbls->maph / vbls->prp_wall_dist);
	vbls->drw_start = -vbls->line_hght / 2 + vbls->maph / 2;
}

void			ray_position_direction(t_vbls *vbls)
{
	int		hit;

	vbls->ray_dir_x = vbls->dir_x + vbls->plane_x * vbls->cmra_x;
	vbls->ray_dir_y = vbls->dir_y + vbls->plane_y * vbls->cmra_x;
	vbls->map_x = (int)vbls->plx;
	vbls->map_y = (int)vbls->ply;
	division_by_zero(vbls);
	euclidean_distance(vbls);
	hit = 0;
	while (!hit)
		hit = dda_hit(vbls);
	vbls->img->tex_x = (int)(vbls->img->wall_x * (double)vbls->tex_width);
	distance_to_wall(vbls);
	vbls->img->tex_x = vbls->tex_width - vbls->img->tex_x - 1;
	vbls->img->wall_x -= floor(vbls->img->wall_x);
	if (vbls->drw_start < 0)
		vbls->drw_start = 0;
	vbls->drw_end = vbls->line_hght / 2 + vbls->maph / 2;
	if (vbls->drw_end >= vbls->maph)
		vbls->drw_end = vbls->maph - 1;
	choose_textures(vbls);
}
