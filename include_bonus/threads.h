/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:30:22 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/03 21:27:38 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

typedef struct	s_thread
{
	pthread_t	thread_id;
	int			id;
	char		*addr;
	int			width;
	int			height;
}	t_thread;

#endif
