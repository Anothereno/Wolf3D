/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 19:16:03 by hdwarven          #+#    #+#             */
/*   Updated: 2019/07/01 15:38:11 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list *begin;

	begin = NULL;
	if (alst && new)
	{
		begin = (*alst);
		new->next = begin;
		*alst = new;
	}
}
