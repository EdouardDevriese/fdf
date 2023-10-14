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

static void	ft_get_min_max_values(t_display_params *dp,
									t_point_coordinates **map,
									t_map_info info)
{
	int	row;
	int	col;

	dp->min_x = (float)INT_MAX;
	dp->max_x = (float)INT_MIN;
	dp->min_y = (float)INT_MAX;
	dp->max_y = (float)INT_MIN;
	row = -1;
	while (++row < info.rows)
	{
		col = -1;
 	while (++col < info.columns)
		{
			if (map[row][col].x < dp->min_x)
				dp->min_x = map[row][col].x;
			if (map[row][col].x > dp->max_x)
				dp->max_x = map[row][col].x;
			if (map[row][col].y < dp->min_y)
				dp->min_y = map[row][col].y;
			if (map[row][col].y > dp->max_y)
				dp->max_y = map[row][col].y;
		}
	}
}

void	ft_apply_display_params(t_display_params dp,
								t_point_coordinates ***map,
								t_map_info info)
{
	int	row;
	int	col;

	row = -1;
	while (++row < info.rows)
	{
		col = -1;
		while (++col < info.columns)
		{
			(*map)[row][col].x = (*map)[row][col].x
				* dp.scale_factor_x + dp.translate_x;
			(*map)[row][col].y = (*map)[row][col].y
				* dp.scale_factor_y + dp.translate_y;
		}
	}
}

void	ft_get_display_params(t_display_params *dp,
							t_point_coordinates **map,
							t_map_info info)
{
	ft_get_min_max_values(dp, map, info);
	dp->scale_factor_x = WINDOW_WIDTH / (dp->max_x
			- dp->min_x);
	dp->scale_factor_y = WINDOW_HEIGHT / (dp->max_y
			- dp->min_y);
	dp->translate_x = -(dp->min_x)
		* dp->scale_factor_x;
	dp->translate_y = -(dp->min_y)
		* dp->scale_factor_y;
}
