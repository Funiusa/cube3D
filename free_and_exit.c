/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:10:23 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:10:25 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	error_exit(char *message)
{
	printf("%sERROR!\n%s%s", RED, YEL, message);
	exit(errno);
}

int		close_window(int keycode, t_vbls *vbls)
{
	(void)keycode;
	(void)vbls;
	exit(0);
}

void	init_vars_map(t_vbls *vbls)
{
	vbls->mapw = 0;
	vbls->maph = 0;
	vbls->n_tex_path = NULL;
	vbls->s_tex_path = NULL;
	vbls->e_tex_path = NULL;
	vbls->w_tex_path = NULL;
	vbls->sp_tex_path = NULL;
	vbls->tmp = NULL;
	vbls->ceiling_color = 0;
	vbls->floor_color = 0;
	vbls->resolution = 0;
	vbls->texture_no = 0;
	vbls->texture_so = 0;
	vbls->texture_ea = 0;
	vbls->texture_we = 0;
	vbls->first_line_map = 0;
	vbls->hero = 0;
	vbls->sprite = 0;
	vbls->floor = 0;
	vbls->ceiling = 0;
	vbls->map_end = 0;
	vbls->params = 0;
}

void	free_tmp_mass(t_vbls *vbls)
{
	int		i;

	i = 0;
	while (vbls->tmp[i])
		free(vbls->tmp[i++]);
	free(vbls->tmp);
}

void	bad_malloc(t_vbls *vbls)
{
	if (vbls->win == NULL || vbls->img == NULL || vbls->z_buf == NULL
	|| vbls->map == NULL || vbls->tmp == NULL || vbls->sprites == NULL)
		error_exit("Memory allocation error\n");
}
