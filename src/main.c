/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:35:54 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/06 17:21:34 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int     ft_openMapFile(const char *mapFile)
{
    int             fd;

    fd = open(mapFile, O_RDONLY);
    if (fd == -1)
        write(1, "System error\n", 13);
    return (fd);
}

static void ft_displayMap(t_pointCoordinates **mapCoordinates)    
{

}

static void ft_createMap(const char *mapFile)
{
    t_mapInfo           mapInfo;
    t_pointCoordinates  **mapCoordinates;
    t_displayParams     displayParams;

    ft_getMapInfo(&mapInfo, mapFile);
    ft_initializeMap(&mapCoordinates, mapInfo);
    ft_getMapCoordinates(mapFile, &mapCoordinates, mapInfo);
    ft_getDisplayParams(&displayParams, mapCoordinates, mapInfo);
    ft_applyDisplayParams(displayParams, &mapCoordinates, mapInfo);
    /* ft_displayMap(mapPixel); */
}

int     main(int argc, char **argv)
{
    if (argc != 2)
        write(1, "Usage: ./fdf <map>\n", 19);
    else
        ft_createMap((const char*)argv[1]);
    return (0);
}

