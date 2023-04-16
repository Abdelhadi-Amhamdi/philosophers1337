/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:12:49 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/04/16 02:21:16 by aamhamdi         ###   ########.fr       */
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

void	ft_print(char *msg, t_philo *ph)
{
	if (!msg)
	{
		printf("%lld %d died\n", (get_time() - ph->data->start), ph->id);
		exit(1);
	}
	printf("%lld %d %s\n", (get_time() - ph->data->start), ph->id, msg);
}

int	get_data_args(t_data *data, char **args)
{
	data->philos_number = atoi(args[0]);
	data->time_do_die = atoi(args[1]);
	data->time_to_eat = atoi(args[2]);
	data->time_to_sleep = atoi(args[3]);
	if (args[4])
	{
		data->times_to_eat = atoi(args[4]);
		data->is_infini = FALSE;
	}
	else
	{
		data->times_to_eat = 1;
		data->is_infini = TRUE;
	}
	if (args[4] && data->times_to_eat < 1)
		return (1);
	return (0);
}
