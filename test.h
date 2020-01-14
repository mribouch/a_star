#ifndef TEST_H
# define TEST_H
# include <stdlib.h>

typedef struct			s_list
{
    int					x;
    int					y;
    struct s_list		*next;
}						t_list;

typedef struct			s_node
{
    int					x;
	int					y;
}						t_node;

#endif