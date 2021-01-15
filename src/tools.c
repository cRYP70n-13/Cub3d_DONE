/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:19:12 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/15 19:40:29 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int i;

	i = 0;
	if (n)
	{
		while (i < n)
		{
			*(unsigned char*)s = 0;
			s++;
			i++;
		}
	}
}

void	ft_drawasquare(int a, int b, t_mapdata *map)
{
	int			i;
	int			j;

	i = 0;
	while (i <= 7)
	{
		j = 0;
		while (j <= 7)
		{
			map->mlxdata[(j + b) * map->width + (i + a)] = 0x0fffff;
			j++;
		}
		i++;
	}
}

void	ft_drawaplayer(t_mapdata *map)
{
	int				i;
	t_horizontal	*it;
	t_horizontal	*tmp;

	it = 0;
	tmp = it;
	it = malloc(sizeof(t_horizontal));
	init(it, map);
	i = 0;
	ft_lstadd_front(&g_mylist, ft_lstnew(it));
	ARC = ANGLE - (M_PI / 6);
	while (i < map->width)
	{
		if (ARC < 0)
			ARC += 2 * M_PI;
		if (ARC > M_PI * 2)
			ARC -= (M_PI * 2);
		RAYDIST[i] = colmdist(map, it);
		generete_wall(map, it, i, RAYDIST[i]);
		ARC += (M_PI / 3) / map->width;
		i++;
	}
	free(tmp);
	to_sprite(map, -1);
}
