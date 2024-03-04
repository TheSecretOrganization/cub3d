/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:20:49 by averin            #+#    #+#             */
/*   Updated: 2023/11/10 13:20:19 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_unsigned_digits_base(unsigned long n, int base)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base;
		digits++;
	}
	return (digits);
}

int	ft_count_unsigned_digits(unsigned long n)
{
	return (ft_count_unsigned_digits_base(n, 10));
}

int	ft_count_digits_base(long n, int base)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		digits++;
	}
	while (n > 0)
	{
		n /= base;
		digits++;
	}
	return (digits);
}

int	ft_count_digits(long n)
{
	return (ft_count_digits_base(n, 10));
}
