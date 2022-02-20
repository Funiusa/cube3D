/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_tmp_mass.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:57:28 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 18:57:32 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	pars_tmp_mass(t_vbls *vbls, char *line, const int *i)
{
	if (line[*i] == 'R' && (line[*i + 1]) == ' ')
		resolution_path(line + *i, vbls);
	else if ((line[*i] == 'N' && line[*i + 1] == 'O' && line[*i + 2] == ' ')
		|| (line[*i] == 'S' && line[*i + 1] == 'O' && line[*i + 2] == ' ')
		|| (line[*i] == 'W' && line[*i + 1] == 'E' && line[*i + 2] == ' ')
		|| (line[*i] == 'E' && line[*i + 1] == 'A' && line[*i + 2] == ' '))
		tex_path(line + *i, vbls);
	else if (line[*i] == 'S' && line[*i + 1] == ' ')
		sp_tex_path(line + *i, vbls);
	else if ((line[*i] == 'F' && line[*i + 1] == ' ')
		|| (line[*i] == 'C' && line[*i + 1] == ' '))
		color_pars(line + *i, vbls);
	else if (line[*i] == '1' || line[*i] == ' ' || line[*i] == '2')
	{
		vbls->params++;
		return (1);
	}
	else
		error_exit("Houston we have a problem with parameters!\n");
	return (0);
}

int			tmp_mass(t_vbls *vbls, char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (0);
	if (pars_tmp_mass(vbls, line, &i))
		return (1);
	return (0);
}

int			null_end_line(t_vbls *vbls, int i, int j)
{
	while (vbls->tmp[i][j])
	{
		if (vbls->tmp[i][j] == '0' || vbls->tmp[i][j] == vbls->hero
			|| vbls->tmp[i][j] == '2')
			return (0);
		j++;
	}
	return (1);
}

static int	count_line_in_file(char *file)
{
	char	*line;
	int		fd;
	int		read;
	int		count;

	count = 0;
	fd = open(file, O_RDONLY);
	read = 1;
	while (read)
	{
		read = get_next_line(fd, &line);
		count++;
		free(line);
	}
	close(fd);
	return (count + 1);
}

void		create_tmp(t_vbls *vbls, char *file)
{
	char	*line;
	int		read;
	int		i;
	int		fd;

	i = 0;
	read = 1;
	init_vars_map(vbls);
	if ((fd = open(file, O_RDONLY)) < 0)
		error_exit("No file - no game!\n");
	vbls->count_line_tmp = count_line_in_file(file);
	vbls->tmp = malloc(sizeof(char*) * (vbls->count_line_tmp + 1));
	while (read)
	{
		read = get_next_line(fd, &line);
		vbls->tmp[i] = malloc((ft_strlen(line) + 1) * sizeof(char));
		vbls->tmp[i] = ft_strlcpy(vbls->tmp[i], line);
		free(line);
		line = NULL;
		i++;
	}
	free(line);
	line = NULL;
	vbls->tmp[i] = 0;
	parser(vbls);
}
