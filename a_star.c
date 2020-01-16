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

int		ft_analyse(int x, int y, char **map, t_list **close)
{
	(void)map;
	// ft_putendl("here ?");
	if (map[y][x] == 'x' || ft_find_node(close, x, y) == 1)
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

int		ft_get_f(int x, int y, t_point point, t_node cur_node)
{
	int	g;
	int	h;
	int	f;

	if (x != cur_node.x && y != cur_node.y)
		g = 14;
	else
		g = 10;
	h = (ft_abs(point.end.x - x) + ft_abs(point.end.y - y)) * 10;
	f = g + h;
	// printf("x = %d, y = %d, f = %d\n", x, y, f);
	return (f);
}

t_node	ft_check_bro(char **map, t_list **close, t_point point, t_node cur_node)
{
	int		f;
	int		tmpf;
	t_node	node;
	if (ft_analyse(cur_node.x - 1, cur_node.y - 1, map, close) == 0)
	{
		f = ft_get_f(cur_node.x - 1, cur_node.y - 1, point, cur_node);
		node = ft_fill_node(cur_node.x - 1, cur_node.y - 1, f);
	}
	else
		f = 2147483647;
	if (ft_analyse(cur_node.x + 1, cur_node.y - 1, map, close) == 0)
		if ((tmpf = ft_get_f(cur_node.x + 1, cur_node.y - 1, point, cur_node)) < f)
			node = ft_fill_node(cur_node.x + 1, cur_node.y - 1, tmpf);
	if (ft_analyse(cur_node.x - 1, cur_node.y, map, close) == 0)
		if ((tmpf = ft_get_f(cur_node.x - 1, cur_node.y, point, cur_node)) < node.f)
			node = ft_fill_node(cur_node.x - 1, cur_node.y, tmpf);
	if (ft_analyse(cur_node.x + 1, cur_node.y, map, close) == 0)
		if ((tmpf = ft_get_f(cur_node.x + 1, cur_node.y, point, cur_node)) < node.f)
			node = ft_fill_node(cur_node.x + 1, cur_node.y, tmpf);
	if (ft_analyse(cur_node.x - 1, cur_node.y + 1, map, close) == 0)
		if ((tmpf = ft_get_f(cur_node.x - 1, cur_node.y + 1, point, cur_node)) < node.f)
			node = ft_fill_node(cur_node.x - 1, cur_node.y + 1, tmpf);
	if (ft_analyse(cur_node.x + 1, cur_node.y + 1, map, close) == 0)
		if ((tmpf = ft_get_f(cur_node.x + 1, cur_node.y + 1, point, cur_node)) < node.f)
			node = ft_fill_node(cur_node.x + 1, cur_node.y + 1, tmpf);
	if (ft_analyse(cur_node.x, cur_node.y - 1, map, close) == 0)
		if ((tmpf = ft_get_f(cur_node.x, cur_node.y - 1, point, cur_node)) < node.f)
			node = ft_fill_node(cur_node.x, cur_node.y - 1, tmpf);
	if (ft_analyse(cur_node.x, cur_node.y + 1, map, close) == 0)
		if ((tmpf = ft_get_f(cur_node.x, cur_node.y + 1, point, cur_node)) < node.f)
			node = ft_fill_node(cur_node.x, cur_node.y + 1, tmpf);
	// printf("node renvoyé = x = %d, y = %d, f = %d\n", node.x, node.y, node.f);
	return (node);
}

void    ft_a_star(char **map, t_list **open, t_list **close, t_point point)
{
    t_list  *path;
	t_node	cur_node;
	t_list	*tmpop;
	t_list	*tmpclo;
	t_node	prev;
	// int		i;

	// i = 0;
	tmpop = *open;
	tmpclo = *close;
	// (void)tmpclo;
	if (ft_isvalid(point.start.x, point.start.y) == 0)
	{
		ft_putendl("Start point invalid !");
		return ;
	}
	if (ft_isvalid(point.end.x, point.end.y) == 0)
	{
		ft_putendl("Destination point is invalid !");
		return ;
	}
	if (!(path = malloc(sizeof(t_list))))
		return ;
    while (tmpop)
    {
		cur_node.x = tmpop->node.x;
		cur_node.y = tmpop->node.y;
		cur_node.f = tmpop->node.f;

		prev = cur_node;
		// ft_putendl("ahahah");
		// ft_putendl("apreesss");
        cur_node = ft_check_bro(map, &tmpclo, point, cur_node);
		ft_add_node(&tmpclo, prev);
		ft_del_node(&tmpop, prev.x, prev.y);
		// ft_putendl("apreesss brooo");
		printf("curx = %d, cury = %d\n", cur_node.x, cur_node.y);
		map[cur_node.y][cur_node.x] = '7';
		// ft_putendl("apres assign");
		ft_add_node(&path, cur_node);
		ft_add_node(&tmpop, cur_node);
		// printf("x = %d, y = %d\n", cur_node.x, cur_node.y);
		ft_print_map(map);
		if (cur_node.x == point.end.x && cur_node.y == point.end.y)
			break;
		// if (i == 3)
		// 	break;
		// i++;
    }
	ft_print_list(path);
}