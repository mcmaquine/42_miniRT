/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:37:58 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/05 18:05:05 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	solve_right(char *str);
static double	power_ten(size_t i );
static size_t	sizeof_split(char **arr);
static void		solve_for_point(char *str, char *split, double *l, double *r);

/*
Converts float number represented in a string and convert it to double.
The separator must be.
*/
// double	ft_atod(const char *nptr)
// {
// 	double	left;
// 	double	right;
// 	char	**parts;

// 	if (!nptr)
// 		return (0.0);
// 	parts = ft_split(nptr, '.');
// 	left = 0.0;
// 	if (sizeof_split(parts) < 2 && ft_strchr(nptr, '.'))
// 		right = solve_right(parts[0]);
// 	else
// 	{
// 		if (ft_strlen(parts[0]) == 1 && **parts == '-')
// 			right = -1 * solve_right(parts[0]);
// 		else
// 			left = ft_atoi(parts[0]);
// 		right = solve_right(parts[1]);
// 	}
// 	ft_free_split(parts);
// 	if (left >= 0)
// 		return (left + right);
// 	else
// 		return (left - right);
// }

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
			solve_for_point(nptr, parts[0], &left, &right);
		else if (ft_strlen(parts[0]) == 1 && **parts == '-')
			right = -solve_right(parts[0]);
		else if (ft_strlen(parts[0]) == 1 && **parts == '+')
			right = solve_right(parts[0]);
	}
	else
		return (ft_atoi(nptr));
}

static double	solve_right(char *str)
{
	size_t	i;
	double	result;

	result = 0;
	i = 0;
	if (!str)
		return (0.0);
	while (str[i] == '0' && str[i])
		i++;
	while (str[i] && (str[i] > '0' && str[i] <= '9'))
	{
		result = result + ((double)(str[i] - '0'))/power_ten(i + 1);
		i++;
	}
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

static void		solve_for_point(char *str, char *split, double *l, double *r)
{
	char	dot;

	dot = ft_strchr(str, '.');
	if (!dot)
	{
		*l = ft_atoi(split);
		*r = 0.0;
		return ;
	}
	if (str > dot)
	{
		*l = 0.0;
		*r = solve_right(split);
	}
	else
	{
		*l = ft_atoi(split);
		*r = 0.0;
	}
	return ;
}
