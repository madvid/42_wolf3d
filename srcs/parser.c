/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:57:35 by mpivet-p          #+#    #+#             */
/*   Updated: 2021/05/15 17:04:57 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <fcntl.h>
#include <stddef.h>

static int	check_line(char *str, t_world *world)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] != ' ' || str[i + 1] < '0' || str[i + 1] > '9')
				return (1);
			else
				count++;
		}
		i++;
	}
	if ((int)count + 1 != world->width)
		return (1);
	return (0);
}

static int	get_world_line(char *str, t_world *world, int line)
{
	int64_t		tmp;
	size_t		i;
	char		**tab;

	i = 0;
	if (check_line(str, world) != 0)
		return (1);
	tab = ft_strsplit(str, ' ');
	while (tab[i])
	{
		if (world->map[i] == NULL)
			world->map[i] = ft_memalloc(sizeof(char) * (world->height));
		tmp = 0;
		if (ft_atol(tab[i], &tmp) != 0 || tmp > 255 || tmp < 0)
		{
			ft_tabdel(&tab);
			return (-1);
		}
		world->map[i][line] = tmp & 0xFF;
		i++;
	}
	ft_tabdel(&tab);
	return (0);
}

static int	get_wolf_map(int fd, t_world *world)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (i < world->height && get_next_line(fd, &line) > 0)
	{
		if (get_world_line(line, world, i) != 0)
		{
			ft_strdel(&line);
			ft_putstr_fd("wolf3d: line ", STDERR_FILENO);
			ft_putnbr_fd(i + 3, STDERR_FILENO);
			ft_putstr_fd(": invalid input\n", STDERR_FILENO);
			return (1);
		}
		ft_strdel(&line);
		i++;
	}
	world->map[world->width] = 0;
	return (0);
}

static int	check_spawn(t_core *wolf)
{
	if (wolf->world.map[wolf->world.spawn_x][wolf->world.spawn_y] != 0)
		return (FAILURE);
	return (SUCCESS);
}

void		parse_wolf_map(t_core *wolf, t_world *world, char *filename)
{
	int	fd;
	int	array[2];

	fd = 0;
	if (check_file(filename) != SUCCESS || (fd = open(filename, O_RDONLY)) < 0)
		print_and_quit("wolf3d: invalid file\n");
	world->ceiling = -1;
	world->floor = -1;
	get_world_dimensions(world, array, fd);
	get_spawn_coords(world, array, fd);
	if (!(world->map = ft_memalloc(sizeof(char*) * (world->width + 1))))
		print_and_quit("wolf3d: malloc error\n");
	if (get_wolf_map(fd, world) != SUCCESS
		|| get_map_properties(wolf, fd) != SUCCESS
		|| check_spawn(wolf) != SUCCESS)
	{
		quit_wolf(wolf);
	}
	center_map(world->width, world->height, 21, world->center);
}
