/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:54:09 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:07:11 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	gamma_correct(double color, double gamma)
{
	return (pow(color / 255.0, 1.0 / gamma) * 255.0);
}

int	convert_color(t_vecto *color)
{
	int	mlx_color;

	mlx_color = (255 << 24) | ((int)color->x << 16)
		| ((int)color->y << 8)
		| (int)color->z;
	return (mlx_color);
}

t_vecto	coloramb_(t_amb *amb, t_vecto *objcol)
{
	t_vecto	res;

	res.x = (int)(objcol->x * amb->lighting * (amb->rgb_colors.x / 255.0));
	res.y = (int)(objcol->y * amb->lighting * (amb->rgb_colors.y / 255.0));
	res.z = (int)(objcol->z * amb->lighting * (amb->rgb_colors.z / 255.0));
	res.x = fmin(res.x, 255);
	res.y = fmin(res.y, 255);
	res.z = fmin(res.z, 255);
	return (res);
}

t_ldata	ldata_fill(t_inter *hit, t_light *light, t_vecto origin)
{
	t_ldata	data;

	data.light_dir = vect_substract(light->coord, hit->coord);
	data.light_dir = normalize_vector(data.light_dir);
	data.diff = fmax(0, vect_prodscal(hit->norm, data.light_dir));
	data.view_dir = normalize_vector(vect_substract(origin, hit->coord));
	data.reflect_dir = vect_substract(vect_scale(hit->norm, 2
				* vect_prodscal(data.light_dir, hit->norm)), data.light_dir);
	data.spec = pow(fmax(0, vect_prodscal(data.view_dir,
					data.reflect_dir)), 32);
	data.hit_normed_col.x = hit->color.x / 255.0;
	data.hit_normed_col.y = hit->color.y / 255.0;
	data.hit_normed_col.z = hit->color.z / 255.0;
	data.light_normed_rgb.x = light->rgb_colors.x / 255.0;
	data.light_normed_rgb.y = light->rgb_colors.y / 255.0;
	data.light_normed_rgb.z = light->rgb_colors.z / 255.0;
	return (data);
}

bool	shadow_realm(t_data *rt, t_ray *shadow_ray, double max_dist)
{
	int		i;
	t_inter	hit;

	i = -1;
	while (++i < rt->data->sp_nb)
	{
		hit = interfind_sp(shadow_ray, &rt->data->spheres[i]);
		if ((hit.dist > 1e-4) && (hit.dist < max_dist - 1e-4))
			return (true);
	}
	i = -1;
	while (++i < rt->data->pl_nb)
	{
		hit = interfind_pl(shadow_ray, &rt->data->planes[i]);
		if ((hit.dist > 1e-4) && (hit.dist < max_dist - 1e-4))
			return (true);
	}
	i = -1;
	while (++i < rt->data->cy_nb)
	{
		hit = interfind_cy(shadow_ray, &rt->data->cylinders[i]);
		if ((hit.dist > 1e-4) && (hit.dist < max_dist - 1e-4))
			return (true);
	}
	return (false);
}
