/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:11:52 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:11:54 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void		hero_in_the_map(t_vbls *vbls, int c, int i, int j)
{
	if (vbls->hero)
		error_exit("Only one hero!\n");
	if (!vbls->tmp[i - 1][j] || !vbls->tmp[i + 1][j]
	|| !vbls->tmp[i][j - 1] || !vbls->tmp[i][j + 1])
		error_exit("Problem with wall around the hero!\n");
	if (vbls->tmp[i - 1][j] != '1' && vbls->tmp[i - 1][j] != '0'
		&& vbls->tmp[i - 1][j] != '2')
		error_exit("Naked king!\n");
	if (vbls->tmp[i + 1][j] != '1' && vbls->tmp[i + 1][j] != '0'
		&& vbls->tmp[i + 1][j] != '2')
		error_exit("Naked king!\n");
	if (vbls->map[c][j - 1] == '4')
		error_exit("Naked king!\n");
	if (vbls->tmp[i][j + 1] != '1' && vbls->tmp[i][j + 1] != '2'
	&& vbls->tmp[i][j + 1] != '0')
		error_exit("Naked king!\n");
	vbls->hero = (int)vbls->tmp[i][j];
	vbls->plx = j;
	vbls->ply = c;
	vbls->map[c][j] = '0';
}

static void	player_dir(t_vbls *vbls)
{
	if (vbls->hero == 'W' || vbls->hero == 'E')
	{
		vbls->dir_x = -1.0;
		vbls->dir_y = -0.0;
		vbls->plane_x = 0.0;
		vbls->plane_y = -0.66;
		if (vbls->hero == 'E')
		{
			vbls->dir_x *= -1;
			vbls->plane_y *= -1;
		}
	}
	else if (vbls->hero == 'N' || vbls->hero == 'S')
	{
		vbls->dir_x = 0.0;
		vbls->plane_y = 0.0;
		vbls->dir_y = -1.0;
		vbls->plane_x = 0.66;
		if (vbls->hero == 'S')
		{
			vbls->dir_y *= -1;
			vbls->plane_x *= -1;
		}
	}
}

void		player(t_vbls *vbls)
{
	player_dir(vbls);
	vbls->plx += 0.05;
	vbls->ply += 0.05;
	vbls->pl_color = 0x575073;
}

void		check_null(t_vbls *vbls, int i, int j)
{
	if (vbls->tmp[i][j] == '0')
	{
		if (vbls->tmp[i - 1][j] != '0' && vbls->tmp[i - 1][j] != '1'
			&& vbls->tmp[i - 1][j] != '2' && vbls->tmp[i - 1][j] != 'S'
			&& vbls->tmp[i - 1][j] != 'N' && vbls->tmp[i - 1][j] != 'W'
			&& vbls->tmp[i - 1][j] != 'E')
			error_exit("Need a wall!\n");
		if (vbls->tmp[i + 1][j] != '0' && vbls->tmp[i + 1][j] != '1'
			&& vbls->tmp[i + 1][j] != '2' && vbls->tmp[i + 1][j] != 'S'
			&& vbls->tmp[i + 1][j] != 'N' && vbls->tmp[i + 1][j] != 'W'
			&& vbls->tmp[i + 1][j] != 'E')
			error_exit("Need a wall!\n");
		if (vbls->tmp[i][j + 1] != '0' && vbls->tmp[i][j + 1] != '1'
			&& vbls->tmp[i][j + 1] != '2' && vbls->tmp[i][j + 1] != 'S'
			&& vbls->tmp[i][j + 1] != 'N' && vbls->tmp[i][j + 1] != 'W'
			&& vbls->tmp[i][j + 1] != 'E')
			error_exit("Need a wall!\n");
		if (vbls->tmp[i][j - 1] != '0' && vbls->tmp[i][j - 1] != '1'
			&& vbls->tmp[i][j - 1] != '2' && vbls->tmp[i][j - 1] != 'S'
			&& vbls->tmp[i][j - 1] != 'N' && vbls->tmp[i][j - 1] != 'W'
			&& vbls->tmp[i][j - 1] != 'E')
			error_exit("Need a wall!\n");
	}
}
