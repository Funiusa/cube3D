/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:12:33 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:12:36 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	get_path(t_vbls *vbls)
{
	vbls->ceiling_color = create_trgb(0, vbls->ceiling_color_r,
				vbls->ceiling_color_g, vbls->ceiling_color_b);
	vbls->floor_color = create_trgb(0, vbls->floor_color_r,
				vbls->floor_color_g, vbls->floor_color_b);
	vbls->n_tex = mlx_xpm_file_to_image(vbls->win->mlx, vbls->n_tex_path,
				&vbls->n_width, &vbls->n_height);
	vbls->s_tex = mlx_xpm_file_to_image(vbls->win->mlx, vbls->s_tex_path,
				&vbls->s_width, &vbls->s_height);
	vbls->w_tex = mlx_xpm_file_to_image(vbls->win->mlx, vbls->w_tex_path,
				&vbls->w_width, &vbls->w_height);
	vbls->e_tex = mlx_xpm_file_to_image(vbls->win->mlx, vbls->e_tex_path,
				&vbls->e_width, &vbls->e_height);
	vbls->sp_tex = mlx_xpm_file_to_image(vbls->win->mlx, vbls->sp_tex_path,
				&vbls->sp_width, &vbls->sp_height);
}

void	so_no_path(char *s, t_vbls *vbls, int i, int j)
{
	if (s[0] == 'N')
	{
		if (vbls->texture_no)
			error_exit("North texture path already defined!\n");
		vbls->n_tex_path = ft_substr(s, i, j);
		cheak_xpm(vbls->n_tex_path);
		vbls->texture_no = 1;
		vbls->params++;
	}
	else if (s[0] == 'S')
	{
		if (vbls->texture_so)
			error_exit("South texture path already defined!\n");
		vbls->s_tex_path = ft_substr(s, i, j);
		cheak_xpm(vbls->s_tex_path);
		vbls->texture_so = 1;
		vbls->params++;
	}
}

void	ea_we_path(char *s, t_vbls *vbls, int i, int j)
{
	if (s[0] == 'W')
	{
		if (vbls->texture_we)
			error_exit("West texture path already defined!\n");
		vbls->w_tex_path = ft_substr(s, i, j);
		cheak_xpm(vbls->w_tex_path);
		vbls->texture_we = 1;
		vbls->params++;
	}
	else if (s[0] == 'E')
	{
		if (vbls->texture_ea)
			error_exit("East texture path already defined!\n");
		vbls->e_tex_path = ft_substr(s, i, j);
		cheak_xpm(vbls->e_tex_path);
		vbls->texture_ea = 1;
		vbls->params++;
	}
}

void	sp_tex_path(char *s, t_vbls *vbls)
{
	int		i;
	int		j;

	i = 1;
	if (!vbls->sprite)
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		j = i;
		while (s[j] != ' ' && s[j] != '\0')
			j++;
		vbls->sp_tex_path = ft_substr(s, i, j);
		cheak_xpm(vbls->sp_tex_path);
		vbls->sprite = 1;
		vbls->params++;
		while (s[j] == ' ' || s[j] == '\t')
			j++;
		if (s[j])
			error_exit("Extra input next to sprite path!\n");
	}
	else
		error_exit("Sprite path already defined!\n");
}

void	tex_path(char *s, t_vbls *vbls)
{
	int i;
	int j;

	i = 2;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	j = i;
	while (s[j] != ' ' && s[j] != '\0')
		j++;
	so_no_path(s, vbls, i, j);
	ea_we_path(s, vbls, i, j);
	while (s[j] == ' ' || s[j] == '\t')
		j++;
	if (s[j])
		error_exit("Extra input next to texture path!\n");
}
