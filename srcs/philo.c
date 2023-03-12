/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:31:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/12 18:21:28 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_init_philosphers(size_t philos, t_philo *list)
{
	size_t index;
	t_philo *philo;

	index = 0;
	while(philos > index)
	{
		philo = ft_creat_philo(index, "thinking");
		if(!philo)
			return (0);
		ft_lst_add_back(&list, philo);
		index++;
	}
	return (1);
}

int take_fork(t_philo *philo, t_philo *next_philo)
{
	philo->forks++;
	next_philo->forks--;
	printf("philo %d did take a fork\n", philo->id);
	return (0);
}

int give_fork(t_philo *philo, t_philo *next_philo)
{
	philo->forks--;
	next_philo->forks++;
	printf("philo %d did give a fork\n", philo->id);
	return (0);
}

int start_eating(t_philo *philo)
{
	philo->status = "eating";
	printf("philo %d is eating\n", philo->id);
}

int start_thinking(t_philo *philo)
{
	philo->status = "thinking";
	printf("philo %d is thinking\n", philo->id);
}	
int start_sleeping(t_philo *philo)
{
	philo->status = "sleeping";
	printf("philo %d is sleeping\n", philo->id);
}	

int start_routin(t_philo *philos, int die, int sleep, int eat)
{
	t_philo *tmp;
	int index;

	index = 0;
	tmp = philos;
	while(tmp)
	{
		if(tmp->forks == 1 && take_fork(tmp, tmp->next)
		{
			start_eating(tmp);
			sleep(eat);
		}
		else
		{
			start_sleeping(tmp);
			sleep(sleep);
		}
		tmp = tmp->next;
	}
	return (1);
}

int main(int ac, char **av)
{
	t_philo *philosophers;
	size_t philos_number;
	size_t time_die;
	size_t time_sleep;
	size_t time_eat;
	if (ac != 5)
		return (0);
	philos_number = ft_atoi(av[1]);
	time_die = ft_atoi(av[2]);
	time_sleep = ft_atoi(av[3]);
	time_eat = ft_atoi(av[4]);

	if(!ft_init_philosphers(philos_number, philosophers))
		return (0);
	if(!start_routin(philosophers, time_die, time_sleep, time_eat))
		return (0);
	
	
	return (0);
}