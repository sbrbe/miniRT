/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:48:26 by sbarbe            #+#    #+#             */
/*   Updated: 2024/07/01 11:48:28 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirts.h"

double	my_atof(const char *str)
{
	double	result;
	double	fraction;
	double	divisor;
	int		sign;

	sign = 1;
	result = 0.0;
	fraction = 0.0;
	divisor = 1.0;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			fraction = fraction * 10.0 + (*str++ - '0');
			divisor *= 10.0;
		}
	}
	return ((result + fraction / divisor) * sign);
}

int	ft_len_atof(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] < 7 || str[i] > 32))
		i++;
	return (i);
}

int	ft_len_waitspace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] >= 7 && str[i] <= 32)
		i++;
	return (i);
}

int	count_word(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i])
	{
		i += ft_len_waitspace(str + i);
		if ((str[i] < 7 || str[i] > 32) && str[i] != 0)
			a++;
		while (str[i] && (str[i] < 7 || str[i] > 32))
			i++;
	}
	return (a);
}

int	ft_is_dig(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
