/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitv2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:31:32 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/05/14 20:03:56 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char *delim);
static char		**split_delim(const char *s, char *delim, size_t num_words);

char	**ft_splitv2(const char *src, char *delim)
{
	char	**splitted;
	size_t	num_words;

	num_words = count_words(src, delim);
	splitted = split_delim(src, delim, num_words);
	return (splitted);
}

static size_t	count_words(const char *s, char *delim)
{
	size_t	num;

	num = 0;
	while (*s)
	{
		if (!ft_strchr(delim, *s)
			&& (ft_strchr(delim, *(s + 1)) || *(s + 1) == '\0'))
			num++;
		s++;
	}
	return (num);
}

static char	**split_delim(const char *s, char *delim, size_t num_words)
{
	char	*start;
	char	*end;
	char	**splitted;
	char	*str;
	size_t	i;

	splitted = ft_calloc((num_words + 1), sizeof(char *));
	i = 0;
	start = (char *)s;
	while (i < num_words)
	{
		while (ft_strchr(delim, *start))
			start++;
		end = start;
		while (!ft_strchr(delim, *end))
			end++;
		str = ft_calloc((end - start), sizeof(char));
		ft_strlcpy(str, start, (end - start + 1));
		splitted[i] = str;
		start = end;
		i++;
	}
	return (splitted);
}
