#include "../../include/minirt.h"

void	print_scene(const t_data *data)
{
	printf("scene>\na_ratio:\t %.1f\n", data->scene->ambi.ratio);
	printf("a_rgb:\t\t [%d,%d,%d]\n", data->scene->ambi.rgb.r, data->scene->ambi.rgb.g, data->scene->ambi.rgb.b);
	printf("c_rient:\t [%.1f,%.1f,%.1f]\n", data->scene->cam.orient.x, data->scene->cam.orient.y, data->scene->cam.orient.z);
	printf("c_xyz:\t\t [%.1f,%.1f,%.1f]\n", data->scene->cam.cords.x, data->scene->cam.cords.y, data->scene->cam.cords.z);
	printf("c_fov:\t\t %d\n", data->scene->cam.fov);
	printf("l_xyz:\t\t [%.1f,%.1f,%.1f]\n", data->scene->lght.cords.x, data->scene->lght.cords.y, data->scene->lght.cords.z);
	printf("l_bright:\t %.1f\n", data->scene->lght.bright);
	printf("l_rgb:\t\t [%d,%d,%d]\n", data->scene->lght.rgb.r, data->scene->lght.rgb.g, data->scene->lght.rgb.b);
}

void	print_shapes(t_list *shapes)
{
	t_list		*temp;
	t_shapes	*shp;

	temp = shapes;
	while (temp != NULL)
	{
		shp = (t_shapes *) temp->content;
		printf("--------\n%s \ncoords:\t%.1f %.1f %.1f; \naxis:\t%.1f %.1f "
			   "%.1f;\nd:\t\t%.2f;\th: %.2f;\nrgb:\t[%d, %d, %d] \n",
			   shp->identifier, shp->cords.x, shp->cords.y, shp->cords.z,
			   shp->axis.x, shp->axis.y, shp->axis.z, shp->diameter, shp->height,
			   shp->rgb.r, shp->rgb.g, shp->rgb.b);
		temp = temp->next;
	}
}
