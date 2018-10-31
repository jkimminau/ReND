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
			sqrt(pow((con->s2->x - x), 2) + pow((con->s2->y - y), 2)) > NODE_RAD + 1)
		img_pixel_put(rnd->img, (int)x, (int)y, ((int)(c[2] * 65536) & 0xff0000) + ((int)(c[1] * 256) & 0xff00) + c[0]);
		x += (dx / inc);
		y += (dy / inc);
		c[0] += (dc[0] / inc);
		c[1] += (dc[1] / inc);
		c[2] += (dc[2] / inc);
	}
}

void		connect_curve(t_rnd *rnd, t_connection *con)
{
	t_point	midpoint;
	t_point	curve;
	double	degree;
	double	rad;
	double	i;
	int		color;
	double	theta1;
	double	theta2;

	if (((con->s1->num == rnd->opt->selected_node) || (con->s1->num == rnd->opt->highlighted_node)) && ((con->s2->num == rnd->opt->selected_node) || (con->s2->num == rnd->opt->highlighted_node)))
		color = 0xffffff;
	else
		color = brightness(0xffffff, ((double)con->strength - rnd->opt->threshold) / (FEATURES - rnd->opt->threshold) * 100);
	degree = ((((con->s1->num + con->s2->num) / 2) * 360) / rnd->data->num_songs) + rnd->opt->degree;
	midpoint.x = (rnd->opt->graph_rad * cos(degree * D2R)) /*+ fabs((double)con->s1->num - con->s2->num)*/ + MIDX;
	midpoint.y = (rnd->opt->graph_rad * sin(degree * D2R)) /*+ fabs((double)con->s1->num - con->s2->num)*/ + MIDY;
	rad = sqrt(pow((midpoint.x - con->s1->x), 2) + pow((midpoint.y - con->s1->y), 2));
	//img_pixel_put(rnd->img, midpoint.x,  midpoint.y, 0xffffff);
	theta1 = acos(con->s1->x / rad) / D2R; /// D2R;
	if (theta1 != theta1)
	{
		//printf("? %f\n", con->s1->x / rad);
		theta1 = asin(con->s1->y / rad) / D2R;
	}
	theta2 = acos(con->s2->x / rad) / D2R; /// D2R;
	//printf("theta1: %f, theta2: %f\n", theta1, theta2);
	i = 0;
	//i = thetamin;
	while (i < 360)
	//while (i < thetamax)
	{
		degree = (i * D2R);// + rnd->opt->degree;
		curve.x = cos(degree) * rad;
		curve.y = sin(degree) * rad;
		if (sqrt(pow(((MIDX) - (curve.x + midpoint.x)), 2) + pow(((MIDY) - (curve.y + midpoint.y)), 2)) < rnd->opt->graph_rad &&
			sqrt(pow((con->s1->x - (curve.x + midpoint.x)), 2) + pow((con->s1->y - (curve.y + midpoint.y)), 2)) > rnd->opt->node_rad &&
			sqrt(pow((con->s2->x - (curve.x + midpoint.x)), 2) + pow((con->s2->y - (curve.y + midpoint.y)), 2)) > rnd->opt->node_rad)
			img_pixel_put(rnd->img, curve.x + midpoint.x, curve.y + midpoint.y, color);
		i += 0.1;
	}
}

void		connect_bezier(t_rnd *rnd, t_connection *con)
{
	int 	color1;
	int 	color2;
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
	degree = ((num * 360) / rnd->data->num_songs) + rnd->opt->degree;
	anchor.x = (rnd->opt->graph_rad * cos(degree * D2R)) + MIDX;
	anchor.y = (rnd->opt->graph_rad * sin(degree * D2R)) + MIDY;
	t = 0;
	while (t < 1)
	{
		curve.x = (1 - t) * (1 - t) * con->s1->x + 2 * (1 - t) * t * anchor.x + t * t * con->s2->x;
		curve.y = (1 - t) * (1 - t) * con->s1->y + 2 * (1 - t) * t * anchor.y + t * t * con->s2->y;
		if (sqrt(pow(con->s1->x - curve.x, 2) + pow(con->s1->y - curve.y, 2)) > rnd->opt->node_rad + 0.5 &&
			sqrt(pow(con->s2->x - curve.x, 2) + pow(con->s2->y - curve.y, 2)) > rnd->opt->node_rad + 0.5)
		//img_pixel_put(rnd->img, curve.x, curve.y, ((int)(c[2] * 65536) & 0xff0000) + ((int)(c[1] * 256) & 0xff00) + c[0]);
		img_pixel_put(rnd->img, curve.x, curve.y, (((int)c[2]) << 16) + (((int)c[1]) << 8) + c[0]);
		//img_pixel_put(rnd->img, curve.x, curve.y, color1);
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
	//connect_curve(rnd, con);
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
	//img_pixel_put(rnd->img, x, y, color);
	i = 0;
	while (i < 360)
	{
		degree = i * D2R;
		img_pixel_put(rnd->img, (cos(degree) * r) + x, (sin(degree) * r) + y, color);
		i++;
	}
}

//void		draw_node_map(t_rnd *rnd, int x, int y, double r)
void		draw_node_map(t_rnd *rnd)
{
	int	i;
	double	degree;

	i = 0;
	while (i < rnd->data->num_songs)
	{
		degree = ((double)i * 360 / rnd->data->num_songs) + rnd->opt->degree;
		//printf("degree = %f, x = %f, y = %f\n", degree, (cos(degree * d2r) * r) + x, (sin(degree * d2r) * r) + y);
		draw_node(rnd, (cos(degree * D2R) * rnd->opt->graph_rad) + MIDX, (sin(degree * D2R) * rnd->opt->graph_rad) + MIDY, rnd->data->songs[i]);
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
			{
				img_pixel_put(rnd->img, x, y, 0x373737);
				x++;
			}
			y++;
	}
}

void			draw_info(t_rnd *rnd)
{
	int		node_num;

	//draw_stat(rnd, 0, 10, 20, rnd->data->songs[rnd->opt->selected_node]->valence, 0x22ee00);
	//mlx_put_image_to_window(rnd->mlx, rnd->win, rnd->img->ptr, 0, 0);
	node_num = (rnd->opt->selected_node == -1) ? rnd->opt->highlighted_node : rnd->opt->selected_node;
	mlx_string_put(rnd->mlx, rnd->win, WID - (SIDEBAR_LEN / 2) - 15, 5, 0xffffff, "ReND");
	mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 10, 20, 0x999999, "Song: ");
	mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 10, 70, 0x999999, "Album: ");
	mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 10, 120, 0x999999, "Artist: ");
	mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 11, 180, 0x999999, "Acousticness: ");
	mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 10, 205, 0x999999, "Danceability: ");
	mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 70, 230, 0x999999, "Energy: ");
	mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 50, 255, 0x999999, "Loudness: ");
	mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 19, 280, 0x999999, "Speechiness: ");
	mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 79, 305, 0x999999, "Tempo: ");
	mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 59, 330, 0x999999, "Valence: ");
	if (node_num > -1)
	{
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 25, 45, 0xffffff, rnd->data->songs[node_num]->title);
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 25, 95, 0xffffff, rnd->data->songs[node_num]->album);
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 25, 145, 0xffffff, rnd->data->songs[node_num]->artist);
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 180, 0xffffff, ft_itoa((int)(rnd->data->songs[node_num]->acousticness * 100)));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 205, 0xffffff, ft_itoa((int)(rnd->data->songs[node_num]->danceability * 100)));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 230, 0xffffff, ft_itoa((int)(rnd->data->songs[node_num]->energy * 100)));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 255, 0xffffff, ft_itoa((int)(rnd->data->songs[node_num]->loudness)));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 280, 0xffffff, ft_itoa((int)(rnd->data->songs[node_num]->speechiness * 100)));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 305, 0xffffff, ft_itoa(rnd->data->songs[node_num]->tempo));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 330, 0xffffff, ft_itoa((int)(rnd->data->songs[node_num]->valence * 100)));
	}
	if (rnd->opt->highlighted_node > -1 && rnd->opt->highlighted_node != node_num)
	{
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 10, 360, 0x999999, "Song: ");
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 10, 410, 0x999999, "Album: ");
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 10, 460, 0x999999, "Artist: ");
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 11, 520, 0x999999, "Acousticness: ");
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 10, 545, 0x999999, "Danceability: ");
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 70, 570, 0x999999, "Energy: ");
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 50, 595, 0x999999, "Loudness: ");
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 19, 620, 0x999999, "Speechiness: ");
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 79, 645, 0x999999, "Tempo: ");
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 59, 670, 0x999999, "Valence: ");
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 25, 385, 0xffffff, rnd->data->songs[rnd->opt->highlighted_node]->title);
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 25, 435, 0xffffff, rnd->data->songs[rnd->opt->highlighted_node]->album);
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 25, 485, 0xffffff, rnd->data->songs[rnd->opt->highlighted_node]->artist);
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 520, 0xffffff, ft_itoa((int)(rnd->data->songs[rnd->opt->highlighted_node]->acousticness * 100)));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 545, 0xffffff, ft_itoa((int)(rnd->data->songs[rnd->opt->highlighted_node]->danceability * 100)));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 570, 0xffffff, ft_itoa((int)(rnd->data->songs[rnd->opt->highlighted_node]->energy * 100)));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 595, 0xffffff, ft_itoa((int)(rnd->data->songs[rnd->opt->highlighted_node]->loudness)));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 620, 0xffffff, ft_itoa((int)(rnd->data->songs[rnd->opt->highlighted_node]->speechiness * 100)));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 645, 0xffffff, ft_itoa(rnd->data->songs[rnd->opt->highlighted_node]->tempo));
		mlx_string_put(rnd->mlx, rnd->win, WID - SIDEBAR_LEN + 150, 670, 0xffffff, ft_itoa((int)(rnd->data->songs[rnd->opt->highlighted_node]->valence * 100)));
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
		degree = (i * 360 / rnd->data->num_songs) + rnd->opt->degree;
		x = (cos(degree * D2R) * rnd->opt->graph_rad) + MIDX;
		y = (sin(degree * D2R) * rnd->opt->graph_rad) + MIDY;
		if (sqrt(pow((x - rnd->opt->mouse_x), 2) + pow((y - rnd->opt->mouse_y), 2)) < rnd->opt->node_rad + 1)
			rnd->opt->highlighted_node = i;
		i++;
	}
}

void			render(t_rnd *rnd)
{
	t_thread		list[8];
	int				i;

	free(rnd->img);
	rnd->img = init_img(rnd->mlx);
	check_mouse(rnd);
	draw_sidebar(rnd);
	draw_node_map(rnd);
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
