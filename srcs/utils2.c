/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:34:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/31 13:38:17 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_args_data(char **args, t_time *time_data)
{
	time_data->time_to_die = ft_atoi(args[0]);
	time_data->time_to_eat = ft_atoi(args[1]);
	time_data->time_to_sleep = ft_atoi(args[2]);
	if (args[3])
		time_data->times_to_eat = ft_atoi(args[3]);
	else
		time_data->times_to_eat = 0;
}

void	check_if_infini(t_data *philo_data, t_time *time)
{
	if (!time->times_to_eat)
	{
		philo_data->is_infini = TRUE;
		time->times_to_eat = 1;
	}
	else
		philo_data->is_infini = FALSE;
	philo_data->died = 0;
}

void	ft_print(char *str, t_philo *ph, unsigned long long time)
{
	pthread_mutex_lock(&ph->philo_data->die);
	if (ph->philo_data->died)
	{
		(void)str;
		pthread_mutex_lock(&ph->philo_data->write);
		printf("%lld %d died\n", time, ph->id);
		pthread_mutex_unlock(&ph->philo_data->write);
		pthread_mutex_unlock(&ph->philo_data->die);
		pthread_exit(NULL);
	}
	else
	{
		pthread_mutex_lock(&ph->philo_data->write);
		printf("%lld %d %s\n", time, ph->id, str);
		pthread_mutex_unlock(&ph->philo_data->write);
	}
	pthread_mutex_unlock(&ph->philo_data->die);
}

void	ft_usleep(unsigned long long time, unsigned long long ttsleep)
{
	while (get_time() - time < ttsleep)
		usleep(50);
}
