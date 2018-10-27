/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addprefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 14:28:19 by jkimmina          #+#    #+#             */
/*   Updated: 2018/05/05 16:33:40 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_addprefix(char *pre, char *str)
{
	char *tmp;

	tmp = ft_strjoin(pre, str);
	free(str);
	return (tmp);
}
