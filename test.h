#ifndef TEST_H
# define TEST_H
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"



typedef struct			s_node
{
    int					x;
	int					y;
    int                 g;
    int                 h;
    int                 f;
    struct s_node		*father;
}						t_node;

typedef struct			s_list
{
	t_node				node;
    struct s_list		*next;
}						t_list;

typedef struct          s_point
{
    t_node              start;
    t_node              end;
}                       t_point;

void    ft_a_star(char **map, t_list **open, t_list **close, t_point point);
void	ft_print_map(char **map);
void	ft_add_node(t_list **list, t_node node);
void	ft_del_node(t_list **list, int x, int y);
void	ft_delist(t_list **list);
int		ft_find_node(t_list **list, int x, int y);
void	ft_print_list(t_list *list);

#endif