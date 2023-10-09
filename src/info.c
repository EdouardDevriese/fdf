/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:37:49 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/07 11:48:29 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    ft_initializeMap(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo)
{
    int                 i;

    *mapCoordinates = (t_pointCoordinates **)malloc(mapInfo.rowsY * sizeof(t_pointCoordinates *));
    i = -1;
    while (++i < mapInfo.rowsY)
        (*mapCoordinates)[i] = (t_pointCoordinates *)malloc(mapInfo.columnsX * sizeof(t_pointCoordinates));
}

void    ft_freeMap(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo)
{
    int                 i;

    i = -1;
    while (++i < mapInfo.rowsY)
        free((*mapCoordinates)[i]);
    free(*mapCoordinates);
}

void    ft_getMapInfo(t_mapInfo *mapInfo, const char *mapFile)
{
    char        *line;
    int         fd;
    int         ret;

    mapInfo->columnsX = 0;
    mapInfo->rowsY = 0;
    fd = ft_openMapFile(mapFile);
    ret = get_next_line(fd, &line);
    while (ret > 0)
    {
        mapInfo->columnsX = (int)ft_word_count(line, ' ') - 1;
        mapInfo->rowsY += 1;
        free(line);
        ret = get_next_line(fd, &line);
    }
    if (ret == -1)
        write(1, "System error\n", 13);
    close(fd);
}
