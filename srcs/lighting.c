/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:52:50 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:11:33 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vecto	light_candles(t_data *rt, t_inter *hit)
{
	int		i;
	t_vecto	coloramb;
	t_vecto	finalcol;
	t_vecto	difflight;
	t_light	light;

	i = 0;
	finalcol.x = 0;
	finalcol.y = 0;
	finalcol.z = 0;
	if (!hit->hit)
		return (finalcol);
	coloramb = coloramb_(&rt->data->amb, &hit->color);
	while (i < rt->data->light_nb)
	{
		light = rt->data->lights[i];
		if (!is_shadowed(rt, hit, &light))
		{
			difflight = light_calculations(hit, &light, rt->data->cam.coord);
			finalcol = add_color(finalcol, difflight);
		}
		i++;
	}
	finalcol = add_color(finalcol, coloramb);
	return (finalcol);
}

t_vecto	light_calculations(t_inter *hit, t_light *light, t_vecto origin)
{
	t_ldata	data;
	t_vecto	color;

	data = ldata_fill(hit, light, origin);
	data.light_dir = vect_substract(light->coord, hit->coord);
	data.light_dir = normalize_vector(data.light_dir);
	if (hit->type == PLANE)
		color = mat_plane(data, hit, light);
	else
		color = phong_figures(data, hit, light, origin);
	color.x = fmin(255, color.x * 255);
	color.y = fmin(255, color.y * 255);
	color.z = fmin(255, color.z * 255);
	return (color);
}

t_vecto	mat_plane(t_ldata data, t_inter *hit, t_light *light)
{
	t_vecto	color;
	double	amb_factor;

	data.diff = fmax(0.5, vect_prodscal(hit->norm, data.light_dir));
	amb_factor = 0.3;
	color.x = data.hit_normed_col.x * data.light_normed_rgb.x
		* light->brightness * (data.diff + amb_factor);
	color.y = data.hit_normed_col.y * data.light_normed_rgb.y
		* light->brightness * (data.diff + amb_factor);
	color.z = data.hit_normed_col.z * data.light_normed_rgb.z
		* light->brightness * (data.diff + amb_factor);
	return (color);
}

t_vecto	phong_figures(t_ldata data, t_inter *hit,
	t_light *light, t_vecto origin)
{
	t_vecto	color;
	double	amb_factor;
	double	spec_intensity;

	data.diff = fmax(0.2, vect_prodscal(hit->norm, data.light_dir));
	amb_factor = 0.1;
	data.view_dir = normalize_vector(vect_substract(origin, hit->coord));
	data.reflect_dir = vect_substract(vect_scale(hit->norm, 2
				* vect_prodscal(data.light_dir, hit->norm)), data.light_dir);
	spec_intensity = pow(fmax(0, vect_prodscal(data.view_dir,
					data.reflect_dir)), 32);
	color.x = (data.hit_normed_col.x * data.light_normed_rgb.x
			* light->brightness * (data.diff + amb_factor))
		+ (data.light_normed_rgb.x * light->brightness * spec_intensity);
	color.y = (data.hit_normed_col.y * data.light_normed_rgb.y
			* light->brightness * (data.diff + amb_factor))
		+ (data.light_normed_rgb.y * light->brightness * spec_intensity);
	color.z = (data.hit_normed_col.z * data.light_normed_rgb.z
			* light->brightness * (data.diff + amb_factor))
		+ (data.light_normed_rgb.z * light->brightness * spec_intensity);
	return (color);
}

bool	is_shadowed(t_data *rt, t_inter *hit, t_light *light)
{
	t_ray	shadow;
	t_vecto	light_dir;
	double	max_dist;

	light_dir = vect_substract(light->coord, hit->coord);
	max_dist = vect_length(light_dir);
	light_dir = normalize_vector(light_dir);
	shadow.origin = vect_add(hit->coord, vect_scale(light_dir, 1e-3));
	shadow.direction = normalize_vector(vect_substract(light->coord,
				hit->coord));
	return (shadow_realm(rt, &shadow, max_dist));
}
