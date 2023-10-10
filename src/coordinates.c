/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:40:05 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/10 14:55:10 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_fill_data(t_point_coordinates ***map_coordinates,
							t_parsing_utils p,
							t_map_info *map_info)
{
	(*map_coordinates)[p.row][p.column].x = (float)p.column * 12;
	(*map_coordinates)[p.row][p.column].y = (float)p.row * 12;
	(*map_coordinates)[p.row][p.column].z = (float)p.height;
	if (p.height < map_info->min_height)
		map_info->min_height = p.height;
	if (p.height > map_info->max_height)
		map_info->max_height = p.height;
}

static int	ft_download_heightmap(int fd,
									t_point_coordinates ***map_coordinates,
									t_map_info *map_info)
{
	t_parsing_utils	p;

	p.ret = get_next_line(fd, &p.line);
	p.row = 0;
	while (p.ret > 0)
	{
		p.numbers = ft_split(p.line, ' ');
		p.column = -1;
		while (++p.column < map_info->columns)
		{
			p.height = ft_atoi(p.numbers[p.column]);
			ft_fill_data(map_coordinates, p, map_info);
			free(p.numbers[p.column]);
		}
		free(p.line);
		free(p.numbers);
		p.row++;
		p.ret = get_next_line(fd, &p.line);
	}
	if (p.ret == -1)
		return (write(1, "System error\n", 13));
	map_info->height_range = map_info->max_height - map_info->min_height;
	return (0);
}

static t_point_coordinates	ft_project_point(t_point_coordinates original_point)
{
	t_point_coordinates	projected_point;

	projected_point.x = original_point.x - original_point.y;
	projected_point.y = (original_point.x + original_point.y) / 2
		- original_point.z;
	projected_point.z = original_point.z;
	return (projected_point);
}

void	ft_apply_isometric_projection(t_point_coordinates ***map_coordinates,
											t_map_info map_info)
{
	int	row;
	int	column;

	row = -1;
	while (++row < map_info.rows)
	{
		column = -1;
		while (++column < map_info.columns)
			(*map_coordinates)[row][column]
				= ft_project_point((*map_coordinates)[row][column]);
	}
}

int	ft_get_map_coordinates(const char *map_file,
							t_point_coordinates ***map_coordinates,
							t_map_info *map_info)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == 1)
		return (write(1, "System error\n", 13));
	if (ft_download_heightmap(fd, map_coordinates, map_info) != 0)
		return (1);
	ft_apply_isometric_projection(map_coordinates, *map_info);
	close(fd);
	return (0);
}
