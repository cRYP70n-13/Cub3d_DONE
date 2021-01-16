/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:16:13 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/16 18:49:54 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include <stdio.h>
#include <string.h>
#include "../includes/ray.h"

void	map_manager(t_mapdata *map)
{
	int		i;
	int		j;

	i = -1;
	map->map2d = (char**)malloc((g_rows + 1) * sizeof(char*));
	while (++i < g_rows)
		map->map2d[i] = (char*)malloc((map->pp + 1) * sizeof(char));
	map->map2d[i] = NULL;
	i = -1;
	while (++i < g_rows)
	{
		j = 0;
		while (j < map->pp)
		{
			if (j < ft_strlen(map->map2dbefore[i]))
				map->map2d[i][j] = map->map2dbefore[i][j];
			else
				map->map2d[i][j] = ' ';
			j++;
		}
		map->map2d[i][j] = '\0';
	}
	i = 0;
}

int		get_next_line(int fd, char **line)
{
	static char	*last[1024];
	char		*tmp;
	char		*pmt;

	if (!last[fd])
		last[fd] = ft_strdup("");
	if (!line || fd < 0)
		return (-1);
	if (ft_fill(&last[fd], fd) < 0)
		return (-1);
	if ((ft_strchr(last[fd], '\n')))
	{
		tmp = last[fd];
		*line = ft_substr(last[fd], 0, ft_strchr(last[fd], '\n') - last[fd]);
		last[fd] = ft_strdup(last[fd] + (ft_strchr(last[fd],
		'\n') - last[fd] + 1));
		free(tmp);
		return (1);
	}
	else
		*line = ft_strdup(last[fd]);
	pmt = last[fd];
	last[fd] = NULL;
	free(pmt);
	return (0);
}

int		ft_fill(char **last, int fd)
{
	int		ret;
	char	*buf;
	char	**tmp;

	while (!ft_strchr(last[0], '\n'))
	{
		if (!(buf = malloc(1000 + 1)) ||
			(ret = read(fd, buf, 1000)) < 0)
			return (-1);
		buf[ret] = '\0';
		last[0] = ft_strjoin(last[0], buf);
		if (ret == 0)
		{
			tmp = last;
			last = 0;
			return (0);
		}
	}
	return (1);
}
