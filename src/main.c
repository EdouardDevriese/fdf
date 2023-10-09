/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:35:54 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/09 17:44:54 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_closeWindow(t_mlxData *mlx)
{
    mlx_destroy_image(mlx->mlxPtr, mlx->img);
    mlx_destroy_window(mlx->mlxPtr, mlx->winPtr);
    mlx_destroy_display(mlx->mlxPtr);
    free(mlx->mlxPtr);
    exit (0);
}

int ft_escape(int keycode, t_mlxData *mlx) 
{
    if (keycode == 65307)
        ft_closeWindow(mlx);
    return (0);
}

static void ft_displayMap(t_pointCoordinates **mapCoordinates, t_mapInfo mapInfo)    
{
    t_mlxData       mlx;

    mlx.mlxPtr = mlx_init();
    mlx.winPtr = mlx_new_window(mlx.mlxPtr, WINDOW_WIDTH, WINDOW_HEIGHT, "Fil de fer");
    mlx.img = mlx_new_image(mlx.mlxPtr, WINDOW_WIDTH, WINDOW_HEIGHT);
    mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bitsPerPixel, &mlx.lineLength, &mlx.endian);
    ft_drawMap(mapCoordinates, mapInfo, &mlx);
    mlx_put_image_to_window(mlx.mlxPtr, mlx.winPtr, mlx.img, 0, 0);
    mlx_hook(mlx.winPtr, 17, 0L, ft_closeWindow, &mlx);
    mlx_key_hook(mlx.winPtr, ft_escape, &mlx); 
    ft_freeMap(&mapCoordinates, mapInfo);
    mlx_loop(mlx.mlxPtr);
}

static void ft_createMap(const char *mapFile)
{
    t_mapInfo           mapInfo;
    t_pointCoordinates  **mapCoordinates;
    t_displayParams     displayParams;

    ft_getMapInfo(&mapInfo, mapFile);
    ft_initializeMap(&mapCoordinates, mapInfo);
    ft_getMapCoordinates(mapFile, &mapCoordinates, &mapInfo);
    ft_getDisplayParams(&displayParams, mapCoordinates, mapInfo);
    ft_applyDisplayParams(displayParams, &mapCoordinates, mapInfo);
    ft_displayMap(mapCoordinates, mapInfo);
}

int     main(int argc, char **argv)
{
    if (argc != 2)
        write(1, "Usage: ./fdf <map>\n", 19);
    else
        ft_createMap((const char*)argv[1]);
    return (0);
}

