/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:58:47 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/04/17 02:26:06 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*ft_lst_creat(int id, t_data *data)
{
	t_philo	*item;

	item = malloc(sizeof(t_philo));
	if (!item)
		return (NULL);
	item->id = id;
	item->next = NULL;
	item->data = data;
	item->last_meal = 0;
	item->pid = -1;
	return (item);
}

t_philo	*ft_lst_last(t_philo *list)
{
	t_philo	*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lst_add_back(t_philo **list, t_philo *item)
{
	t_philo	*last;

	if (!*list)
		*list = item;
	else
	{
		last = ft_lst_last(*list);
		last->next = item;
	}
}

t_philo	*init_philos(int len, t_data *data)
{
	t_philo	*item;
	t_philo	*list;
	int		index;

	item = NULL;
	list = NULL;
	index = 0;
	while (len > index)
	{
		item = ft_lst_creat(index + 1, data);
		ft_lst_add_back(&list, item);
		index++;
	}
	item->next = list;
	return (list);
}

void	ft_eat(t_philo *ph, sem_t *sem_eat)
{
	sem_wait(sem_eat);
	ft_print("has taken a fork", ph);
	if (ph->data->philos_number == 1)
		ft_print(NULL, ph);
	sem_wait(sem_eat);
	ft_print("has taken a fork", ph);
	ft_print("is eating", ph);
	if (ft_usleep(get_time(), ph->data->time_to_eat, ph))
		ft_print(NULL, ph);
	ph->last_meal = get_time();
	sem_post(sem_eat);
	sem_post(sem_eat);
}
