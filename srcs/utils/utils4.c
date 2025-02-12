/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-18 17:19:12 by libelmim          #+#    #+#             */
/*   Updated: 2025-01-18 17:19:12 by libelmim         ###   ########marvin@4  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	update_close_hit(t_inter *close_hit, t_inter hit, double *ray_max)
{
	if (hit.dist < *ray_max && hit.dist)
	{
		*ray_max = hit.dist;
		*close_hit = hit;
	}
}

void	inter_base_set(double basedist, t_cy *cylinder, t_inter *inter, bool n)
{
	if (!n && (basedist > 0) && (basedist < inter->dist))
	{
		inter->hit = true;
		inter->dist = basedist;
		inter->norm = vect_scale(cylinder->norm_vect, -1);
		inter->color = cylinder->rgb_colors;
	}
	if (n && (basedist > 0) && (basedist < inter->dist))
	{
		inter->hit = true;
		inter->dist = basedist;
		inter->norm = cylinder->norm_vect;
		inter->color = cylinder->rgb_colors;
	}
}

void	get_me_out_of_this_project(t_inter *inter, t_cy *cylinder, double sol1)
{
	inter->hit = true;
	inter->dist = sol1;
	interfind_cy_norm_body(cylinder, inter);
	inter->color = cylinder->rgb_colors;
}

double	solution_cy(t_eq *eq)
{
	double	sol1;
	double	sol2;

	sol1 = (-eq->b - sqrt(eq->delta)) / (2 * eq->a);
	sol2 = (-eq->b + sqrt(eq->delta)) / (2 * eq->a);
	return (fmin(sol1, sol2));
}
