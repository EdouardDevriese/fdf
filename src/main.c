/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:35:54 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/05 18:50:15 by wdevries         ###   ########.fr       */
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

t_mapInfo    ft_getMapInfo(int fd)
{
    t_mapInfo   mapInfo;
    char        *line;
    int         ret;

    mapInfo.columnsX = 0;
    mapInfo.rowsY = 0;
    ret = get_next_line(fd, &line);
    while (ret > 0)
    {
        mapInfo.columnsX = (int)ft_word_count(line, ' ') - 1;
        mapInfo.rowsY += 1;
        free(line);
        ret = get_next_line(fd, &line);
    }
    if (ret == -1)
        write(1, "System error\n", 13);
    close(fd);
    return (mapInfo);
}

void    ft_initializeMaps(t_pointCoordinates ***mapCoordinates, t_pointPixels ***mapPixels, t_mapInfo mapInfo)
{
    int                 i;
    int                 rows;
    int                 columns;

    rows = mapInfo.rowsY;
    columns = mapInfo.columnsX;
    *mapCoordinates = (t_pointCoordinates **)malloc(rows * sizeof(t_pointCoordinates *));
    i = -1;
    while (++i < rows)
        (*mapCoordinates)[i] = (t_pointCoordinates *)malloc(columns * sizeof(t_pointCoordinates));
    *mapPixels = (t_pointPixels **)malloc(rows * sizeof(t_pointPixels *));
    i = -1;
    while (++i < rows)
        (*mapPixels)[i] = (t_pointPixels *)malloc(columns * sizeof(t_pointPixels));
}

void    ft_fdf(const char *mapFile)
{
    int                 fd;
    t_mapInfo           mapInfo;
    /* t_scalingInfo       scalingInfo; */
    t_pointCoordinates  **mapCoordinates;
    t_pointPixels       **mapPixels;

    fd = ft_openMapFile(mapFile);
    mapInfo = ft_getMapInfo(fd);

    //WORKING HERE
    ft_initializeMaps(&mapCoordinates, &mapPixels, mapInfo);
    /* mapCoordinates = ft_getMapCoordinates(fd, mapInfo); */
    /* scalingInfo = ft_getScalingInfo(mapIso); */
    /* mapPixel = ft_scaleToWindow(&mapIso, scalingInfo); */
    /* ft_displayMap(mapPixel); */
}


int     main(int argc, char **argv)
{
    if (argc != 2)
        write(1, "Usage: ./fdf <map>\n", 19);
    else
        ft_fdf((const char*)argv[1]);
    return (0);
}

