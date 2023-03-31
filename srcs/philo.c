/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:31:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/31 15:50:16 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_init_philos(t_time *time_data, t_data *philo_data)
{
	int		i;
	t_philo	*list;
	t_philo	*philo;
	t_philo	*last;

	i = 0;
	list = NULL;
	time_data->start = 0;
	while (i < philo_data->philos_num)
	{
		philo = ft_creat_philo((i + 1), philo_data, time_data);
		if (!philo)
			return (NULL);
		ft_lst_add_back(&list, philo);
		i++;
	}
	last = ft_get_last(list);
	last->next = list;
	return (list);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)(args);
	pthread_mutex_lock(&philo->philo_data->die);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->philo_data->die);
	if (philo->id % 2)
		ft_usleep(get_time(), 50);
	while (philo->eated < philo->time->times_to_eat)
	{
		take_forks(philo);
		eat(philo);
		if (philo->eated + 1 == philo->time->times_to_eat \
		&& !philo->philo_data->is_infini)
			break ;
		ft_sleep(philo);
		ft_think(philo);
		if (!philo->philo_data->is_infini)
			philo->eated++;
	}
	pthread_exit(NULL);
}

void	check_death(t_philo *ph)
{
	while (ph->philo_data->died == 0)
	{
		ft_usleep(get_time(), 10);
		while (ph)
		{
			pthread_mutex_lock(&ph->philo_data->die);
			if ((int)(get_time() - ph->last_eat) > ph->time->time_to_die)
			{
				if (ph->eated + 1 != ph->time->times_to_eat)
				{
					pthread_mutex_lock(&ph->philo_data->write);
					printf("%lld %d died", (get_time() - \
					ph->time->start), ph->id);
					pthread_mutex_unlock(&ph->philo_data->write);
				}
				ph->philo_data->died = 1;
				pthread_mutex_unlock(&ph->philo_data->die);
				return ;
			}
			pthread_mutex_unlock(&ph->philo_data->die);
			ph = ph->next;
			if (ph->id == 1)
				break ;
		}
	}
}

void	ft_start_philos(t_philo *phs)
{
	t_philo	*tmp;

	tmp = phs;
	tmp->time->start = get_time();
	while (phs)
	{
		pthread_mutex_init(&phs->fork, NULL);
		pthread_create(&phs->philo, NULL, routine, phs);
		phs = phs->next;
		if (phs->id == 1)
			break ;
	}
	check_death(phs);
	while (tmp)
	{
		pthread_join(tmp->philo, NULL);
		pthread_mutex_destroy(&tmp->fork);
		tmp = tmp->next;
		if (tmp->id == 1)
			break ;
	}
}

int	main(int ac, char **av)
{
	t_time	time;
	t_data	philo_data;
	t_philo	*philos;

	if (ac < 5)
		return (0);
	philo_data.philos_num = ft_atoi(av[1]);
	get_args_data(av + 2, &time);
	check_if_infini(&philo_data, &time);
	pthread_mutex_init(&philo_data.write, NULL);
	pthread_mutex_init(&philo_data.die, NULL);
	philo_data.died = 0;
	philos = ft_init_philos(&time, &philo_data);
	ft_start_philos(philos);
	pthread_mutex_destroy(&philo_data.write);
	pthread_mutex_destroy(&philo_data.die);
	return (0);
}
