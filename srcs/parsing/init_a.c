/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:12:30 by sbarbe            #+#    #+#             */
/*   Updated: 2024/07/04 15:03:36 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirts.h"

int	init_pl(char *str, t_data_rt *data_rt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 2)
	{
		i = 0;
		while (data_rt->plane[i].pass == true)
			i++;
		data_rt->plane[i].pass = true;
		if (init_pl_i(str, data_rt, i))
			return (1);
		j++;
		if (j == 1)
		{
			data_rt->plane[i].pose.y = data_rt->plane[i].pose.y + 0.000001;
			data_rt->plane[i].pose.x = data_rt->plane[i].pose.x + 0.000001;
			data_rt->plane[i].pose.z = data_rt->plane[i].pose.z + 0.000001;
		}
	}
	return (0);
}

int	init_a(char *str, t_data_rt *data_rt)
{
	int	i;

	i = 0;
	if (count_word(str) > 2)
		return (printf("Error : too many arguments\n"));
	while (str[i] >= 7 && str[i] <= 32)
		i++;
	if (my_atof(str + i) >= 0.0 && my_atof(str + i) <= 1.0
		&& ft_len_atof(str + i) <= 17 && check_0_9(str + i, '.', 1))
		data_rt->ambient.embient = my_atof(str + i);
	else
	{
		printf("Error : \033[31mambient ligthing\033[0m in range [0.0,1.0]\n");
		return (1);
	}
	i += ft_len_atof(str + i);
	i += ft_len_waitspace(str + i);
	if (!str[i])
		return (printf("Error : argument(s) missing in A\n"));
	if (check_0_255_a(str + i, data_rt))
		return (1);
	return (0);
}

int	check_neg1_1(char *str, t_data_rt *data_rt)
{
	int		i;
	int		j;
	char	**argv;

	i = 0;
	j = 0;
	while (str[i] && j != 2)
	{
		if (!check_0_9_point((str + i), ',', 2 - j))
			return (printf("Error: \033[31m3D vct too "
					"long or invalid \033[0min C\n"));
		i += ft_where(str + i, ',') + 2;
		j++;
	}
	argv = ft_split(str, ',');
	i = -1;
	while (argv[++i])
		if (ft_len_atof(str + i) >= 17 || (!argv[i + 1] && i + 1 < 3))
			return (my_free_tab(argv),
				printf("Error: \033[31m3D vect too"
					" long or invld\033[0m in C\n"));
	data_rt->camera.orientation.x = my_atof(argv[0]);
	data_rt->camera.orientation.y = my_atof(argv[1]);
	data_rt->camera.orientation.z = my_atof(argv[2]);
	return (my_free_tab(argv), 0);
}

int	init_a_c_l(char *str, t_data_rt *data_rt)
{
	int	i;

	i = 0;
	while (str[i] >= 7 && str[i] <= 32)
		i++;
	if (ft_strncmp("A", (str + i), 1) == 0)
		if (init_a((str + i + 1), data_rt))
			return (1);
	if (ft_strncmp("C", (str + i), 1) == 0)
		if (init_c((str + i + 1), data_rt))
			return (1);
	if (ft_strncmp("L", (str + i), 1) == 0)
		if (init_l((str + i + 1), data_rt))
			return (1);
	if (ft_strncmp("sp", (str + i), 2) == 0)
		if (init_sp((str + i + 2), data_rt))
			return (1);
	if (ft_strncmp("pl", (str + i), 2) == 0)
		if (init_pl((str + i + 2), data_rt))
			return (1);
	if (ft_strncmp("cy", (str + i), 2) == 0)
		if (init_cy((str + i + 2), data_rt))
			return (1);
	return (0);
}

int	check_0_255_a(char *str, t_data_rt *data_rt)
{
	int		i;
	int		j;
	char	**av;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			j++;
		if ((str[i] == ',' && str[i + 1] == ',') || j > 2)
			return (1);
		if (!check_0_9((str + i), ',', 2))
			return (printf("Error: \033[31marg R,G,B\033[0m\n"));
	}
	av = ft_split(str, ',');
	i = -1;
	while (av[++i])
		if (ft_atoi(av[i]) > 255 || ft_atoi(av[i]) < 0 || (!av[i + 1] && i < 2))
			return (my_free_tab(av),
				printf("Error : \033[31mR,G,B colors\033[0m [0-255]\n"));
	data_rt->ambient.color.red = ft_atoi(av[0]);
	data_rt->ambient.color.green = ft_atoi(av[1]);
	data_rt->ambient.color.blue = ft_atoi(av[2]);
	return (my_free_tab(av), 0);
}
