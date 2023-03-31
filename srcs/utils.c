/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:49:48 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/31 15:40:36 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *src)
{
	int	signe;
	int	result;
	int	index;

	index = 0;
	result = 0;
	signe = 1;
	while ((src[index] >= 9 && src[index] <= 13) || src[index] == ' ')
		index++;
	if (src[index] == '-' || src[index] == '+')
	{
		if (src[index] == '-')
			signe = -1;
		index++;
	}
	while (src[index] >= '0' && src[index] <= '9')
	{
		result = (result * 10) + (src[index] - '0');
		index++;
	}
	return (result * signe);
}

t_philo	*ft_creat_philo(int id, t_data *data, t_time *time)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->next = NULL;
	philo->last_eat = 0;
	philo->philo_data = data;
	philo->time = time;
	philo->eated = 0;
	return (philo);
}

t_philo	*ft_get_last(t_philo *list)
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
		last = ft_get_last(*list);
		last->next = item;
	}
}

unsigned long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
