/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:10:07 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:10:10 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	wall_around_sprite(t_vbls *vbls, int i, int j)
{
	if (vbls->tmp[i][j + 1] == ' ' || vbls->tmp[i][j - 1] == ' ')
		error_exit("Sprites need a company!\n");
	if (vbls->tmp[i - 1][j] == ' ' || vbls->tmp[i + 1][j] == ' ')
		error_exit("Sprites need a company!\n");
	vbls->count_sprites++;
}

void	get_sprites(t_vbls *vbls)
{
	int			x;
	int			y;
	int			i;

	y = 0;
	i = 0;
	if (!(vbls->sprites = malloc(sizeof(t_sprite) * vbls->count_sprites)))
		bad_malloc(vbls);
	while (y < vbls->line_in_map - 1)
	{
		x = 0;
		while (x < vbls->max_str)
		{
			if (vbls->map[y][x] == '2')
			{
				vbls->sprites[i].x = x + 0.5;
				vbls->sprites[i++].y = y + 0.5;
			}
			x++;
		}
		y++;
	}
}
