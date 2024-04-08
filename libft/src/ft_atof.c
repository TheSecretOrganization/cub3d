/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:17:25 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/08 17:34:27 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

static void	init_ft_atof(float *r, float *frac_mult, int *sign, int *frac_part)
{
	*r = 0.0;
	*frac_mult = 1.0;
	*sign = 1;
	*frac_part = 0;
}

float	ft_atof(const char *nptr)
{
	float	r;
	float	frac_mult;
	int		sign;
	int		frac_part;

	init_ft_atof(&r, &frac_mult, &sign, &frac_part);
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*(nptr++) == '-')
			sign = -1;
	while (*nptr && (ft_isdigit(*nptr) || (!frac_part && *nptr == '.')))
	{
		if (!frac_part && *nptr == '.')
			frac_part = 1;
		else if (frac_part)
		{
			frac_mult /= 10.0;
			r += (*nptr - '0') * frac_mult;
		}
		else
			r = r * 10.0 + *nptr - '0';
		nptr++;
	}
	return (r * sign);
}
