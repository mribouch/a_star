/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 03:47:45 by marvin            #+#    #+#             */
/*   Updated: 2020/01/14 03:47:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "libft/libft.h"
#include <math.h>

int		ft_isvalid(int x, int y)
{
	if ((x >= 0 && x < 10) && (y >= 0 && y < 10))
		return (1);
	return (0);
}

int		ft_analyse(int x, int y, t_star star, t_list **close)
{
	// ft_putendl("here ?");
	if (star.map.map[y][x] == star.wall || ft_find_node(close, x, y) == 1)
		return (1);
	if (ft_isvalid(x, y) == 0)
		return (1);
	// ft_putendl("here apres?");
	return (0);
}

int		ft_abs(int num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

t_node	ft_fill_node(int x, int y, int f)
{
	t_node	node;

	// printf("x = %d, y = %d, f = %d rempli le node\n", x, y ,f);
	node.x = x;
	node.y = y;
	node.f = f;
	return (node);
}

t_node		ft_get_f(int x, int y, t_mainnode point, t_node cur_node)
{
	t_node	ret;

	ret.father = ft_switchnode(cur_node);
	// printf("ATTRIBUTION : father a x = %d, y = %d : x = %d, y = %d\n", x, y, ret.father.x, ret.father.y);
	if (x != cur_node.x && y != cur_node.y)
		ret.g = 14 + cur_node.g;
	else
		ret.g = 10 + cur_node.g;
	ret.h = (ft_abs(point.end.x - x) + ft_abs(point.end.y - y)) * 10;
	ret.f = ret.g + ret.h;
	ret.x = x;
	ret.y = y;
	// printf("x = %d, y = %d, f = %d\n", x, y, f);
	return (ret);
}

void	ft_step_child(t_node child, t_node cur_node, t_list **open, t_list **close, t_mainnode point)
{
	(void)close;
	(void)point;
	if (child.x == point.end.x && child.y == point.end.y)
	{
		child.father = ft_switchnode(cur_node);
		ft_add_node(close, child);
		// return ;
	}
	if (ft_find_node(open, child.x, child.y) == 1 && ft_get_node(open, child.x, child.y).f < child.f)
		return ;
	if (ft_find_node(open, child.x, child.y) == 1 && child.g < ft_get_node(open, child.x, child.y).g)
		ft_change_g(open, child.g, ft_switchnode(cur_node), child);
	// if (ft_find_node(open, child.x, child.y) == 1 && child.g > cur_node.g)
	// 	ft_change_g(open, cur_node.g, &cur_node, child);
	else if (ft_find_node(open, child.x, child.y) == 0)
		ft_add_node(open, child);
}

void	ft_check_child(t_star star, t_list **open, t_list **close, t_node cur_node)
{
	t_node node;

	if (ft_analyse(cur_node.x - 1, cur_node.y - 1, star, close) == 0)
	{
		node = ft_get_f(cur_node.x - 1, cur_node.y - 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.x + 1, cur_node.y - 1, star, close) == 0)
	{
		node = ft_get_f(cur_node.x + 1, cur_node.y - 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.x - 1, cur_node.y, star, close) == 0)
	{
		node = ft_get_f(cur_node.x - 1, cur_node.y, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.x + 1, cur_node.y, star, close) == 0)
	{
		node = ft_get_f(cur_node.x + 1, cur_node.y, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.x - 1, cur_node.y + 1, star, close) == 0)
	{
		node = ft_get_f(cur_node.x - 1, cur_node.y + 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.x + 1, cur_node.y + 1, star, close) == 0)
	{
		node = ft_get_f(cur_node.x + 1, cur_node.y + 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.x, cur_node.y - 1, star, close) == 0)
	{
		node = ft_get_f(cur_node.x, cur_node.y - 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	if (ft_analyse(cur_node.x, cur_node.y + 1, star, close) == 0)
	{
		node = ft_get_f(cur_node.x, cur_node.y + 1, star.point, cur_node);
		ft_step_child(node, cur_node, open, close, star.point);
	}
	// printf("node renvoyé = x = %d, y = %d, f = %d\n", node.x, node.y, node.f);
}

t_node	ft_find_lower_f(t_list **list)
{
	t_node	ret;
	t_list	*tmp;

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

void	ft_get_path(t_node cur_node, t_list **close, t_mainnode point, char **map)
{
	//  t_list *tmp;
	// int		i;
	t_node	find;

	// i = 0;
	// tmp = *close;
	find = cur_node;
	while (find.x != point.start.x || find.y != point.start.y)
	{
		map[find.y][find.x] = '7';
		find = ft_get_node(close, find.father.x, find.father.y);
		// printf("je suis dedans apreeeees : x = %d, y = %d\n", find.x, find.y);
	}
	ft_print_map(map);
}

void    ft_a_star(t_star star, t_list **open, t_list **close)
{
    t_list  *path;
	t_node	cur_node;
	t_list	*tmpop;
	t_list	*tmpclo;
	// t_node	prev;
	// int		i;

	// i = 0;
	tmpop = *open;
	tmpclo = *close;
	// (void)tmpclo;
	// (void)map;
	if (ft_isvalid(star.point.start.x, star.point.start.y) == 0)
	{
		ft_putendl("Start point invalid !");
		return ;
	}
	if (ft_isvalid(star.point.end.x, star.point.end.y) == 0)
	{
		ft_putendl("Destination point is invalid !");
		return ;
	}
	if (!(path = malloc(sizeof(t_list))))
		return ;
    while (tmpop)
    {
		// ft_putendl("------DEBUT DE BOUCLE-------");
		// ft_putendl("liste open avant del");
		// ft_print_list(tmpop);
		// ft_putendl("avant find lower f");
		cur_node = ft_find_lower_f(&tmpop);
		if (cur_node.x == star.point.end.x && cur_node.y == star.point.end.y)
			break;
		// ft_putendl("avant del node");
		ft_del_node(&tmpop, cur_node.x, cur_node.y);
		// ft_putendl("liste open pres del");
		// ft_putendl("aprees del node");
		ft_add_node(&tmpclo, cur_node);
        ft_check_child(star, &tmpop, &tmpclo, cur_node);
		// printf("curx = %d, cury = %d\n", tmpclo->node.x, tmpclo->node.y);
		// ft_print_list(tmpclo);
		// ft_putendl("------FIN DE BOUCLE-------");
		// map[cur_node.y][cur_node.x] = '7';
		// ft_putendl("apres assign");
		// ft_add_node(&path, cur_node);
		// ft_add_node(&tmpop, cur_node);
		// printf("x = %d, y = %d\n", cur_node.x, cur_node.y);
		// ft_print_map(map);
		// if (i == 3)
		// 	break;
		// i++;
    }
	// ft_print_list(tmpclo);
	// cur_node = ft_get_node(&tmpclo, 5, 6);
	// printf("curx = %d, cury = %d\n", cur_node.father.x, cur_node.father.y);
	// printf("father : x = %d, y = %d\n", cur_node.father.x, cur_node.father.y);
	ft_get_path(cur_node, &tmpclo, star.point, star.map.map);
}