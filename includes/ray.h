/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:14:06 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/16 18:32:16 by okimdil          ###   ########.fr       */
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

int				g_count;
void			init(t_horizontal *it, t_mapdata *map);
void			ft_facewhere(t_horizontal *it);
void			generete_wall(t_mapdata *map, t_horizontal *it,
	int b, double theone);
void			init_spt(t_mapdata *map);
void			ray_direction(t_horizontal *it);
void			square_helper(t_mapdata *map);
void			picktxt(t_horizontal *it);
void			draw_player(t_mapdata *map);
void			save_bmp(t_mapdata *map);
void			texture(t_mapdata *map);
double			cast_horz(t_mapdata *map, t_horizontal *it);
double			cast_vert(t_mapdata *map, t_horizontal *it);
double			colmdist(t_mapdata *map, t_horizontal *it);

#endif
