/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_collector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:49:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/11 15:37:18 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum garbege_collector {ALLOCATION, FREE} g_c;

typedef struct s_list {void *add; struct s_list *next} t_list;

t_list	ft_list_creat(void *add)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->add = add;
	node->next = NULL;
	return (node);
}

void	ft_lst_add_front(t_list **list, t_list *item)
{
	if (*list)
		item->next = *list;
	*list = item;
}

void	ft_free_list(t_list *list)
{
	t_list	*tmp;
	t_list	*next;

	tmp = list;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

int	g_collector(void *add, g_c type)
{
	static t_list	*adresses;
	t_list			*node;

	node = NULL;
	if (type == ALLOCATION)
	{
		node  = ft_list_creat(add);
		if (!node)
			return (0);
		ft_lst_add_front(&adresses, node);
	}
	else
		ft_free_list(adresses);
	return (1);
}
