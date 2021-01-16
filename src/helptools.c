/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helptools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:16:53 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/16 17:06:47 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

void	ft_small_check(char *line, t_mapdata *map, int notmap)
{
	if (line[0] == 'R' && line[1] == ' ' && (map->mapcheck++ || 1))
		ft_fetch(line, map);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		ft_north(map, line);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		ft_south(map, line);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		ft_west(map, line);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		east(map, line);
	else if (line[0] == 'S' && line[1] == ' ')
		ft_sprite(map, line);
	else if (line[0] == 'F' && line[1] == ' ')
		draw_floor(map, line);
	else if (line[0] == 'C' && line[1] == ' ')
		ceiling(map, line);
	else if (line[0] != '\0' && map->mapcheck < 8)
		ft_error("there is a none empty line");
	else if (line[0] != ' ' && line[0] != '1' && map->mapcheck == 8 && !notmap)
		ft_error("something is wrong with the map");
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (i != n - 1 && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

double	colmdist(t_mapdata *map, t_horizontal *it)
{
	double dist;
	double hdist;
	double vdist;

	rayfacing(it);
	it->hith = 0;
	it->hitv = 0;
	dist = 0;
	hdist = ft_horizontal(map, it);
	vdist = ft_vertical(map, it);
	if (hdist < vdist)
	{
		it->wallx = it->wallhx;
		it->wally = it->wallhy;
		dist = hdist;
		it->hith = 1;
	}
	else
	{
		it->wallx = it->wallvx;
		it->wally = it->wallvy;
		dist = vdist;
		it->hitv = 1;
	}
	return (dist);
}
