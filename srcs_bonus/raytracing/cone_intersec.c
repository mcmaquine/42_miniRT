/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 20:35:06 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/03 17:53:59 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static	t_hit	full_intersection(t_cone *con, t_ray ray);
static	t_hit	check_cone_intersec(t_cone *con, t_ray ray, t_point vo);
static	t_hit	check_height_intersec(t_cone *con, t_ray r, double t);

t_hit	intersect_cone(t_window *win, t_ray ray)
{
	t_list	*con;
	t_hit	hit;
	t_hit	temp;

	init_t_hit(&hit, -1);
	con = win->scene_obj->objs[CONE];
	if (!con)
		return (hit);
	hit.t = DBL_MAX;
	while (con != NULL)
	{
		temp = full_intersection((t_cone *)con->content, ray);
		if (temp.t >= 0 && temp.t < hit.t)
			hit = temp;
		con = con->next;
	}
	return (hit);
}

static	t_hit	full_intersection(t_cone *con, t_ray ray)
{
	t_hit	hit_base;
	t_hit	hit_cone;
	t_hit	hit_small;

	init_t_hit(&hit_small, DBL_MAX);
	hit_base = circular_plane_intersec(&(con->base), con->radius, ray);
	hit_cone = check_cone_intersec(con, ray, vec_sub(ray.origin, con->vertex));
	if (hit_base.t < hit_small.t && hit_base.t > 0)
		hit_small = hit_base;
	if (hit_cone.t < hit_small.t && hit_cone.t > 0)
		hit_small = hit_cone;
	if (hit_small.t == DBL_MAX)
		hit_small.t = -1;
	return (hit_small);
}

static	t_hit	check_cone_intersec(t_cone *con, t_ray ray, t_point vo)
{
	double	dtv;
	double	votd;
	double	votv;
	double	vo_sq;
	double	k;

	dtv = vec_dot(ray.direction, con->v_axis);
	votd = vec_dot(vo, ray.direction);
	votv = vec_dot(vo, con->v_axis);
	vo_sq = vec_magnitude(vo);
	vo_sq *= vo_sq;
	k = 1.0 + con->tan2;
	return (check_height_intersec(con, ray, roots(1.0 - dtv * dtv * k,
				2 * (votd - votv * dtv * k), vo_sq - votv * votv * k)));
}

static	t_hit	check_height_intersec(t_cone *con, t_ray r, double t)
{
	t_point	point;
	t_hit	hit;
	double	h;

	init_t_hit(&hit, -1);
	if (t < 0)
		return (hit);
	point = vec_add(r.origin, vec_scale(r.direction, t));
	h = vec_dot(vec_sub(point, con->vertex), con->v_axis);
	if (h < 0.0 || h > con->height)
		hit.t = -1;
	else
	{
		hit.t = t;
		hit.obj = (t_scene_obj *)con;
		hit.color = con->color;
	}
	return (hit);
}
