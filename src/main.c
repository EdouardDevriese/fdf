/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:35:54 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/06 16:16:44 by wdevries         ###   ########.fr       */
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

void    ft_initializeMap(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo)
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
   }

void    ft_downloadHeightMap(int fd, t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo)
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
            (*mapCoordinates)[row][column].x = column;
            (*mapCoordinates)[row][column].y = row;
            (*mapCoordinates)[row][column].z = ft_atoi(numbers[column]);
            free(numbers[column]);
        }
        free(line);
        free(numbers);
    }
}

t_pointCoordinates  ft_projectPoint(t_pointCoordinates originalPoint)
{
    t_pointCoordinates  projectedPoint;

    projectedPoint.x = originalPoint.x - originalPoint.y;
    projectedPoint.y = (originalPoint.x + originalPoint.y) / 2 - originalPoint.z;
    projectedPoint.z = originalPoint.z;
    return (projectedPoint);
}

void    ft_applyIsometricProjection(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo)
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

void ft_printMapCoordinates(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo)
{
    int row;
   int column;

    row = -1;
    while (++row < mapInfo.rowsY)
    {
        column = -1;
        while (++column < mapInfo.columnsX)
        {
            printf("Point at row %d, column %d: x = %d, y = %d, z = %d\n",
                   row,
                   column,
                   (*mapCoordinates)[row][column].x,
                   (*mapCoordinates)[row][column].y,
                   (*mapCoordinates)[row][column].z);
        }
        printf("\n");  // new line after each row
    }
}

void    ft_getMinMaxValues(t_displayParams *displayParams, t_pointCoordinates **mapCoordinates, t_mapInfo mapInfo)
{
    int                 row;
    int                 column;

    displayParams->minX = INT_MAX;
    displayParams->maxX = INT_MIN;
    displayParams->minY = INT_MAX;
    displayParams->maxY = INT_MIN;
    row = -1;
    while (++row < mapInfo.rowsY)
    {
        column = -1;
        while (++column < mapInfo.columnsX)
        {
            if (mapCoordinates[row][column].x < displayParams->minX)
                displayParams->minX = mapCoordinates[row][column].x;
            if (mapCoordinates[row][column].x > displayParams->maxX)
                displayParams->maxX = mapCoordinates[row][column].x;
            if (mapCoordinates[row][column].y < displayParams->minY)
                displayParams->minY = mapCoordinates[row][column].y;
            if (mapCoordinates[row][column].y > displayParams->maxY)
                displayParams->maxY = mapCoordinates[row][column].y;
        }
    }
}   

void    ft_getDisplayParams(t_displayParams *displayParams, t_pointCoordinates **mapCoordinates, t_mapInfo mapInfo)
{
    ft_getMinMaxValues(displayParams, mapCoordinates, mapInfo);
    displayParams->scaleFactorX = WINDOW_HEIGHT / (displayParams->maxX - displayParams->minX);
    displayParams->scaleFactorY = WINDOW_WIDTH / (displayParams->maxY - displayParams->minY);
    displayParams->translateX = -(displayParams->minX) * displayParams->scaleFactorX;
    displayParams->translateY = -(displayParams->minY) * displayParams->scaleFactorY;
}

void    ft_applyDisplayParams(t_displayParams displayParams, t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo) 
{
    int                 row;
    int                 column;

   row = -1;
    while (++row < mapInfo.rowsY)
    {
        column = -1;
        while (++column < mapInfo.columnsX)
        {
            (*mapCoordinates)[row][column].x = (*mapCoordinates)[row][column].x * displayParams.scaleFactorX + displayParams.translateX;
            (*mapCoordinates)[row][column].y = (*mapCoordinates)[row][column].y * displayParams.scaleFactorY + displayParams.translateY;
        }
    }

}

void    ft_fdf(const char *mapFile)
{
    int                 fd;
    t_mapInfo           mapInfo;
    t_displayParams     displayParams;
    t_pointCoordinates  **mapCoordinates;

    fd = ft_openMapFile(mapFile);
    mapInfo = ft_getMapInfo(fd);
    ft_initializeMap(&mapCoordinates, mapInfo);
    ft_getMapCoordinates(mapFile, &mapCoordinates, mapInfo);
    ft_getDisplayParams(&displayParams, mapCoordinates, mapInfo);
    ft_applyDisplayParams(displayParams, &mapCoordinates, mapInfo);
    ft_printMapCoordinates(&mapCoordinates, mapInfo);
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

