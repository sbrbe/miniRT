/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cy_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:18:17 by sbarbe            #+#    #+#             */
/*   Updated: 2024/07/10 11:18:18 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirts.h"

int	check_0_255_cy(char *str, t_data_rt *data_rt, int z)
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
			return (printf("Error : \033[31mR,G,B\033[0m in cy.%d\n", z + 1));
	}
	av = ft_split(str, ',');
	i = -1;
	while (av[++i])
		if (ft_atoi(av[i]) > 255 || ft_atoi(av[i]) < 0 || (!av[i + 1] && i < 2))
			return (my_free_tab(av),
				printf("Error: \033[31mR,G,B\033[0m in cy.%d\n", z + 1));
	data_rt->cylinder[z].color.red = ft_atoi(av[0]);
	data_rt->cylinder[z].color.green = ft_atoi(av[1]);
	data_rt->cylinder[z].color.blue = ft_atoi(av[2]);
	return (my_free_tab(av), 0);
}

int	check_neg1_1_cy(char *str, t_data_rt *data_rt, int z)
{
	int		i;
	int		j;
	char	**argv;

	i = 0;
	j = 0;
	while (str[i] && j != 2)
	{
		if (!check_0_9_point((str + i), ',', 2 - j))
			return (printf("Error: \033[31m3D vct too long \033[0min cy.%d\n",
					z + 1));
		i += ft_where(str + i, ',') + 2;
		j++;
	}
	argv = ft_split(str, ',');
	i = -1;
	while (argv[++i])
		if (ft_len_atof(str + i) >= 17 || (!argv[i + 1] && i + 1 < 5))
			return (my_free_tab(argv),
				printf("Error: \033[31m3D vect too long\033[0m in cy.%d\n",
					z + 1));
	data_rt->cylinder[z].axis.x = my_atof(argv[0]);
	data_rt->cylinder[z].axis.y = my_atof(argv[1]);
	data_rt->cylinder[z].axis.z = my_atof(argv[2]);
	return (my_free_tab(argv), 0);
}

int	check_0_9_suite(char *str, int i, int z)
{
	if (z == 2
		|| (str[i] == '-' && (str[i + 1] < '0' || str[i + 1] > '9'))
		|| (str[i] == '+' && (str[i + 1] < '0' || str[i + 1] > '9'))
		|| ((str[i] == 43 || str[i] == 45) && i >= 1 && ((str[i - 1] < 7
					|| str[i - 1] > 32) && str[i - 1] != ',')))
		return (0);
	return (1);
}

int	ft_check_rt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[--i] != 't')
		return (printf("Error : File isn't .rt type\n"));
	if (str[--i] != 'r')
		return (printf("Error : File isn't .rt type\n"));
	if (str[--i] != '.')
		return (printf("Error : File isn't .rt type\n"));
	return (0);
}
