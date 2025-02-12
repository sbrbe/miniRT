/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_verifs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-25 00:48:10 by libelmim          #+#    #+#             */
/*   Updated: 2024-12-25 00:48:10 by libelmim         ###   ########marvin@4  */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	is_vector(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		else if (!ft_isdigit(str[i]) && str[i] != '.' && str[i] != '-')
			return (0);
		i++;
	}
	return (count == 2);
}

int	is_in_range(char *str, double min, double max)
{
	double	val;

	val = ft_atof(str);
	return (val >= min && val <= max);
}

int	is_vector_is_in_range(char *str, double min, double max)
{
	int		i;
	double	val;
	char	**vect;

	i = 0;
	if (!is_vector(str))
		return (0);
	vect = ft_split(str, ',');
	while (vect[i])
	{
		val = ft_atof(vect[i]);
		if (val < min || val > max)
			return (0);
		i++;
	}
	freesplits(vect);
	return (1);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}
