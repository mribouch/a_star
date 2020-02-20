#ifndef TEST_H
# define TEST_H
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define INT_MAX 2147483647


typedef struct			s_map
{
	int					width;
	int					height;
	int					*map;
}						t_map;

typedef struct			s_father
{
	int					x;
	int					y;
	int					g;
	int					f;
}						t_father;

typedef struct			s_node
{
    int					x;
	int					y;
    int                 g;
    int                 h;
    int                 f;
	t_father			father;
}						t_node;

typedef struct			s_list
{
	t_node				node;
    struct s_list		*next;
}						t_list;

typedef struct          s_mainnode
{
    t_node              start;
    t_node              end;
}                       t_mainnode;

typedef struct			s_mob
{
	float				x;
	float				y;
	int					wall;
}						t_mob;

typedef struct			s_star
{
	int					wall;
	t_map				map;
	t_mainnode			point;
}						t_star;

t_node    	ft_a_star(t_star star, t_list **open, t_list **close);
void		ft_print_map(t_map map);
void		ft_add_node(t_list **list, t_node node);
void		ft_del_node(t_list **list, int x, int y);
void		ft_delist(t_list **list);
int			ft_find_node(t_list **list, int x, int y);
int			ft_count_node(t_list **list);
void		ft_print_list(t_list *list);
t_node		*ft_get_node(t_list **list, int x, int y);
t_node		init(t_map map, t_mob monstre, t_mob player);
void		ft_change_g(t_list **list, int g, t_father father, t_node find);
t_map		ft_map(int fd, t_map map);
t_father	ft_convertnode(t_node node);

#endif