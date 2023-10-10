/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:40:05 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/10 09:09:37 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void ft_fillData(t_pointCoordinates ***mapCoordinates, t_parsingUtils p, t_mapInfo *mapInfo)
{
    (*mapCoordinates)[p.row][p.column].x = (float)p.column * 12;
    (*mapCoordinates)[p.row][p.column].y = (float)p.row * 12;
    (*mapCoordinates)[p.row][p.column].z = (float)p.height;
    if (p.height < mapInfo->minHeight)
        mapInfo->minHeight = p.height;
    if (p.height > mapInfo->maxHeight)
        mapInfo->maxHeight = p.height;
}

static int  ft_downloadHeightMap(int fd, t_pointCoordinates ***mapCoordinates, t_mapInfo *mapInfo)
{
    t_parsingUtils      p;

    p.row = -1;
    while (++p.row < mapInfo->rowsY)
    {
        if (get_next_line(fd, &p.line) == -1)
            return (write(1, "System error\n", 13));
        p.numbers = ft_split(p.line, ' ');
        if (!p.numbers)
            return (write(1, "System error\n", 13));
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
    return (0);
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

int ft_getMapCoordinates(const char *mapFile, t_pointCoordinates ***mapCoordinates, t_mapInfo *mapInfo)
{
    int                 fd;

    fd = open(mapFile, O_RDONLY);
    if (fd == 1)
        return (write(1, "System error\n", 13));
    if (ft_downloadHeightMap(fd, mapCoordinates, mapInfo) != 0)
        return (1);
    ft_applyIsometricProjection(mapCoordinates, *mapInfo);
    close(fd);
    return (0);
}

