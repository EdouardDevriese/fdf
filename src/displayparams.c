/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayparams.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:40:57 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/10 10:23:54 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_get_min_max_values(t_display_params *display_params,
									t_point_coordinates **map_coordinates,
									t_map_info map_info)
{
	int	row;
	int	col;

	display_params->min_x = (float)INT_MAX;
	display_params->max_x = (float)INT_MIN;
	display_params->min_y = (float)INT_MAX;
	display_params->max_y = (float)INT_MIN;
	row = -1;
	while (++row < map_info.rows)
	{
		col = -1;
		while (++col < map_info.columns)
		{
			if (map_coordinates[row][col].x < display_params->min_x)
				display_params->min_x = map_coordinates[row][col].x;
			if (map_coordinates[row][col].x > display_params->max_x)
				display_params->max_x = map_coordinates[row][col].x;
			if (map_coordinates[row][col].y < display_params->min_y)
				display_params->min_y = map_coordinates[row][col].y;
			if (map_coordinates[row][col].y > display_params->max_y)
				display_params->max_y = map_coordinates[row][col].y;
		}
	}
}

void	ft_apply_display_params(t_display_params display_params,
								t_point_coordinates ***map_coordinates,
								t_map_info map_info)
{
	int	row;
	int	col;

	row = -1;
	while (++row < map_info.rows)
	{
		col = -1;
		while (++col < map_info.columns)
		{
			(*map_coordinates)[row][col].x = (*map_coordinates)[row][col].x
				* display_params.scale_factor_x + display_params.translate_x;
			(*map_coordinates)[row][col].y = (*map_coordinates)[row][col].y
				* display_params.scale_factor_y + display_params.translate_y;
		}
	}
}

void	ft_get_display_params(t_display_params *display_params,
							t_point_coordinates **map_coordinates,
							t_map_info map_info)
{
	ft_get_min_max_values(display_params, map_coordinates, map_info);
	display_params->scale_factor_x = WINDOW_WIDTH / (display_params->max_x
			- display_params->min_x);
	display_params->scale_factor_y = WINDOW_HEIGHT / (display_params->max_y
			- display_params->min_y);
	display_params->translate_x = -(display_params->min_x)
		* display_params->scale_factor_x;
	display_params->translate_y = -(display_params->min_y)
		* display_params->scale_factor_y;
}
