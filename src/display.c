/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:38:34 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/16 12:09:59 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_interpolate_color(int color_start, int color_end, float t)
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

static int	ft_calculate_color(float height, t_map_info info)
{
	float	t;

	if (ft_strncmp(map_info.file, "test_maps/Japan.fdf", 18) == 0
		|| ft_strncmp(map_info.file, "test_maps/France.fdf", 19) == 0)
	{
		if (height < -100)
			return (DEEPSEA);
		if (height < 0)
			return (SEA);
		if (height < 5)
			return (SAND);
		if (height < 35)
			return (GRASS);
		else
			return (SNOW);
	}
	else
	{
		if (info.min_height == 0)
			return (PURPLE);
		t = (height - info.min_height) / info.height_range;
		return (ft_interpolate_color(ORANGE, PURPLE, t));
	}
}

static void	ft_initialize_bresenham_params(t_bresenham_params *p,
											t_point_coordinates a,
											t_point_coordinates b,
											t_map_info info)
{
	p->dx = abs((int)b.x - (int)a.x);
	p->dy = abs((int)b.y - (int)a.y);
	if (a.x < b.x)
		p->sx = 1;
	else
		p->sx = -1;
	if (a.y < b.y)
		p->sy = 1;
	else
		p->sy = -1;
	p->err = p->dx - p->dy;
	p->x = (int)a.x;
	p->y = (int)a.y;
	p->color_start = ft_calculate_color(a.z, info);
	p->color_end = ft_calculate_color(b.z, info);
}

static void	ft_draw_line(t_point_coordinates a,
							t_point_coordinates b,
							t_mlx_data *mlx,
							t_map_info info)
{
	t_bresenham_params	p;
	float				t;
	int					color;

	ft_initialize_bresenham_params(&p, a, b, info);
	while (1)
	{
		t = sqrt(pow(p.x - a.x, 2) + pow(p.y - a.y, 2)) / sqrt(pow(b.x - a.x, 2)
				+ pow(b.y - a.y, 2));
		color = ft_interpolate_color(p.color_start, p.color_end, t);
		ft_mlx_pixel_put(mlx, p.x, p.y, color);
		if (p.x == (int)b.x && p.y == (int)b.y)
			break ;
		p.e2 = 2 * p.err;
		if (p.e2 > -p.dy)
		{
			p.err -= p.dy;
			p.x += p.sx;
		}
		if (p.e2 < p.dx)
		{
			p.err += p.dx;
			p.y += p.sy;
		}
	}
}

void	ft_draw_map(t_point_coordinates **map, t_map_info info,
		t_mlx_data *mlx)
{
	int	row;
	int	column;

	row = -1;
	while (++row < info.rows)
	{
		column = -1;
		while (++column < info.columns)
		{
			if (row + 1 < info.rows)
				ft_draw_line(map[row][column],
					map[row + 1][column],
					mlx,
					info);
			if (column + 1 < info.columns)
				ft_draw_line(map[row][column],
					map[row][column + 1],
					mlx,
					info);
		}
	}
}
