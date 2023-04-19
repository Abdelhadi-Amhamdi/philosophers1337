/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:58:44 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/04/19 16:07:41 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo, sem_t *semaphore)
{
	int	i;

	i = philo->data->times_to_eat;
	while (i)
	{
		ft_eat(philo, semaphore);
		if (!(i - 1) && !philo->data->is_infini)
			exit (0);
		ft_print("is sleeping", philo);
		if (ft_usleep(get_time(), philo->data->time_to_sleep, philo))
			ft_print(NULL, philo);
		ft_print("is thinking", philo);
		if (!philo->data->is_infini)
			i--;
	}
	exit (0);
}

void	ft_wait_for_end(t_philo *phs)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	while (phs)
	{
		if (status)
		{
			if (phs->pid != pid)
				kill(phs->pid, SIGINT);
		}
		else
		{
			if (phs->pid != pid)
				waitpid(phs->pid, NULL, 0);
		}
		phs = phs->next;
		if (phs->id == 1)
			break ;
	}	
}

void	ft_start_philos(t_philo *phs, sem_t *sem)
{
	phs->data->start = get_time();
	while (phs)
	{
		phs->pid = fork();
		if (phs->pid == 0)
		{
			phs->last_meal = get_time();
			routine(phs, sem);
		}
		phs = phs->next;
		if (phs->id == 1)
			break ;
	}
	ft_wait_for_end(phs);
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
	sem_t	*sem_eat;
	t_data	*data;
	t_philo	*philos;

	if (ac < 5 || ac > 6)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (get_data_args(data, av + 1) || parsing(data))
		return (free(data), 0);
	sem_unlink("sem_eat");
	sem_unlink("sem_write");
	sem_eat = sem_open("sem_eat", O_CREAT, 0666, data->philos_number);
	data->sem_write = sem_open("sem_write", O_CREAT, 0666, 1);
	philos = init_philos(data->philos_number, data);
	ft_start_philos(philos, sem_eat);
	sem_close(sem_eat);
	sem_close(data->sem_write);
	sem_unlink("sem_eat");
	sem_unlink("sem_write");
	ft_free_list(philos);
	free(data);
	return (0);
}
