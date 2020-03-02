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
#include "a_star.h"

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

void	ft_print_list(t_star_list *list)
{
	t_star_list	*tmp;

	tmp = list;
	printf("LISTE\n");
	while (tmp->next != NULL)
	{
		printf("x = %d, y = %d, f = %d\n", tmp->node.pos.x, tmp->node.pos.y, tmp->node.f);
		// if (tmp->node.father != NULL)
		printf("x = %d, y = %d, f = %d\n", tmp->node.father.pos.x, tmp->node.father.pos.y, tmp->node.father.f);
		tmp = tmp->next;
	}
}

t_father	ft_initfather(void)
{
	t_father	ret;

	ret.pos.x = 0;
	ret.pos.y = 0;
	ret.f = 0;
	ret.g = 0;
	return (ret);
}

t_node	*init(t_map map, t_mob monstre, t_mob player)
{
	t_star			*star;
	t_node			*node;

	if (!(star = malloc(sizeof(t_star))))
		return (NULL);
	if (!(star->closel = malloc(sizeof(t_star_list))))
		return (NULL);
	if (!(star->openl = malloc(sizeof(t_star_list))))
		return (NULL);
	star->start.pos.x = (int)monstre.pos.x;
	star->start.pos.y = (int)monstre.pos.y;
	star->end.pos.x = (int)player.pos.x;
	star->end.pos.y = (int)player.pos.y;
	star->start.g = 0;
	star->start.father = ft_initfather();
	star->openl->next = NULL;
	star->closel->next = NULL;
	star->map = map;
	star->wall = 1;
	ft_add_node(&star->openl, star->start);
	ft_putendl("------------------");
	node = ft_a_star(star);
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
	t_node			*node;

	i = 0;
	if (ac != 2)
	{
		ft_putendl("no map");
		return (0);
	}
	monstre.pos.x = 0;
	monstre.pos.y = 6;
	player.pos.x = 10;
	player.pos.y = 2;
	map.width = 0;
	fd = open(av[1], O_RDONLY);
	map = ft_map(fd, map);
	while (i < 20)
	{
		ft_putendl("main boucle");
		node = init(map, monstre, player);
		monstre.pos.x = node->pos.x;
		monstre.pos.y = node->pos.y;
		i++;
	}
	return (0);
}