#ifndef RND_H
# define RND_H

# define WID 1000
# define LEN 800
# define MIDX WID / 2
# define MIDY LEN / 2
# define NODE_RAD 8.0
# define GRAPH_RAD 350.0
# define FEATURES 7

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "./libft/gnl/get_next_line.h"

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
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
	char			*title;
	char			*artist;
	char			*album;
	int				genre;
	int				num;
	double			acousticness;
	double			danceability;
	double			energy;
	double			loudness;
	double			speechiness;
	double			tempo;
	double			valence;
}					t_song;

typedef struct		s_connection
{
	t_song			*s1;
	t_song			*s2;
	double			strength;
}					t_connection;

typedef struct		s_data
{
	//int				genres;
	int				num_songs;
	int				num_connections;
	t_song			**songs;
	t_connection	**connections;
}					t_data;

typedef struct 		s_options
{
	double			rad;
	int				autorotate;	//for autorotation
	double			degree;		//for autorotation		stored separate so we 'pause' rotation when autorotate is 0
	double 			brightness;	//for pulsing connections
	int				auto_color;	//if 1, set colors based on color_select; else, genre string has set color
	int				mouse_x;
	int				mouse_y;
	int				selected_node;
}					t_options;

typedef struct		s_rnd
{
	void			*mlx;
	void			*win;
	t_img			*img;
	t_data			*data;
	t_options		*opt;
}					t_rnd;

typedef struct 		s_thread
{
	pthread_t		thread_id;
	int				i;
	t_rnd			*rnd;
}					t_thread;

void				free_all(t_rnd *rnd);
t_point				new_point(int x, int y, int z);
t_song				*init_song(void);
t_connection		*init_connection(t_song *s1, t_song *s2, int strength);
t_data				*init_data(int num_songs);
t_img				*init_img(void *mlx);
t_rnd				*init_rnd(double rad);
int					mouse_move(int x, int y, t_rnd *rnd);
int					handle_exit(t_rnd *rnd);
int					handle_keys(int key, t_rnd *rnd);
int					read_params(int ac, char **av);
int					read_data(t_rnd *rnd);
void				img_pixel_put(t_img *img, int x, int y, int color);
void				draw_node(t_rnd *rnd, int x, int y, t_song *song);
void				*draw_node_map(void *arg);
void				draw(t_rnd *rnd);
void				render(t_rnd *rnd);
t_point				project_point(t_rnd *rnd, t_point p);
int					color_select(int color, int num);
int					brightness(int color, int brightness);
int					are_similar(double stat1, double stat2, double min, double max);
void				create_connections(t_rnd *rnd);

#endif
