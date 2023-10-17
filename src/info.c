/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:37:49 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/16 13:39:49 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_initialize_map(t_point_coordinates ***map,
						t_map_info info)
{
	int	i;

	*map = (t_point_coordinates **)malloc(info.rows
			* sizeof(t_point_coordinates *));
	if (!*map)
		return (write(1, "System error\n", 13));
	i = -1;
	while (++i < info.rows)
	{
		(*map)[i] = (t_point_coordinates *)malloc(info.columns
				* sizeof(t_point_coordinates));
		if (!(*map)[i])
			return (write(1, "System error\n", 13));
	}
	return (0);
}

int	ft_free_map(t_point_coordinates ***map, t_map_info info)
{
	int	i;

	i = -1;
	while (++i < info.rows)
		if ((*map)[i])
			free((*map)[i]);
	if (*map)
		free(*map);
	return (1);
}

void	ft_initialize_map_info(t_map_info *info, const char *file)
{
	info->min_height = INT_MAX;
	info->max_height = INT_MIN;
	info->columns = 0;
	info->rows = 0;
	info->file = file;
	if (ft_strncmp(info->file, "test_maps/Japan.fdf", 18) == 0
		|| ft_strncmp(info->file, "test_maps/France.fdf", 19) == 0)
		info->colorscheme = LANDSCAPE;
	else
		info->colorscheme = GRADIENT;
}

int	ft_get_map_info(t_map_info *info)
{
	char	*line;
	int		fd;
	int		ret;

	fd = open(info->file, O_RDONLY);
	if (fd == -1)
		return (write(1, "System error\n", 13));
	ret = get_next_line(fd, &line);
	if (ft_isdigit(line[ft_strlen(line) - 2]))
		info->columns = (int)ft_word_count(line, ' ');
	else
		info->columns = (int)ft_word_count(line, ' ') - 1;
	while (ret > 0)
	{
		info->rows += 1;
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
		return (write(1, "System error\n", 13));
	close(fd);
	return (0);
}
