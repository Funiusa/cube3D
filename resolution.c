/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:12:06 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:12:08 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	resolution_path(char *line_map, t_vbls *vbls)
{
	int		i;

	i = 1;
	while (line_map[i] == ' ' || line_map[i] == '\t')
		i++;
	if (vbls->resolution)
		error_exit("No more resolution!\n");
	if (!ft_isdigit(line_map[i]))
		error_exit("No resolution or bad symbol in 1st resolution!\n");
	while (ft_isdigit(line_map[i]))
		vbls->mapw = (vbls->mapw * 10) + (line_map[i++] - '0');
	while (line_map[i] == ' ' || line_map[i] == '\t')
		i++;
	if (!ft_isdigit(line_map[i]))
		error_exit("No resolution or bad symbol in 2nd resolution!\n");
	while (ft_isdigit(line_map[i]))
		vbls->maph = (vbls->maph * 10) + (line_map[i++] - '0');
	while (line_map[i] == ' ' || line_map[i] == '\t')
		i++;
	if (line_map[i])
		error_exit("No more resolution i said!\n");
	vbls->resolution = 1;
	vbls->params++;
}

void	cheak_all_path(t_vbls *vbls)
{
	cheak_textures(vbls);
	if (vbls->maph < 1 || vbls->maph > 16384)
		error_exit("Height of resolution must be adequate!\n");
	if (vbls->mapw < 1 || vbls->mapw > 16384)
		error_exit("Width of resolution must be adequate!\n");
	mlx_get_screen_size(vbls->win->mlx, &vbls->res_w, &vbls->res_h);
	if (vbls->maph > vbls->res_h && !vbls->save)
		vbls->maph = vbls->res_h;
	if (vbls->mapw > vbls->res_w && !vbls->save)
		vbls->mapw = vbls->res_w;
	if (check_path(vbls->n_tex_path) == -1)
		error_exit("Сan't find north texture!\n");
	if (check_path(vbls->s_tex_path) == -1)
		error_exit("Сan't find south texture!\n");
	if (check_path(vbls->e_tex_path) == -1)
		error_exit("Сan't find east texture!\n");
	if (check_path(vbls->w_tex_path) == -1)
		error_exit("Сan't find west texture!\n");
	if (check_path(vbls->sp_tex_path) == -1)
		error_exit("Сan't find texture of sprite!\n");
}
