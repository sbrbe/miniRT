/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 00:27:35 by libelmim          #+#    #+#             */
/*   Updated: 2025/01/30 18:44:43 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	exit_err(int errcode)
{
	if (errcode == -1)
	{
		(void)write(2, "Error: Can't allocate memory for new element\n", 46);
		exit(errcode);
	}
	if (errcode == 0)
	{
		(void)write(2, "Error: Missing/Wrong parameters in .rt file.\n", 46);
		exit(errcode);
	}
	if (errcode == 1)
	{
		(void)write(2, "Error: Wrong file descriptor\n", 30);
		exit(errcode);
	}
	if (errcode == 3)
	{
		(void)write(2, "Error: Wrong height/width values\n", 34);
		exit(errcode);
	}
	if (errcode == 4)
	{
		(void)write(2, "Error: mlx_new_window failed\n", 30);
		exit(errcode);
	}
}

int	parsedumbshit(char *line, char *elem)
{
	int	i;

	i = 0;
	while (line[i] && elem[i] && line[i] == elem[i])
		i++;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && (line[i] != ' ') && (line[i] != '\t')
			&& (line[i] != '.') && (line[i] != ',') && (line[i] != '-'))
		{
			printf("Error : Unwanted char(s) found on %s line\n", elem);
			return (0);
		}
		i++;
	}
	return (1);
}

int	multiple_single_msg(int cam, int amb)
{
	if (cam < 1)
		printf("Error : No camera found (C)\n");
	if (amb < 1)
		printf("Error : No ambient lighting found (A)\n");
	if (cam > 1)
		printf("Error : %d cameras found (C)\n", cam);
	if (amb > 1)
		printf("Error : %d ambient lighting found (A)\n", amb);
	return (0);
}
