/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:19:26 by averin            #+#    #+#             */
/*   Updated: 2023/12/01 16:09:56 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

int		print_char(int fd, char c);
int		print_str(int fd, char *s);
int		print_base(int fd, unsigned int i, char *base);
int		print_ptr_hexa(int fd, unsigned long n);
int		print_int(int fd, int i);
int		print_unsigned_int(int fd, unsigned int i);

int		ft_count_unsigned_digits_base(unsigned long n, int base);
int		ft_count_unsigned_digits(unsigned long n);
int		ft_count_digits_base(long n, int base);
int		ft_count_digits(long n);
int		ft_putnbr_unsigned_base_fd(unsigned long n, char *base, int fd);
void	ft_putnbr_unsigned_fd(unsigned long n, int fd);

#endif
