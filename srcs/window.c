/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:11:28 by libelmim          #+#    #+#             */
/*   Updated: 2025/01/30 18:51:34 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_exit(t_data *rt)
{
	if (rt->data)
	{
		if (rt->data->lights)
			free(rt->data->lights);
		if (rt->data->spheres)
			free(rt->data->spheres);
		if (rt->data->planes)
			free(rt->data->planes);
		if (rt->data->cylinders)
			free(rt->data->cylinders);
		free(rt->data);
	}
	if (rt->img.img)
		mlx_destroy_image(rt->mlx, rt->img.img);
	if (rt->mlx)
		mlx_destroy_display(rt->mlx);
	if (rt->mlx)
		free(rt->mlx);
	if (rt)
		free(rt);
}

void	exit_end(t_data *rt)
{
	mlx_destroy_window(rt->mlx, rt->win);
	free_exit(rt);
	exit(0);
}

void	init_winrt(t_data *rt)
{
	rt->mlx = mlx_init();
	rt->width = WINDOW_WIDTH;
	rt->height = WINDOW_HEIGHT;
	if (!rt->width || !rt->height)
	{
		free_exit(rt);
		exit_err(3);
	}
	rt->win = mlx_new_window(rt->mlx, rt->width, rt->height, "MiniRT");
	if (!rt->win)
	{
		mlx_destroy_display(rt->mlx);
		free_exit(rt);
		exit_err(4);
	}
	rt->img.img = mlx_new_image(rt->mlx, rt->width, rt->height);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bpp,
			&rt->img.line_length, &rt->img.endian);
	mlx_hook(rt->win, 2, (1L << 0) + (1L << 1), moving, rt);
	mlx_hook(rt->win, 17, 0L, (void *)exit_end, rt);
	mlx_key_hook(rt->win, key_hook, rt);
}

int	key_hook(int keycode, t_data *rt)
{
	if (keycode == 65307)
	{
		exit_end(rt);
		return (0);
	}
	return (1);
}
