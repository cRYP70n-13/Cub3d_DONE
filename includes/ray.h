/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:14:06 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/15 19:55:08 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <stdint.h>

typedef	struct	s_bmp_header
{
	char		bftype[3];
	u_int32_t	bfsize;
	u_int16_t	bfreserved1;
	u_int16_t	bfreserved2;
	u_int32_t	bfoffbits;
	u_int32_t	bisize;
	int32_t		biwidth;
	int32_t		biheight;
	u_int16_t	biplanes;
	u_int16_t	bibitcount;
	u_int32_t	bicompression;
	u_int32_t	bisizeimage;
	int32_t		bixpermeter;
	int32_t		biypermeter;
	u_int32_t	biclrused;
	u_int32_t	biclrimportant;
}				t_bmp_file;

# define WALLVY it->wallvy
# define WALLHY it->wallhy
# define DX it->dx
# define X it->x
# define WALLVX it->wallvx
# define WALLHX it->wallhx
# define WALLX it->wallx
# define ARC it->arc
# define HH it->hith
# define HV it->hitv
# define TXTNUM it->textnum
# define SH map->s_height
# define SW map->s_width
# define DT map->ditch
# define DT1 map->ditch1

int				g_count;
void			init(t_horizontal *it, t_mapdata *map);
void			ft_facewhere(t_horizontal *it);
void			generete_wall(t_mapdata *map, t_horizontal *it,
	int b, double theone);
void			init_spt(t_mapdata *map);
void			rayfacing(t_horizontal *it);
void			ft_helpdrawasquare(t_mapdata *map);
void			picktxt(t_horizontal *it);
void			ft_drawaplayer(t_mapdata *map);
void			save_bmp(t_mapdata *map);
void			texture(t_mapdata *map);
double			ft_horizontal(t_mapdata *map, t_horizontal *it);
double			ft_vertical(t_mapdata *map, t_horizontal *it);
double			colmdist(t_mapdata *map, t_horizontal *it);

#endif
