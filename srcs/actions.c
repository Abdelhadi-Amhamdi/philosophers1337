/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:50:51 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/04/08 10:35:13 by aamhamdi         ###   ########.fr       */
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
