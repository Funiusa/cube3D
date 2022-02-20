/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <tevelyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:47:40 by tevelyne          #+#    #+#             */
/*   Updated: 2021/01/03 14:06:40 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_tail_extender(char *tail, char *buf)
{
	char	*tmp;

	tmp = NULL;
	if (tail)
	{
		tmp = ft_strjoin(tail, buf);
		free(tail);
		tail = tmp;
		return (tail);
	}
	return (ft_strdup(buf));
}

char	*ft_add_in_line(char *tail, char **line)
{
	char		*tmp;
	int			n_l_point;

	tmp = NULL;
	n_l_point = 0;
	while (tail[n_l_point] != '\n' && tail[n_l_point] != '\0')
		n_l_point++;
	if (n_l_point < ft_strlen(tail))
	{
		*line = ft_substr(tail, 0, n_l_point);
		tmp = ft_substr(tail, n_l_point + 1, ft_strlen(tail));
		free(tail);
		tail = tmp;
	}
	else
	{
		*line = ft_substr(tail, 0, n_l_point);
		free(tail);
		tail = ft_strdup("");
	}
	return (tail);
}

int		get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			byte_was_read;
	static char	*tail;

	if (!line || BUFFER_SIZE < 1 || fd < 0)
		return (-1);
	byte_was_read = 1;
	while (byte_was_read && !(ft_strchr(tail, '\n')))
	{
		if ((byte_was_read = read(fd, buf, BUFFER_SIZE)) < 0)
			return (-1);
		buf[byte_was_read] = '\0';
		tail = ft_tail_extender(tail, buf);
	}
	tail = ft_add_in_line(tail, line);
	if (byte_was_read == 0)
	{
		free(tail);
		tail = NULL;
		return (0);
	}
	return (1);
}
