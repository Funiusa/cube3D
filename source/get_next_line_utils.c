/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <tevelyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:32:02 by tevelyne          #+#    #+#             */
/*   Updated: 2020/12/26 14:50:10 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *src)
{
	int		size;
	char	*mass;

	mass = NULL;
	size = ft_strlen(src);
	mass = (char *)malloc(sizeof(char) * (size + 1));
	if (!mass)
		return (NULL);
	size = 0;
	while (src[size] != '\0')
	{
		mass[size] = src[size];
		size++;
	}
	mass[size] = '\0';
	return (mass);
}

int		ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (str)
		while (*str++)
			count++;
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	i;

	new_string = NULL;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	new_string = (char *)malloc(sizeof(char) * i + 1);
	if (!new_string)
		return (NULL);
	i = 0;
	while (*s1)
	{
		new_string[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		new_string[i] = *s2++;
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

char	*ft_strchr(const char *str, int ch)
{
	while (str != NULL && *str)
	{
		if (*str == ch || ch == '\0')
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	it;

	it = 0;
	substring = NULL;
	substring = (char *)malloc(sizeof(char) * (len - start + 1));
	if (!substring || !s)
		return (NULL);
	if ((size_t)ft_strlen((char *)s) > start)
		while (len > (start + it))
		{
			substring[it] = s[start + it];
			it++;
		}
	substring[it] = '\0';
	return (substring);
}
