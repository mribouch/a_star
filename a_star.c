/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:02:04 by mribouch          #+#    #+#             */
/*   Updated: 2020/02/07 15:02:04 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <math.h>
#include <stdio.h>

int		ft_isvalid(int x, int y, t_map map)
{
	if ((x >= 0 && x < map.width) && (y >= 0 && y < map.height))
		return (1);
	return (0);
}

int		ft_analyse(int x, int y, t_star star, t_star_list **close)
{
	if (star.map.map[x + y * star.map.width] >= star.wall ||
		ft_find_node(close, x, y) == 1)
		return (1);
	if (ft_isvalid(x, y, star.map) == 0)
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

t_node	ft_get_f(int x, int y, t_mainnode point, t_node cur_node)
{
	t_node	ret;

	ret.father = ft_convertnode(cur_node);
	if (x != cur_node.pos.x && y != cur_node.pos.y)
		ret.g = 14 + cur_node.g;
	else
		ret.g = 10 + cur_node.g;
	ret.h = (abs(point.end.pos.x - x) + abs(point.end.pos.y - y)) * 10;
	ret.f = ret.g + ret.h;
	ret.pos.x = x;
	ret.pos.y = y;
	return (ret);
}

void	ft_step_child(t_node child, t_node cur_node, t_star_list **open, t_star_list **close, t_mainnode point)
{
	if (child.pos.x == point.end.pos.x && child.pos.y == point.end.pos.y)
	{
		child.father = ft_convertnode(cur_node);
		ft_add_node(close, child);
	}
	if (ft_find_node(open, child.pos.x, child.pos.y) == 1 &&
		ft_get_node(open, child.pos.x, child.pos.y)->f < child.f)
		return ;
	if (ft_find_node(open, child.pos.x, child.pos.y) == 1 &&
		child.g < ft_get_node(open, child.pos.x, child.pos.y)->g)
		ft_change_g(open, child.g, ft_convertnode(cur_node), child);
	else if (ft_find_node(open, child.pos.x, child.pos.y) == 0)
		ft_add_node(open, child);
}

int		ft_validiag(int x, int y, t_star star, t_star_list **close, t_node cur_node)
{
	if (x < cur_node.pos.x && y < cur_node.pos.y)
		if (ft_analyse(cur_node.pos.x, cur_node.pos.y - 1, star, close) == 0 ||
			ft_analyse(cur_node.pos.x - 1, cur_node.pos.y, star, close) == 0)
			return (0);
	if (x > cur_node.pos.x && y > cur_node.pos.y)
		if (ft_analyse(cur_node.pos.x, cur_node.pos.y + 1, star, close) == 0 ||
			ft_analyse(cur_node.pos.x + 1, cur_node.pos.y, star, close) == 0)
			return (0);
	if (x > cur_node.pos.x && y < cur_node.pos.y)
		if (ft_analyse(cur_node.pos.x, cur_node.pos.y - 1, star, close) == 0 ||
			ft_analyse(cur_node.pos.x + 1, cur_node.pos.y, star, close) == 0)
			return (0);
	if (x < cur_node.pos.x && y > cur_node.pos.y)
		if (ft_analyse(cur_node.pos.x, cur_node.pos.y + 1, star, close) == 0 ||
			ft_analyse(cur_node.pos.x - 1, cur_node.pos.y, star, close) == 0)
			return (0);
	return (1);
}

void	ft_diag(t_star star, t_star_list **open, t_star_list **close, t_node cur_node)
{
	t_node	node;

	if (ft_analyse(cur_node.pos.x - 1, cur_node.pos.y - 1, star, close) == 0 &&
		ft_validiag(cur_node.pos.x - 1, cur_node.pos.y - 1, star, close, cur_node) == 0)
	{
		node = ft_get_f(cur_node.pos.x - 1, cur_node.pos.y - 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.pos.x + 1, cur_node.pos.y - 1, star, close) == 0 &&
		ft_validiag(cur_node.pos.x + 1, cur_node.pos.y - 1, star, close, cur_node) == 0)
	{
		node = ft_get_f(cur_node.pos.x + 1, cur_node.pos.y - 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.pos.x - 1, cur_node.pos.y + 1, star, close) == 0 &&
		ft_validiag(cur_node.pos.x - 1, cur_node.pos.y + 1, star, close, cur_node) == 0)
	{
		node = ft_get_f(cur_node.pos.x - 1, cur_node.pos.y + 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.pos.x + 1, cur_node.pos.y + 1, star, close) == 0 &&
		ft_validiag(cur_node.pos.x + 1, cur_node.pos.y + 1, star, close, cur_node) == 0)
	{
		node = ft_get_f(cur_node.pos.x + 1, cur_node.pos.y + 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
}

void	ft_check_child(t_star star, t_star_list **open, t_star_list **close, t_node cur_node)
{
	t_node node;

	ft_diag(star, open, close, cur_node);
	if (ft_analyse(cur_node.pos.x - 1, cur_node.pos.y, star, close) == 0)
	{
		node = ft_get_f(cur_node.pos.x - 1, cur_node.pos.y, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.pos.x + 1, cur_node.pos.y, star, close) == 0)
	{
		node = ft_get_f(cur_node.pos.x + 1, cur_node.pos.y, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.pos.x, cur_node.pos.y - 1, star, close) == 0)
	{
		node = ft_get_f(cur_node.pos.x, cur_node.pos.y - 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.pos.x, cur_node.pos.y + 1, star, close) == 0)
	{
		node = ft_get_f(cur_node.pos.x, cur_node.pos.y + 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
}

t_node	ft_find_lower_f(t_star_list **list)
{
	t_node	ret;
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
	t_node	node;
	int		dist;
	int		lastdist;

	tmp = *close;
	lastdist = INT_MAX;
	while (tmp->next != NULL)
	{
		dist = (tmp->node.pos.x - end.pos.x) *  (tmp->node.pos.x - end.pos.x) + (tmp->node.pos.y - end.pos.y) * (tmp->node.pos.y - end.pos.y);
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

t_node	ft_get_path(t_node cur_node, t_star_list **close, t_star star)
{
	t_node	find;
	t_node	prev;
	int		i;

	i = 0;
	find = cur_node;
	prev = find;
	ft_print_list(*close);
	while (find.pos.x != star.point.start.pos.x || find.pos.y != star.point.start.pos.y)
	{
		find = *ft_get_node(close, find.father.pos.x, find.father.pos.y);
		if (find.pos.x != star.point.start.pos.x || find.pos.y != star.point.start.pos.y)
			prev = find;
		i++;
	}
	star.map.map[prev.pos.x + prev.pos.y * star.map.width] = 7;
	ft_print_map(star.map);
	return (prev);
}

t_node    ft_a_star(t_star star, t_star_list **open, t_star_list **close)
{
    t_star_list  *path;
	t_node	cur_node;
	int		count;

	if (ft_isvalid(star.point.start.pos.x, star.point.start.pos.y, star.map) == 0)
	{
		ft_putendl("Start point invalid !");
		exit(0);
	}
	if (ft_isvalid(star.point.end.pos.x, star.point.end.pos.y, star.map) == 0)
	{
		ft_putendl("Destination point is invalid !");
		exit(0);
	}
	if (!(path = malloc(sizeof(t_star_list))))
		exit(0);
    while (*open)
    {
		cur_node = ft_find_lower_f(open);
		if (cur_node.pos.x == star.point.end.pos.x && cur_node.pos.y == star.point.end.pos.y)
		{
			ft_add_node(close, cur_node);
			break;
		}
		if ((count = ft_count_node(open)) >= 1)
			ft_del_node(open, cur_node.pos.x, cur_node.pos.y);
		if (count == 0)
		{
			t_star_list	*retop;
			t_star_list	*retclo;

			if (!(retop = malloc(sizeof(t_star_list))))
				return (cur_node);
			if (!(retclo = malloc(sizeof(t_star_list))))
				return (cur_node);
			retclo->next = NULL;
			retop->next = NULL;
			star.point.end = ft_closest_node(close, star.point.end);
			ft_delist(close);
			ft_delist(open);
			ft_add_node(&retop, star.point.start);
			return (ft_a_star(star, &retop, &retclo));
		}
		ft_add_node(close, cur_node);
        ft_check_child(star, open, close, cur_node);
    }
	return (ft_get_path(cur_node, close, star));
}