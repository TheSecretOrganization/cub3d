/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:06:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/09 18:51:11 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_sprite	*sorted_merge(t_sprite *a, t_sprite *b)
{
	t_sprite	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->distance <= b->distance)
	{
		result = a;
		result->next = sorted_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next);
	}
	return (result);
}

static void	front_back_split(t_sprite *head, t_sprite **a, t_sprite **b)
{
	t_sprite	*fast;
	t_sprite	*slow;

	slow = head;
	fast = head->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = head;
	*b = slow->next;
	slow->next = NULL;
}

static void	merge_sort(t_sprite **sprites)
{
	t_sprite	*head;
	t_sprite	*a;
	t_sprite	*b;

	head = *sprites;
	if ((head == NULL) || (head->next == NULL))
		return ;
	front_back_split(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*sprites = sorted_merge(a, b);
}

static void	set_distance(t_sprite *s, t_vector pos)
{
	while (s)
	{
		s->distance = (pos.x - s->pos.x) * (pos.x - s->pos.x)
			+ (pos.y - s->pos.y) * (pos.y - s->pos.y);
		s = s->next;
	}
}

void	sort_sprites(t_sprite **sprites, t_vector pos)
{
	set_distance(*sprites, pos);
	merge_sort(sprites);
}
