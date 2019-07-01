/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:37:50 by hdwarven          #+#    #+#             */
/*   Updated: 2018/12/05 18:15:56 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*begin;

	begin = (unsigned char*)dest;
	if (dest == src)
		return (dest);
	while (n-- > 0)
	{
		*begin = *(unsigned char*)src;
		begin++;
		src++;
	}
	return (dest);
}
