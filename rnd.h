#ifndef RND_H
# define RND_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "./libft/gnl/get_next_line.h"

# define D2R (M_PI / 180.0)
# define WID 1440
# define LEN 855
# define SIDEBAR_LEN (WID / 4)
# define MIDX ((WID - SIDEBAR_LEN) / 2.0)
# define MIDY (LEN / 2.0)
# define NODE_RAD 10.0
# define GRAPH_RAD ((MIDX < MIDY) ? MIDX : MIDY) * (0.95);
# define BUTTON_RAD 10.0
# define STAT_WID (SIDEBAR_LEN * 8 / 10)
# define STAT_LEN 15
# define CONNECTION_THRESHOLD 5
# define FEATURES 7

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_img
{
	void			*ptr;
	char			*data_addr;
	int				bpp;
	int				line_size;
	int				endian;
}					t_img;

typedef struct		s_song
{
	double			x;
	double			y;
	char			*title;
	char			*artist;
	char			*album;
	int				genre;
	double			num;
	double			acousticness;
	double			danceability;
	double			energy;
	double			instrumentalness;
	double			loudness;
	double			speechiness;
	double			tempo;
	double			valence;
	double			stat_scale;
}					t_song;

typedef struct		s_user
{
	double			acousticness;
	double			danceability;
	double			energy;
	double			instrumentalness;
	double			loudness;
	double			speechiness;
	double			tempo;
	double			valence;
	double			stat_scale;	
}					t_user;

typedef struct		s_connection
{
	t_song			*s1;
	t_song			*s2;
	int				strength;
}					t_connection;

typedef struct		s_data
{
	int				num_songs;
	int				num_connections;
	t_song			**songs;
	t_connection	**connections;
}					t_data;

typedef struct 		s_options
{
	double			graph_rad;
	double			node_rad;
	int				autorotate;	//for autorotation
	double			degree;		//for autorotation		stored separate so we 'pause' rotation when autorotate is 0
	double			offset;
	double 			brightness;	//for pulsing connections
	int				auto_color;	//if 1, set colors based on color_select; else, genre string has set color
	double			mouse_degree;
	int				highlighted_node;
	int				selected_node;
	int				threshold;
	int				sidebar_mode;
	t_point			mouse;
}					t_options;

typedef struct		s_buttons
{
	t_point			settings;
	t_point			songs;
	t_point			user;
	t_point			grad_up;
	t_point			grad_down;
	t_point			nrad_up;
	t_point			nrad_down;
	t_point			thresh_up;
	t_point			thresh_down;
}					t_buttons;

typedef struct		s_menu
{
	int				active;
	int				start_pressed;
	int				recently_played;
	int				discover_weekly;
}					t_menu;

typedef struct		s_rnd
{
	void			*mlx;
	void			*win;
	t_img			*img;
	t_data			*data;
	t_menu			*menu;
	t_options		*opt;
	t_buttons		*btn;
	t_user			*user;
}					t_rnd;

typedef struct 		s_thread
{
	pthread_t		thread_id;
	int				i;
	t_rnd			*rnd;
}					t_thread;


//init
void				free_all(t_rnd *rnd);
t_point				new_point(int x, int y);
t_song				*init_song(void);
t_user				*init_user(void);
t_connection		*init_connection(t_song *s1, t_song *s2, int strength);
t_data				*init_data(int num_songs);
t_menu				*init_menu(void);
t_img				*init_img(void *mlx);
t_rnd				*init_rnd(int ac, char **av);

//event
int					mouse_move(int x, int y, t_rnd *rnd);
int             	mouse_click(int button, int x, int y, t_rnd *rnd);
int					handle_exit(t_rnd *rnd);
int					handle_keys(int key, t_rnd *rnd);

//data
void				read_params(t_rnd *rnd, int ac, char **av);
int					read_data(t_rnd *rnd);
t_data				*menu_data(void);
void				generate_user_stats(t_rnd *rnd);
void				print_song(t_song *song);

//draw
void				img_pixel_put(t_img *img, int x, int y, int color);
void				draw_rectangle(t_img *img, int x, int y, int wid, int len, int color);
void				draw_node(t_rnd *rnd, int x, int y, t_song *song);
void				draw_node_map(t_rnd *rnd, int x, int y);
void				draw_buttons(t_rnd *rnd);
void				draw_sidebar(t_rnd *rnd);
void				render(t_rnd *rnd);

//sidebar
int					check_buttons(t_rnd *rnd, int x, int y);
void				draw_tabs(t_rnd *rnd);
void				draw_text(t_rnd *rnd);

//menu
void				render_menu(t_rnd *rnd);

//view
int					color_select(int color, int num);
int					brightness(int color, int brightness);
double				get_angle_for_node(t_rnd *rnd, double node);
double				get_mouse_degree(t_rnd *rnd, int x, int y);

//connect
void				create_connections(t_rnd *rnd);

#endif
