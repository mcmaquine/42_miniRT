/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:37:58 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/05 22:11:52 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	solve_right(char *str, char **param);
static double	power_ten(size_t i );
static size_t	sizeof_split(char **arr);
static double	solve_for_point(const char *str, char *split, char **param);

/*
Converts float number represented in a string and convert it to double.
The separator must be.
*/
 double	ft_atod(const char *nptr)
{
	char	**parts;
	double	left;
	double	right;

	left  = 0.0;
	if (ft_strchr(nptr, '.'))
	{
		parts = ft_split(nptr, '.');
		if (sizeof_split(parts) < 2)
			return (solve_for_point(nptr, parts[0], parts));
		else if (ft_strlen(parts[0]) == 1 && **parts == '-')
			return (-solve_right(parts[1], parts));
		else if (ft_strlen(parts[0]) == 1 && **parts == '+')
			return (solve_right(parts[1], parts));
		else if (ft_atoi(parts[0]) == 0 && ft_strchr(parts[0], '-'))
			return (-solve_right(parts[1], parts));
		left = ft_atoi(parts[0]);
		if (left < 0)
			right = -solve_right(parts[1], parts);
		else
			right = solve_right(parts[1], parts);
	}
	else
		return (ft_atoi(nptr));
	return (left + right);
}

static double	solve_right(char *str, char **param)
{
	size_t	i;
	double	result;

	result = 0;
	i = 0;
	(void)param;
	if (!str)
	{
		ft_free_split(param);
		return (0.0);
	}
	while (str[i] == '0' && str[i])
		i++;
	while (str[i] && (str[i] > '0' && str[i] <= '9'))
	{
		result = result + ((double)(str[i] - '0'))/power_ten(i + 1);
		i++;
	}
	ft_free_split(param);
	return (result);
}

static double	power_ten(size_t i)
{
	double tens;

	tens = 1;
	if (!i)
		return (1);
	while (i > 0)
	{
		tens *= 10;
		i--;
	}
	return (tens);
}

static size_t	sizeof_split(char **arr)
{
	size_t	i;

	if (!arr)
		return (0);
	i = 0;
	while(arr[i])
		i++;
	return (i);
}

static double	solve_for_point(const char *str, char *split, char **param)
{
	char	*dot;
	double	result;

	(void)param;
	dot = ft_strchr(str, '.');
	if (str >= dot)
		return (solve_right(split, param));
	else
	{
		result = ft_atoi(split);
		ft_free_split(param);
		return (result);
	}
}
