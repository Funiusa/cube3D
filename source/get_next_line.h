/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <tevelyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:47:24 by tevelyne          #+#    #+#             */
/*   Updated: 2021/01/03 14:13:25 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
#include "../cube.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# if BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE -1
# endif
# if BUFFER_SIZE > 1000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_tail_extender(char *tail, char *buf);
char	*ft_add_in_line(char *tail, char **line);
char	*ft_strchr(const char *str, int ch);
int		get_next_line(int fd, char **line);
int		ft_strlen(const char *str);
char	*ft_strdup(char *src);

#endif
