/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycats.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:18:07 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/15 19:39:38 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

int		iswall(double x, double y, t_mapdata *map)
{
	int	mapy;
	int	mapx;

	mapx = floor(x / (double)g_tiles);
	mapy = floor(y / (double)g_tiles);
	if (mapx >= 0 && mapx < map->pp && mapy >= 0 && mapy < g_rows)
		return (map->map2d[mapy][mapx] == '1');
	return (0);
}

void	rayfacing(t_horizontal *it)
{
	FCEDOWN = ((ARC > 0) && (ARC < M_PI));
	FCEUP = !FCEDOWN;
	FCERIGHT = ((ARC < M_PI_2) || (ARC > (1.5 * M_PI)));
	FCELEFT = !FCERIGHT;
}

int		inwin(double x, double y, t_mapdata *map)
{
	return (((x >= 0) && (x <= g_tiles * map->pp))
		&& ((y >= 0) && (y <= g_rows * g_tiles)));
}

double	ft_horizontal(t_mapdata *map, t_horizontal *it)
{
	double	ax;
	double	ay;
	double	xstep;
	double	ystep;
	double	h;

	h = 0;
	ay = floor(map->playery / g_tiles) * g_tiles + (g_tiles * FCEDOWN);
	ax = map->playerx + ((ay - map->playery) / tan(ARC));
	ystep = g_tiles * (FCEUP ? -1 : 1);
	xstep = g_tiles / tan(ARC);
	xstep *= (FCELEFT && xstep > 0) ? -1 : 1;
	xstep *= (FCERIGHT && xstep < 0) ? -1 : 1;
	if (FCEUP)
		h++;
	while (inwin(ax, ay - h, map) && !iswall(ax, ay - h, map))
	{
		ax += xstep;
		ay += ystep;
	}
	WALLHX = ax;
	WALLHY = ay;
	return (sqrtf((ay - map->playery) * (ay - map->playery) + (ax - map->playerx) * (ax - map->playerx)));
}

double	ft_vertical(t_mapdata *map, t_horizontal *it)
{
	double	ax;
	double	ay;
	double	xstep;
	double	ystep;
	double	hu;

	hu = 0;
	ax = floor(map->playerx / g_tiles) * g_tiles + (g_tiles * FCERIGHT);
	ay = map->playery + ((ax - map->playerx) * tan(ARC));
	xstep = g_tiles * (FCELEFT ? -1 : 1);
	ystep = g_tiles * tan(ARC);
	ystep *= (FCEUP && (ystep > 0)) ? -1 : 1;
	ystep *= (FCEDOWN && (ystep < 0)) ? -1 : 1;
	if (FCELEFT)
		hu++;
	while (inwin(ax - hu, ay, map) && !iswall(ax - hu, ay, map))
	{
		ax += xstep;
		ay += ystep;
	}
	WALLVX = ax;
	WALLVY = ay;
	return (sqrtf((ay - map->playery) * (ay - map->playery) + (ax - map->playerx) * (ax - map->playerx)));
}
