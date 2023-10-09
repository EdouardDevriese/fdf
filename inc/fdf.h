/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:09:12 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/09 15:04:12 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# define WINDOW_HEIGHT 1440
# define WINDOW_WIDTH 2560
# define ORANGE 0x00FF8000
# define PURPLE 0x00800080
# define RANGE 0x00FFFFBF

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <float.h>

///////////////////////////////////////////////////////////////////////////////
//STRUCTS//////////////////////////////////////////////////////////////////////

typedef struct      s_mapInfo
{
    int             columnsX;
    int             rowsY;
    int             minHeight;
    int             maxHeight;
    int             heightRange;
}                   t_mapInfo;

typedef struct      s_pointCoordinates
{
    float             x;
    float             y;
    float             z;
}                   t_pointCoordinates;

typedef struct      s_parsingUtils
{
    int                 row;
    int                 column;
    char                *line;
    char                **numbers;
    int                 height;
}                   t_parsingUtils;

typedef struct      s_displayParams
{
    float             minX;
    float             maxX;
    float             minY;
    float             maxY;
    float             scaleFactorX;
    float             scaleFactorY;
    float             translateX;
    float             translateY;
}                   t_displayParams;

typedef struct      s_imgData
{
    void            *img;
    char            *addr;
    int             bitsPerPixel;
    int             lineLength;
    int             endian;
}                   t_imgData;

typedef struct      s_bresenhamParams
{
    int             x;
    int             y;
    int             dx;
    int             dy;
    int             sx;
    int             sy;
    int             err;
    int             e2;
    int             colorStart;
    int             colorEnd;
}                   t_bresenhamParams;

typedef struct      s_color
{
    int             r;
    int             g;
    int             b;
}                   t_color;

//////////////////////////////////////////////////////////////////////////////
//FUNCTIONS////////////////////////////////////////////////////////////////////

//UTILS//
int     ft_openMapFile(const char *mapFile);
void    ft_mlxPixelPut(t_imgData *imgData, int x, int y, int color);

//INFO//
void    ft_getMapInfo(t_mapInfo *mapInfo, const char *mapFile);
void    ft_initializeMap(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo);
void    ft_freeMap(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo);

//COORDINATES//
void    ft_getMapCoordinates(const char *mapFile, t_pointCoordinates ***mapCoordinates, t_mapInfo *mapInfo);
void    ft_initializeMap(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo);

//DISPLAYPARAMS//
void    ft_getDisplayParams(t_displayParams *displayParams, t_pointCoordinates **mapCoordinates, t_mapInfo mapInfo);
void    ft_applyDisplayParams(t_displayParams displayParams, t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo);

//DISPLAY//
void    ft_drawMap(t_pointCoordinates **mapCoordinates, t_mapInfo mapInfo, t_imgData *img);

#endif
