/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:30:06 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/20 14:22:40 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef enum s_bool {FALSE,TRUE}	t_bool ;

typedef struct s_time
{
	int					eat;
	int					sleep;
	int					die;
	int					times_to_eat;
	int					philos_num;
	unsigned long long	l_eat;
}	t_time;

typedef struct s_philo
{
	int				id;
	pthread_t		philo;
	pthread_mutex_t	fork;
	t_time			*time_data;
	struct s_philo	*next;
}	t_philo;

// actions
void				ft_sleep(t_philo *ph, unsigned long long start);
void				ft_eat(t_philo *ph, unsigned long long start);
void				ft_think(t_philo *ph, unsigned long long start);
void				check_if_die(t_philo *ph, unsigned long \
l_eat, unsigned long long start);
void				ft_usleep(unsigned long long time, unsigned \
long long ttsleep);

// utils
int					ft_atoi(const char *src);
t_philo				*ft_get_last(t_philo *list);
t_philo				*ft_creat_philo(int id, t_time *time_data);
void				ft_lst_add_back(t_philo **list, t_philo *item);
unsigned long long	get_time(void);

// main
t_philo				*ft_init_philos(t_time *time_data);
void				*routine(void *args);
void				ft_start_philos(t_philo *phs);

#endif