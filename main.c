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

int	main(void)
{
	char			**map;
	t_list			*close;
	t_list			*open;
	t_point			point;
	// char			*map1[] = {"00000000",
	// 							"00000000", 
	// 							"0000x000",
	// 							"010xx020",
	// 							"0000x000",
	// 							"00000000",
	// 							"00000000",
	// 						};

	point.start.x = 1;
	point.start.y = 5;
	point.end.x = 6;
	point.end.y = 5;
	point.start.g = 0;
	point.start.father = ft_initfather();
	if (!(close = malloc(sizeof(t_list))))
		return (0);
	if (!(open = malloc(sizeof(t_list))))
		return (0);
	map = ft_get_map();
	map[point.start.y][point.start.x] = '1';
	map[point.end.y][point.end.x] = '2';
	map[3][0] = 'x';
	map[3][1] = 'x';
	map[3][2] = 'x';
	map[3][3] = 'x';
	map[5][3] = 'x';
	map[5][4] = 'x';
	map[4][4] = 'x';
	map[6][4] = 'x';
	map[3][4] = 'x';
	map[2][4] = 'x';
	open->next = NULL;
	close->next = NULL;
	ft_add_node(&open, point.start);
	// ft_print_list(open);
	ft_print_map(map);
	ft_putendl("------------------");
	ft_a_star(map, &open, &close, point);
	ft_delist(&open);
	return (0);
}