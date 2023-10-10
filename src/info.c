/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:37:49 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/10 15:44:02 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_initialize_map(t_point_coordinates ***map_coordinates,
						t_map_info map_info)
{
	int	i;

	*map_coordinates = (t_point_coordinates **)malloc(map_info.rows
			* sizeof(t_point_coordinates *));
	if (!*map_coordinates)
		return (write(1, "System error\n", 13));
	i = -1;
	while (++i < map_info.rows)
	{
		(*map_coordinates)[i] = (t_point_coordinates *)malloc(map_info.columns
				* sizeof(t_point_coordinates));
		if (!(*map_coordinates)[i])
			return (write(1, "System error\n", 13));
	}
	return (0);
}

int	ft_free_map(t_point_coordinates ***map_coordinates, t_map_info map_info)
{
	int	i;

	i = -1;
	while (++i < map_info.rows)
		if ((*map_coordinates)[i])
			free((*map_coordinates)[i]);
	if (*map_coordinates)
		free(*map_coordinates);
	return (1);
}

void	ft_initialize_map_info(t_map_info *map_info, const char *file)
{
	map_info->min_height = INT_MAX;
	map_info->max_height = INT_MIN;
	map_info->columns = 0;
	map_info->rows = 0;
	map_info->file = file;
}

int	ft_get_map_info(t_map_info *map_info)
{
	char	*line;
	int		fd;
	int		ret;

	fd = open(map_info->file, O_RDONLY);
	if (fd == -1)
		return (write(1, "System error\n", 13));
	ret = get_next_line(fd, &line);
	if (ft_isdigit(line[ft_strlen(line) - 2]))
		map_info->columns = (int)ft_word_count(line, ' ');
	else
		map_info->columns = (int)ft_word_count(line, ' ') - 1;
	while (ret > 0)
	{
		map_info->rows += 1;
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
		return (write(1, "System error\n", 13));
	close(fd);
	return (0);
}
