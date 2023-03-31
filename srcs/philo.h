/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:30:06 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/31 13:47:23 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum s_bool {FALSE,TRUE}	t_bool;

typedef struct s_time
{
	pthread_mutex_t		t;
	unsigned long long	start;
	int					time_to_eat;
	int					time_to_die;
	int					times_to_eat;
	int					time_to_sleep;
}	t_time;

typedef struct s_data
{
	pthread_mutex_t	die;
	int				died;
	pthread_mutex_t	write;
	t_bool			is_infini;
	int				philos_num;
}	t_data;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		fork;
	pthread_t			philo;
	int					eated;
	unsigned long long	last_eat;
	t_data				*philo_data;
	t_time				*time_data;
	struct s_philo		*next;
}	t_philo;

// actions 
void				take_forks(t_philo *ph);
void				eat(t_philo *ph);
void				ft_sleep(t_philo *ph);
void				ft_think(t_philo *ph);

// utils
void				get_args_data(char **args, t_time *time_data);
void				check_if_infini(t_data *philo_data, t_time *time);
void				ft_print(char *str, t_philo *ph, unsigned long long time);
int					ft_atoi(const char *src);

// time
unsigned long long	get_time(void);
void				ft_usleep(unsigned long long time, \
unsigned long long ttsleep);

// list
t_philo				*ft_get_last(t_philo *list);
void				ft_lst_add_back(t_philo **list, t_philo *item);
t_philo				*ft_creat_philo(int id, t_data *data, t_time *time);

#endif