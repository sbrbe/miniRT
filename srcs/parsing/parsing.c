/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:29:14 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/27 13:29:27 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirts.h"

int	parsing_rt(char *str, t_data_rt *data_rt)
{
	char	**argv;

	if (ft_check_rt(str))
		return (0);
	argv = main_get_next_line(str);
	if (!argv)
		return (0);
	if (check_rt_a_c_l(argv, data_rt))
	{
		data_rt->camera.pass = false;
		return (0);
	}
	if (verif_caract_rt(argv, data_rt))
		return (my_free_tab(argv), 0);
	my_free_tab(argv);
	return (1);
}

int	check_false_valeur(char *str, t_data_rt *data_rt)
{
	int	i;

	i = 0;
	while (str[i] >= 7 && str[i] <= 32)
		i++;
	if ((str[i] == 'A' || str[i] == 'C' || str[i] == 'L')
		&& (str[i + 1] >= 7 && str[i + 1] <= 32))
	{
		if (str[i] == 'A' && data_rt->ambient.pass == false)
			data_rt->ambient.pass = true;
		else if (str[i] == 'A')
			return (printf("Error: Two \033[31mA\033[0m in file .rt\n"));
		if (str[i] == 'C' && data_rt->camera.pass == false)
			data_rt->camera.pass = true;
		else if (str[i] == 'C')
			return (printf("Error: Two \033[31mC\033[0m in file .rt\n"));
		if (str[i] == 'L' && data_rt->light.pass == false)
			data_rt->light.pass = true;
	}
	return (0);
}

int	check_rt_a_c_l(char **argv, t_data_rt *data_rt)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (check_false_valeur(argv[i], data_rt))
		{
			my_free_tab(argv);
			return (1);
		}
		i++;
	}
	if (data_rt->ambient.pass == false)
		return (my_free_tab(argv)
			, printf("Error :No \033[31mA\033[0m in .rt\n"));
	if (data_rt->camera.pass == false)
		return (my_free_tab(argv)
			, printf("Error :No \033[31mC\033[0m in .rt\n"));
	if (data_rt->light.pass == false)
		return (my_free_tab(argv)
			, printf("Error :No \033[31mL\033[0m in .rt\n"));
	return (0);
}

int	count_line_rt(char *str)
{
	int		fd;
	char	*buffer;
	int		i;

	i = 0;
	fd = open(str, O_RDONLY);
	buffer = get_next_lines(fd);
	while (buffer)
	{
		free(buffer);
		buffer = get_next_lines(fd);
		i++;
	}
	close(fd);
	return (i);
}

char	**main_get_next_line(char *str)
{
	int		fd;
	int		i;
	char	**argv;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror(str);
		return (NULL);
	}
	argv = ft_calloc(sizeof(char *), count_line_rt(str) + 1);
	argv[0] = get_next_lines(fd);
	i = 0;
	while (argv[i])
		argv[++i] = get_next_lines(fd);
	close(fd);
	return (argv);
}
