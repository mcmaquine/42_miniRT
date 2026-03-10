/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compare_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:29:48 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/09 21:33:27 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static double abs_double(double x)
{
    if (x < 0.0)
        return (-x);
    return (x);
}

/*
Return 0 if two doubles are equal (or their difference is less than tol), 1
otherwise.
*/
int ft_dcmp(double num1, double num2, double tol)
{
    double	diff;

    diff = num1 - num2;
    if (abs_double(diff) <= tol)
        return (0);
    return (1);
}
