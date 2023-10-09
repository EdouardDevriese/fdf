/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:38:34 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/07 16:59:45 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int ft_calculateColor(float z)
{
    int color = (int)z + 150;
    return (color << 16) | (color << 8) | color; // R, G, B components
}

static void ft_initBresenhamParams(t_bresenhamParams *p, t_pointCoordinates pointA, t_pointCoordinates pointB)
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
    p->colorStart = ft_calculateColor(pointA.z);
    p->colorEnd = ft_calculateColor(pointB.z);
}

int ft_interpolateColor(int color_start, int color_end, float t)
{
    int r_start = (color_start >> 16) & 0xFF;
    int g_start = (color_start >> 8) & 0xFF;
    int b_start = color_start & 0xFF;

    int r_end = (color_end >> 16) & 0xFF;
    int g_end = (color_end >> 8) & 0xFF;
    int b_end = color_end & 0xFF;

    int r_current = (int)((1 - t) * r_start + t * r_end);
    int g_current = (int)((1 - t) * g_start + t * g_end);
    int b_current = (int)((1 - t) * b_start + t * b_end);

    return (r_current << 16) | (g_current << 8) | b_current;
}

static void ft_drawLine(t_pointCoordinates pointA, t_pointCoordinates pointB, t_imgData *img)
{
    t_bresenhamParams   p;
    float               t;
    int                 color;

    ft_initBresenhamParams(&p, pointA, pointB);
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
                ft_drawLine(mapCoordinates[row][column], mapCoordinates[row + 1][column], img);
            if (column + 1 < mapInfo.columnsX)
                ft_drawLine(mapCoordinates[row][column], mapCoordinates[row][column + 1], img);
        }
    }
}


