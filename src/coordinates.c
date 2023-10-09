/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:40:05 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/09 14:53:03 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void ft_fillData(t_pointCoordinates ***mapCoordinates, t_parsingUtils p, t_mapInfo *mapInfo)
{
    (*mapCoordinates)[p.row][p.column].x = (float)p.column;
    (*mapCoordinates)[p.row][p.column].y = (float)p.row;
    (*mapCoordinates)[p.row][p.column].z = (float)p.height;
    if (p.height < mapInfo->minHeight)
        mapInfo->minHeight = p.height;
    if (p.height > mapInfo->maxHeight)
        mapInfo->maxHeight = p.height;
}

static void ft_downloadHeightMap(int fd, t_pointCoordinates ***mapCoordinates, t_mapInfo *mapInfo)
{
    t_parsingUtils      p;

    p.row = -1;
    while (++p.row < mapInfo->rowsY)
    {
        get_next_line(fd, &p.line);
        p.numbers = ft_split(p.line, ' ');
        p.column = -1;
        while (++p.column < mapInfo->columnsX)
        {
            p.height = ft_atoi(p.numbers[p.column]);
            ft_fillData(mapCoordinates, p, mapInfo);
            free(p.numbers[p.column]);
        }
        free(p.line);
        free(p.numbers);
    }
    mapInfo->heightRange = mapInfo->maxHeight - mapInfo->minHeight;
}

static t_pointCoordinates  ft_projectPoint(t_pointCoordinates originalPoint)
{
    t_pointCoordinates  projectedPoint;

    projectedPoint.x = originalPoint.x - originalPoint.y;
    projectedPoint.y = (originalPoint.x + originalPoint.y) / 2 - originalPoint.z;
    projectedPoint.z = originalPoint.z;
    return (projectedPoint);
}

static void    ft_applyIsometricProjection(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo)
{
    int                 row;
    int                 column;

    row = -1;
    while (++row < mapInfo.rowsY)
    {
        column = -1;
        while (++column < mapInfo.columnsX)
            (*mapCoordinates)[row][column] = ft_projectPoint((*mapCoordinates)[row][column]);
    }
}

void ft_getMapCoordinates(const char *mapFile, t_pointCoordinates ***mapCoordinates, t_mapInfo *mapInfo)
{
    int                 fd;

    fd = ft_openMapFile(mapFile);
    ft_downloadHeightMap(fd, mapCoordinates, mapInfo);
    ft_applyIsometricProjection(mapCoordinates, *mapInfo);
    close(fd);
}

