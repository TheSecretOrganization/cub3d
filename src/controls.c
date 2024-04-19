/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:14:02 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/19 17:21:38 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggle_control(int *controls, int key)
{
	*controls ^= 1 << key;
}

int	get_control_value(int controls, int key)
{
	return ((controls >> key) & 1);
}
