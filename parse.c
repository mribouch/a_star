/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mribouch <mribouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:32:57 by mribouch          #+#    #+#             */
/*   Updated: 2020/01/21 14:31:39 by mribouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		ft_size_tab(char *full)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (full[i] != '\0')
	{
		if (full[i] >= 48 && full[i] <= 57)
		{
			size++;
			while (full[i] >= 48 && full[i] <= 57)
				i++;
		}
		i++;
	}
	return (size);
}

int		ft_get_number(char*full, int i)
{
	int		ret;
	char	*nb;
	int		tmpi;
	int		count;

	count = 0;
	tmpi = i;
	while (full[i] >= 48 && full[i] <= 57)
	{
		i++;
		count++;
	}
	if (!(nb = malloc(sizeof(char) * count)))
		return (0);
	count = 0;
	while (full[tmpi] >= 48 && full[tmpi] <= 57)
	{
		nb[count] = full[tmpi];
		count++;
		// i++;
		tmpi++;
	}
	ret = ft_atoi(nb);
	return (ret);
}

int	*ft_tab(char *full)
{
	int	size;
	int	*tab;
	int	i;
	int	nb;
	int	index;

	i = 0;
	index = 0;
	size = ft_size_tab(full);
	if (!(tab = malloc(sizeof(int) * (size + 1))))
		return (NULL);
	while (full[i] != '\0')
	{
		if (full[i] >= 48 && full[i] <= 57)
		{
			nb = ft_get_number(full, i);
			tab[index] = nb;
			index++;
			while (full[i] >= 48 && full[i] <= 57)
				i++;
		}
		i++;
	}
	return (tab);
}

void	ft_print_tab(int *tab)
{
	int	i;

	i = 0;
	while (i < 90)
	{
		ft_putnbr(tab[i]);
		ft_putchar(' ');
		i++;
	}
}

int		ft_get_width(char *line)
{
	int	i;
	int	width;

	width = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] >= 48 && line[i] <= 57)
		{
			width++;
			while (line[i] >= 48 && line[i] <= 57)
				i++;
		}
		i++;
	}
	return (width);
}

t_map	ft_map(int fd, t_map map)
{
	char	*full;
	int		*tab;
	char	*line;
	int		height;

	full = NULL;
	height = 0;
	if (get_next_line(fd, &line) > 0)
	{
		full = ft_strnew(1);
		full = ft_strjoin(full, line);
		height++;
		map.width = ft_get_width(line);
	}
	while (get_next_line(fd, &line) > 0)
	{
		full = ft_strjoin(full, line);
		height++;
		// free(line);
	}
	// ft_putendl(full);
	tab = ft_tab(full);
	map.height = height;
	ft_print_tab(tab);
	ft_putendl("voila");
	map.map = tab;
	return (map);
}
