/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 16:34:09 by jkimmina          #+#    #+#             */
/*   Updated: 2018/04/02 16:34:18 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_wordcount(char *str)
{
	int		wc;

	wc = 0;
	str = ft_nextword(str);
	while (*str)
	{
		wc++;
		str = ft_nextspace(str);
		str = ft_nextword(str);
	}
	return (wc);
}
