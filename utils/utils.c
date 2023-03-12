/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:57:34 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/12 14:09:16 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../srcs/philo.h"

int ft_atoi(const char *src)
{
    int signe;
    int result;
    int index;
    
    index = 0;
    result = 0;
    signe = 1;
    while (src[index] >= 9 && src[index] <= 13 || src[index] == ' ')
        index++;
    if (src[index] == '-' || src[index] == '+')
    {
        if(src[index] == '-')
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


t_philo *ft_creat_philo(int id, char *status)
{
    t_philo *philo;

    philo = malloc(sizeof(t_philo));
    if(!philo)
        return (0);
    philo->id = id;
    philo->forks = 1;
    philo->status = status;
    philo->next = NULL;
    return (philo);
}

t_philo *ft_get_last(t_philo *list)
{
    t_philo *tmp;

    tmp = list;
    while(tmp->next)
        tmp = tmp->next;
    return (tmp);
}

void ft_lst_add_back(t_philo **list, t_philo *item)
{
    t_philo *last;
    
    if(!*list)
        *list = item;
    else
    {
        last = ft_get_last(*list);
        last->next = item;
    }
}

