#include <rnd.h>

void			img_pixel_put(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < WID && y >= 0 && y < LEN)
		*(int *)(img->data_addr + ((x + y * WID) * img->bpp)) = color;
}

void			draw_circle(t_img *img, int x, int y, double rad, int color)
{
	int	i;
	double	degree;
	double	d2r;

	d2r = M_PI / 180;
	i = 0;
	while (i < 360)
	{
		degree = i * d2r;
		img_pixel_put(img, (cos(degree) * rad) + x, (sin(degree) * rad) + y, color);
		i++;
	}
}

void			connect_straight(t_rnd *rnd, t_point p1, t_point p2, int color1, int color2)
{
	double		dx;
	double		dy;
	double		dc[3];
	double		x;
	double		y;
	double		c[3];
	double		inc;

	dx = (p2.x - p1.x);
	dy = (p2.y - p1.y);
	//printf("c1: %x, 0: %x, 1: %x, 2: %x\n", color1, (color1 & 0xff), (color1 & 0xff00) >> 8, (color1 & 0xff0000) >> 16);
	//printf("c2: %x, 0: %x, 1: %x, 2: %x\n", color2, (color2 & 0xff), (color2 & 0xff00) >> 8, (color2 & 0xff0000) >> 16);
	dc[0] = (color2 & 0xff) - (color1 & 0xff);
	dc[1] = ((color2 & 0xff00) >> 8) - ((color1 & 0xff00) >> 8);
	dc[2] = ((color2 & 0xff0000) >> 16) - ((color1 & 0xff0000) >> 16);
	//printf("0:%d 1:%d 2:%d\n", (int)dc[0], (int)dc[1], (int)dc[2]);
	inc = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	x = p1.x;
	y = p1.y;
	c[0] = color1 & 0xff;
	c[1] = (color1 & 0xff00) >> 8;
	c[2] = (color1 & 0xff0000) >> 16;
	while (fabs(x - p2.x) >= 1 || fabs(y - p2.y) >= 1)
	{
		//printf("c = %x\n", (int)(c[2] * 65536) & 0xff0000, (int)(c[1] * 256) & 0xff00, (int)c[0]);
		if (sqrt(pow((p1.x - x), 2) + pow((p1.y - y), 2)) > NODE_RAD + 1 &&
			sqrt(pow((p2.x - x), 2) + pow((p2.y - y), 2)) > NODE_RAD + 1)
		img_pixel_put(rnd->img, (int)x, (int)y, ((int)(c[2] * 65536) & 0xff0000) + ((int)(c[1] * 256) & 0xff00) + c[0]);
		x += (dx / inc);
		y += (dy / inc);
		c[0] += (dc[0] / inc);
		c[1] += (dc[1] / inc);
		c[2] += (dc[2] / inc);
	}
}

void		connect_curve(t_rnd *rnd, t_point p1, t_point p2, int color1, int color2, int num1, int num2)
{
	t_point	midpoint;
	t_point	curve;
	double	degree;
	double	thetamin;
	double	thetamax;
	double	d2r;
	double	rad;
	double	i;

	(void)p1;
	(void)p2;
	(void)color1;
	(void)color2;
	d2r = M_PI / 180;
	degree = ((num1 + num2) / 2.0 * 360 / rnd->data->num_songs) + rnd->opt->degree;
	midpoint.x = (cos(degree * d2r) * (rnd->opt->rad + abs(num1 - num2) * 100)) + WID / 2;
	midpoint.y = (sin(degree * d2r) * (rnd->opt->rad + abs(num1 - num2) * 100)) + LEN / 2;
	rad = sqrt(pow((midpoint.x - p1.x), 2) + pow((midpoint.y - p1.y), 2));
	thetamin = (acos((p1.x - midpoint.x) / rad)) / d2r;
	//printf("p1.x = %d, thetamin = %f, calculated p1.x = %f\n", p1.x, thetamin, cos(thetamin * d2r) * rad + midpoint.x);
	thetamax = (acos((p2.x - midpoint.x) / rad)) / d2r;
	//img_pixel_put(rnd->img, cos(thetamin * d2r) + midpoint.x, sin(thetamin) + midpoint.y, 0x00ff00);
	//img_pixel_put(rnd->img, cos(thetamax  *d2r) + midpoint.x, curve.y + midpoint.y, 0x00ff00);
	i = (thetamin < thetamax) ? thetamin : thetamin;
	while (i < 360)
	{
		degree = (i * d2r) + rnd->opt->degree;
		curve.x = cos(degree) * rad;
		curve.y = sin(degree) * rad;
		if (sqrt(pow(((WID / 2) - (curve.x + midpoint.x)), 2) + pow(((LEN / 2) - (curve.y + midpoint.y)), 2)) < rnd->opt->rad)
			img_pixel_put(rnd->img, curve.x + midpoint.x, curve.y + midpoint.y, 0xffffff);
		i += 1;
	}
}

/*void		connect_curve(t_rnd *rnd, t_point p1, t_point p2, int color1, int color2, int num1, int num2)
{
	int		i;
	double	degree;
	int		smaller;
	double		d2r;
	
	(void)p1;
	(void)p2;
	(void)color1;
	(void)color2;
	i = 0;
	d2r = M_PI / 180;
	smaller = (num1 < num2) ? num1 : num2;
	while (i < abs(num1 - num2) * 360 / rnd->data->num_songs)
	{
		degree = (i + (smaller * 360 / rnd->data->num_songs) + rnd->opt->degree)  * d2r;
		img_pixel_put(rnd->img, WID / 2 + pow(cos(degree), 3) * rnd->opt->rad, LEN / 2 + pow(sin(degree), 3) * rnd->opt->rad, 0xffffff);
		i++;
	}
}*/

void		draw_connection(t_rnd *rnd, t_connection *con, int offset)
{
	t_point		p1;
	t_point		p2;
	double		degree;
	double		d2r;

	(void)offset;
	d2r = M_PI / 180;
	degree =(con->s1->num * 360 / rnd->data->num_songs) + rnd->opt->degree;
	p1.x = (cos(degree  * d2r) * rnd->opt->rad) + WID/2;
	p1.y = (sin(degree * d2r) * rnd->opt->rad) + LEN/2;
	degree =(con->s2->num * 360 / rnd->data->num_songs) + rnd->opt->degree;
	p2.x = (cos(degree * d2r) * rnd->opt->rad) + WID/2;
	p2.y = (sin(degree * d2r) * rnd->opt->rad) + LEN/2;
	connect_straight(rnd, p1, p2, brightness(con->s1->genre, con->strength), brightness(con->s2->genre, con->strength));
	//connect_curve(rnd, p1, p2, brightness(con->s1->genre, fabs(rnd->opt->brightness + offset)), brightness(con->s2->genre, fabs(rnd->opt->brightness + offset)), con->s1->num, con->s2->num);
}

void		draw_node(t_rnd *rnd, int x, int y, t_song *song)
{
	int	i;
	int	r;
	double	degree;
	double	d2r;

	r = NODE_RAD;
	d2r = M_PI / 180;
	i = 0;
	while (i < 360)
	{
		degree = i * d2r;
		img_pixel_put(rnd->img, (cos(degree) * r) + x, (sin(degree) * r) + y, song->genre);
		i++;
	}
	if (sqrt(pow((x - rnd->opt->mouse_x), 2) + pow((y - rnd->opt->mouse_y), 2)) < NODE_RAD + 1)
		rnd->opt->selected_node = song->num;
}

//void		draw_node_map(t_rnd *rnd, int x, int y, double r)
void		*draw_node_map(void *arg)
{
	t_rnd	*rnd;
	int	i;
	double	degree;
	double	d2r;

	rnd = (t_rnd *)((t_thread *)arg)->rnd;
	d2r = M_PI / 180;
	i = 0;
	rnd->opt->selected_node = -1;
	while (i < rnd->data->num_songs)
	{
		degree = (i * 360 / rnd->data->num_songs) + rnd->opt->degree;
		//printf("degree = %f, x = %f, y = %f\n", degree, (cos(degree * d2r) * r) + x, (sin(degree * d2r) * r) + y);
		draw_node(rnd, (cos(degree * d2r) * rnd->opt->rad) + MIDX, (sin(degree * d2r) * rnd->opt->rad) + MIDY, rnd->data->songs[i]);
		i++;
	}
	return (NULL);
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

void			draw_connections(t_rnd *rnd)
{
	int		i;

	rnd->img = init_img(rnd->mlx);
	//draw_node_map(rnd, WID / 2, LEN / 2, rnd->opt->rad, rnd->data);
	i = 0;
	if (rnd->opt->selected_node == -1)
	{

		while (i < rnd->data->num_connections)
		{
			draw_connection(rnd, rnd->data->connections[i], i);
			i++;
		}
	}
	else
	{
		while (i < rnd->data->num_connections)
		{
			if (rnd->data->connections[i]->s1->num == rnd->opt->selected_node ||
				rnd->data->connections[i]->s2->num == rnd->opt->selected_node)
				draw_connection(rnd, rnd->data->connections[i], i);
			i++;
		}
	}
	
}

void			draw_info(t_rnd *rnd)
{
	//draw_stat(rnd, 0, 10, 20, rnd->data->songs[rnd->opt->selected_node]->valence, 0x22ee00);
	//mlx_put_image_to_window(rnd->mlx, rnd->win, rnd->img->ptr, 0, 0);
	mlx_string_put(rnd->mlx, rnd->win, 10, LEN - 80, 0xffffff, "Song: ");
	mlx_string_put(rnd->mlx, rnd->win, 70, LEN - 80, 0xffffff, rnd->data->songs[rnd->opt->selected_node]->title);
	mlx_string_put(rnd->mlx, rnd->win, 10, LEN - 60, 0xffffff, "Album: ");
	mlx_string_put(rnd->mlx, rnd->win, 80, LEN - 60, 0xffffff, rnd->data->songs[rnd->opt->selected_node]->album);
	mlx_string_put(rnd->mlx, rnd->win, 10, LEN - 40, 0xffffff, "Artist: ");
	mlx_string_put(rnd->mlx, rnd->win, 90, LEN - 40, 0xffffff, rnd->data->songs[rnd->opt->selected_node]->artist);
}

void			render(t_rnd *rnd)
{
	t_thread		list[8];
	int				i;
	t_img			*old;

	old = rnd->img;
	rnd->img = init_img(rnd->mlx);
	i = 0;
	while (i < 8)
	{
		list[i].i = i;
		list[i].rnd = rnd;
		if (i == 0)
			pthread_create(&(list[i]).thread_id, NULL, draw_node_map, &list[i]);
		//else
		//	pthread_create(&(list[i]).tid, NULL, draw_connections, &list[i]);
		i++;
	}
	mlx_put_image_to_window(rnd->mlx, rnd->win, rnd->img->ptr, 0, 0);
	//mlx_destroy_image(rnd->mlx, old->ptr);
	free(old);
	if (rnd->opt->selected_node > -1)
		draw_info(rnd);
	mlx_string_put(rnd->mlx, rnd->win, WID/2 - 10, LEN/2 - 10, 0xffffff, "ReND");
}
