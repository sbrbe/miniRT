/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:54:31 by libelmim          #+#    #+#             */
/*   Updated: 2025/01/30 18:57:52 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_inter	ray_closest_inter(t_data *rt, t_ray *ray, int x, int y)
{
	t_inter	hit;
	t_inter	close_hit;

	close_hit.hit = false;
	close_hit.dist = DBL_MAX;
	rt->ray_max[y][x] = DBL_MAX;
	rt->iter = -1;
	while (++rt->iter < rt->data->sp_nb)
	{
		hit = interfind_sp(ray, &rt->data->spheres[rt->iter]);
		update_close_hit(&close_hit, hit, &rt->ray_max[y][x]);
	}
	rt->iter = -1;
	while (++rt->iter < rt->data->pl_nb)
	{
		hit = interfind_pl(ray, &rt->data->planes[rt->iter]);
		update_close_hit(&close_hit, hit, &rt->ray_max[y][x]);
	}
	rt->iter = -1;
	while (++rt->iter < rt->data->cy_nb)
	{
		hit = interfind_cy(ray, &rt->data->cylinders[rt->iter]);
		update_close_hit(&close_hit, hit, &rt->ray_max[y][x]);
	}
	return (close_hit);
}

t_eq	eq_members_sp(t_ray *ray, t_sp *sphere)
{
	t_eq	eq;

	eq.o_to_center = vect_substract(ray->origin, sphere->coord);
	eq.a = vect_prodscal(ray->direction, ray->direction);
	eq.b = 2.0 * vect_prodscal(eq.o_to_center, ray->direction);
	eq.c = vect_prodscal(eq.o_to_center, eq.o_to_center)
		- ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	eq.delta = eq.b * eq.b - 4 * eq.a * eq.c;
	return (eq);
}

t_inter	interfind_sp(t_ray *ray, t_sp *sphere)
{
	t_eq	eq;
	t_inter	inter;
	double	sqrt_delta;
	double	sol1;
	double	sol2;

	init_inter(&inter);
	eq = eq_members_sp(ray, sphere);
	if (eq.delta < 0)
		return (inter);
	sqrt_delta = sqrt(eq.delta);
	sol1 = (-eq.b - sqrt_delta) / (2 * eq.a);
	sol2 = (-eq.b + sqrt_delta) / (2 * eq.a);
	if (sol1 > 0 && sol1 < inter.dist)
		inter.dist = sol1;
	if (sol2 > 0 && sol2 < inter.dist)
		inter.dist = sol2;
	if (inter.dist == DBL_MAX)
		return (inter);
	inter.hit = true;
	inter.coord = vect_add(ray->origin, vect_scale(ray->direction, inter.dist));
	inter.norm = normalize_vector(vect_substract(inter.coord, sphere->coord));
	inter.color = sphere->rgb_colors;
	inter.type = SPHERE;
	return (inter);
}

t_eq	eq_members_pl(t_ray *ray, t_pl *plane)
{
	t_eq	eq;

	eq.o_to_center = vect_substract(plane->coord, ray->origin);
	eq.a = vect_prodscal(plane->norm_vect, ray->direction);
	return (eq);
}

t_inter	interfind_pl(t_ray *ray, t_pl *plane)
{
	t_eq	eq;
	t_inter	inter;
	double	dist;

	init_inter(&inter);
	eq = eq_members_pl(ray, plane);
	if (fabs(eq.a) < 0)
		return (inter);
	dist = vect_prodscal(eq.o_to_center, plane->norm_vect) / eq.a;
	if (dist < 0)
		return (inter);
	inter.hit = true;
	inter.dist = dist;
	inter.coord = vect_add(ray->origin, vect_scale(ray->direction, dist));
	inter.norm = plane->norm_vect;
	inter.color = plane->rgb_colors;
	inter.type = PLANE;
	return (inter);
}
