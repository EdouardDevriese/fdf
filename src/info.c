/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:37:49 by wdevries          #+#    #+#             */
/*   Updated: 2023/10/10 09:08:58 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int      ft_initializeMap(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo)
{
    int                 i;

    *mapCoordinates = (t_pointCoordinates **)malloc(mapInfo.rowsY * sizeof(t_pointCoordinates *));
    if (!*mapCoordinates)
        return (write(1, "System error\n", 13));
    i = -1;
    while (++i < mapInfo.rowsY)
    {
        (*mapCoordinates)[i] = (t_pointCoordinates *)malloc(mapInfo.columnsX * sizeof(t_pointCoordinates));
        if (!(*mapCoordinates)[i])
            return (write(1, "System error\n", 13));
    }
    return (0);
}

int     ft_freeMap(t_pointCoordinates ***mapCoordinates, t_mapInfo mapInfo)
{
    int                 i;

    i = -1;
    while (++i < mapInfo.rowsY)
        if ((*mapCoordinates)[i])
            free((*mapCoordinates)[i]);
    if (*mapCoordinates)
        free(*mapCoordinates);
    return (1);
}

void    ft_initializeMapInfo(t_mapInfo *mapInfo)
{
    mapInfo->minHeight = INT_MAX;
    mapInfo->maxHeight = INT_MIN;
    mapInfo->columnsX = 0;
    mapInfo->rowsY = 0;
}

int     ft_getMapInfo(t_mapInfo *mapInfo, const char *mapFile)
{
    char        *line;
    int         fd;
    int         ret;
    
    fd = open(mapFile, O_RDONLY);
    if (fd == -1)
        return (write(1, "System error\n", 13));
    ret = get_next_line(fd, &line);
    if (ft_isdigit(line[ft_strlen(line) - 2]))
        mapInfo->columnsX = (int)ft_word_count(line, ' ');
    else
        mapInfo->columnsX = (int)ft_word_count(line, ' ') - 1;
    while (ret > 0)
    {
        mapInfo->rowsY += 1;
        free(line);
        ret = get_next_line(fd, &line);
    }
    if (ret == -1)
        return (write(1, "System error\n", 13));
    close(fd);
    return (0);
}
