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

t_father	ft_switchnode(t_node node)
{
	t_father father;

	father.x = node.x;
	father.y = node.y;
	father.g = node.g;
	father.f = node.f;
	return (father);
}

void	ft_change_g(t_list **list, int g, t_father father, t_node find)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp->next != NULL)
	{
		if (tmp->node.x == find.x && tmp->node.y == find.y)
		{
			tmp->node.g = g;
			tmp->node.father = father;
		}
		tmp = tmp->next;
	}
}

t_node	ft_get_node(t_list **list, int x, int y)
{
	t_node ret;

	ret.x = -1;
	ret.y = -1;
	t_list	*tmp;

	tmp = *list;
	while (tmp->next != NULL)
	{
		// printf("nodex = %d, nody = %d, x = %d, y = %d\n", tmp->node.father->x, tmp->node.father->y, x, y);
		if (tmp->node.x == x && tmp->node.y == y)
			return (tmp->node);
		tmp = tmp->next;
	}
	return (ret);
}

int		ft_find_node(t_list **list, int x, int y)
{
	t_list	*tmp;

	tmp = *list;
	while(tmp->next != NULL)
	{
		// ft_putendl("wowo");
		// printf("dans close list : x = %d, y = %d\n", tmp->x, tmp->y);
		if (tmp->node.x == x && tmp->node.y == y)
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
	// printf("je cherche %d ; %d\n", x, y);
	// ft_putendl("avant premier if");
	// ft_print_list(*list);
	if ((tmp != NULL) && (tmp->node.x == x && tmp->node.y == y))
	{
		// ft_putendl("dans premier if");
		*list = tmp->next;
		free(tmp);
		return ;
	}
	// printf("tmpnode %d ; %d\n", tmp->node.x, tmp->node.y);
	// while (tmp->next != NULL)
	while (tmp->node.x != x || tmp->node.y != y)
	{
		// ft_putendl("dans boucle");
		previous = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	// ft_putendl("avant previous machin");
	// if (tmp->next != NULL)
	previous->next = tmp->next;
	// ft_putendl("apres previous machin");
	free(tmp);
}

void	ft_add_node(t_list **list, t_node node)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return ;
	new->node = node;
	new->next = *list;
	*list = new;
}