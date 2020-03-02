/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:02:04 by mribouch          #+#    #+#             */
/*   Updated: 2020/03/02 18:57:04 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_star.h"
#include <math.h>
#include <stdio.h>

int		ft_isvalid(int x, int y, t_map map)
{
	if ((x >= 0 && x < map.width) && (y >= 0 && y < map.height))
		return (1);
	return (0);
}

int		ft_analyse(int x, int y, t_star *star)
{
	if (star->map.map[x + y * star->map.width] >= star->wall ||
		ft_find_node(&star->closel, x, y) == 1)
		return (1);
	if (ft_isvalid(x, y, star->map) == 0)
		return (1);
	return (0);
}

t_node	ft_fill_node(int x, int y, int f)
{
	t_node	node;

	node.pos.x = x;
	node.pos.y = y;
	node.f = f;
	return (node);
}

t_node	ft_get_f(int x, int y, t_star *star, t_node cur_node)
{
	t_node	ret;

	ret.father = ft_convertnode(cur_node);
	if (x != cur_node.pos.x && y != cur_node.pos.y)
		ret.g = 14 + cur_node.g;
	else
		ret.g = 10 + cur_node.g;
	ret.h = (abs(star->end.pos.x - x) + abs(star->end.pos.y - y)) * 10;
	ret.f = ret.g + ret.h;
	ret.pos.x = x;
	ret.pos.y = y;
	return (ret);
}

void	ft_step_child(t_node child, t_node cur_node, t_star *star)
{
	if (child.pos.x == star->end.pos.x && child.pos.y == star->end.pos.y)
	{
		child.father = ft_convertnode(cur_node);
		ft_add_node(&star->closel, child);
	}
	if (ft_find_node(&star->openl, child.pos.x, child.pos.y) == 1 &&
		ft_get_node(&star->openl, child.pos.x, child.pos.y)->f < child.f)
		return ;
	if (ft_find_node(&star->openl, child.pos.x, child.pos.y) == 1 &&
		child.g < ft_get_node(&star->openl, child.pos.x, child.pos.y)->g)
		ft_change_g(&star->openl, child.g, ft_convertnode(cur_node), child);
	else if (ft_find_node(&star->openl, child.pos.x, child.pos.y) == 0)
		ft_add_node(&star->openl, child);
}

int		ft_validiag(int x, int y, t_star *star, t_node cur_node)
{
	if (x < cur_node.pos.x && y < cur_node.pos.y)
		if (ft_analyse(cur_node.pos.x, cur_node.pos.y - 1, star) == 0 ||
			ft_analyse(cur_node.pos.x - 1, cur_node.pos.y, star) == 0)
			return (0);
	if (x > cur_node.pos.x && y > cur_node.pos.y)
		if (ft_analyse(cur_node.pos.x, cur_node.pos.y + 1, star) == 0 ||
			ft_analyse(cur_node.pos.x + 1, cur_node.pos.y, star) == 0)
			return (0);
	if (x > cur_node.pos.x && y < cur_node.pos.y)
		if (ft_analyse(cur_node.pos.x, cur_node.pos.y - 1, star) == 0 ||
			ft_analyse(cur_node.pos.x + 1, cur_node.pos.y, star) == 0)
			return (0);
	if (x < cur_node.pos.x && y > cur_node.pos.y)
		if (ft_analyse(cur_node.pos.x, cur_node.pos.y + 1, star) == 0 ||
			ft_analyse(cur_node.pos.x - 1, cur_node.pos.y, star) == 0)
			return (0);
	return (1);
}

void	ft_diag(t_star *star, t_node c_node)
{
	t_node	node;

	if (ft_analyse(c_node.pos.x - 1, c_node.pos.y - 1, star) == 0 &&
		ft_validiag(c_node.pos.x - 1, c_node.pos.y - 1, star, c_node) == 0)
	{
		node = ft_get_f(c_node.pos.x - 1, c_node.pos.y - 1, star, c_node);
		ft_step_child(node, c_node, star);
	}
	if (ft_analyse(c_node.pos.x + 1, c_node.pos.y - 1, star) == 0 &&
		ft_validiag(c_node.pos.x + 1, c_node.pos.y - 1, star, c_node) == 0)
	{
		node = ft_get_f(c_node.pos.x + 1, c_node.pos.y - 1, star, c_node);
		ft_step_child(node, c_node, star);
	}
	if (ft_analyse(c_node.pos.x - 1, c_node.pos.y + 1, star) == 0 &&
		ft_validiag(c_node.pos.x - 1, c_node.pos.y + 1, star, c_node) == 0)
	{
		node = ft_get_f(c_node.pos.x - 1, c_node.pos.y + 1, star, c_node);
		ft_step_child(node, c_node, star);
	}
	if (ft_analyse(c_node.pos.x + 1, c_node.pos.y + 1, star) == 0 &&
		ft_validiag(c_node.pos.x + 1, c_node.pos.y + 1, star, c_node) == 0)
	{
		node = ft_get_f(c_node.pos.x + 1, c_node.pos.y + 1, star, c_node);
		ft_step_child(node, c_node, star);
	}
}

void	ft_check_child(t_star *star, t_node cur_node)
{
	t_node node;

	ft_diag(star, cur_node);
	if (ft_analyse(cur_node.pos.x - 1, cur_node.pos.y, star) == 0)
	{
		node = ft_get_f(cur_node.pos.x - 1, cur_node.pos.y, star, cur_node);
		ft_step_child(node, cur_node, star);
	}
	if (ft_analyse(cur_node.pos.x + 1, cur_node.pos.y, star) == 0)
	{
		node = ft_get_f(cur_node.pos.x + 1, cur_node.pos.y, star, cur_node);
		ft_step_child(node, cur_node, star);
	}
	if (ft_analyse(cur_node.pos.x, cur_node.pos.y - 1, star) == 0)
	{
		node = ft_get_f(cur_node.pos.x, cur_node.pos.y - 1, star, cur_node);
		ft_step_child(node, cur_node, star);
	}
	if (ft_analyse(cur_node.pos.x, cur_node.pos.y + 1, star) == 0)
	{
		node = ft_get_f(cur_node.pos.x, cur_node.pos.y + 1, star, cur_node);
		ft_step_child(node, cur_node, star);
	}
}

t_node	ft_find_lower_f(t_star_list **list)
{
	t_node		ret;
	t_star_list	*tmp;

	ret.f = INT_MAX;
	tmp = *list;
	while (tmp->next != NULL)
	{
		if (tmp->node.f < ret.f)
			ret = tmp->node;
		tmp = tmp->next;
	}
	return (ret);
}

t_node	ft_closest_node(t_star_list **close, t_node end)
{
	t_star_list	*tmp;
	t_node		node;
	int			dist;
	int			lastdist;

	tmp = *close;
	lastdist = INT_MAX;
	while (tmp->next != NULL)
	{
		dist = (tmp->node.pos.x - end.pos.x) * (tmp->node.pos.x - end.pos.x) +
			(tmp->node.pos.y - end.pos.y) * (tmp->node.pos.y - end.pos.y);
		if (dist < lastdist)
		{
			lastdist = dist;
			node.pos.x = tmp->node.pos.x;
			node.pos.y = tmp->node.pos.y;
		}
		tmp = tmp->next;
	}
	return (node);
}

t_node	*ft_get_path(t_node cur_node, t_star *star)
{
	t_node	find;
	t_node	prev;
	int		i;
	t_node	*ret;

	i = 0;
	find = cur_node;
	prev = find;
	// ft_print_list(*close);
	while (find.pos.x != star->start.pos.x || find.pos.y != star->start.pos.y)
	{
		find = *ft_get_node(&star->closel,
			find.father.pos.x, find.father.pos.y);
		if (find.pos.x != star->start.pos.x || find.pos.y != star->start.pos.y)
			prev = find;
		i++;
	}
	star->map.map[prev.pos.x + prev.pos.y * star->map.width] = 7;
	ft_print_map(star->map);
	if (!(ret = malloc(sizeof(t_node))))
		return (NULL);
	ret->pos.x = prev.pos.x;
	ret->pos.y = prev.pos.y;
	return (ret);
}

void	ft_check_start_end(t_node start, t_node end, t_map map)
{
	if (ft_isvalid(start.pos.x, start.pos.y, map) == 0)
	{
		ft_putendl("Start point invalid !");
		exit(0);
	}
	if (ft_isvalid(end.pos.x, end.pos.y, map) == 0)
	{
		ft_putendl("Destination point is invalid !");
		exit(0);
	}
}

t_node	*ft_is_openl_empty(t_star *star)
{
	t_star_list	*retop;
	t_star_list	*retclo;

	if (!(retop = malloc(sizeof(t_star_list))))
		return (NULL);
	if (!(retclo = malloc(sizeof(t_star_list))))
		return (NULL);
	retclo->next = NULL;
	retop->next = NULL;
	star->end = ft_closest_node(&star->closel, star->end);
	ft_delist(&star->closel);
	ft_delist(&star->openl);
	star->openl = retop;
	star->closel = retclo;
	ft_add_node(&star->openl, star->start);
	return (ft_a_star(star));
}

t_node	*ft_a_star(t_star *star)
{
	t_node	c_node;
	int		count;

	ft_check_start_end(star->start, star->end, star->map);
	while (star->openl)
	{
		c_node = ft_find_lower_f(&star->openl);
		if (c_node.pos.x == star->end.pos.x && c_node.pos.y == star->end.pos.y)
		{
			ft_add_node(&star->closel, c_node);
			break ;
		}
		if ((count = ft_count_node(&star->openl)) >= 1)
			ft_del_node(&star->openl, c_node.pos.x, c_node.pos.y);
		if (count <= 0)
			return (ft_is_openl_empty(star));
		ft_add_node(&star->closel, c_node);
		ft_check_child(star, c_node);
	}
	return (ft_get_path(c_node, star));
}
