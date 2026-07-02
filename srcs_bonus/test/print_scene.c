#include "../includes/minirt.h"

void    print_scene(t_scene *scene);

static void print_color(t_color color)
{
    printf("R:%d G:%d B:%d", color.red, color.green, color.blue);
}

static void print_point(t_point p)
{
    printf("x:%.4f y:%.4f z:%.4f", p.x, p.y, p.z);
}

static void print_amb(t_amb_light *amb)
{
    printf("  [AMB] rate:%.4f color:", amb->light_rate);
    print_color(amb->color);
    printf("\n");
}

static void print_cam(t_cam *cam)
{
    printf("  [CAM] point:");
    print_point(cam->point);
    printf(" orient:");
    print_point(cam->orient);
    printf(" fov:%.4f\n", cam->fov);
}

static void print_objs(t_list *objs[])
{
	t_list		*node;
    t_scene_obj *obj;
    t_sphere    *sp;
    t_plane     *pl;
    t_cylinder  *cy;
	int			i = -1;

	while (++i < COUNT)
	{
		node = objs[i];
		while (node)
		{
			obj = (t_scene_obj *)node->content;
			if (obj->type == SPHERE)
			{
				sp = (t_sphere *)obj;
				printf("  [SP] center:");
				print_point(sp->center);
				printf(" diam:%.4f color:", sp->diam);
				print_color(sp->color);
				printf("\n");
			}
			else if (obj->type == PLANE)
			{
				pl = (t_plane *)obj;
				printf("  [PL] point:");
				print_point(pl->a_point);
				printf(" normal:");
				print_point(pl->normal);
				printf(" color:");
				print_color(pl->color);
				printf("\n");
			}
			else if (obj->type == CYLINDER)
			{
				cy = (t_cylinder *)obj;
				printf("  [CY] center:");
				print_point(cy->center);
				printf(" axis:");
				print_point(cy->v_axis);
				printf(" diam:%.4f height:%.4f color:", cy->diam, cy->height);
				print_color(cy->color);
				printf("\n");
			}
			node = node->next;
		}
	}
}

void    print_scene(t_scene *scene)
{
    if (!scene)
    {
        printf("  scene: NULL\n");
        return ;
    }
    print_amb(scene->amb);
    print_cam(scene->cam);
    printf("  [LIGHT] coord:");
    print_point(scene->light->coord);
    printf(" bright:%.4f color:", scene->light->bright_rate);
    print_color(scene->light->color);
    printf("\n");
    print_objs(scene->objs);
}
