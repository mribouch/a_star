/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:48:32 by mribouch          #+#    #+#             */
/*   Updated: 2020/03/03 18:52:59 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_star.h"

t_node		*ft_get_node(t_star_list **list, int x, int y)
{
	t_node		ret;
	t_star_list	*tmp;

	ret.pos.x = -1;
	ret.pos.y = -1;
	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->node.pos.x == x && tmp->node.pos.y == y)
			return (&tmp->node);
		tmp = tmp->next;
	}
	return (NULL);
}

t_father	ft_convertnode(t_node node)
{
	t_father father;

	father.pos.x = node.pos.x;
	father.pos.y = node.pos.y;
	father.g = node.g;
	father.f = node.f;
	return (father);
}

int			ft_count_node(t_star_list **list)
{
	t_star_list	*tmp;
	int			i;

	tmp = *list;
	i = 0;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int			ft_find_node(t_star_list **list, int x, int y)
{
	t_star_list	*tmp;

	tmp = *list;
	while (tmp->next != NULL)
	{
		if (tmp->node.pos.x == x && tmp->node.pos.y == y)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
