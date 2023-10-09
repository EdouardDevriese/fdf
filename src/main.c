/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:35:54 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/09 12:19:32 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void ft_displayMap(t_pointCoordinates **mapCoordinates, t_mapInfo mapInfo)    
{
    void        *mlx;
    void        *mlxWin;
    t_imgData   img;

    (void)mapCoordinates;
    mlx = mlx_init();
    mlxWin = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Fil de fer");
    img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bitsPerPixel, &img.lineLength, &img.endian);
    ft_drawMap(mapCoordinates, mapInfo, &img);
    mlx_put_image_to_window(mlx, mlxWin, img.img, 0, 0);
    mlx_loop(mlx);
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
    ft_freeMap(&mapCoordinates, mapInfo);
}

int     main(int argc, char **argv)
{
    if (argc != 2)
        write(1, "Usage: ./fdf <map>\n", 19);
    else
        ft_createMap((const char*)argv[1]);
    return (0);
}

