/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 00:47:46 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:12:12 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	config_camera(t_data *rt)
{
	double	fov_rad;

	fov_rad = rt->data->cam.fov * (M_PI / 180.0);
	rt->aspectratio = rt->width / rt->height;
	rt->width_view = tan(fov_rad / 2);
	rt->height_view = rt->width_view / rt->aspectratio;
}

t_ray	set_ray(t_data *rt, int x, int y)
{
	t_ray	ray;
	t_vecto	temp;
	t_vecto	pixel_pos;
	double	norm_x;
	double	norm_y;

	norm_x = -(2.0 * ((x + 0.5) / WINDOW_WIDTH) - 1.0) * rt->width_view;
	norm_y = (1.0 - 2.0 * ((y + 0.5) / WINDOW_HEIGHT)) * rt->height_view;
	pixel_pos = vect_add(vect_add(rt->data->cam.coord,
				vect_scale(rt->data->cam.right, norm_x)),
			vect_scale(rt->data->cam.up, norm_y));
	pixel_pos = vect_add(pixel_pos, rt->data->cam.orientation);
	ray.origin = rt->data->cam.coord;
	temp = vect_substract(pixel_pos, ray.origin);
	ray.direction = normalize_vector(temp);
	return (ray);
}

int	raytrace_loop(t_data *rt)
{
	int		x;
	int		y;
	t_ray	ray;

	y = 0;
	config_camera(rt);
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			ray = set_ray(rt, x, y);
			magic(rt, &ray, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

void	magic(t_data *rt, t_ray *ray, int x, int y)
{
	int		mlx_col;
	t_inter	hit;
	t_vecto	color;

	hit = ray_closest_inter(rt, ray, x, y);
	color = light_candles(rt, &hit);
	mlx_col = convert_color(&color);
	pixeldraw(&rt->img, mlx_col, x, y);
}

void	pixeldraw(t_img *img, int mlx_color, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = mlx_color;
}
