/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycats.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:18:07 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/16 18:32:16 by okimdil          ###   ########.fr       */
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

void	ray_direction(t_horizontal *it)
{
	it->facedown = ((it->arc > 0) && (it->arc < M_PI));
	it->faceup = !it->facedown;
	it->faceright = ((it->arc < M_PI_2) || (it->arc > (1.5 * M_PI)));
	it->faceleft = !it->faceright;
}

int		valid_cord(double x, double y, t_mapdata *map)
{
	return (((x >= 0) && (x <= g_tiles * map->pp))
		&& ((y >= 0) && (y <= g_rows * g_tiles)));
}

double	cast_horz(t_mapdata *map, t_horizontal *it)
{
	double	ax;
	double	ay;
	double	xstep;
	double	ystep;
	double	h;

	h = 0;
	ay = floor(map->playery / g_tiles) * g_tiles + (g_tiles * it->facedown);
	ax = map->playerx + ((ay - map->playery) / tan(it->arc));
	ystep = g_tiles * (it->faceup ? -1 : 1);
	xstep = g_tiles / tan(it->arc);
	xstep *= (it->faceleft && xstep > 0) ? -1 : 1;
	xstep *= (it->faceright && xstep < 0) ? -1 : 1;
	if (it->faceup)
		h++;
	while (valid_cord(ax, ay - h, map) && !iswall(ax, ay - h, map))
	{
		ax += xstep;
		ay += ystep;
	}
	it->wallhx = ax;
	it->wallhy = ay;
	return (sqrtf((ay - map->playery) * (ay - map->playery)
		+ (ax - map->playerx) * (ax - map->playerx)));
}

double	cast_vert(t_mapdata *map, t_horizontal *it)
{
	double	ax;
	double	ay;
	double	xstep;
	double	ystep;
	double	hu;

	hu = 0;
	ax = floor(map->playerx / g_tiles) * g_tiles + (g_tiles * it->faceright);
	ay = map->playery + ((ax - map->playerx) * tan(it->arc));
	xstep = g_tiles * (it->faceleft ? -1 : 1);
	ystep = g_tiles * tan(it->arc);
	ystep *= (it->faceup && (ystep > 0)) ? -1 : 1;
	ystep *= (it->facedown && (ystep < 0)) ? -1 : 1;
	if (it->faceleft)
		hu++;
	while (valid_cord(ax - hu, ay, map) && !iswall(ax - hu, ay, map))
	{
		ax += xstep;
		ay += ystep;
	}
	it->wallvx = ax;
	it->wallvy = ay;
	return (sqrtf((ay - map->playery) * (ay - map->playery)
		+ (ax - map->playerx) * (ax - map->playerx)));
}
