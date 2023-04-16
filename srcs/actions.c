/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:50:51 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/04/16 02:11:57 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->fork);
	ft_print("has taken a fork", ph, (get_time() - ph->time->start));
	pthread_mutex_lock(&ph->next->fork);
	ft_print("has taken a fork", ph, (get_time() - ph->time->start));
}

void	eat(t_philo *ph)
{
	ft_print("is eating", ph, (get_time() - ph->time->start));
	ft_usleep(get_time(), ph->time->time_to_eat);
	pthread_mutex_lock(&ph->t);
	ph->last_eat = get_time();
	pthread_mutex_unlock(&ph->t);
	pthread_mutex_unlock(&ph->fork);
	pthread_mutex_unlock(&ph->next->fork);
	if (!ph->philo_data->is_infini)
	{
		pthread_mutex_lock(&ph->t);
		ph->eated++;
		pthread_mutex_unlock(&ph->t);
	}
}

void	ft_sleep(t_philo *ph)
{
	ft_print("is sleeping", ph, (get_time() - ph->time->start));
	ft_usleep(get_time(), ph->time->time_to_sleep);
}

void	ft_think(t_philo *ph)
{
	ft_print("is thinking", ph, (get_time() - ph->time->start));
}

int	parsing(t_data *data, t_time *time)
{
	if (data->philos_num < 1)
		return (1);
	if (time->time_to_die < 1 || time->time_to_eat < 1 \
	|| time->time_to_sleep < 1)
		return (1);
	return (0);
}
