#include <rnd.h>

int			color_select(int color, int num)
{
	color += num;
	color %= 1536;
	if (color >= 0 && color < 256)
		color = 0xFF0000 + (color << 8);
	else if (color >= 256 && color < 512)
		color = 0xFFFF00 - ((color % 256) << 16);
	else if (color >= 512 && color < 768)
		color = 0x00FF00 + ((color % 256));
	else if (color >= 512 && color < 1024)
		color = 0x00FFFF - ((color % 256) << 8);
	else if (color >= 512 && color < 1280)
		color = 0x0000FF + ((color % 256) << 16);
	else if (color >= 512 && color < 1536)
		color = 0xFF00FF - ((color % 256));
	return (color);
}

int			brightness(int color, int brightness)
{
	int	r;
	int	g;
	int	b;

	if (brightness > 100)
		brightness = 100 - brightness % 100;
	//printf("\tbrightness = %d\n",brightness);
	r = (color & 0xff0000) >> 16;
	g = (color & 0xff00) >> 8;
	b = color & 0xff;
	r = r * brightness / 100;
	g = g * brightness / 100;
	b = b * brightness / 100;
	return ((r << 16) + (g << 8) + b);
}

double		get_angle_for_node(t_rnd *rnd, double node)
{
	return (node / rnd->data->num_songs * 360);
}

double		get_mouse_degree(t_rnd *rnd, int x, int y)
{
	int deg;

	(void)rnd;
	deg = (int)((atan2(y - MIDY,x - MIDX) / D2R + 360)) % 360;
	return (deg);
}