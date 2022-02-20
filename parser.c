/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:11:36 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:11:38 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int			check_space(t_vbls *vbls, int i, int j)
{
	if (i == vbls->first_line_map - 1
		|| j == 0 || j == vbls->max_str - 1 || !vbls->tmp[i + 1])
		return (1);
	else if (vbls->tmp[i - 1][j] != ' ' && vbls->tmp[i - 1][j] != '\t'
	&& vbls->tmp[i - 1][j] != '1'
	&& vbls->tmp[i + 1][j] != '\t'
	&& vbls->tmp[i + 1][j] != '1' && vbls->tmp[i + 1][j] != ' '
	&& vbls->tmp[i][j - 1] != ' ' && vbls->tmp[i][j - 1] != '\t'
	&& vbls->tmp[i][j - 1] != '1'
	&& vbls->tmp[i][j + 1] != ' ' && vbls->tmp[i][j + 1] != '\t'
	&& vbls->tmp[i][j + 1] != '1')
		return (0);
	return (1);
}

void		check_map_line(t_vbls *vbls)
{
	int i;
	int j;

	i = 1;
	while (i < vbls->line_in_map - 1)
	{
		j = 0;
		while (vbls->map[i][j] != '0')
			j++;
		while (vbls->map[i][j + 1] && vbls->map[i][j] == '0')
		{
			if (vbls->map[i + 1][j] == '4' || vbls->map[i - 1][j] == '4')
				error_exit("Bad wall!\n");
			while (vbls->map[i][j]
				&& (vbls->map[i][j + 1] == '2' || vbls->map[i][j + 1] == '1'))
				j++;
			j++;
		}
		i++;
	}
}

static void	format_line_in_map(t_vbls *vbls, int str_nbr)
{
	int		j;

	j = 0;
	while (vbls->tmp[str_nbr][j] == ' ' || vbls->tmp[str_nbr][j] == '\t')
		j++;
	while (vbls->tmp[str_nbr][j])
	{
		if (vbls->tmp[str_nbr][j] != '1')
			if (vbls->tmp[str_nbr][j] == '0' || vbls->tmp[str_nbr][j] == '2')
				error_exit("Bad map parameter!\n");
		j++;
	}
	vbls->max_str = ft_strlen(vbls->tmp[str_nbr]);
	vbls->line_in_map = vbls->count_line_tmp - str_nbr;
	while (vbls->tmp[str_nbr + 1])
	{
		if (vbls->max_str < ft_strlen(vbls->tmp[str_nbr + 1]))
			vbls->max_str = ft_strlen(vbls->tmp[str_nbr + 1]);
		str_nbr++;
	}
}

static void	map_create(t_vbls *vbls, int line)
{
	int		i;
	int		nl;

	nl = 0;
	format_line_in_map(vbls, --line);
	if (!(vbls->map = malloc(sizeof(char*) * (vbls->line_in_map + 2))))
		bad_malloc(vbls);
	while (vbls->tmp[line] && !vbls->map_end)
	{
		i = 0;
		if (!(vbls->map[nl] = (char*)malloc(sizeof(char)
													* vbls->max_str + 1)))
			bad_malloc(vbls);
		end_line_check(vbls, line, i);
		check_map(vbls, &line, &i, &nl);
		while (i < vbls->max_str - 1)
			vbls->map[nl][i++] = '4';
		vbls->map[nl][i] = '\0';
		line++;
		nl++;
	}
	vbls->map[nl] = "\0";
	vbls->line_in_map = nl;
	check_map_line(vbls);
}

void		parser(t_vbls *vbls)
{
	int		i;
	int		right_params;

	i = 0;
	right_params = 0;
	while (i < vbls->count_line_tmp - 1 && !right_params)
		right_params = tmp_mass(vbls, vbls->tmp[i++]);
	if (vbls->params != 9)
		error_exit("Bad parameters. No game #$@%&^ucker!\n");
	cheak_all_path(vbls);
	vbls->first_line_map = i;
	map_create(vbls, i);
	get_sprites(vbls);
	if (vbls->hero == 0)
		error_exit("People need a hero!\n");
	free_tmp_mass(vbls);
}
