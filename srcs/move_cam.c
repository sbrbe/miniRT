/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-21 23:16:39 by libelmim          #+#    #+#             */
/*   Updated: 2025-01-21 23:16:39 by libelmim         ###   ########marvin@4  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	moving(int keycode, t_data *rt)
{
	if (keycode == RIGHT_ARROW)
		move_left_right(rt, -1);
	else if (keycode == LEFT_ARROW)
		move_left_right(rt, 1);
	else if (keycode == UP_ARROW)
		move_forward_back(rt, 1);
	else if (keycode == DOWN_ARROW)
		move_forward_back(rt, -1);
	else if (keycode == KEY_A)
		move_orientation(rt, -ROTATION_SPEED, 0);
	else if (keycode == KEY_D)
		move_orientation(rt, ROTATION_SPEED, 0);
	else if (keycode == KEY_W)
		move_orientation(rt, 0, ROTATION_SPEED);
	else if (keycode == KEY_S)
		move_orientation(rt, 0, -ROTATION_SPEED);
	return (0);
}

void	move_left_right(t_data *rt, int direction)
{
	if (direction < 0)
		rt->data->cam.coord = vect_substract(rt->data->cam.coord,
				vect_scale(rt->data->cam.right, MOVE_SPEED));
	else
		rt->data->cam.coord = vect_add(rt->data->cam.coord,
				vect_scale(rt->data->cam.right, MOVE_SPEED));
	raytrace_loop(rt);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img, 0, 0);
}

void	move_forward_back(t_data *rt, int direction)
{
	if (direction > 0)
		rt->data->cam.coord = vect_add(rt->data->cam.coord,
				vect_scale(rt->data->cam.orientation, MOVE_SPEED));
	else
		rt->data->cam.coord = vect_substract(rt->data->cam.coord,
				vect_scale(rt->data->cam.orientation, MOVE_SPEED));
	raytrace_loop(rt);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img, 0, 0);
}
