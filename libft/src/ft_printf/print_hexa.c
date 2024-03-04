/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:18:44 by averin            #+#    #+#             */
/*   Updated: 2023/12/01 16:07:48 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define HEX_BASE "0123456789abcdef"

int	print_ptr_hexa(int fd, unsigned long n)
{
	if (n == 0)
	{
		ft_putstr_fd("(nil)", fd);
		return (5);
	}
	ft_putstr_fd("0x", fd);
	ft_putnbr_unsigned_base_fd(n, HEX_BASE, fd);
	return (2 + ft_count_unsigned_digits_base(n, 16));
}
