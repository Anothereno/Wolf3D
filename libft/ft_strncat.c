/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:47:54 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/06 17:55:47 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	int		i;
	char	*temp;

	temp = dest;
	i = 0;
	while (*dest)
		dest++;
	while (*src && n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	*dest = '\0';
	return (temp);
}
