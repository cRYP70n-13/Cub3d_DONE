/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:17:23 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/16 17:13:41 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

void	get_data(char *line, t_mapdata *map)
{
	static int	i = 0;
	static int	cond1 = 1;
	static int	cond2 = 1;
	static int	check = 0;

	while (line[i++] != '\0')
	{
		(ft_isalpha(line[i])) ? ft_error("there are some abnormal chars") : 0;
		if (ft_isdigit(line[i]) && cond1 && (check += 1))
		{
			(map->width = ft_atoi(line + i)) && (cond1 -= cond1);
			i += ft_intlen(map->width);
		}
		if (ft_isdigit(line[i]) && !cond1 && cond2 && (check += 1))
		{
			map->height = ft_atoi(line + i);
			i += ft_intlen(map->height);
		}
		(ft_isdigit(line[i]) && !cond1 && !cond2) ? check++ : 0;
	}
	(!(line[1] == ' ')) ? ft_error("no space after R") : 0;
	(check != 2) ? ft_error("wrong number of R params") : 0;
	fix_res(map);
}

int		ft_intlen(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		i++;
	if (num < 0)
	{
		i++;
		num *= -1;
	}
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

void	north(t_mapdata *map, char *line)
{
	static int	i = 1;

	while (line[++i])
	{
		if (line[i] == '.' || ft_isalpha(line[i]))
		{
			map->north = ft_substr(line, i, ft_strlen(line));
			ft_lstadd_front(&g_mylist, ft_lstnew(map->north));
			map->mapcheck++;
			break ;
		}
	}
}

void	south(t_mapdata *map, char *line)
{
	static int i = 1;

	while (line[++i])
	{
		if (line[i] == '.' || ft_isalpha(line[i]))
		{
			map->south = ft_substr(line, i, ft_strlen(line));
			ft_lstadd_front(&g_mylist, ft_lstnew(map->south));
			map->mapcheck++;
			break ;
		}
	}
}

void	west(t_mapdata *map, char *line)
{
	static int i = 1;

	while (line[++i])
	{
		if (line[i] == '.' || ft_isalpha(line[i]))
		{
			map->west = ft_substr(line, i, ft_strlen(line));
			ft_lstadd_front(&g_mylist, ft_lstnew(map->west));
			map->mapcheck++;
			break ;
		}
	}
}
