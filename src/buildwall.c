/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildwall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:14:20 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/15 19:25:06 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

static void	ft_drawceeling(double wall, t_mapdata *map, int b)
{
	int			i;
	int			j;

	j = 0;
	i = (map->height / 2) - (wall / 2);
	while (j < i)
	{
		if (j >= 0 && j < map->height && b >= 0 && b < map->width)
			DATA[j * map->width + b] = HEXC;
		j++;
	}
}

static void	ft_drawfloor(double wall, t_mapdata *map, int b)
{
	int			i;
	int			j;

	j = map->height;
	i = (map->height / 2) + (wall / 2);
	while (i < j)
	{
		if (i >= 0 && i < map->height && b >= 0 && b < map->width)
			DATA[i * map->width + b] = HEXF;
		i++;
	}
}

static void	ft_drawwall(double wall, t_mapdata *map,
	t_horizontal *it, int b)
{
	double	i;
	double	toppix;
	double	botpix;
	double	offsetx;
	double	offsety;

	if (HV)
		offsetx = (int)WALLY % g_tiles;
	else
		offsetx = (int)WALLX % g_tiles;
	toppix = (map->height / 2) - (wall / 2);
	toppix = (toppix < 0) ? 0 : toppix;
	i = toppix;
	botpix = (map->height / 2) + (wall / 2);
	botpix = (botpix >= map->height) ? map->height : botpix;
	picktxt(it);
	while (i < botpix)
	{
		offsety = (i + (wall - map->height) / 2) * ((double)g_tiles / wall);
		if (i >= 0 && i < map->height && b >= 0 && b < map->width)
			DATA[(int)i * map->width + b] = TXTDATA[TXTNUM][(int)offsetx
				+ (g_tiles * (int)offsety)];
		i++;
	}
}

static void	render_wall(t_mapdata *map, double stripheight,
	int b, t_horizontal *it)
{
	double	wall;

	wall = stripheight;
	ft_drawwall(wall, map, it, b);
	ft_drawceeling(wall, map, b);
	ft_drawfloor(wall, map, b);
}

void		generete_wall(t_mapdata *map, t_horizontal *it,
	int b, double theone)
{
	double		prjplane;
	double		dist;
	double		stripheight;

	dist = theone * cos(ARC - ANGLE);
	prjplane = (map->width / 2) / tan(M_PI / 6);
	stripheight = (g_tiles / dist) * prjplane;
	render_wall(map, stripheight, b, it);
}
