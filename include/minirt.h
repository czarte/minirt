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
	char 	*filename;

} s_data;
