/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_range_vals1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:04:54 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:07:11 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	amb_in_range_values(t_amb *amb, char **tab)
{
	int		i;
	char	**amb_tab;

	i = 0;
	while (tab[i] && tab[i][0] != 'A')
		i++;
	amb_tab = ft_split(tab[i], ' ');
	i = 0;
	if (is_in_range(amb_tab[1], 0.0, 1.0)
		&& is_vector_is_in_range(amb_tab[2], 0, 255))
	{
		amb->lighting = ft_atof(amb_tab[1]);
		amb->rgb_colors = fill_vect(amb_tab[2]);
		i = 1;
	}
	freesplits(amb_tab);
	return (i);
}

void	up_vec(t_cam *cam)
{
	t_vecto	wup;

	wup.x = 0.0;
	wup.y = 1.0;
	wup.z = 0.0;
	cam->right = vect_product(cam->orientation, wup);
	cam->up = vect_product(cam->right, cam->orientation);
	cam->right = normalize_vector(cam->right);
	cam->up = normalize_vector(cam->up);
}

int	cam_in_range_values(t_cam *cam, char **tab)
{
	int		i;
	char	**cam_tab;

	i = 0;
	while (tab[i] && tab[i][0] != 'C')
		i++;
	cam_tab = ft_split(tab[i], ' ');
	i = 0;
	if (is_vector(cam_tab[1]) && is_vector_is_in_range(cam_tab[2], -1, 1)
		&& is_in_range(cam_tab[3], 0, 180))
	{
		cam->coord = fill_vect(cam_tab[1]);
		cam->orientation = fill_vect(cam_tab[2]);
		cam->fov = ft_atof(cam_tab[3]);
		up_vec(cam);
		i = 1;
	}
	freesplits(cam_tab);
	return (i);
}

int	light_check_save_all(t_light *lights, char **tab)
{
	int			i;
	int			lightnb;
	char		**light_tab;

	i = 0;
	lightnb = 0;
	while (tab[i])
	{
		if (tab[i][0] == 'L')
		{
			light_tab = ft_split(tab[i], ' ');
			if (is_vector(light_tab[1]) && is_in_range(light_tab[2], 0.0, 1.0)
				&& is_vector_is_in_range(light_tab[3], 0, 255))
			{
				lights[lightnb].coord = fill_vect(light_tab[1]);
				lights[lightnb].brightness = ft_atof(light_tab[2]);
				lights[lightnb].rgb_colors = fill_vect(light_tab[3]);
				lightnb++;
			}
			freesplits(light_tab);
		}
		i++;
	}
	return (lightnb);
}
