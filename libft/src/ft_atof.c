/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:17:25 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/10 18:51:08 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

static void	init_ft_atof(float *r, float *frac_mult, int *frac_part)
{
	*r = 0.0;
	*frac_mult = 1.0;
	*frac_part = 0;
}

static int	check_sign(const char **nptr)
{
	int	sign;

	sign = 1;
	if (**nptr == '+' || **nptr == '-')
	{
		if (**nptr == '-')
			sign = -1;
		(*nptr)++;
	}
	return (sign);
}

float	ft_atof(const char *nptr)
{
	float	r;
	float	frac_mult;
	int		sign;
	int		frac_part;

	init_ft_atof(&r, &frac_mult, &frac_part);
	while (ft_isspace(*nptr))
		nptr++;
	sign = check_sign(&nptr);
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
