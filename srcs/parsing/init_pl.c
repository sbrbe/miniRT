/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:21:03 by sbarbe            #+#    #+#             */
/*   Updated: 2024/07/09 14:21:05 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirts.h"

int	check_0_255_pl(char *str, t_data_rt *data_rt, int z)
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
			return (printf("Error: \033[31mR,G,B\033[0m in pl.%d\n", z + 1));
	}
	av = ft_split(str, ',');
	i = -1;
	while (av[++i])
		if (ft_atoi(av[i]) > 255 || ft_atoi(av[i]) < 0 || (!av[i + 1] && i < 2))
			return (my_free_tab(av),
				printf("Error: \033[31mR,G,B\033[0m in pl.%d\n", z + 1));
	data_rt->plane[z].color.red = ft_atoi(av[0]);
	data_rt->plane[z].color.green = ft_atoi(av[1]);
	data_rt->plane[z].color.blue = ft_atoi(av[2]);
	return (my_free_tab(av), 0);
}

int	check_neg1_1_pl(char *str, t_data_rt *data_rt, int z)
{
	int		i;
	int		j;
	char	**argv;

	i = 0;
	j = 0;
	while (str[i] && j != 2)
	{
		if (!check_0_9_point((str + i), ',', 2 - j))
			return (printf("Error: \033[31m3D vct too long \033[0min pl.%d\n",
					z + 1));
		i += ft_where(str + i, ',') + 2;
		j++;
	}
	argv = ft_split(str, ',');
	i = -1;
	while (argv[++i])
		if (ft_len_atof(str + i) >= 17 || (!argv[i + 1] && i + 1 < 5))
			return (my_free_tab(argv),
				printf("Error: \033[31m3D vect long or invld\033[0m in pl.%d\n",
					z + 1));
	data_rt->plane[z].orientation.x = my_atof(argv[0]);
	data_rt->plane[z].orientation.y = my_atof(argv[1]);
	data_rt->plane[z].orientation.z = my_atof(argv[2]);
	return (my_free_tab(argv), 0);
}

int	pl_pos_y(char *temp, t_data_rt *data_rt, int j)
{
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->plane[j].pose.y = my_atof(temp);
	else
		return (free(temp),
			printf("Error : \033[31mtoo long or inva"
				"lid for y in pl.%d\033[0m\n",
				j + 1));
	free(temp);
	return (0);
}

int	init_pl_suite(char *str, t_data_rt *data_rt, int j)
{
	int		i;
	char	*temp;

	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str, ft_where(str, ',') + 2);
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->plane[j].pose.x = my_atof(temp);
	else
		return (free(temp),
			printf("Error: \033[31mlong or invld x in pl.%d\033[0m\n", j + 1));
	i = ft_where(str, ',') + 2;
	free(temp);
	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str + i, ft_where(str + i, ',') + 2);
	if (pl_pos_y(temp, data_rt, j))
		return (1);
	i += ft_where(str + i, ',') + 2;
	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str + i, ft_len_atof(str + i) + 2);
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->plane[j].pose.z = my_atof(temp);
	else
		return (free(temp),
			printf("Error : \033[31mlong or invld z in pl.%d\033[0m\n", j + 1));
	return (free(temp), 0);
}

int	init_pl_i(char *str, t_data_rt *data_rt, int i)
{
	int	j;

	j = ft_len_waitspace(str);
	if (count_word(str) > 3)
		return (printf("Error : too many arguments in line pl.%d\n", i + 1));
	else if (count_word(str) != 3)
		return (printf("Error : argument(s) missing in line pl.%d\n", i + 1));
	if (!check_0_9_point(str + j, ',', 2))
		return (printf("Error : \033[31mInvalid"
				" charcat for x,y,z in pl\n\033[0m"));
	if (init_pl_suite(str + j, data_rt, i))
		return (1);
	j += ft_len_atof(str + j);
	j += ft_len_waitspace(str + j);
	if (check_neg1_1_pl(str + j, data_rt, i))
		return (1);
	j += ft_len_atof(str + j);
	j += ft_len_waitspace(str + j);
	if (check_0_255_pl(str + j, data_rt, i))
		return (1);
	return (0);
}
