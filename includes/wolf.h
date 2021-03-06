/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 03:55:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2021/05/15 17:29:37 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "wolfdata.h"
# include <stdint.h>

typedef struct	s_core
{
	void				*mlx;
	void				*win;
	void				*screen;
	char				*img;
	double				time;
	double				oldtime;
	t_world				world;
	t_camera			cam;
	int					socket;
	struct sockaddr_in	sin;
}				t_core;

/*
** ============================================================================
**	EVENTS.....................................................................
** ============================================================================
*/

int				mouse_press(int button, int x, int y, t_core *wolf);
int				mouse_move(int x, int y, t_core *wolf);
int				deal_key(int key, t_core *wolf);
int				check_box(t_camera *cam, t_vector d, t_world *world);

/*
** ============================================================================
**	TOOLS......................................................................
** ============================================================================
*/

void			center_map(int width, int height, int sq_size, int *shift);
t_vector		rotate_vector(t_vector *vector, double angle);
t_vector		set_vec(double x, double y);
void			set_pixel(char *image, int x, int y, int color);
int				quit_wolf(void *wolf);
void			init_camera(t_camera *cam, t_world *world);
int				print_and_quit(char *error);
void			unit(t_vector *dir);
t_vector		get_side_dist(
		t_camera *cam, t_ray *ray, t_vector *delta_dist, int *step);
t_vector		get_delta_dist(t_vector *raydir);

/*
** ============================================================================
**	MAP VISUALIZER.............................................................
** ============================================================================
*/

void			bresenham(t_core *wolf, t_vector one, t_vector two, int color);
void			draw_ray(t_core *wolf, t_vector ray, int color);
void			draw_square(t_core *wolf, int x, int y, int color);
void			draw_map(t_core *wolf, t_ray *ray);
void			map_visualizer(t_core *wolf);

/*
** ============================================================================
**	PARSING....................................................................
** ============================================================================
*/

void			parse_wolf_map(t_core *wolf, t_world *world, char *filename);
void			get_test_textures(t_core *wolf);
int8_t			file_to_texture(
		t_core *wolf, t_world *world, char *file, int tex_i);
int8_t			get_map_properties(t_core *wolf, int fd);
int8_t			get_index(char **array, char *key);
int8_t			set_new_sprite(t_core *wolf, char **prp, char **files
		, int *tex_i);
int				set_new_wall(t_core *wolf, char **properties
		, char **files, int *tex_i);
int				register_new_texture(t_core *wolf, char **prp
		, char **files, int *tex_i);
void			get_world_dimensions(t_world *world, int *array, int fd);
void			get_spawn_coords(t_world *world, int *array, int fd);
int				check_file(char *filename);

/*
** ============================================================================
**	RENDER.....................................................................
** ============================================================================
*/

int				draw_scene(t_core *wolf);
void			floor_ceiling_casting(t_core *wolf);
void			draw_sprites(t_core *wolf, double *z_buffer);
int				get_tex_dir(t_wall *wall, t_ray *ray);
void			intersect(t_core *wolf, t_ray *ray, int *step);
void			get_sprites_dist(t_core *wolf, int *sprite_order);

int8_t			connect_to_server(t_core *wolf, const char *address);
int8_t			send_pos_to_server(t_core *wolf);
int8_t			receive_players_pos(t_core *wolf);

#endif
