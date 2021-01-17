/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapstuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:17:38 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/17 14:32:57 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

int		wallconditions(t_mapdata *map, int *i, int *j)
{
	if (map->map2d[*i][*j] == '0' || map->map2d[*i][*j] == '2'
		|| map->map2d[*i][*j] == 'N' ||
		map->map2d[*i][*j] == 'S' || map->map2d[*i][*j] == 'W'
		|| map->map2d[*i][*j] == 'E')
	{
		if (map->map2d[*i][*j - 1] == ' ' || map->map2d[*i][*j + 1] == ' '
			|| map->map2d[*i - 1][*j] == ' ' || map->map2d[*i + 1][*j] == ' ')
			return (1);
	}
	return (0);
}

void	map_helper(t_mapdata *map)
{
	static int		i = -1;
	static int		j;

	while (map->map2d[++i])
	{
		ft_lstadd_front(&g_mylist, ft_lstnew((map->map2d[i])));
		if ((map->map2d[i][0] != '1' && map->map2d[i][0] != ' ')
			|| (map->map2d[i][ft_strlen(map->map2d[i]) - 1] != '1'
			&& map->map2d[i][ft_strlen(map->map2d[i]) - 1] != ' '))
			err("map extreems aren't closed");
		j = -1;
		while (map->map2d[i][++j])
		{
			if (map->map2d[i][j] == '2')
				g_count++;
			if (i == 0 || i == g_rows - 1)
				if (map->map2d[i][j] != '1' && map->map2d[i][j] != ' ')
					err("map extreems  aren't closed,");
		}
	}
}

int		map_helper_2(char c)
{
	if (c != '1' && c != '2' && c != '0' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W' && c != ' ')
		return (0);
	else
		return (1);
}

int		helpread(char *line, t_mapdata *map)
{
	map_one_line(map, line);
	return (0);
}

void	map_parser(t_mapdata *map)
{
	static int i = -1;
	static int j = -1;
	static int p = 0;

	map_helper(map);
	while (map->map2d[++i])
	{
		j = -1;
		while (map->map2d[i][++j])
		{
			if ((map->map2d[i][j] == 'N' || map->map2d[i][j] == 'W' ||
			map->map2d[i][j] == 'E' || map->map2d[i][j] == 'S') && p == 0)
			{
				p = 1;
				(map->playerx = ((j + 0.5) * g_tiles)) &&
				(map->playery += ((i + 0.5) * g_tiles));
			}
			else if ((map->map2d[i][j] == 'N' || map->map2d[i][j] == 'W'
			|| map->map2d[i][j] == 'E' || map->map2d[i][j] == 'S') && p == 1)
				err("multiplayer game");
			!(map_helper_2(map->map2d[i][j])) ? err("Wrong Char") : 0;
			(wallconditions(map, &i, &j)) ? err("map isn't closed") : 0;
		}
	}
	(p == 0) ? err("there's no player") : 0;
}
