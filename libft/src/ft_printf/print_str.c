/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:08:44 by averin            #+#    #+#             */
/*   Updated: 2023/12/01 16:08:14 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str(int fd, char *s)
{
	if (s == NULL)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	ft_putstr_fd(s, fd);
	return (ft_strlen(s));
}
