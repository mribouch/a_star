/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 02:22:58 by marvin            #+#    #+#             */
/*   Updated: 2020/01/12 02:22:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include "test.h"

void	ft_print_map(char **map)
{
	int	i;
	// int	j;

	i = 0;
	// j = 0;
	while (i < 10)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

char	**ft_get_map(void)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(map = malloc(sizeof(char*) * 10)))
		return (NULL);
	while (i < 10)
	{
		if (!(map[i] = malloc(sizeof(char) * 10)))
			return (NULL);
		while (j < 10)
		{
			map[i][j] = '0';
			j++;
		}
		j = 0;
		i++;
	}
	return (map);
}

void	ft_print_list(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	printf("LISTE\n");
	while (tmp->next != NULL)
	{
		printf("x = %d, y = %d, f = %d\n", tmp->node.x, tmp->node.y, tmp->node.f);
		// if (tmp->node.father != NULL)
		printf("x = %d, y = %d, f = %d\n", tmp->node.father.x, tmp->node.father.y, tmp->node.father.f);
		tmp = tmp->next;
	}
}

t_father	ft_initfather(void)
{
	t_father	ret;

	ret.x = 0;
	ret.y = 0;
	ret.f = 0;
	ret.g = 0;
	return (ret);
}

int	main(int ac, char **av)
{
	t_map			map;
	t_star			star;
	int				fd;
	char			**map1;
	t_list			*closel;
	t_list			*openl;
	t_mainnode			point;

	(void)ac;
	point.start.x = 1;
	point.start.y = 5;
	point.end.x = 6;
	point.end.y = 5;
	point.start.g = 0;
	point.start.father = ft_initfather();
	if (!(closel = malloc(sizeof(t_list))))
		return (0);
	if (!(openl = malloc(sizeof(t_list))))
		return (0);
	fd = open(av[1], O_RDONLY);
	ft_map(fd);
	map1 = ft_get_map();
	map1[point.start.y][point.start.x] = '1';
	map1[point.end.y][point.end.x] = '2';
	map1[3][0] = 'x';
	map1[3][1] = 'x';
	map1[3][2] = 'x';
	map1[3][3] = 'x';
	map1[5][3] = 'x';
	map1[5][4] = 'x';
	map1[4][4] = 'x';
	map1[6][4] = 'x';
	map1[3][4] = 'x';
	map1[2][4] = 'x';
	openl->next = NULL;
	closel->next = NULL;
	map.map = map1;
	star.map = map;
	star.wall = 'x';
	star.point = point;
	ft_add_node(&openl, point.start);
	// ft_print_list(openl);
	ft_print_map(map1);
	ft_putendl("------------------");
	ft_a_star(star, &openl, &closel);
	ft_delist(&openl);
	return (0);
}