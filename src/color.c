/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:32:36 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/16 15:58:32 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_interpolate_color(int color_start, int color_end, float t)
{
	t_color	start;
	t_color	end;
	t_color	current;

	start.r = (color_start >> 16) & 0xFF;
	start.g = (color_start >> 8) & 0xFF;
	start.b = color_start & 0xFF;
	end.r = (color_end >> 16) & 0xFF;
	end.g = (color_end >> 8) & 0xFF;
	end.b = color_end & 0xFF;
	current.r = (int)((1 - t) * start.r + t * end.r);
	current.g = (int)((1 - t) * start.g + t * end.g);
	current.b = (int)((1 - t) * start.b + t * end.b);
	return ((current.r << 16) | (current.g << 8) | current.b);
}

static int	ft_landscape(float height)
{
	if (height > 100)
		return (0xE0DED8);
	if (height > 70)
		return (0xAC9A7C);
	if (height > 50)
		return (0XB9985A);
	if (height > 30)
		return (0xDED6A3);
	if (height > 10)
		return (0xD1D7AB);
	if (height > 0)
		return (0xACD0A5);
	if (height > -5)
		return (0xD8F2FE);
	if (height > -15)
		return (0xACDBFB);
	if (height > -30)
		return (0x8DC1EA);
	return (0x71ABD8);
}

static int	ft_gradient(float height, t_map_info info)
{
	float	t;

	if (info.height_range == 0)
		return (PURPLE);
	t = (height - info.min_height) / info.height_range;
	return (ft_interpolate_color(ORANGE, PURPLE, t));
}

int	ft_calculate_color(float height, t_map_info info)
{
	if (info.colorscheme == LANDSCAPE)
		return (ft_landscape(height));
	else
		return (ft_gradient(height, info));
}
