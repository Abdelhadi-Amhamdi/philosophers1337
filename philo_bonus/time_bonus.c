/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/04/19 15:55:06 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(unsigned long long time, unsigned long long ttsleep, t_philo *ph)
{
	while ((get_time() - time) < ttsleep)
	{
		if ((int)(get_time() - ph->last_meal) > ph->data->time_do_die)
			return (1);
		usleep(500);
	}
	return (0);
}
