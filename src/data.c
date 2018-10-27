#include <rnd.h>

int	read_params(int ac, char **av)
{
	int		i;
	int		rad = GRAPH_RAD;

	i = 1;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-r") == 0 || ft_strcmp(av[i], "--graphradius") == 0)
			rad = ft_atoi(av[++i]);
		else
		{
			if (av[i][0] == '-')
				printf("unrecognized flag '%s', ignoring/...\n", av[i]);
			else
				printf("unexpected command line parameter '%s', ignoring...\n", av[i]);
		}
		i++;
	}
	return (rad);
}

char	*read_word(char **str)
{
	char	*res;
	int		i;

	while (*(*str) == ' ' || *(*str) == '\t' || *(*str) == '"')
		(*str)++;
	i = 0;
	while ((*str)[i] != '"')
		i++;
	res = ft_strnew(i);
	ft_strncpy(res, *str, i);
	(*str) += i + 1;
	return (res);
}

double	read_double(char **str)
{
	double	res;
	int		i;

	while (*(*str) == ' ' || *(*str) == '\t' || *(*str) == '"')
		(*str)++;
	i = 0;
	while ((*str)[i] != '"')
		i++;
	res = ft_atof(*str);
	(*str) += i + 1;
	return (res);
}

t_song	*parse_line(char *line)
{
	t_song *song;
	char	**tmp;

	tmp = &line;
	song = init_song();

	song->title = read_word(tmp);
	song->artist = read_word(tmp);
	song->album = read_word(tmp);
	/*printf("title = '%s'\n", song->title);
	printf("artist = '%s'\n", song->artist);
	printf("album = '%s'\n", song->album);*/
	song->acousticness = read_double(tmp);
	song->danceability = read_double(tmp);
	song->energy = read_double(tmp);
	song->loudness = read_double(tmp);
	song->speechiness = read_double(tmp);
	song->tempo = read_double(tmp);
	song->valence = read_double(tmp);
	/*printf("acousticness = '%f'\n", song->acousticness);
	printf("danceability = '%f'\n", song->danceability);
	printf("energy = '%f'\n", song->energy);
	printf("loudness = '%f'\n", song->loudness);
	printf("speechiness = '%f'\n", song->speechiness);
	printf("tempo = '%f'\n", song->tempo);
	printf("valence = '%f'\n\n", song->valence);*/
	return (song);
}

int		read_data(t_rnd *rnd)
{
	int		num;
	int		fd;
	char	*line;
	t_data	*data;

	//system ("python3 py_scripts/get_tracks.py");
	if ((fd = open("data.txt", O_RDONLY)) == -1)
		return (0);
	num = 0;
	while (get_next_line(fd, &line) > 0)
	{
		num++;
		free(line);
	}
	close(fd);

	data = init_data(num);
	if ((fd = open("data.txt", O_RDONLY)) == -1)
		return (-1);
	num = 0;
	while (get_next_line(fd, &line) > 0)
	{
		data->songs[num] = parse_line(line);
		data->songs[num]->num = num;
		data->songs[num]->genre = color_select(num * 1536 / data->num_songs, 0);
		free(line);
		num++;
	}
	close(fd);
	rnd->data = data;
	return (1);
}