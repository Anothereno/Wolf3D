/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_of_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 19:47:08 by hdwarven          #+#    #+#             */
/*   Updated: 2018/12/02 17:07:09 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_size_of_lst(t_list *lst)
{
	t_list	*begin;
	int		count;

	count = 0;
	begin = lst;
	if (begin)
	{
		while (begin && begin->next)
		{
			count++;
			begin = begin->next;
		}
		if (begin)
			count++;
	}
	return (count);
}
