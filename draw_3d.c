/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 23:57:29 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:08:29 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void		choose_textures(t_vbls *vbls)
{
	if (vbls->walldir == 'N')
	{
		get_textures(vbls, vbls->n_tex);
		vbls->tex_width = vbls->n_width;
		vbls->tex_height = vbls->n_height;
	}
	else if (vbls->walldir == 'S')
	{
		get_textures(vbls, vbls->s_tex);
		vbls->tex_width = vbls->s_width;
		vbls->tex_height = vbls->s_height;
	}
	else if (vbls->walldir == 'W')
	{
		get_textures(vbls, vbls->w_tex);
		vbls->tex_width = vbls->w_width;
		vbls->tex_height = vbls->w_height;
	}
	else if (vbls->walldir == 'E')
	{
		get_textures(vbls, vbls->e_tex);
		vbls->tex_width = vbls->e_width;
		vbls->tex_height = vbls->e_height;
	}
}

static void	draw(t_vbls *vbls, int x, double tex_pos, double step)
{
	int		y;

	y = vbls->drw_start - 1;
	while (y < vbls->drw_end)
	{
		vbls->img->tex_y = (int)tex_pos & (vbls->tex_height - 1);
		tex_pos += step;
		vbls->color = (int)my_mlx_pixel_get(vbls, vbls->img->tex_x,
											vbls->img->tex_y);
		if (x >= 0 && y >= 0)
			my_mlx_pixel_put(vbls, x, y, vbls->color);
		y++;
	}
}

void		draw_3d(t_vbls *vbls)
{
	int		x;
	double	step;
	double	tex_pos;

	x = 0;
	while (x < vbls->mapw)
	{
		vbls->cmra_x = 2 * x / (double)vbls->mapw - 1;
		ray_position_direction(vbls);
		step = 1.0 * vbls->tex_height / vbls->line_hght;
		tex_pos = (vbls->drw_start -
				(double)vbls->maph / 2 + (double)vbls->line_hght / 2) * step;
		draw(vbls, x, tex_pos, step);
		vbls->z_buf[x++] = vbls->prp_wall_dist;
	}
}
