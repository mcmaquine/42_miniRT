/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 21:02:44 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/03 21:04:24 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	get_num_thread(void)
{
	int	num_cores;

	num_cores = sysconf(_SC_NPROCEORS_ONLN);
	if (num_cores < 1)
		return (1);
	return (num_cores);
}
