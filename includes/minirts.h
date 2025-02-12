/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirts.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>      			    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:47:59 by sbarbe       	   #+#    #+#             */
/*   Updated: 2025/01/30 18:35:38 by sbarbe        	  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRTS_H
# define MINIRTS_H

# include "libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>

// valgrind --leak-check=full --show-leak-kinds=all
// --trace-children=yes --track-origins=yes -s ./miniRT 

# define LENGHT_WIN	800
# define WIDTH_WIN	600
# define PI 3.14159265358979323846

/*=================================================
				STRUCTUR UTILES
  =================================================*/

typedef struct s_rgb
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	int				color_hexa;
}	t_rgb;

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}	t_vec3;

typedef struct s_rays
{
	t_vec3	origine;
	t_vec3	direction;
}	t_rays;

typedef struct s_data_window
{
	void	*mlx;
	void	*window;
	void	*buff_img;
	char	*img_data;
	int		pits_per_pixel;
	int		size_line;
	int		endian;
}	t_data_window;

/*=================================================
			ENV STRUCTUR FOR MIN
  =================================================*/

typedef struct s_pls
{
	t_vec3			pose;
	t_vec3			orientation;
	t_rgb			color;
	double			disitance;
	bool			pass;
}	t_pls;

typedef struct s_sps
{
	t_vec3			pos;
	t_vec3			point;
	t_vec3			normal;
	double			radius;
	t_rgb			color;
}	t_sps;

typedef struct s_cys
{
	t_vec3			pos;
	t_vec3			axis;
	double			diameter;
	double			height;
	int				ok;
	t_rgb			color;
}	t_cys;
/*=================================================
			ENV STRUCTUR FOR MAJ
  =================================================*/

typedef struct s_ambient
{
	double			embient;
	t_rgb			color;
	bool			pass;
}	t_ambient;

typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			orientation;
	t_vec3			right_x;
	t_vec3			up_y;
	unsigned char	fov;
	double			d_focal;
	bool			pass;
}	t_camera;

typedef struct s_lights
{
	double			light;
	t_sps			pos;
	bool			pass;
}	t_lights;

/*=================================================
					STRUCTUR	
  =================================================*/

typedef struct s_data_rt
{
	t_ambient		ambient;
	t_camera		camera;
	t_lights		light;
	t_pls			*plane;
	int				nb_plane;
	int				nb_plane_intersept;
	t_sps			*sphere;
	int				nb_sphere;
	int				nb_sphere_intersept;
	int				nb_cylinder_intersept;
	t_cys			*cylinder;
	int				ok;
	int				check;
	int				nb_cylinder;
	t_data_window	data_window;
	t_rays			rayon;
}	t_data_rt;

typedef struct s_stuct_add_color
{
	int			i;
	t_vec3		point;
	t_vec3		normal;
	t_vec3		color_amb;
	t_lights	light;
	t_rgb		color_obj;
	int			nb_obj;
	char		obj[1];
	double		lenght;
}	t_stuct_add_color;

typedef struct s_intersect_cyl_data
{
	t_vec3	oc;
	t_vec3	dir;
	double	m;
	double	n;
	t_vec3	x;
	t_vec3	y;
	double	a;
	double	b;
	double	c;
	double	t0;
	double	t1;
	double	y0;
	double	y1;
	double	q;
	double	temp;
	int		hit;
}	t_cyl_data;

int		parsing_rt(char *str, t_data_rt *data_rt);
int		check_rt_a_c_l(char **argv, t_data_rt *data_rt);
int		verif_caract_rt(char **argv, t_data_rt *data_rt);
double	my_atof(const char *str);
int		ft_len_atof(char *str);
int		ft_len_waitspace(char *str);
int		count_word(char *str);
int		init_a(char *str, t_data_rt *data_rt);
int		init_a_c_l(char *str, t_data_rt *data_rt);
int		check_0_255_a(char *str, t_data_rt *data_rt);
int		check_0_9(char *str, char c, int j);
int		ft_is_dig(char c);
int		check_0_9_point(char *str, char c, int j);
size_t	ft_where(char *str, char c);
int		check_neg1_1(char *str, t_data_rt *data_rt);
int		init_l(char *str, t_data_rt *data_rt);
int		init_c(char *str, t_data_rt *data_rt);
int		init_sp(char *str, t_data_rt *data_rt);
int		init_pl(char *str, t_data_rt *data_rt);
int		init_pl_i(char *str, t_data_rt *data_rt, int i);
int		init_cy(char *str, t_data_rt *data_rt);
int		check_0_255_cy(char *str, t_data_rt *data_rt, int z);
int		check_neg1_1_cy(char *str, t_data_rt *data_rt, int z);
int		check_0_9_suite(char *str, int i, int z);
int		ft_check_rt(char *str);
void	free_first_parsing(t_data_rt *data_rt);
char	*get_next_lines(int fd);
char	**main_get_next_line(char *str);

/*==================================== 
				UTILES
 ======================================*/
void	my_free_tab(char **tab);
int		stop(t_data_rt *data_rt);
char	*ft_strchrs(const char *s, int c);
size_t	ft_strlens(const char *s);
#endif