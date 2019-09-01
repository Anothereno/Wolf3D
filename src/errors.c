/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:54:56 by hdwarven          #+#    #+#             */
/*   Updated: 2019/08/28 17:14:02 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	msg(char *message)
{
	ft_putendl(message);
	exit(0);
}

void	usage(void)
{
	ft_putstr("usage: ./wolf3d <argument>\n");
}
