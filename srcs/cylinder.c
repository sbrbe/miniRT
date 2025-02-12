/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 00:32:50 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:11:11 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_eq	eq_members_cy(t_ray *ray, t_cy *cylinder)
{
	t_eq	eq;
	t_vecto	d;
	t_vecto	o;

	eq.o_to_center = vect_substract(ray->origin, cylinder->coord);
	d = vect_substract(ray->direction, vect_scale(cylinder->norm_vect,
				vect_prodscal(ray->direction, cylinder->norm_vect)));
	o = vect_substract(eq.o_to_center, vect_scale(cylinder->norm_vect,
				vect_prodscal(eq.o_to_center, cylinder->norm_vect)));
	eq.a = vect_prodscal(d, d);
	eq.b = 2 * vect_prodscal(d, o);
	eq.c = vect_prodscal(o, o) - (cylinder->diameter / 2)
		* (cylinder->diameter / 2);
	eq.delta = eq.b * eq.b - 4 * eq.a * eq.c;
	return (eq);
}

t_inter	interfind_cy(t_ray *ray, t_cy *cylinder)
{
	t_eq	eq;
	t_inter	inter;
	t_vecto	topbase;
	double	basedist;
	double	basedist2;

	init_inter(&inter);
	eq = eq_members_cy(ray, cylinder);
	inter = interfind_cy_body(&eq, cylinder, ray);
	basedist = interfind_cy_base(cylinder, ray, cylinder->coord);
	inter_base_set(basedist, cylinder, &inter, 0);
	topbase = vect_add(cylinder->coord,
			vect_scale(cylinder->norm_vect, cylinder->height));
	basedist2 = interfind_cy_base(cylinder, ray, topbase);
	inter_base_set(basedist2, cylinder, &inter, 1);
	inter.type = CYLINDER;
	return (inter);
}

void	interfind_cy_norm_body(t_cy *cylinder, t_inter *inter)
{
	t_vecto	to_center;
	double	proj_length;
	t_vecto	projection;

	to_center = vect_substract(inter->coord, cylinder->coord);
	proj_length = vect_prodscal(to_center, cylinder->norm_vect);
	projection = vect_scale(cylinder->norm_vect, proj_length);
	inter->norm = vect_substract(to_center, projection);
	inter->norm = normalize_vector(inter->norm);
}

t_inter	interfind_cy_body(t_eq *eq, t_cy *cylinder, t_ray *ray)
{
	double	sol;
	double	projection;
	t_inter	inter;

	projection = 0;
	init_inter(&inter);
	if (eq->delta > 0)
	{
		sol = solution_cy(eq);
		if (sol > 0)
		{
			if (cylinder->height > 0)
			{
				inter.coord = vect_add(ray->origin,
						vect_scale(ray->direction, sol));
				projection = vect_prodscal(vect_substract(inter.coord,
							cylinder->coord), cylinder->norm_vect);
			}
			if (projection < 0 || (projection > cylinder->height))
				return (inter);
			get_me_out_of_this_project(&inter, cylinder, sol);
		}
	}
	return (inter);
}

double	interfind_cy_base(t_cy *cylinder, t_ray *ray, t_vecto center)
{
	t_vecto	inter;
	double	denom;
	double	t;
	double	dist;

	denom = vect_prodscal(ray->direction, cylinder->norm_vect);
	if (fabs(denom) < 0)
		return (-1);
	t = vect_prodscal(vect_substract(center, ray->origin),
			cylinder->norm_vect) / denom;
	if (t < 0)
		return (-1);
	inter = vect_add(ray->origin, vect_scale(ray->direction, t));
	dist = vect_length(vect_substract(inter, center));
	if (dist > (cylinder->diameter / 2.0))
		return (-1);
	return (t);
}
