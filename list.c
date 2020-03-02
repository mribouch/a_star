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

#include "a_star.h"

t_father	ft_convertnode(t_node node)
{
	t_father father;

	father.pos.x = node.pos.x;
	father.pos.y = node.pos.y;
	father.g = node.g;
	father.f = node.f;
	return (father);
}

void	ft_change_g(t_star_list **list, int g, t_father father, t_node find)
{
	t_star_list	*tmp;

	tmp = *list;
	while (tmp->next != NULL)
	{
		if (tmp->node.pos.x == find.pos.x && tmp->node.pos.y == find.pos.y)
		{
			tmp->node.g = g;
			tmp->node.father = father;
		}
		tmp = tmp->next;
	}
}

t_node	*ft_get_node(t_star_list **list, int x, int y)
{
	t_node	ret;
	// int	i;

	ret.pos.x = -1;
	ret.pos.y = -1;
	t_star_list	*tmp;

	tmp = *list;
	// i = 0;
	while (tmp != NULL)
	{
		// printf("nodex = %d, nody = %d, x = %d, y = %d\n", tmp->node.pos.x, tmp->node.pos.y, x, y);
		if (tmp->node.pos.x == x && tmp->node.pos.y == y)
			return (&tmp->node);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_count_node(t_star_list **list)
{
	t_star_list	*tmp;
	int		i;

	tmp = *list;
	i = 0;
	while (tmp->next != NULL)
	{
		// ft_putendl("wahou");
		// printf("nodex = %d, nody = %d, x = %d, y = %d\n", tmp->node.father->x, tmp->node.father->y, x, y);
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int		ft_find_node(t_star_list **list, int x, int y)
{
	t_star_list	*tmp;

	tmp = *list;
	while(tmp->next != NULL)
	{
		// ft_putendl("wowo");
		// printf("dans close list : x = %d, y = %d\n", tmp->x, tmp->y);
		if (tmp->node.pos.x == x && tmp->node.pos.y == y)
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

void	ft_delist(t_star_list **list)
{
	t_star_list	*tmp;

	// ft_putendl("dans delist");
	if (*list != NULL)
	{
		// ft_putendl("dans if");
		while (*list)
		{
			// ft_putendl("dans boucle");
			tmp = (*list)->next;
			// ft_putendl("apres next");
			free(*list);
			// ft_putendl("apres free");
			*list = tmp;
			// ft_putendl("fin boucle");
		}
		// ft_putendl("avant NULL");
		*list = NULL;
		// ft_putendl("apres NULL");

	}
}

void	ft_del_node(t_star_list **list, int x, int y)
{
	t_star_list	*tmp;
	t_star_list	*previous;

	tmp = *list;
	// ft_putendl("debut delnode");
	if ((tmp != NULL) && (tmp->node.pos.x == x && tmp->node.pos.y == y) && list)
	{
		// ft_putendl("dans if delnode");
		*list = tmp->next;
		// ft_putendl("after list = tmpnext");
		free(tmp);
		// ft_putendl("after free");
		// ft_putendl("dans if delnode mais apres omgalul");
		return ;
	}
	// ft_putendl("avant boucle");
	while (tmp->node.pos.x != x || tmp->node.pos.y != y)
	{
		previous = tmp;
		tmp = tmp->next;
	}
	// ft_putendl("apres boucle");
	if (tmp == NULL)
		return ;
	previous->next = tmp->next;
	// ft_putendl("prevnext");
	free(tmp);
}

void	ft_add_node(t_star_list **list, t_node node)
{
	t_star_list	*new;

	if (!(new = malloc(sizeof(t_star_list))))
		return ;
	new->node = node;
	new->next = *list;
	*list = new;
}