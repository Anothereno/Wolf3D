/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:48:05 by hdwarven          #+#    #+#             */
/*   Updated: 2018/11/28 13:48:16 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iswhitespaces(const char c)
{
	if (c == '\t' || c == '\v' || c == '\f' ||
		c == '\r' || c == '\n' || c == ' ')
		return (1);
	else
		return (0);
}
