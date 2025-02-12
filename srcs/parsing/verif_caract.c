/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_caract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:08:04 by sbarbe            #+#    #+#             */
/*   Updated: 2024/07/04 14:59:39 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirts.h"

int	caract_rt(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] >= 7 && str[i] <= 32)
		i++;
	if ((i == ft_strlens(str)
			|| (ft_strncmp("A", (str + i), 1) == 0
				&& (str[i + 1] >= 7 && str[i + 1] <= 32))
			|| (ft_strncmp("C", (str + i), 1) == 0
				&& (str[i + 1] >= 7 && str[i + 1] <= 32))
			|| (ft_strncmp("L", (str + i), 1) == 0
				&& (str[i + 1] >= 7 && str[i + 1] <= 32))
			|| (ft_strncmp("pl", (str + i), 2) == 0
				&& (str[i + 2] >= 7 && str[i + 2] <= 32))
			|| (ft_strncmp("sp", (str + i), 2) == 0
				&& (str[i + 2] >= 7 && str[i + 2] <= 32))
			|| (ft_strncmp("cy", (str + i), 2) == 0
				&& (str[i + 2] >= 7 && str[i + 2] <= 32))
			|| (ft_strncmp("#", (str + i), 1) == 0)))
		return (0);
	return (1);
}

void	check_pl_sp_cy(char *str, t_data_rt *data_rt)
{
	size_t	i;

	i = 0;
	while (str[i] >= 7 && str[i] <= 32)
		i++;
	if ((ft_strncmp("pl", (str + i), 2) == 0
			&& (str[i + 2] >= 7 && str[i + 2] <= 32)))
		data_rt->nb_plane++;
	else if (ft_strncmp("sp", (str + i), 2) == 0
		&& (str[i + 2] >= 7 && str[i + 2] <= 32))
		data_rt->nb_sphere++;
	else if (ft_strncmp("cy", (str + i), 2) == 0
		&& (str[i + 2] >= 7 && str[i + 2] <= 32))
		data_rt->nb_cylinder++;
}

int	check_0_9(char *str, char c, int j)
{
	int	i;
	int	a;
	int	z;

	i = -1;
	a = 0;
	z = 0;
	while (str[++i] && (str[i] < 7 || str[i] > 32))
	{
		if ((!ft_is_dig(str[i])) && str[i] != c && str[i] != 45 && str[i] != 43)
			return (0);
		if (str[i] == c || str[i] == '-' || str[i] == '+')
		{
			if (str[i] == c)
				a++;
			else
				z++;
			if (a == j + 1 || (str[i] == c && (str[i + 1] < '0'
						|| str[i + 1] > '9')) || !check_0_9_suite(str, i, z))
				return (0);
		}
	}
	return (1);
}

void	ft_malloc_sp_pl_cy(t_data_rt *data_rt)
{
	int	i;

	i = 0;
	data_rt->nb_plane = data_rt->nb_plane * 2;
	data_rt->sphere = ft_calloc(sizeof(t_sps), data_rt->nb_sphere + 2);
	if (!data_rt->sphere)
		return ;
	data_rt->plane = ft_calloc(sizeof(t_pls), data_rt->nb_plane + 1);
	if (!data_rt->plane)
		return ;
	while (i <= data_rt->nb_plane)
	{
		data_rt->plane[i].pass = false;
		i++;
	}
	data_rt->cylinder = ft_calloc(sizeof(t_cys), data_rt->nb_cylinder + 1);
	if (!data_rt->cylinder)
		return ;
}

int	verif_caract_rt(char **argv, t_data_rt *data_rt)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (caract_rt(argv[i]))
			return (printf("Error : Unauthorized : \033[31m%s\033[0m",
					argv[i]));
		check_pl_sp_cy(argv[i], data_rt);
		i++;
	}
	ft_malloc_sp_pl_cy(data_rt);
	data_rt->ok = 1;
	i = -1;
	while (argv[++i])
		if (init_a_c_l(argv[i], data_rt))
			return (1);
	return (0);
}
