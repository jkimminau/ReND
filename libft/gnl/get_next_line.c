/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 13:20:29 by jkimmina          #+#    #+#             */
/*   Updated: 2018/03/26 03:59:12 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		shiftbuf(char *buf, int exit)
{
	int		i;
	int		j;

	if (exit == 1)
	{
		ft_bzero(buf, BUFF_SIZE + 1);
		return (1);
	}
	i = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	j = 0;
	while (++i <= BUFF_SIZE && buf[i])
		buf[j++] = buf[i];
	while (j <= BUFF_SIZE)
		buf[j++] = '\0';
	return (1);
}

int		strbeg(char *buf, char **line)
{
	int		s;

	if (!line)
		return (-1);
	if (buf[0] == '\n')
	{
		*line = ft_strdup("");
		shiftbuf(buf, 0);
		return (1);
	}
	s = 0;
	while (buf[s] && buf[s] != '\n')
		s++;
	if (s == 0)
		*line = 0;
	else
		*line = ft_strndup((const char *)buf, (size_t)s);
	if (ft_strstr(buf, "\n"))
		return (shiftbuf(buf, 0));
	return (0);
}

char	*append(char **line, char *buf)
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!*line)
		return (ft_strndup(buf, (size_t)i));
	str2 = ft_strsub(buf, 0, (size_t)i);
	str = ft_strjoin((char const *)*line, (char const *)str2);
	free(*line);
	free(str2);
	return (str);
}

t_gnl	*init(t_list **list, const int fd)
{
	t_list		*node;
	t_gnl		*new;

	if (*list)
	{
		node = *list;
		while (node != 0)
		{
			if ((((t_gnl *)(node->content))->fd) == fd)
				return ((t_gnl *)(node->content));
			node = node->next;
		}
	}
	while (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
		return (0);
	ft_bzero(new->buf, BUFF_SIZE + 1);
	new->fd = fd;
	node = ft_lstnew(new, sizeof(t_gnl));
	free(new);
	ft_lstadd(list, node);
	return ((t_gnl *)node->content);
}

int		get_next_line(const int fd, char **line)
{
	int				ret;
	static t_list	*list;
	t_gnl			*ptr;

	ptr = init(&list, fd);
	if ((ret = strbeg(ptr->buf, line)) != 0)
		return (ret);
	while ((ret = read(fd, ptr->buf, BUFF_SIZE)))
	{
		if (ret < 0 || fd < 0)
			return (-1);
		ptr->buf[ret] = '\0';
		*line = append(line, ptr->buf);
		if (ft_strstr(ptr->buf, "\n"))
			return (shiftbuf(ptr->buf, 0));
	}
	if (*line)
		return (shiftbuf(ptr->buf, 1));
	return (0);
}
