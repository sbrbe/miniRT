/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:39:49 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:10:36 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define MOVE_SPEED 1.0
# define ROTATION_SPEED 0.1

# define ESC_KEY 65307
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define DBL_MAX 1.7976931348623157e+308
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../GNL/get_next_line.h"
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vecto;

void	end(void);

typedef struct s_amb
{
	double	lighting;
	t_vecto	rgb_colors;
}	t_amb;

typedef struct s_cam
{
	t_vecto	right;
	t_vecto	up;
	t_vecto	coord;
	t_vecto	orientation;
	double	fov;	
}	t_cam;

typedef struct s_light
{
	t_vecto	coord;
	t_vecto	rgb_colors;
	double	brightness;
}	t_light;

typedef struct s_sphere
{
	t_vecto	coord;
	double	diameter;
	t_vecto	rgb_colors;
}	t_sp;

typedef struct s_plane
{
	t_vecto	coord;
	t_vecto	norm_vect;
	t_vecto	rgb_colors;
}	t_pl;

typedef struct s_cylinder
{
	t_vecto	coord;
	t_vecto	norm_vect;
	double	diameter;
	double	height;
	t_vecto	rgb_colors;
}	t_cy;

typedef struct s_ray
{
	t_vecto	direction;
	t_vecto	origin;
}	t_ray;

typedef struct s_ldata
{
	double	diff;
	double	spec;
	t_vecto	light_dir;
	t_vecto	view_dir;
	t_vecto	reflect_dir;
	t_vecto	light_normed_rgb;
	t_vecto	hit_normed_col;
}	t_ldata;

typedef struct s_scene_data
{
	int		light_nb;
	int		sp_nb;
	int		pl_nb;
	int		cy_nb;
	t_amb	amb;
	t_cam	cam;
	t_light	*lights;
	t_sp	*spheres;
	t_pl	*planes;
	t_cy	*cylinders;
}	t_scene_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_eq
{
	t_vecto	o_to_center;
	double	a;
	double	b;
	double	c;
	double	delta;
}	t_eq;

typedef enum s_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef struct s_inter
{
	double		dist;
	t_vecto		coord;
	t_vecto		norm;
	t_vecto		color;
	bool		hit;
	int			iter;
	t_obj_type	type;
}	t_inter;

typedef struct s_elems
{
	char	*name;
	int		count;
}	t_elem;

typedef struct s_data
{
	int				iter;
	int				fd;
	double			height;
	double			width;
	double			width_view;
	double			height_view;
	double			aspectratio;
	double			ray_max[WINDOW_HEIGHT][WINDOW_WIDTH];
	void			*mlx;
	void			*win;
	t_img			img;
	t_scene_data	*data;
}	t_data;

int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		init_parse_scene(t_data *rt, char **argv);
int		scene_name_check(char *ext, char *scene);
char	*scene_get_loop(int fd);
char	**ft_split(char const *s, char c);
int		obj_check(char *str, char first, char sec);
int		parse_scene(t_data *rt, char **tab);
int		mandatory_components(t_scene_data *data, char **tab);
int		mandatory_params_01(char *line, char *elem);
void	save_coords(t_data *rt, char **tab);
int		obj_check(char *str, char first, char sec);
int		obj_allcheck(t_scene_data *data, char *line);
void	freesplits(char **tab);
int		ft_count_words(char const *str, char c);
int		im_trash_(char *line);
double	ft_atof(const char *str);
int		is_vector(char *str);
int		is_in_range(char *str, double min, double max);
int		is_vector_is_in_range(char *str, double min, double max);
int		amb_in_range_values(t_amb *amb, char **tab);
int		cam_in_range_values(t_cam *cam, char **tab);
int		light_check_save_all(t_light *lights, char **tab);
int		sphere_check_save_all(t_sp *spheres, char **tab);
int		plane_check_save_all(t_pl *planes, char **tab);
int		cyl_check_save_all(t_cy *cyls, char **tab);
int		obj_nb_check(t_scene_data *data, char **tab);
void	obj_save_data(t_scene_data *data, t_sp *spheres,
			t_pl *planes, t_cy *cylinders);
int		in_range_values(t_scene_data *data, char **tab);
void	init_struct(t_data *rt);
void	init_winrt(t_data *rt);
void	exit_end(t_data *rt);
int		key_hook(int keycode, t_data *rt);
double	vect_prodscal(t_vecto a, t_vecto b);
double	vect_length(t_vecto v);
bool	is_shadowed(t_data *rt, t_inter *hit, t_light *light);
bool	shadow_realm(t_data *rt, t_ray *shadow_ray, double max_dist);
void	magic(t_data *rt, t_ray *ray, int x, int y);
int		raytrace_loop(t_data *rt);
void	pixeldraw(t_img *img, int mlx_color, int x, int y);
int		convert_color(t_vecto *color);
void	exit_err(int errcode);
void	free_exit(t_data *rt);
double	interfind_cy_base(t_cy *cylinder, t_ray *ray, t_vecto center);
void	init_inter(t_inter *inter);
double	gamma_correct(double color, double gamma);
void	inter_base_set(double basedist, t_cy *cylinder,
			t_inter *inter, bool n);
void	fill_cyls(char **cyl_tab, int cylnb, t_cy *cyls);
void	get_me_out_of_this_project(t_inter *inter,
			t_cy *cylinder, double sol1);
double	solution_cy(t_eq *eq);
void	interfind_cy_norm_body(t_cy *cylinder, t_inter *inter);
void	update_close_hit(t_inter *close_hit, t_inter hit, double *ray_max);
int		moving(int keycode, t_data *rt);
void	rotate_vertical(t_data *rt, double angle);
void	rotate_horizontal(t_data *rt, double angle);
void	move_orientation(t_data *rt, double angle_h, double angle_v);
void	move_left_right(t_data *rt, int direction);
void	move_forward_back(t_data *rt, int direction);
int		parsedumbshit(char *line, char *elem);
int		multiple_single_msg(int cam, int amb);

t_vecto	normalize_vector(t_vecto vector);
t_vecto	vect_product(t_vecto a, t_vecto b);
t_vecto	vect_add(t_vecto a, t_vecto b);
t_vecto	vect_substract(t_vecto a, t_vecto b);
t_vecto	vect_scale(t_vecto v, double scalaire);
t_vecto	add_color(t_vecto a, t_vecto b);
t_vecto	light_candles(t_data *rt, t_inter *hit);
t_vecto	light_calculations(t_inter *hit, t_light *light, t_vecto origin);
t_inter	interfind_cy(t_ray *ray, t_cy *cylinder);
t_eq	eq_members_cy(t_ray *ray, t_cy *cylinder);
t_inter	interfind_pl(t_ray *ray, t_pl *plane);
t_eq	eq_members_pl(t_ray *ray, t_pl *plane);
t_inter	interfind_sp(t_ray *ray, t_sp *sphere);
t_eq	eq_members_sp(t_ray *ray, t_sp *sphere);
t_inter	ray_closest_inter(t_data *rt, t_ray *ray, int x, int y);
t_inter	interfind_cy_body(t_eq *eq, t_cy *cylinder, t_ray *ray);
t_vecto	coloramb_(t_amb *amb, t_vecto *objcol);
t_vecto	rotate_vector(t_vecto v, t_vecto axis, double angle);
t_vecto	mat_plane(t_ldata data, t_inter *hit, t_light *light);
t_elem	*elems(void);
t_vecto	phong_figures(t_ldata data, t_inter *hit,
			t_light *light, t_vecto origin);
t_ldata	ldata_fill(t_inter *hit, t_light *light, t_vecto origin);
t_vecto	fill_vect(char *vect);

#endif