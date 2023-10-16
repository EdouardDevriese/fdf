/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:26:10 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/16 13:22:30 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close_window(t_mlx_data *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit(0);
}

int	ft_escape(int keycode, t_mlx_data *mlx)
{
	if (keycode == 65307)
		ft_close_window(mlx);
	return (0);
}

static void	ft_display_map(t_point_coordinates **map,
							t_map_info info)
{
	t_mlx_data	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Fil de fer");
	mlx.img = mlx_new_image(mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,
			&mlx.endian);
	ft_draw_map(map, info, &mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img, 0, 0);
	mlx_hook(mlx.win_ptr, 17, 0L, ft_close_window, &mlx);
	mlx_key_hook(mlx.win_ptr, ft_escape, &mlx);
	ft_free_map(&map, info);
	mlx_loop(mlx.mlx_ptr);
}

static int	ft_create_map(const char *file)
{
	t_map_info			info;
	t_point_coordinates	**map;
	t_display_params	display_params;

	ft_initialize_map_info(&info, file);
	if (ft_get_map_info(&info) != 0)
		return (1);
	if (ft_initialize_map(&map, info) != 0)
		return (ft_free_map(&map, info));
	if (ft_get_map_coordinates(&map, &info) != 0)
		return (ft_free_map(&map, info));
	ft_get_display_params(&display_params, map, info);
	ft_apply_display_params(display_params, &map, info);
	ft_display_map(map, info);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		write(1, "Usage: ./fdf <map>\n", 19);
	else
		ft_create_map((const char *)argv[1]);
	return (0);
}
