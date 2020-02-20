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

void	ft_print_map(t_map map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map.height)
	{
		while (j < map.width)
		{
			ft_putnbr(map.map[j + i * map.width]);
			j++;
		}
		j = 0;
		ft_putchar('\n');
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

t_node	init(t_map map, t_mob monstre, t_mob player)
{
	t_star			star;
	t_list			*closel;
	t_list			*openl;
	t_mainnode		point;
	t_node			node;

	point.start.x = (int)monstre.x;
	point.start.y = (int)monstre.y;
	point.end.x = (int)player.x;
	point.end.y = (int)player.y;
	point.start.g = 0;
	point.start.father = ft_initfather();
	node.x = 0;
	if (!(closel = malloc(sizeof(t_list))))
		return (node);
	if (!(openl = malloc(sizeof(t_list))))
		return (node);
	openl->next = NULL;
	closel->next = NULL;
	star.map = map;
	star.wall = 1;
	star.point = point;
	ft_add_node(&openl, point.start);
	ft_putendl("------------------");
	node = ft_a_star(star, &openl, &closel);
	// ft_delist(&openl);
	return (node);
}

int	main(int ac, char **av)
{
	t_map			map;
	int				fd;
	t_mob			monstre;
	t_mob			player;
	int				i;
	t_node			node;

	i = 0;
	if (ac != 2)
	{
		ft_putendl("no map");
		return (0);
	}
	monstre.x = 1;
	monstre.y = 6;
	player.x = 10;
	player.y = 2;
	map.width = 0;
	fd = open(av[1], O_RDONLY);
	map = ft_map(fd, map);
	while (i < 20)
	{
		ft_putendl("main boucle");
		node = init(map, monstre, player);
		monstre.x = node.x;
		monstre.y = node.y;
		i++;
	}
	return (0);
}