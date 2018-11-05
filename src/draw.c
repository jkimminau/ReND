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

void					draw_rectangle(t_img *img, int x, int y, int wid, int len, int color)
{
	int 	i;
	int		j;

	i = y;
	while (i < y + len)
	{
		j = x;
		while (j < x + wid)
		{
			if (j == x || j == x + wid - 1 || i == y || i == y + len - 1)
			img_pixel_put(img, j, i, color);
			j++;
		}
		i++;
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
	double	dt;

	dt = 360 / (rad * 5);
	i = 0;
	degree = i * D2R;
	prev_x = cos(degree) * rad;
	prev_y = sin(degree) * rad;
	img_pixel_put(img, prev_x + x, prev_y + y, color);
	i += dt;
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
		i += dt;
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
		color1 = brightness(con->s1->genre, ((double)con->strength - rnd->opt->threshold) / FEATURES * 100);
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
		c[0] += (dc[0] * 0.002);
		c[1] += (dc[1] * 0.002);
		c[2] += (dc[2] * 0.002);
		t += 0.002;
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

void		draw_node(t_rnd *rnd, int x, int y, t_song *song)
{
	int		color;
	int		node_num;
	//double	i;
	double	r;
	//double	degree;

	song->x = x;
	song->y = y;
	node_num = (rnd->opt->selected_node == -1) ? rnd->opt->highlighted_node : rnd->opt->selected_node;
	color = (node_num != -1 && rnd->opt->highlighted_node != song->num && rnd->opt->selected_node != song->num) ? brightness(song->genre, 50) : song->genre;
	r = rnd->opt->node_rad;
	draw_circle(rnd->img, x, y, r, color);
}

void			draw_node_map(t_rnd *rnd, int x, int y)
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

void			draw_buttons(t_rnd *rnd)
{
	draw_circle(rnd->img, rnd->btn->grad_up.x, rnd->btn->grad_up.y, BUTTON_RAD, 0xbbbbbb);
	draw_circle(rnd->img, rnd->btn->grad_down.x, rnd->btn->grad_down.y, BUTTON_RAD, 0xbbbbbb);
	draw_circle(rnd->img, rnd->btn->nrad_up.x, rnd->btn->nrad_up.y, BUTTON_RAD, 0xbbbbbb);
	draw_circle(rnd->img, rnd->btn->nrad_down.x, rnd->btn->nrad_down.y, BUTTON_RAD, 0xbbbbbb);
	draw_circle(rnd->img, rnd->btn->thresh_up.x, rnd->btn->thresh_up.y, BUTTON_RAD, 0xbbbbbb);
	draw_circle(rnd->img, rnd->btn->thresh_down.x, rnd->btn->thresh_down.y, BUTTON_RAD, 0xbbbbbb);
}

void			check_mouse(t_rnd *rnd)
{
	int		i;
	double	degree;
	double	x;
	double	y;
	int		highlight;

	highlight = -1;
	i = 0;
	while (i < rnd->data->num_songs)
	{
		degree = get_angle_for_node(rnd, i) + rnd->opt->degree;
		x = (cos(degree * D2R) * rnd->opt->graph_rad) + MIDX;
		y = (sin(degree * D2R) * rnd->opt->graph_rad) + MIDY;
		if (sqrt(pow((x - rnd->opt->mouse.x), 2) + pow((y - rnd->opt->mouse.y), 2)) < rnd->opt->node_rad + 1)
			highlight = i;
		i++;
	}
	if (rnd->opt->selected_node != -1 && sqrt(pow((rnd->opt->mouse.x - MIDX), 2) + pow((rnd->opt->mouse.y - MIDY), 2)) < rnd->opt->graph_rad + 1)
	{
		degree = rnd->opt->mouse_degree - rnd->opt->degree;
		degree += (degree < 0) ? 360 : 0;
		highlight = (degree / 360 * rnd->data->num_songs) + 0.5;
		if (highlight == rnd->data->num_songs)
			highlight = 0;
	}
	i = 0;
	while (i < rnd->data->num_songs)
	{
		if (rnd->data->songs[i]->num != rnd->opt->selected_node && rnd->data->songs[i]->num != highlight)
			rnd->data->songs[i]->stat_scale = 0;
		i++;
	}
	rnd->opt->highlighted_node = highlight;
}

void			render(t_rnd *rnd)
{
	t_thread		list[8];
	int				i;

	free(rnd->img);
	rnd->img = init_img(rnd->mlx);
	check_mouse(rnd);
	draw_node_map(rnd, MIDX, MIDY);
	draw_sidebar(rnd);
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
	draw_text(rnd);
}
