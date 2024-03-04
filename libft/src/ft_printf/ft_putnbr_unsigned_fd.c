/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:14:27 by averin            #+#    #+#             */
/*   Updated: 2023/11/21 10:24:08 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	recu_unsigned(unsigned long n, char *base, unsigned int base_len, int fd)
{
	int	digits;

	digits = 0;
	if (n >= base_len)
		digits = recu_unsigned(n / base_len, base, base_len, fd) + 1;
	ft_putchar_fd(base[n % base_len], fd);
	return (digits);
}

int	ft_putnbr_unsigned_base_fd(unsigned long n, char *base, int fd)
{
	int	base_len;

	base_len = ft_strlen(base);
	return (recu_unsigned(n, base, base_len, fd));
}

void	ft_putnbr_unsigned_fd(unsigned long n, int fd)
{
	ft_putnbr_unsigned_base_fd(n, "0123456789", fd);
}
