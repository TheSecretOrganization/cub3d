/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:42:57 by averin            #+#    #+#             */
/*   Updated: 2023/12/01 16:09:29 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	dispatch(int fd, const char type, va_list ap)
{
	if (type == 'c')
		return (print_char(fd, va_arg(ap, int)));
	if (type == 's')
		return (print_str(fd, va_arg(ap, char *)));
	if (type == 'p')
		return (print_ptr_hexa(fd, va_arg(ap, unsigned long)));
	if (type == 'd' || type == 'i')
		return (print_int(fd, va_arg(ap, int)));
	if (type == 'u')
		return (print_unsigned_int(fd, va_arg(ap, unsigned int)));
	if (type == 'x')
		return (print_base(fd, va_arg(ap, int), "0123456789abcdef"));
	if (type == 'X')
		return (print_base(fd, va_arg(ap, int), "0123456789ABCDEF"));
	if (type == '%')
		return (print_char(fd, '%'));
	return (1);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	int		chars;
	va_list	ap;

	va_start(ap, s);
	chars = 0;
	while (*s)
	{
		if (*s == '%')
		{
			chars += dispatch(fd, s[1], ap);
			s += 2;
		}
		else
		{
			ft_putchar_fd(*s++, fd);
			chars++;
		}
	}
	va_end(ap);
	return (chars);
}

int	ft_printf(const char *s, ...)
{
	int		chars;
	va_list	ap;

	va_start(ap, s);
	chars = 0;
	while (*s)
	{
		if (*s == '%')
		{
			chars += dispatch(1, s[1], ap);
			s += 2;
		}
		else
		{
			ft_putchar_fd(*s++, 1);
			chars++;
		}
	}
	va_end(ap);
	return (chars);
}
