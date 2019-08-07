/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:51:18 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/06 17:55:47 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *ptr;

	ptr = (char*)malloc(size + 1);
	if (sizeof(ptr) == 0)
		return (NULL);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, size);
	ptr[size] = '\0';
	return (ptr);
}
