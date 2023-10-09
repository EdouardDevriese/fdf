/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayparams.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:40:57 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/07 15:46:06 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void    ft_getMinMaxValues(t_displayParams *displayParams, t_pointCoordinates **mapCoordinates, t_mapInfo mapInfo)
{
    int                 row;
    int                 column;

    displayParams->minX = (float)INT_MAX;
    displayParams->maxX = (float)INT_MIN;
    displayParams->minY = (float)INT_MAX;
    displayParams->maxY = (float)INT_MIN;
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
    displayParams->scaleFactorX = WINDOW_WIDTH / (displayParams->maxX - displayParams->minX);
    displayParams->scaleFactorY = WINDOW_HEIGHT / (displayParams->maxY - displayParams->minY);
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

