/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:57:11 by libelmim          #+#    #+#             */
/*   Updated: 2025/01/30 18:45:25 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirts.h"
#include "../../includes/miniRT.h"

void	init_bool(t_data_rt *data_rt)
{
	data_rt->ambient.pass = false;
	data_rt->camera.pass = false;
	data_rt->light.pass = false;
	data_rt->nb_cylinder = 0;
	data_rt->nb_plane = 0;
	data_rt->nb_sphere = 0;
	data_rt->ok = 0;
	data_rt->check = 2;
}

int	main(int argc, char **argv)
{
	t_data		*rt;
	t_data_rt	data_rt;

	if (argc == 2)
	{
		init_bool(&data_rt);
		if (!parsing_rt(argv[1], &data_rt))
		{
			if (data_rt.ok == 1)
				free_first_parsing(&data_rt);
			return (0);
		}
		free_first_parsing(&data_rt);
		rt = ft_calloc(sizeof(t_data), 1);
		init_parse_scene(rt, argv);
		init_winrt(rt);
		raytrace_loop(rt);
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img, 0, 0);
		mlx_loop(rt->mlx);
	}
	else
		printf("Error : Number of arguments\n");
}

void	free_first_parsing(t_data_rt *data_rt)
{
	free(data_rt->plane);
	free(data_rt->sphere);
	free(data_rt->cylinder);
}
