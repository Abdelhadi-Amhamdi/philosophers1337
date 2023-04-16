/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:31:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/04/16 02:11:46 by aamhamdi         ###   ########.fr       */
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
	if (philo->id % 2)
		usleep(10000);
	while (philo->eated < philo->time->times_to_eat)
	{
		take_forks(philo);
		eat(philo);
		if (philo->eated == philo->time->times_to_eat \
		&& !philo->philo_data->is_infini)
			break ;
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	check_death(t_philo *phs)
{
	t_philo				*tmp;
	unsigned long long	lm;

	tmp = phs;
	while (1)
	{
		usleep(1000);
		while (tmp)
		{
			pthread_mutex_lock(&tmp->t);
			lm = tmp->last_eat;
			pthread_mutex_unlock(&tmp->t);
			if ((int)(get_time() - lm) > tmp->time->time_to_die \
			|| tmp->eated == tmp->time->times_to_eat)
			{
				if ((tmp->eated) != tmp->time->times_to_eat)
					ft_print(NULL, tmp, (get_time() - tmp->time->start));
				return ;
			}
			tmp = tmp->next;
			if (tmp->id == 1)
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
		pthread_mutex_init(&phs->t, NULL);
		phs->last_eat = get_time();
		pthread_create(&phs->philo, NULL, routine, phs);
		phs = phs->next;
		if (phs->id == 1)
			break ;
	}
	while (phs)
	{
		pthread_detach(phs->philo);
		phs = phs->next;
		if (phs->id == 1)
			break ;
	}
	check_death(phs);
}

int	main(int ac, char **av)
{
	t_time	*time_data;
	t_data	*philo_data;
	t_philo	*philos;

	philos = NULL;
	if (ac < 5 || ac > 6)
		return (0);
	time_data = malloc(sizeof(t_time));
	philo_data = malloc(sizeof(t_data));
	philo_data->philos_num = ft_atoi(av[1]);
	if (get_args_data(av + 2, time_data) || parsing(philo_data, time_data))
	{
		free(philo_data);
		free(time_data);
		return (0);
	}
	check_if_infini(philo_data, time_data);
	pthread_mutex_init(&philo_data->write, NULL);
	philos = ft_init_philos(time_data, philo_data);
	ft_start_philos(philos);
	free(philo_data);
	free(time_data);
	return (0);
}
