#include <rnd.h>

void			img_pixel_put(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < WID && y >= 0 && y < LEN)
		*(int *)(img->data_addr + ((x + y * WID) * img->bpp)) = color;
}

void                    draw_line(t_rnd *rnd, double x1, double y1, double x2, double y2, int color)
{
        double          d[2];
        double          x;
        double          y;
        double          inc;

        d[0] = (x2 - x1);
        d[1] = (y2 - y1);
        inc = (fabs(d[0]) > fabs(d[1])) ? fabs(d[0]) : fabs(d[1]);
        x = x1;
        y = y1;
        while (fabs(x - x2) >= 1 || fabs(y - y2) >= 1)
        {
        	img_pixel_put(rnd->img, (int)x, (int)y, color);
			x += (d[0] / inc);
			y += (d[1] / inc);
        }
}

//Less efficient, but avoids any gaps, at least for 500 radius circle 
void			draw_circle(t_img *img, int x, int y, double rad, int color)
{
	double	i;
	double	degree;
	int		dx;
    int		dy;		
	int		prev_x;
	int		prev_y;

	i = 0;
	degree = i * D2R;
	prev_x = cos(degree) * rad;
	prev_y = sin(degree) * rad;
	img_pixel_put(img, prev_x + x, prev_y + y, color);
	i += 0.01;
	while (i < 360)
	{
		degree = i * D2R;
		dx = cos(degree) * rad;
		dy = sin(degree) * rad;
		if (dx != prev_x || dy != prev_y)
		{
			img_pixel_put(img, dx + x, dy + y, color);
			prev_x = x;
			prev_y = y;
		}
		i += 0.01;
	}
}

void			connect_straight(t_rnd *rnd, t_connection *con)
{
	double		dx;
	double		dy;
	double		dc[3];
	double		x;
	double		y;
	double		c[3];
	double		inc;
	int			color1;
	int			color2;

	dx = (con->s2->x - con->s1->x);
	dy = (con->s2->y - con->s1->y);
	if (((con->s1->num == rnd->opt->selected_node) || (con->s1->num == rnd->opt->highlighted_node)) && ((con->s2->num == rnd->opt->selected_node) || (con->s2->num == rnd->opt->highlighted_node)))
	{
		color1 = con->s1->genre;
		color2 = con->s2->genre;
	}
	else
	{
		color1 = brightness(con->s1->genre, ((double)con->strength - rnd->opt->threshold) / (FEATURES - rnd->opt->threshold) * 100);
		color2 = brightness(con->s2->genre, ((double)con->strength - rnd->opt->threshold) / (FEATURES - rnd->opt->threshold) * 100);
	}
	dc[0] = (color2 & 0xff) - (color1 & 0xff);
	dc[1] = ((color2 & 0xff00) >> 8) - ((color1 & 0xff00) >> 8);
	dc[2] = ((color2 & 0xff0000) >> 16) - ((color1 & 0xff0000) >> 16);
	inc = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	x = con->s1->x;
	y = con->s1->y;
	c[0] = color1 & 0xff;
	c[1] = (color1 & 0xff00) >> 8;
	c[2] = (color1 & 0xff0000) >> 16;
	while (fabs(x - con->s2->x) >= 1 || fabs(y - con->s2->y) >= 1)
	{
		if (sqrt(pow((con->s1->x - x), 2) + pow((con->s1->y - y), 2)) > NODE_RAD + 1 &&
			sqrt(pow((con->s2->x - x), 2) + pow((con->s2->y - y), 2)) > NODE_RAD + 1 &&
			*(int *)(rnd->img->data_addr + (((int)x + (int)y * WID) * rnd->img->bpp)) == 0)
		img_pixel_put(rnd->img, (int)x, (int)y, ((int)(c[2] * 65536) & 0xff0000) + ((int)(c[1] * 256) & 0xff00) + c[0]);
		x += (dx / inc);
		y += (dy / inc);
		c[0] += (dc[0] / inc);
		c[1] += (dc[1] / inc);
		c[2] += (dc[2] / inc);
	}
}

void		connect_bezier(t_rnd *rnd, t_connection *con)
{
	int 	color1;
	int 	color2;
	int		color;
	double	c[3];
	double	dc[3];
	double	num;
	double	degree;
	t_point	anchor;
	t_point	curve;
	double	t;

	if (((con->s1->num == rnd->opt->selected_node) || (con->s1->num == rnd->opt->highlighted_node)) && ((con->s2->num == rnd->opt->selected_node) || (con->s2->num == rnd->opt->highlighted_node)))
	{
		color1 = con->s1->genre;
		color2 = con->s2->genre;
	}
	else
	{
		color1 = brightness(con->s1->genre, ((double)con->strength - rnd->opt->threshold) / (FEATURES - rnd->opt->threshold) * 100);
		color2 = brightness(con->s2->genre, ((double)con->strength - rnd->opt->threshold) / (FEATURES - rnd->opt->threshold) * 100);
	}
	dc[0] = (color2 & 0xff) - (color1 & 0xff);
	dc[1] = ((color2 & 0xff00) >> 8) - ((color1 & 0xff00) >> 8);
	dc[2] = ((color2 & 0xff0000) >> 16) - ((color1 & 0xff0000) >> 16);
	c[0] = color1 & 0xff;
	c[1] = (color1 & 0xff00) >> 8;
	c[2] = (color1 & 0xff0000) >> 16;
	if (con->s2->num - con->s1->num < con->s1->num + rnd->data->num_songs - con->s2->num)
		num = con->s1->num + (con->s2->num - con->s1->num) / 2;
	else
		num = con->s2->num + (con->s1->num + rnd->data->num_songs - con->s2->num) / 2;
	num = num + rnd->data->num_songs / 2;
	if (num >= rnd->data->num_songs)
		num -= rnd->data->num_songs;
	degree = get_angle_for_node(rnd, num) + rnd->opt->degree;
	anchor.x = (rnd->opt->graph_rad * cos(degree * D2R)) + MIDX;
	anchor.y = (rnd->opt->graph_rad * sin(degree * D2R)) + MIDY;
	t = 0;
	while (t < 1)
	{
		curve.x = (1 - t) * (1 - t) * con->s1->x + 2 * (1 - t) * t * anchor.x + t * t * con->s2->x;
		curve.y = (1 - t) * (1 - t) * con->s1->y + 2 * (1 - t) * t * anchor.y + t * t * con->s2->y;
		color = *(int *)(rnd->img->data_addr + (((int)curve.x + (int)curve.y * WID) * rnd->img->bpp));
		if (sqrt(pow(con->s1->x - curve.x, 2) + pow(con->s1->y - curve.y, 2)) > rnd->opt->node_rad + 0.5 &&
			sqrt(pow(con->s2->x - curve.x, 2) + pow(con->s2->y - curve.y, 2)) > rnd->opt->node_rad + 0.5 &&
			 ((color & 0xff0000) >> 16) + ((color & 0x00ff00) >> 8) + (color & 0x0000ff) < c[0] + c[1] + c[2])
		img_pixel_put(rnd->img, curve.x, curve.y, ((int)(c[2] * 65536) & 0xff0000) + ((int)(c[1] * 256) & 0xff00) + c[0]);
		c[0] += (dc[0] * 0.001);
		c[1] += (dc[1] * 0.001);
		c[2] += (dc[2] * 0.001);
		t += 0.001;
	}
}

void		draw_connection(t_rnd *rnd, t_connection *con, int offset)
{

	(void)offset;
	if (con->s2->num - con->s1->num == rnd->data->num_songs / 2)
		connect_straight(rnd, con);
	else
		connect_bezier(rnd, con);
}

void		draw_node(t_rnd *rnd, int x, int y, t_song *song)
{
	int		color;
	int		node_num;
	double	i;
	double	r;
	double	degree;

	song->x = x;
	song->y = y;
	node_num = (rnd->opt->selected_node == -1) ? rnd->opt->highlighted_node : rnd->opt->selected_node;
	color = (node_num != -1 && rnd->opt->highlighted_node != song->num && rnd->opt->selected_node != song->num) ? brightness(song->genre, 50) : song->genre;
	r = rnd->opt->node_rad;
	i = 0;
	while (i < 360)
	{
		degree = i * D2R;
		img_pixel_put(rnd->img, (cos(degree) * r) + x, (sin(degree) * r) + y, color);
		i++;
	}
}

void		draw_node_map(t_rnd *rnd, int x, int y)
{
	int	i;
	double	degree;

	i = 0;
	while (i < rnd->data->num_songs)
	{
		degree = get_angle_for_node(rnd, i) + rnd->opt->degree;
		draw_node(rnd, (cos(degree * D2R) * rnd->opt->graph_rad) + x, (sin(degree * D2R) * rnd->opt->graph_rad) + y, rnd->data->songs[i]);
		i++;
	}
}

void		draw_stat(t_rnd *rnd, int x, int y, int len, double stat, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < stat * 500)
		{
			img_pixel_put(rnd->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void			*draw_connections(void *arg)
{
	t_rnd	*rnd;
	int		i;
	int		node_num;

	rnd = (t_rnd *)((t_thread *)arg)->rnd;
	i = ((t_thread *)arg)->i;
	node_num = (rnd->opt->selected_node == -1) ? rnd->opt->highlighted_node : rnd->opt->selected_node;
	if (node_num == -1)
	{
		while (i < rnd->data->num_connections)
		{
			if (rnd->data->connections[i]->strength > rnd->opt->threshold)
				draw_connection(rnd, rnd->data->connections[i], i);
			i += 8;
		}
	}
	else
	{
		while (i < rnd->data->num_connections)
		{
			if (rnd->data->connections[i]->strength > rnd->opt->threshold && (rnd->data->connections[i]->s1->num == node_num || rnd->data->connections[i]->s2->num == node_num))
				draw_connection(rnd, rnd->data->connections[i], i);
			i += 8;
		}
	}
	return (NULL);
}

void			draw_sidebar(t_rnd *rnd)
{
	int		x;
	int		y;

	y = 0;
	while (y < LEN)
	{
			x = WID - SIDEBAR_LEN;
			while (x < WID)
				img_pixel_put(rnd->img, x++, y, 0x373737);
			y++;
	}
}

void			draw_song_template(t_rnd *rnd, int x, int y)
{
	mlx_string_put(rnd->mlx, rnd->win, x, y, 0x999999, "Song: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 50, 0x999999, "Album: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 100, 0x999999, "Artist: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 160, 0x999999, "A: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 185, 0x999999, "D: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 210, 0x999999, "E: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 235, 0x999999, "I: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 260, 0x999999, "L: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 285, 0x999999, "S: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 310, 0x999999, "T: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 335, 0x999999, "V: ");
}

void			draw_song_info(t_rnd *rnd, t_song *s, int x, int y)
{
	mlx_string_put(rnd->mlx, rnd->win, x, y, 0xffffff, s->title);
	mlx_string_put(rnd->mlx, rnd->win, x, y + 50, 0xffffff, s->album);
	mlx_string_put(rnd->mlx, rnd->win, x, y +100, 0xffffff, s->artist);
	mlx_string_put(rnd->mlx, rnd->win, x + 10, y + 135, 0xffffff, ft_itoa((int)(s->acousticness * 100)));
	mlx_string_put(rnd->mlx, rnd->win, x + 10, y + 160, 0xffffff, ft_itoa((int)(s->danceability * 100)));
	mlx_string_put(rnd->mlx, rnd->win, x + 10, y + 185, 0xffffff, ft_itoa((int)(s->energy * 100)));
	mlx_string_put(rnd->mlx, rnd->win, x + 10, y + 210, 0xffffff, ft_itoa((int)(s->instrumentalness * 100)));
	mlx_string_put(rnd->mlx, rnd->win, x + 10, y + 235, 0xffffff, ft_itoa((int)(s->loudness)));
	mlx_string_put(rnd->mlx, rnd->win, x + 10, y + 260, 0xffffff, ft_itoa((int)(s->speechiness * 100)));
	mlx_string_put(rnd->mlx, rnd->win, x + 10, y + 285, 0xffffff, ft_itoa(s->tempo));
	mlx_string_put(rnd->mlx, rnd->win, x + 10, y + 310, 0xffffff, ft_itoa((int)(s->valence * 100)));
}

void			draw_info(t_rnd *rnd)
{
	int		node_num;

	//draw_stat(rnd, 0, 10, 20, rnd->data->songs[rnd->opt->selected_node]->valence, 0x22ee00);
	//mlx_put_image_to_window(rnd->mlx, rnd->win, rnd->img->ptr, 0, 0);
	node_num = (rnd->opt->selected_node == -1) ? rnd->opt->highlighted_node : rnd->opt->selected_node;
	mlx_string_put(rnd->mlx, rnd->win, WID - (SIDEBAR_LEN / 2) - 15, 5, 0xffffff, "ReND");
	draw_song_template(rnd, WID - SIDEBAR_LEN + 10, 20);
	if (node_num > -1)
		draw_song_info(rnd, rnd->data->songs[node_num], WID - SIDEBAR_LEN + 25, 45);
	if (rnd->opt->highlighted_node > -1 && rnd->opt->highlighted_node != node_num)
	{
		draw_song_template(rnd, WID - SIDEBAR_LEN + 10, 400);
		draw_song_info(rnd, rnd->data->songs[rnd->opt->highlighted_node], WID - SIDEBAR_LEN + 25, 425);
	}
}

void			check_mouse(t_rnd *rnd)
{
	int		i;
	double	degree;
	double	x;
	double	y;

	rnd->opt->highlighted_node = -1;
	i = 0;
	while (i < rnd->data->num_songs)
	{
		degree = get_angle_for_node(rnd, i) + rnd->opt->degree;
		x = (cos(degree * D2R) * rnd->opt->graph_rad) + MIDX;
		y = (sin(degree * D2R) * rnd->opt->graph_rad) + MIDY;
		if (sqrt(pow((x - rnd->opt->mouse_x), 2) + pow((y - rnd->opt->mouse_y), 2)) < rnd->opt->node_rad + 1)
			rnd->opt->highlighted_node = i;
		i++;
	}
	if (rnd->opt->selected_node != -1 && /*rnd->opt->highlighted_node == -1 &&*/ 
		sqrt(pow((rnd->opt->mouse_x - MIDX), 2) + pow((rnd->opt->mouse_y - MIDY), 2)) < rnd->opt->graph_rad + 1)
		rnd->opt->highlighted_node = (int)((rnd->opt->mouse_degree / 360 * rnd->data->num_songs) - (rnd->opt->degree / 360 * rnd->data->num_songs)) +rnd->data->num_songs % rnd->data->num_songs;
}

void			render(t_rnd *rnd)
{
	t_thread		list[8];
	int				i;

	free(rnd->img);
	rnd->img = init_img(rnd->mlx);
	check_mouse(rnd);
	draw_sidebar(rnd);
	draw_node_map(rnd, MIDX, MIDY);
	i = 0;
	while (i < 8)
	{
		list[i].i = i;
		list[i].rnd = rnd;
		pthread_create(&(list[i]).thread_id, NULL, draw_connections, &list[i]);
		i++;
	}
	i = 0;
	while (i < 8)
		pthread_join(list[i++].thread_id, NULL);
	mlx_put_image_to_window(rnd->mlx, rnd->win, rnd->img->ptr, 0, 0);
	draw_info(rnd);
}

void			render_menu(t_rnd *rnd)
{
	//t_thread		list[8];
	//int				i;

	free(rnd->img);
	rnd->img = init_img(rnd->mlx);
	draw_node_map(rnd, WID / 2, LEN / 2);
	mlx_put_image_to_window(rnd->mlx, rnd->win, rnd->img->ptr, 0, 0);
	if (rnd->menu->start_pressed)
	{
		mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 15, (LEN / 2) - 80, 0xffffff, "ReND");
		mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 200, (LEN / 2) - 50, 0x999999, "Select options and push [Space] to continue");
		mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 70, (LEN / 2) - 20, (rnd->menu->recently_played) ? 0x00ff00 : 0xff0000, "1) Recently Played");
		mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 70, (LEN / 2), (rnd->menu->discover_weekly) ? 0x00ff00 : 0xff0000, "2) Discover Weekly");
		mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 70, (LEN / 2) + 20, 0xff0000, "3) Add Album");
	}
	else
		mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 15, LEN / 2, brightness(0xffffff, fabs(rnd->opt->brightness)), "ReND");
}
