/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:41:14 by mpivet-p          #+#    #+#             */
/*   Updated: 2021/05/15 17:41:15 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <fcntl.h>
#include <unistd.h>

static int	check_number(char param)
{
	if (param < '0' || param > '9')
		return (0);
	return (1);
}

int			check_file(char *filename)
{
	char	buf[5];
	int		fd;

	if ((fd = open(filename, O_RDONLY)) >= 0 && read(fd, &buf, 5) == 5
		&& check_number(buf[0]) && check_number(buf[1])
		&& check_number(buf[3]) && check_number(buf[4])
		&& buf[2] == 'x')
		return (SUCCESS);
	return (FAILURE);
}
