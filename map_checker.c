/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:10:48 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:10:51 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int				check_empty_line_in_map(const char *str)
{
	int		i;

	i = 0;
	if (str != NULL)
		while (str[i] != '\0')
		{
			if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
				i++;
			else
				return (0);
		}
	return (1);
}

static int		cheak_line(t_vbls *vbls, int i)
{
	int		j;

	j = 0;
	while (vbls->tmp[i][j])
	{
		if (vbls->tmp[i][j] != ' ' && vbls->tmp[i][j] != '1'
			&& i == vbls->first_line_map - 1 && i == vbls->count_line_tmp - 1)
			return (0);
		else if (vbls->tmp[i][j] == ' ' && i == vbls->count_line_tmp - 1)
			if (vbls->tmp[i - 1][j] != '1' && vbls->tmp[i - 1][j] != ' ')
				return (0);
		j++;
	}
	return (1);
}

static int		cheak_walls(t_vbls *vbls, int i)
{
	int		j;

	j = 0;
	if (i == vbls->first_line_map - 1 || i == vbls->count_line_tmp - 1)
		if (!cheak_line(vbls, i))
			return (0);
	while (vbls->tmp[i][j] == ' ' || vbls->tmp[i][j] == '\t')
		j++;
	if (vbls->tmp[i][j] == '2' ||
		(vbls->tmp[i][(ft_strlen(vbls->tmp[i]) - 1)] != '1'
		&& vbls->tmp[i][(ft_strlen(vbls->tmp[i]) - 1)] != ' '
		&& vbls->tmp[i][(ft_strlen(vbls->tmp[i]))] != '2'))
		return (0);
	return (1);
}

void			end_line_check(t_vbls *vbls, int line, int i)
{
	if (!vbls->map_end && !ft_strlen(vbls->tmp[line + 1]))
	{
		if (!null_end_line(vbls, line, i))
			error_exit("Map line error!\n");
		++line;
		while (line < vbls->count_line_tmp)
			if (!check_empty_line_in_map(vbls->tmp[line++]))
				error_exit("Map error!\n");
		vbls->map_end = 1;
	}
}

void			check_map(t_vbls *vbls, int *i, int *j, int *c)
{
	while (vbls->tmp[*i][*j] != '\0')
	{
		if (!cheak_walls(vbls, *i))
			error_exit("Wall map error!\n");
		if (vbls->tmp[*i][*j] == ' ' || vbls->tmp[*i][*j] == '\t')
		{
			if (!check_space(vbls, *i, *j) || vbls->tmp[*i][*j] == '\n')
				error_exit("Breach, commander!\n");
			vbls->map[*c][*j] = '4';
		}
		else if ((vbls->tmp[*i][*j] == '1' || vbls->tmp[*i][*j] == '0'
				|| vbls->tmp[*i][*j] == '2') && vbls->tmp[*i][*j] != ' ')
		{
			check_null(vbls, *i, *j);
			if (vbls->tmp[*i][*j] == '2')
				wall_around_sprite(vbls, *i, *j);
			vbls->map[*c][*j] = vbls->tmp[*i][*j];
		}
		else if (vbls->tmp[*i][*j] == 'W' || vbls->tmp[*i][*j] == 'N'
				|| vbls->tmp[*i][*j] == 'E' || vbls->tmp[*i][*j] == 'S')
			hero_in_the_map(vbls, *c, *i, *j);
		else
			error_exit("Playing with dirty map man!\n");
		(*j)++;
	}
}
