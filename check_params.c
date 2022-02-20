/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:07:39 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:07:44 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		checker_save(const char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	if (arg[i - 1] == 'e' && arg[i - 2] == 'v' && arg[i - 3] == 'a' &&
		arg[i - 4] == 's' && arg[i - 5] == '-' && arg[i - 6] == '-')
		return (1);
	return (0);
}

int		checker_name(const char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	if (arg[i - 1] == 'b' && arg[i - 2] == 'u' && arg[i - 3] == 'c'
		&& arg[i - 4] == '.')
		return (1);
	return (0);
}

void	cheak_xpm(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (s[i - 1] != 'm' || s[i - 2] != 'p' || s[i - 3] != 'x'
		|| s[i - 4] != '.')
		error_exit("Only .xpm textures!\n");
}

int		check_path(char *path)
{
	int				fd;
	unsigned int	nbytes;
	char			buf[60000];

	nbytes = 60000;
	fd = open(path, O_RDONLY);
	if ((read(fd, buf, nbytes)) == -1)
	{
		close(fd);
		error_exit("Bad texture file!\n");
	}
	close(fd);
	return (fd);
}

int		cheak_textures(t_vbls *vbls)
{
	if (!vbls->resolution)
		error_exit("Bad resolution!\n");
	else if (!vbls->texture_no)
		error_exit("North texture is empty!\n");
	else if (!vbls->texture_so)
		error_exit("South texture is empty!\n");
	else if (!vbls->texture_we)
		error_exit("West texture is empty!\n");
	else if (!vbls->texture_ea)
		error_exit("East texture is empty!\n");
	else if (!vbls->sprite)
		error_exit("Have not sprite texture!\n");
	else if (!vbls->floor)
		error_exit("Floor color is empty!\n");
	else if (!vbls->ceiling)
		error_exit("Ceiling color is empty!\n");
	else
		return (0);
	exit(errno);
}
