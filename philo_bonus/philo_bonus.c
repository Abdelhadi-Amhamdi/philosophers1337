/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:58:44 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/04/16 02:43:36 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo, sem_t *semaphore)
{
	int	i;

	i = philo->data->times_to_eat;
	if ((philo->id % 2))
		usleep(1000);
	while (i)
	{
		philo->last_meal = get_time();
		sem_wait(semaphore);
		ft_print("has taken a fork", philo);
		ft_print("has taken a fork", philo);
		ft_print("is eating", philo);
		if (ft_usleep(get_time(), philo->data->time_to_eat, philo))
			ft_print(NULL, philo);
		philo->last_meal = get_time();
		sem_post(semaphore);
		if (!(i - 1) && !philo->data->is_infini)
			exit (1);
		ft_print("is sleeping", philo);
		if (ft_usleep(get_time(), philo->data->time_to_sleep, philo))
			ft_print(NULL, philo);
		ft_print("is thinking", philo);
		if (!philo->data->is_infini)
			i--;
	}
}

void	ft_start_philos(t_philo *phs, sem_t *sem)
{
	while (phs)
	{
		phs->pid = fork();
		if (phs->pid == 0)
		{
			routine(phs, sem);
			exit (1);
		}
		phs = phs->next;
		if (phs->id == 1)
			break ;
	}
	return ;
}

int	parsing(t_data *data)
{
	if (data->philos_number < 1 || data->time_do_die < 1 || data->time_to_eat \
	< 1 || data->time_to_sleep < 1)
		return (1);
	return (0);
}

void	ft_free_list(t_philo *ph)
{
	t_philo	*next;
	t_philo	*tmp;
	int		i;
	int		len;

	i = 0;
	len = ph->data->philos_number;
	tmp = ph;
	while (i < len)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
		i++;
	}
}

int	main(int ac, char **av)
{
	sem_t	*semaphore;
	t_data	*data;
	t_philo	*philos;

	if (ac < 5 || ac > 6)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (get_data_args(data, av + 1) || parsing(data))
		return (free(data), 0);
	sem_unlink("sem");
	semaphore = sem_open("sem", O_CREAT, 0666, (data->philos_number / 2));
	philos = init_philos(data->philos_number, data);
	data->start = get_time();
	ft_start_philos(philos, semaphore);
	wait(NULL);
	sem_close(semaphore);
	sem_unlink("sem");
	ft_free_list(philos);
	free(data);
	return (0);
}
