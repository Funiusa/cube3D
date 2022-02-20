/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:08:36 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:09:40 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void		get_textures(t_vbls *vbls, void *tex)
{
	vbls->img->tx_addr = mlx_get_data_addr(tex,
		&vbls->img->tx_bpp, &vbls->img->tx_lnl, &vbls->img->tx_endian);
	vbls->img->i_addr = mlx_get_data_addr(vbls->img->image,
		&vbls->img->i_bpp, &vbls->img->i_lnl, &vbls->img->i_endian);
}

static void	sort_sprite(t_vbls *vbls, int *order, double *dist)
{
	int		i;
	int		j;
	int		dist_tmp;
	int		tmp;

	i = 0;
	while (i < vbls->count_sprites - 1)
	{
		j = 0;
		while (j < vbls->count_sprites - i - 1)
		{
			if (dist[j] < dist[j + 1])
			{
				dist_tmp = (int)dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = dist_tmp;
				tmp = order[j];
				order[j] = order[j + 1];
				order[1 + j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	calculate_sprite(t_vbls *vbls)
{
	vbls->invers_det = 1.0 /
			(vbls->plane_x * vbls->dir_y - vbls->dir_x * vbls->plane_y);
	vbls->trnsfrm_x = vbls->invers_det *
		(vbls->dir_y * vbls->spr_x - vbls->dir_x * vbls->spr_y);
	vbls->trnsfrm_y = vbls->invers_det *
		(-vbls->plane_y * vbls->spr_x + vbls->plane_x * vbls->spr_y);
	vbls->spr_screen_x = (int)(((double)vbls->mapw / 2) *
			(1.0 + vbls->trnsfrm_x / vbls->trnsfrm_y));
	vbls->spr_hgt = abs((int)(vbls->maph / (vbls->trnsfrm_y))) + 20;
	vbls->draw_start_y = -vbls->spr_hgt / 2 + vbls->maph / 2;
	if (vbls->draw_start_y < 0)
		vbls->draw_start_y = 0;
	vbls->draw_end_y = vbls->spr_hgt / 2 + vbls->maph / 2;
	if (vbls->draw_end_y >= vbls->maph)
		vbls->draw_end_y = vbls->maph - 1;
	vbls->spr_wdt = abs((int)(vbls->mapw / (vbls->trnsfrm_y * 2)));
	vbls->draw_strt_x = -vbls->spr_wdt / 2 + vbls->spr_screen_x;
	if (vbls->draw_strt_x < 0)
		vbls->draw_strt_x = 0;
	vbls->draw_end_x = vbls->spr_wdt / 2 + vbls->spr_screen_x;
	if (vbls->draw_end_x >= vbls->mapw)
		vbls->draw_end_x = vbls->mapw - 1;
	vbls->stripe = vbls->draw_strt_x;
}

static void	draw(t_vbls *vbls)
{
	int		y;
	int		d;

	while (vbls->stripe < vbls->draw_end_x)
	{
		vbls->tex_x = (int)(256 *
			(vbls->stripe - (-vbls->spr_wdt / 2 + vbls->spr_screen_x))
					* vbls->sp_height / vbls->spr_wdt) / 256;
		if (vbls->trnsfrm_y > 0 && vbls->stripe > 0
		&& vbls->stripe < vbls->mapw && vbls->trnsfrm_y
			&& vbls->trnsfrm_y < vbls->z_buf[vbls->stripe])
		{
			y = vbls->draw_start_y;
			while (y < vbls->draw_end_y)
			{
				d = (y) * 256 - vbls->maph * 128 + vbls->spr_hgt * 128;
				vbls->tex_y = ((d * vbls->sp_height) / vbls->spr_hgt) / 256;
				vbls->color = my_mlx_pixel_get(vbls, vbls->tex_x, vbls->tex_y);
				if (vbls->color != 0)
					my_mlx_pixel_put(vbls, vbls->stripe, y, vbls->color);
				y++;
			}
		}
		vbls->stripe++;
	}
}

void		draw_sprite(t_vbls *vbls)
{
	int		i;
	int		sprite_order[vbls->count_sprites];
	double	sprite_dist[vbls->count_sprites];

	i = 0;
	while (i < vbls->count_sprites)
	{
		sprite_order[i] = i;
		sprite_dist[i] = ((vbls->plx - vbls->sprites[i].x) *
		(vbls->plx - vbls->sprites[i].x) + (vbls->ply - vbls->sprites[i].y) *
					(vbls->ply - vbls->sprites[i].y));
		i++;
	}
	get_textures(vbls, vbls->sp_tex);
	sort_sprite(vbls, sprite_order, sprite_dist);
	i = 0;
	while (i < vbls->count_sprites)
	{
		vbls->spr_x = vbls->sprites[sprite_order[i]].x - vbls->plx;
		vbls->spr_y = vbls->sprites[sprite_order[i]].y - vbls->ply;
		calculate_sprite(vbls);
		draw(vbls);
		i++;
	}
}
