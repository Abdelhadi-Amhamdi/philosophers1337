/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:50:51 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/20 13:56:43 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *ph, unsigned long long start)
{
	printf("%llu philo %d sleeping\n", (get_time() - start), ph->id);
	ft_usleep(get_time(), ph->time_data->sleep);
}

void	ft_eat(t_philo *ph, unsigned long long start)
{
	printf("%llu philo %d eating\n", (get_time() - start), ph->id);
	ft_usleep(get_time(), ph->time_data->eat);
}

void	ft_think(t_philo *ph, unsigned long long start)
{
	printf("%llu philo %d thinking\n", (get_time() - start), ph->id);
}

void	check_if_die(t_philo *ph, unsigned long l_eat, unsigned long long start)
{
	if (get_time() - l_eat > ph->time_data->die)
	{
		printf("%llu philo %d die.\n", (get_time() - start), ph->id);
		pthread_exit(NULL);
	}
}

void	ft_usleep(unsigned long long time, unsigned long long ttsleep)
{
	while (get_time() - time < ttsleep)
		usleep(50);
}
