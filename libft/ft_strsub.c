/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:05:53 by hdwarven          #+#    #+#             */
/*   Updated: 2018/11/28 21:19:52 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *tmp;
	char *begin;

	tmp = NULL;
	begin = NULL;
	if (s)
	{
		tmp = (char*)malloc(sizeof(char) * len + 1);
		if (tmp == NULL)
			return (NULL);
		begin = tmp;
		while (len > 0)
		{
			*tmp = s[start];
			tmp++;
			start++;
			len--;
		}
		*tmp = '\0';
	}
	return (begin);
}
