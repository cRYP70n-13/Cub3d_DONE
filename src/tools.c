/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:19:12 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/17 15:12:05 by okimdil          ###   ########.fr       */
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

void	draw_square(int a, int b, t_mapdata *map)
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

void	draw_player(t_mapdata *map)
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
	it->arc = map->angle - (M_PI / 6);
	while (i < map->width)
	{
		if (it->arc < 0)
			it->arc += 2 * M_PI;
		if (it->arc > M_PI * 2)
			it->arc -= (M_PI * 2);
		map->raydist[i] = colmdist(map, it);
		generete_wall(map, it, i, map->raydist[i]);
		it->arc += (M_PI / 3) / map->width;
		i++;
	}
	free(tmp);
	to_sprite(map, -1);
}
