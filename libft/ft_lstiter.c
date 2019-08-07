/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 19:37:29 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/06 17:55:47 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *tmp;

	tmp = lst;
	if (lst && f)
	{
		while (tmp && tmp->next)
		{
			f(tmp);
			tmp = tmp->next;
		}
		if (!tmp->next)
		{
			f(tmp);
		}
	}
}
