/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:40:05 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/09 11:43:27 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void ft_downloadHeightMap(int fd, t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo)
{
    int                 row;
    int                 column;
    char                *line;
    char                **numbers;

    row = -1;
    while (++row < mapInfo.rowsY)
    {
        get_next_line(fd, &line);
        numbers = ft_split(line, ' ');
        column = -1;
        while (++column < mapInfo.columnsX)
        {
            (*mapCoordinates)[row][column].x = (float)column;
            (*mapCoordinates)[row][column].y = (float)row;
            (*mapCoordinates)[row][column].z = (float)ft_atoi(numbers[column]);
            free(numbers[column]);
        }
        free(line);
        free(numbers);
    }
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

void ft_getMapCoordinates(const char *mapFile, t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo)
{
    int                 fd;

    fd = ft_openMapFile(mapFile);
    ft_downloadHeightMap(fd, mapCoordinates, mapInfo);
    ft_applyIsometricProjection(mapCoordinates, mapInfo);
    close(fd);
}

