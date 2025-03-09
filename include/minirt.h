#ifndef MINIRT_LIBRARY
#define MINIRT_LIBRARY
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define WIN_TITLE "MiniRT"

#include <stdio.h>
#include <stdlib.h>
#include "../mlx/mlx.h"

typedef struct g_list {
	char			**content;
	struct g_list	*next;
} garbage;

typedef struct d_list {
	char	*identifier;
	float	cords[3];
	float	diameter;
	int		rgb[3];

} shapes;

typedef struct mian_data {
	int 	argc;
	char 	**argv;
	garbage *garbage;
	shapes 	*scene;
    int		key;
	char 	*filename;
    void	*mlx_ptr;
    void	*win_ptr;

} s_data;

#endif
