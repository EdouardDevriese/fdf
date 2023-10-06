/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:09:12 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/06 17:03:45 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# define WINDOW_HEIGHT 750
# define WINDOW_WIDTH 1250

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
//STRUCTS//////////////////////////////////////////////////////////////////////

typedef struct      s_mapInfo
{
    int             columnsX;
    int             rowsY;
}                   t_mapInfo;

typedef struct      s_pointCoordinates
{
    int             x;
    int             y;
    int             z;
}                   t_pointCoordinates;

typedef struct      s_displayParams
{
    int             minX;
    int             maxX;
    int             minY;
    int             maxY;
    int             scaleFactorX;
    int             scaleFactorY;
    int             translateX;
    int             translateY;
}                   t_displayParams;

//////////////////////////////////////////////////////////////////////////////
//FUNCTIONS////////////////////////////////////////////////////////////////////

//UTILS//
int     ft_openMapFile(const char *mapFile);

//INFO//
void    ft_getMapInfo(t_mapInfo *mapInfo, const char *mapFile);
void    ft_initializeMap(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo);

//COORDINATES//
void    ft_getMapCoordinates(const char *mapFile, t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo);
void    ft_initializeMap(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo);

//DISPLAYPARAMS//
void    ft_getDisplayParams(t_displayParams *displayParams, t_pointCoordinates **mapCoordinates, t_mapInfo mapInfo);
void    ft_applyDisplayParams(t_displayParams displayParams, t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo);

#endif
