/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 23:16:48 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:11:56 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_orientation(t_data *rt, double angle_h, double angle_v)
{
	if (angle_h != 0)
		rotate_horizontal(rt, angle_h);
	if (angle_v != 0)
		rotate_vertical(rt, angle_v);
	raytrace_loop(rt);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img, 0, 0);
}

void	rotate_horizontal(t_data *rt, double angle)
{
	t_vecto	new_orient;

	new_orient.x = rt->data->cam.orientation.x * cos(angle)
		- rt->data->cam.orientation.z * sin(angle);
	new_orient.y = rt->data->cam.orientation.y;
	new_orient.z = rt->data->cam.orientation.x * sin(angle)
		+ rt->data->cam.orientation.z * cos(angle);
	rt->data->cam.orientation = normalize_vector(new_orient);
	rt->data->cam.right = normalize_vector(
			vect_product(rt->data->cam.orientation,
				(t_vecto){0, 1, 0}));
	rt->data->cam.up = normalize_vector(vect_product(rt->data->cam.right,
				rt->data->cam.orientation));
}

void	rotate_vertical(t_data *rt, double angle)
{
	t_vecto	new_orient;
	t_vecto	new_up;

	new_orient = rotate_vector(rt->data->cam.orientation,
			rt->data->cam.right, angle);
	new_up = rotate_vector(rt->data->cam.up, rt->data->cam.right, angle);
	rt->data->cam.orientation = normalize_vector(new_orient);
	rt->data->cam.up = normalize_vector(new_up);
}

t_vecto	rotate_vector(t_vecto v, t_vecto axis, double angle)
{
	t_vecto	result;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	result = vect_add(vect_scale(v, cos_angle),
			vect_add(vect_scale(vect_product(axis, v), sin_angle),
				vect_scale(axis, vect_prodscal(axis, v) * (1 - cos_angle))));
	return (normalize_vector(result));
}
