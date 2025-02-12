/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 00:48:32 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:07:11 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vecto	vect_add(t_vecto a, t_vecto b)
{
	t_vecto	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vecto	vect_substract(t_vecto a, t_vecto b)
{
	t_vecto	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vecto	vect_product(t_vecto a, t_vecto b)
{
	t_vecto	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

t_vecto	vect_scale(t_vecto v, double scalaire)
{
	t_vecto	res;

	res.x = v.x * scalaire;
	res.y = v.y * scalaire;
	res.z = v.z * scalaire;
	return (res);
}

double	vect_prodscal(t_vecto a, t_vecto b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
