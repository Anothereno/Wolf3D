/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:13:03 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/06 11:05:17 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	void			*b;

	b = s;
	while (n > 0)
	{
		ptr = (unsigned char *)s;
		*ptr = c;
		n--;
		s++;
	}
	return ((void*)b);
}
