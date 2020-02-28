#ifndef TEST_H
# define TEST_H
# include <stdlib.h>
# include <stdio.h>
# include "libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define INT_MAX 2147483647


typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
}						t_point;

typedef struct			s_map
{
	int					width;
	int					height;
	int					*map;
}						t_map;

typedef struct			s_father
{
	t_point				pos;
	int					g;
	int					f;
}						t_father;

typedef struct			s_node
{
	t_list_head			node;
    t_point				pos;
    int                 g;
    int                 h;
    int                 f;
	t_father			father;
}						t_node;

typedef struct			s_star_list
{
	t_node				node;
    struct s_star_list	*next;
}						t_star_list;

typedef struct          s_mainnode
{
    t_node              start;
    t_node              end;
}                       t_mainnode;

typedef struct			s_mob
{
	t_point				pos;
	int					wall;
}						t_mob;

typedef struct			s_star
{
	int					wall;
	t_map				map;
	t_mainnode			point;
}						t_star;

t_node    	ft_a_star(t_star star, t_star_list **open, t_star_list **close);
void		ft_print_map(t_map map);
void		ft_add_node(t_star_list **list, t_node node);
void		ft_del_node(t_star_list **list, int x, int y);
void		ft_delist(t_star_list **list);
int			ft_find_node(t_star_list **list, int x, int y);
int			ft_count_node(t_star_list **list);
void		ft_print_list(t_star_list *list);
t_node		*ft_get_node(t_star_list **list, int x, int y);
t_node		init(t_map map, t_mob monstre, t_mob player);
void		ft_change_g(t_star_list **list, int g, t_father father, t_node find);
t_map		ft_map(int fd, t_map map);
t_father	ft_convertnode(t_node node);

#endif