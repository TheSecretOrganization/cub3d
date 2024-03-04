/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:24:47 by averin            #+#    #+#             */
/*   Updated: 2023/12/01 16:08:32 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned_int(int fd, unsigned int i)
{
	ft_putnbr_unsigned_fd(i, fd);
	return (ft_count_unsigned_digits(i));
}
