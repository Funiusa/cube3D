/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:08:16 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:08:19 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void		draw_player_2d(t_vbls *vbls)
{
	int		i;
	int		j;

	i = 0;
	while (vbls->wall_size > i++)
	{
		j = 0;
		while (vbls->wall_size > j)
		{
			my_mlx_pixel_put(vbls, vbls->plx * vbls->wall_size + i + 5,
						vbls->ply * vbls->wall_size + j + 5, vbls->pl_color);
			j++;
		}
	}
}

static void	draw(t_vbls *vbls, int x, int y)
{
	int		i;
	int		j;
	int		color;

	i = y * vbls->wall_size;
	while (y * vbls->wall_size + vbls->wall_size > i++)
	{
		if (vbls->map[x][y] == '0')
			color = 0x3f6b5c;
		else if (vbls->map[x][y] == '1')
			color = 0x2d3033;
		else if (vbls->map[x][y] == '2')
			color = 0x5c2627;
		else
			break ;
		j = x * vbls->wall_size;
		while (x * vbls->wall_size + vbls->wall_size > j)
		{
			my_mlx_pixel_put(vbls, i + 5, j + 5, color);
			j++;
		}
	}
}

void		draw_map2d(t_vbls *vbls)
{
	int		x;
	int		y;

	y = 0;
	while (vbls->max_str > y)
	{
		x = 0;
		while (vbls->line_in_map > x)
		{
			draw(vbls, x, y);
			x++;
		}
		y++;
	}
}
