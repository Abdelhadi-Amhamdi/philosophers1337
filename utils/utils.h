/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:03:23 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/12 14:00:05 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H


int ft_atoi(const char *src);
void ft_lst_add_back(t_philo **list, t_philo *item);
t_philo *ft_get_last(t_philo *list);
t_philo *ft_creat_philo(int id, char *status);


#endif