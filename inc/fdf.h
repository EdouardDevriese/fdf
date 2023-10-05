/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:09:12 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/05 18:49:55 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# define WINDOW_HEIGHT 750
# define WINDOW_WIDHT 1250

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>


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

typedef struct      s_scalingInfo
{
    int             minX;
    int             maxX;
    int             minY;
    int             maxY;
    int             scaleFactorX;
    int             scaleFactorY;
    int             translateX;
    int             translateY;
}                   t_scalingInfo;

typedef struct      s_pointPixels
{
    int             x;
    int             y;
    int             color;
}                   t_pointPixels;



#endif
