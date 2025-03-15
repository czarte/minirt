#ifndef MINIRT_LIBRARY
#define MINIRT_LIBRARY
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define WIN_TITLE "MiniRT"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../mlx/mlx.h"
#include <fcntl.h>

typedef struct g_list {
	char			**content;
	struct g_list	*next;
} garbage;

typedef struct d_list {
	char			*identifier;
	float			cords[3];
	float			diameter;
	int				rgb[3];
	struct d_list	*next;
} shapes;

typedef struct mian_data {
	int 	argc;
	char 	**argv;
	garbage *garbage;
	int		scenefd;
	shapes	*scene;
    int		key;
	char 	*filename;
    void	*mlx_ptr;
    void	*win_ptr;

} s_data;

/*window handing functions*/

int init_mlx_window(s_data *data);
int	key_exit(int key, void *params);
int	check_exit_button(int button,int x,int y, void *p);
int	check_mouse_button(int button,int x,int y, void *p);

#endif
