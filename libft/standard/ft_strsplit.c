/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:49:49 by jkimmina          #+#    #+#             */
/*   Updated: 2018/02/25 00:45:36 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	countwords(char const *s, char c)
{
	int size;

	if (!s)
		return (0);
	size = 0;
	while (*s)
	{
		if (*s != c)
		{
			size++;
			while (*s && *s != c)
				s++;
		}
		while (*s == c)
			s++;
	}
	return (size);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		size;
	int		i;

	size = countwords(s, c);
	if (!s || !(arr = (char **)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	i = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		size = 0;
		while (s[size] && s[size] != c)
			size++;
		arr[i] = ft_strsub((char const *)s, 0, (size_t)size);
		if (!arr[i++])
			return (NULL);
		s += size;
		while (*s == c)
			s++;
	}
	arr[i] = 0;
	return (arr);
}
