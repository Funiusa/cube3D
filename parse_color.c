/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:11:20 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:11:22 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		color_formatting(t_vbls *vbls, int count, const char *s)
{
	if (count == 1)
	{
		if (s[0] == 'C')
			vbls->ceiling_color_r = vbls->tmp_color;
		else
			vbls->floor_color_r = vbls->tmp_color;
	}
	if (count == 2)
	{
		if (s[0] == 'C')
			vbls->ceiling_color_g = vbls->tmp_color;
		else
			vbls->floor_color_g = vbls->tmp_color;
	}
	if (count == 3)
	{
		if (s[0] == 'C')
			vbls->ceiling_color_b = vbls->tmp_color;
		else
			vbls->floor_color_b = vbls->tmp_color;
		return (0);
	}
	vbls->tmp_color = 0;
	return (1);
}

void	color_fill(char *s, int *i, t_vbls *vbls)
{
	int		count;

	count = 0;
	vbls->tmp_color = 0;
	vbls->count_colors = 0;
	while (count < 3)
	{
		while (s[*i] == ' ' || s[*i] == '\t')
			(*i)++;
		if (!ft_isdigit(s[*i]) || (ft_atoi(s + *i)) > 255
		|| (ft_atoi(s + *i)) < 0)
			error_exit("Bad, bad color my friend!\n");
		while (ft_isdigit(s[*i]))
			vbls->tmp_color = (vbls->tmp_color * 10) + (s[(*i)++] - '0');
		count++;
		if (!color_formatting(vbls, count, s))
			break ;
		while (s[*i] == ' ' || s[*i] == '\t')
			(*i)++;
		if (s[(*i)++] == ',')
			vbls->count_colors++;
	}
	vbls->params++;
}

void	color_pars(char *s, t_vbls *vbls)
{
	int		i;

	i = 1;
	vbls->tmp_color = 0;
	vbls->count_colors = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	color_fill(s, &i, vbls);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (vbls->count_colors != 2 || s[i])
		error_exit("Are you think is it a color?!\n");
	if (s[0] == 'C')
	{
		if (vbls->ceiling)
			error_exit("To mach color in this bicolor world!\n");
		vbls->ceiling = 1;
	}
	else
	{
		if (vbls->floor)
			error_exit("Only one color for floor!\n");
		vbls->floor = 1;
	}
}
