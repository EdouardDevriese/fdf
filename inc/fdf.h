/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:09:12 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/17 16:20:03 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# define WINDOW_HEIGHT 1440
# define WINDOW_WIDTH 2560
# define LANDSCAPE 1
# define GRADIENT 2
# define ORANGE 0x00FF8000
# define PURPLE 0x00800080
# define RANGE 0x00FFFFBF
# define DEEPSEA 0x00004080
# define SEA 0x000080FF
# define SAND 0x00C2B280
# define GRASS 0x004CAF50
# define SNOW 0x00FFFFFF

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

///////////////////////////////////////////////////////////////////////////////
//STRUCTS//////////////////////////////////////////////////////////////////////

typedef struct s_map_info
{
	int			columns;
	int			rows;
	int			min_height;
	int			max_height;
	int			height_range;
	const char	*file;
	int			colorscheme;
}				t_map_info;

typedef struct s_point_coordinates
{
	float		x;
	float		y;
	float		z;
}				t_point_coordinates;

typedef struct s_parsing_utils
{
	int			row;
	int			column;
	char		*line;
	char		**numbers;
	int			height;
	int			ret;
}				t_parsing_utils;

typedef struct s_display_params
{
	float		min_x;
	float		max_x;
	float		min_y;
	float		max_y;
	float		scale_factor;
	float		translate_x;
	float		translate_y;
}				t_display_params;

typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx_data;

typedef struct s_bresenham_params
{
	int			x;
	int			y;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
	int			color_start;
	int			color_end;
}				t_bresenham_params;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

//////////////////////////////////////////////////////////////////////////////
//FUNCTIONS////////////////////////////////////////////////////////////////////

//UTILS//
void			ft_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color);

//INFO//
int				ft_get_map_info(t_map_info *map_info);
void			ft_initialize_map_info(t_map_info *map_info, const char *file);
int				ft_initialize_map(t_point_coordinates ***map_coordinates,
					t_map_info map_info);
int				ft_free_map(t_point_coordinates ***map_coordinates,
					t_map_info map_info);

//COORDINATES//
int				ft_get_map_coordinates(t_point_coordinates ***map_coordinates,
					t_map_info *map_info);

//DISPLAYPARAMS//
void			ft_get_display_params(t_display_params *display_params,
					t_point_coordinates **map_coordinates,
					t_map_info map_info);
void			ft_apply_display_params(t_display_params display_params,
					t_point_coordinates ***map_coordinates,
					t_map_info map_info);

//DISPLAY//
void			ft_draw_map(t_point_coordinates **map_coordinates,
					t_map_info map_info,
					t_mlx_data *mlx);

//COLOR//
int				ft_interpolate_color(int color_start, int color_end, float t);
int				ft_calculate_color(float height, t_map_info info);

#endif
