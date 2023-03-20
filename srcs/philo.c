/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:31:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/20 14:13:59 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_init_philos(t_time *time_data)
{
	int		i;
	t_philo	*list;
	t_philo	*philo;
	t_philo	*last;

	i = 0;
	list = NULL;
	while (i < time_data->philos_num)
	{
		philo = ft_creat_philo((i + 1), time_data);
		if (!philo)
			return (NULL);
		ft_lst_add_back(&list, philo);
		i++;
	}
	last = ft_get_last(list);
	last->next = list;
	return (list);
}

void	take_forks(t_philo *philo, unsigned long long start)
{
	pthread_mutex_lock(&philo->fork);
	printf("%llu philo %d did take a fork\n", (get_time() - start), philo->id);
	pthread_mutex_lock(&philo->next->fork);
	printf("%llu philo %d did take a fork\n", (get_time() - start), philo->id);
}

void	*routine(void *args)
{
	t_philo				*philo;
	t_bool				is_infini;
	unsigned long long	start;

	philo = (t_philo *)(args);
	philo->time_data->l_eat = get_time();
	start = get_time();
	if (!philo->time_data->times_to_eat)
	{
		philo->time_data->times_to_eat = 1;
		is_infini = TRUE;
	}
	else
		is_infini = FALSE;
	if (philo->id % 2 != 0)
		ft_usleep(get_time(), 50);
	while (philo->time_data->times_to_eat)
	{
		take_forks(philo, start);
		ft_eat(philo, start);
		philo->time_data->l_eat = get_time();
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		ft_sleep(philo, start);
		ft_think(philo, start);
		if (is_infini == FALSE && philo->time_data->times_to_eat > 0)
			philo->time_data->times_to_eat--;
	}
	pthread_exit(NULL);
}

void	ft_start_philos(t_philo *phs)
{
	t_philo	*tmp;

	tmp = phs;
	while (phs)
	{
		pthread_mutex_init(&phs->fork, NULL);
		pthread_create(&phs->philo, NULL, routine, phs);
		phs = phs->next;
		if (phs->id == 1)
			break ;
	}
	while (tmp)
	{
		pthread_join(tmp->philo, NULL);
		tmp = tmp->next;
		if (tmp->id == 1)
			break ;
	}
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_time	time;

	if (ac < 5)
	{
		printf("at least 4 args required\n");
		return (0);
	}
	time.philos_num = ft_atoi(av[1]);
	time.die = ft_atoi(av[2]);
	time.eat = ft_atoi(av[3]);
	time.sleep = ft_atoi(av[4]);
	if (ac == 6)
		time.times_to_eat = ft_atoi(av[5]);
	else
		time.times_to_eat = 0;
	philos = ft_init_philos(&time);
	ft_start_philos(philos);
	return (0);
}
