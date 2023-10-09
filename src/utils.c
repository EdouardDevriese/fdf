/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:15:01 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/07 13:50:35 by wdevries         ###   ########.fr       */
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

void    ft_mlxPixelPut(t_imgData *img, int x, int y, int color)
{
    char            *dst;

    dst = img->addr + (y * img->lineLength + x * (img->bitsPerPixel / 8));
    *(unsigned int *)dst = color;
}

