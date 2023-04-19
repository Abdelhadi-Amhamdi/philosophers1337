/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:58:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/04/19 16:12:53 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>

typedef enum s_bool {FALSE,TRUE}	t_bool;

typedef struct s_data
{
	int					philos_number;
	int					time_do_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_to_eat;
	t_bool				is_infini;
	sem_t				*sem_write;
	unsigned long long	start;
}	t_data;

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	t_data				*data;
	unsigned long long	last_meal;
	struct s_philo		*next;
}	t_philo;

unsigned long long	get_time(void);
int					ft_usleep(unsigned long long time, unsigned \
long long ttsleep, t_philo *ph);
t_philo				*ft_lst_creat(int id, t_data *data);
t_philo				*ft_lst_last(t_philo *list);
t_philo				*init_philos(int len, t_data *data);
int					get_data_args(t_data *data, char **args);
void				ft_lst_add_back(t_philo **list, t_philo *item);
void				ft_print(char *msg, t_philo *ph);
void				ft_eat(t_philo *ph, sem_t *sem_eat);
int					ft_atoi(const char *src);
int					parsing(t_data *data);
void				ft_wait_for_end(t_philo *phs);

#endif