#include <rnd.h>

void		free_all(t_rnd *rnd)
{
	mlx_destroy_window(rnd->mlx, rnd->win);
	mlx_destroy_image(rnd->mlx, rnd->img->ptr);
	free(rnd->img);
	while (rnd->data->num_songs)
	{
		rnd->data->num_songs--;
		if (rnd->data->songs[rnd->data->num_songs]->title)
			free(rnd->data->songs[rnd->data->num_songs]->title);
		if (rnd->data->songs[rnd->data->num_songs]->album)
			free(rnd->data->songs[rnd->data->num_songs]->album);
		if (rnd->data->songs[rnd->data->num_songs]->artist)
			free(rnd->data->songs[rnd->data->num_songs]->artist);
		free(rnd->data->songs[rnd->data->num_songs]);
	}
	free(rnd->data->songs);
	while (rnd->data->num_connections)
	{
		rnd->data->num_connections--;
		free(rnd->data->connections[rnd->data->num_connections]);
	}
	free(rnd->data->connections);
	free(rnd->data);
	free(rnd->opt);
	mlx_del(rnd->mlx);
	free(rnd);
}

t_point		new_point(int x, int y)
{
	t_point		point;

	point.x = x;
	point.y = y;
	return (point);
}

t_song		*init_song(void)
{
	t_song	*song;

	if (!(song = (t_song *)malloc(sizeof(t_song))))
		return (NULL);
	song->title = 0;
	song->album = 0;
	song->artist = 0;
	song->stat_scale = 0;
	return (song);
}

t_user			*init_user(void)
{
	t_user	*user;

	if (!(user = (t_user *)malloc(sizeof(t_user))))
		return (NULL);
	user->acousticness = 0;
	user->danceability = 0;
	user->energy = 0;
	user->instrumentalness = 0;
	user->loudness = 0;
	user->speechiness = 0;
	user->tempo = 0;
	user->valence = 0;
	user->stat_scale = 0;
	return (user);
}

t_connection	*init_connection(t_song *s1, t_song *s2, int strength)
{
	t_connection *con;

	con = (t_connection *)malloc(sizeof(t_connection));
	con->s1 = s1;
	con->s2 = s2;
	con->strength = strength;
	return (con);
}

t_data		*init_data(int num_songs)
{
	t_data	*data;
	//int	i;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->num_songs = num_songs;
	data->num_connections = 0;
	if (!(data->songs = (t_song **)malloc(sizeof(t_song *) * num_songs)))
		return (NULL);
	return (data);
}

t_img		*init_img(void *mlx)
{
	t_img	*img;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		return (0);
	if (!(img->ptr = mlx_new_image(mlx, WID, LEN)))
		return (0);
	img->data_addr = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_size, &img->endian);
	img->bpp /= 8;
	return (img);
}

t_options	*init_options(void)
{
	t_options *opt;

	if (!(opt = (t_options *)malloc(sizeof(t_options))))
		return (0);
	opt->autorotate = 1;
	opt->degree = 0;
	opt->brightness = 100;
	opt->graph_rad = GRAPH_RAD;
	opt->node_rad = NODE_RAD;
	opt->mouse_degree = 0;
	opt->highlighted_node = -1;
	opt->selected_node = -1;
	opt->threshold = CONNECTION_THRESHOLD;
	opt->offset = 0;
	opt->sidebar_mode = 1;
	opt->mouse.x = 0;
	opt->mouse.y = 0;
	return (opt);
}

t_buttons	*init_buttons(void)
{
	t_buttons *b;

	if (!(b = (t_buttons *)malloc(sizeof(t_buttons))))
		return (0);
	//draw_rectangle(rnd->img, (WID - SIDEBAR_LEN) + (i * SIDEBAR_LEN / 3) + (SIDEBAR_LEN / 12), 5, SIDEBAR_LEN / 6, 20, 0x999999);
	b->settings.x = (WID - SIDEBAR_LEN) + (SIDEBAR_LEN / 3) - (SIDEBAR_LEN / 4.5);
	b->settings.y = 5;
	b->songs.x = (WID - SIDEBAR_LEN) + (SIDEBAR_LEN / 3) + (SIDEBAR_LEN / 12);
	b->songs.y = 5;
	b->user.x = (WID - SIDEBAR_LEN) + (SIDEBAR_LEN * 2 / 3) + (SIDEBAR_LEN / 12);
	b->user.y = 5;
	b->grad_up.x = WID - SIDEBAR_LEN + 30;
	b->grad_up.y = 120;
	b->grad_down.x = WID - SIDEBAR_LEN + 30;
	b->grad_down.y = 140;
	b->nrad_up.x = WID - SIDEBAR_LEN + 30;
	b->nrad_up.y = 180;
	b->nrad_down.x = WID - SIDEBAR_LEN + 30;
	b->nrad_down.y = 200;
	b->thresh_up.x = WID - SIDEBAR_LEN + 30;
	b->thresh_up.y = 240;
	b->thresh_down.x = WID - SIDEBAR_LEN + 30;
	b->thresh_down.y = 260;
	return (b);
}

t_menu		*init_menu(void)
{
	t_menu	 *menu;

	if (!(menu = (t_menu *)malloc(sizeof(t_menu))))
		return (0);
	menu->active = 1;
	menu->start_pressed = 0;
	menu->recently_played = 1;
	menu->discover_weekly = 0;
	return (menu);
}

t_rnd		*init_rnd(int ac, char **av)
{
	t_rnd	*rnd;

	if (!(rnd = (t_rnd *)malloc(sizeof(t_rnd))))
		return (0);
	if (!(rnd->mlx = mlx_init()))
		return (0);
	if (!(rnd->win = mlx_new_window(rnd->mlx, WID, LEN, "ReND")))
		return (0);
	if (!(rnd->img = init_img(rnd->mlx)))
		return (0);
	if (!(rnd->opt = init_options()))
		return (0);
	if (!(rnd->btn = init_buttons()))
		return (0);
	if (!(rnd->user = init_user()))
		return (0);
	if (!(rnd->menu = init_menu()))
		return (0);
	if (!(rnd->data = menu_data()))
		return (0);
	read_params(rnd, ac, av);
	return (rnd);
}
