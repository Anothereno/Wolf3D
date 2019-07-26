/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 16:59:08 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/26 19:32:27 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(int c)
{
	int first;
	int second;

	if (c < 128)
		write(1, &c, 1);
	else
	{
		first = 192 + c / 64;
		second = 128 + c % 64;
		write(1, &first, 1);
		write(1, &second, 1);
	}
}
