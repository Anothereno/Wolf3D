/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:39:05 by hdwarven          #+#    #+#             */
/*   Updated: 2019/01/02 14:39:01 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_arr(void ***arr, unsigned long i)
{
	int z;

	z = (int)i;
	if (*arr)
	{
		while (--z >= 0)
		{
			if (*arr[z])
			{
				free(*arr[z]);
				*arr[z] = NULL;
			}
		}
		free(*arr);
		*arr = NULL;
	}
	return (*arr);
}
