/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:50:06 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/06 17:55:47 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void*)s);
		s++;
		n--;
	}
	return (NULL);
}
