/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:34:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/04/17 18:45:53 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_args_data(char **args, t_time *time_data)
{
	time_data->time_to_die = ft_atoi(args[0]);
	time_data->time_to_eat = ft_atoi(args[1]);
	time_data->time_to_sleep = ft_atoi(args[2]);
	if (args[3])
		time_data->times_to_eat = ft_atoi(args[3]);
	else
		time_data->times_to_eat = 0;
	if (args[3] && time_data->times_to_eat < 1)
		return (1);
	return (0);
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
}

void	ft_print(char *str, t_philo *ph, unsigned long long time)
{
	pthread_mutex_lock(&ph->philo_data->write);
	if (!str)
	{
		printf("%lld %d died\n", time, ph->id);
		pthread_mutex_destroy(&ph->philo_data->write);
		return ;
	}
	else
		printf("%lld %d %s\n", time, ph->id, str);
	pthread_mutex_unlock(&ph->philo_data->write);
}

void	ft_free_list(t_philo *phs)
{
	t_philo	*next;
	t_philo	*tmp;
	int		i;
	int		len;

	i = 0;
	len = phs->philo_data->philos_num;
	tmp = phs;
	while (i < len)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
		i++;
	}
}
