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
    float t1;
    float t2;
    float shp_radius = shp->diameter / 2;
    t_vec *oc = vec_sub(&ray.origin, &shp->cords);
    float a = 1;
    float b = 2 * (ray.dir.x * oc->x + ray.dir.y * oc->y + ray.dir.z * oc->z);
    float c = oc->x * oc->x + oc->y * oc->y + oc->z * oc->z - shp_radius * shp_radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    if (t1 > 0.001f) {
        *t = t1;
        return true;
    } else if (t2 > 0.001f) {
        *t = t2;
        return true;
    }
    return false;
}
