#include "../../include/minirt.h"
#include "../../include/vec.h"

t_ray   shoot_ray(int x, int y, t_data *data) {
    float aspect = (float) WIN_WIDTH / WIN_HEIGHT;
    float fov_radians = (data->scene->cam.fov * M_PI) / 180.0;
    float scale = tanf(fov_radians / 2);

    float nor_x = (2 * (x + 0.5) / (float) WIN_WIDTH - 1) * aspect * scale;
    float nor_y = (1 - 2 * (y + 0.5) / (float) WIN_HEIGHT) * scale;

    t_vec *canvas_point = new_vec(nor_x, nor_y, -1);
    t_vec *direction = normalize(vec_sub(canvas_point, &data->scene->cam.cords));

    return ((t_ray){data->scene->cam.cords, *direction});
}

bool    ray_inter_sp(t_ray ray, t_shapes *shp, float *t) {
	//printf("ray_inter_sp ray.origin: %.f %.f %.f\n", ray.origin.x, ray.origin.y, ray.origin.z);
    float t1;
    float t2;
    float shp_radius = shp->diameter / 2;
    t_vec *oc = vec_sub(&ray.origin, &shp->cords);
    float a = 1.0f;
    float b = 2.0f * (ray.dir.x * oc->x + ray.dir.y * oc->y + ray.dir.z * oc->z);
    float c = oc->x * oc->x + oc->y * oc->y + oc->z * oc->z - shp_radius * shp_radius;
    float discriminant = b * b - 4 * a * c;
//	float a = vec_dot(&ray.dir, &ray.dir);
//	float b = 2.0f * vec_dot(oc, &ray.dir);
//	float c = vec_dot(oc, oc) - shp_radius * shp_radius;
//	float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0)
        return false;

	float sqrt_disc = sqrtf(discriminant);
    t1 = (-b - sqrt_disc) / (2.0f * a);
    t2 = (-b + sqrt_disc) / (2.0f * a);
    if (t1 > 0.001f) {
        *t = t1;
        return true;
    } else if (t2 > 0.001f) {
        *t = t2;
        return true;
    }
    return false;
}
