/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:17:09 by marvin            #+#    #+#             */
/*   Updated: 2020/01/14 15:17:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		ft_find_node(t_list **list, int x, int y)
{
	t_list	*tmp;

	tmp = *list;
	while(tmp->next != NULL)
	{
		// ft_putendl("wowo");
		// printf("dans close list : x = %d, y = %d\n", tmp->x, tmp->y);
		if (tmp->x == x && tmp->y == y)
		{
			// ft_putendl("OUI JE SUIS DANS LA CLOSE");
			// printf("DANS LA CLOSE : x = %d, y = %d\n", x, y);
			return (1);
		}
		tmp = tmp->next;
	}
	// ft_print_list(*list);
	return (0);
}

void	ft_delist(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	ft_del_node(t_list **list, int x, int y)
{
	t_list	*tmp;
	t_list	*previous;

	tmp = *list;
	if ((tmp != NULL) && (tmp->x == x && tmp->y == y))
	{
		*list = tmp->next;
		free(tmp);
		return ;
	}
	while ((tmp != NULL) && (tmp->x != x && tmp->y != y))
	{
		previous = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	previous->next = tmp->next;
	free(tmp);
}

void	ft_add_node(t_list **list, int x, int y, int f)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return ;
	new->x = x; 
	new->y = y;
	new->f = f;
	new->next = *list;
	*list = new;
}