#include <libft.h>
#include <math.h>

double	ft_atof(char *str)
{
	double	res;
	int		i;

	res = 0.0;
	res += ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	if (*str)
		str++;
	i = 1;
	while (ft_isdigit(*str))
		res += (double)(*(str++) - '0') / pow(10, i++);
	return (res);
}