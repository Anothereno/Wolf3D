/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:05:59 by hdwarven          #+#    #+#             */
/*   Updated: 2018/11/30 14:00:45 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*tmp;
	char	*begin;

	begin = NULL;
	tmp = NULL;
	len = 0;
	if (s != NULL)
	{
		len = ft_strlen(s);
		tmp = (char*)malloc(sizeof(char) * len + 1);
		begin = tmp;
		len = 0;
		if (tmp == NULL)
			return (NULL);
		while (*s)
		{
			*tmp++ = f(len, *s++);
			len++;
		}
		*tmp = '\0';
	}
	return (begin);
}
