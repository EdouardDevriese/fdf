/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:38:34 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/09 15:11:02 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int ft_interpolateColor(int colorStart, int colorEnd, float t)
{
    t_color             start;
    t_color             end;
    t_color             current;

    start.r = (colorStart >> 16) & 0xFF;
    start.g = (colorStart >> 8) & 0xFF;
    start.b = colorStart & 0xFF;
    end.r = (colorEnd >> 16) & 0xFF;
    end.g = (colorEnd >> 8) & 0xFF;
    end.b = colorEnd & 0xFF;
    current.r = (int)((1 - t) * start.r + t * end.r);
    current.g = (int)((1 - t) * start.g + t * end.g);
    current.b = (int)((1 - t) * start.b + t * end.b);
    return ((current.r << 16) | (current.g << 8) | current.b);
}

static int ft_calculateColor(float height, t_mapInfo mapInfo)
{
    float               t;

    t = (height - mapInfo.minHeight) / mapInfo.heightRange;
    return (ft_interpolateColor(ORANGE, PURPLE, t));
}

static void ft_initBresenhamParams(t_bresenhamParams *p, t_pointCoordinates pointA, t_pointCoordinates pointB, t_mapInfo mapInfo)
{
    p->dx = abs((int)pointB.x - (int)pointA.x);
    p->dy = abs((int)pointB.y - (int)pointA.y);
    if (pointA.x < pointB.x)
        p->sx = 1;
    else
        p->sx = -1;
    if (pointA.y < pointB.y)
        p->sy = 1;
    else
        p->sy = -1;
    p->err = p->dx - p->dy;
    p->x = (int)pointA.x;
    p->y = (int)pointA.y;
    p->colorStart = ft_calculateColor(pointA.z, mapInfo);
    p->colorEnd = ft_calculateColor(pointB.z, mapInfo);
}
static void ft_drawLine(t_pointCoordinates pointA, t_pointCoordinates pointB, t_imgData *img, t_mapInfo mapInfo)
{
    t_bresenhamParams   p;
    float               t;
    int                 color;

    ft_initBresenhamParams(&p, pointA, pointB, mapInfo);
    while (1)
    {
        t = sqrt(pow(p.x - pointA.x, 2) + pow(p.y - pointA.y, 2)) / sqrt(pow(pointB.x - pointA.x, 2) + pow(pointB.y - pointA.y, 2));
        color = ft_interpolateColor(p.colorStart, p.colorEnd, t);
        ft_mlxPixelPut(img, p.x, p.y, color);
        if (p.x == (int)pointB.x && p.y == (int)pointB.y)
            break;
        p.e2 = 2 * p.err;
        if (p.e2 > -p.dy)
        {
            p.err -= p.dy;
            p.x += p.sx;
        }
        if (p.e2 < p.dx)
        {
            p.err += p.dx;
            p.y += p.sy;
        }
    }
}

void    ft_drawMap(t_pointCoordinates **mapCoordinates, t_mapInfo mapInfo, t_imgData *img)
{
    int         row;
    int         column;

    row = -1;
    while (++row < mapInfo.rowsY)
    {
        column = -1;
        while (++column < mapInfo.columnsX)
        {
            if (row + 1 < mapInfo.rowsY)
                ft_drawLine(mapCoordinates[row][column], mapCoordinates[row + 1][column], img, mapInfo);
            if (column + 1 < mapInfo.columnsX)
                ft_drawLine(mapCoordinates[row][column], mapCoordinates[row][column + 1], img, mapInfo);
        }
    }
}


