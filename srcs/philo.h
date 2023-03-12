/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:30:06 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/12 14:19:15 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include "libc.h"
#include "../utils/utils.h"

typedef struct s_philo
{
    int id;
    char *status;
    int forks;
    struct s_philo *next;
} t_philo;

int ft_init_philosphers(size_t philos, t_philo *list);
int start_routin(t_philo *philos, int die, int sleep, int eat);
int take_fork(t_philo *philo, t_philo *next_philo);
int give_fork(t_philo *philo, t_philo *next_philo);

#endif