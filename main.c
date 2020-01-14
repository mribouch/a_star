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
	while (tmp->next != NULL)
	{
		printf("x = %d\n", tmp->x);
		printf("y = %d\n", tmp->y);
		tmp = tmp->next;
	}
}

void	ft_del_node(t_list **list, int x, int y)
{
	t_list	*tmp;
	t_list	*previous;

	tmp = *list;
	if ((tmp != NULL) && (tmp->x == x && tmp->y == y))
	{
		*list = tmp->next;
		free(tmp);
		return ;
	}
	while ((tmp != NULL) && (tmp->x != x && tmp->y != y))
	{
		previous = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	previous->next = tmp->next;
	free(tmp);
}

void	ft_add_node(t_list **list, int x, int y)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return ;
	new->x = x; 
	new->y = y;
	new->next = *list;
	*list = new;
}

int	main(void)
{
	char			**map;
	t_list			*close;
	t_list			*open;
	t_node			start;
	t_node			end;

	start.x = 1;
	start.y = 1;
	end.x = 6;
	end.y = 8;
	if (!(close = malloc(sizeof(t_list))))
		return (0);
	if (!(open = malloc(sizeof(t_list))))
		return (0);
	map = ft_get_map();
	map[start.y][start.x] = '1';
	map[end.y][end.x] = '2';
	open->next = NULL;
	close->next = NULL;
	ft_add_node(&open, start.x, start.y);
	ft_add_node(&open, 3, 7);
	ft_add_node(&open, 4, 2);
	ft_del_node(&open, 3, 7);
	ft_print_list(open);
	ft_print_map(map);
	return (0);
}