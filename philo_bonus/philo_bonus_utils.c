/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:58:47 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/04/14 17:47:21 by aamhamdi         ###   ########.fr       */
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
