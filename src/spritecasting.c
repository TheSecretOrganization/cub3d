/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:12:40 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/10 19:04:10 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_s_cast(const t_player *p, const t_sprite *s, t_vector *tr)
{
	t_vector	sprt;
	float		inv_det;

	sprt.x = s->pos.x - p->pos.x;
	sprt.y = s->pos.y - p->pos.y;
	inv_det = 1.0 / (p->plane.x * p->direction.y - p->direction.x * p->plane.y);
	tr->x = inv_det * (p->direction.y * sprt.x - p->direction.x * sprt.y);
	tr->y = inv_det * (-p->plane.y * sprt.x + p->plane.x * sprt.y);
	return ((int)((WIDTH / 2) * (1 + tr->x / tr->y)));
}

static void	init_draw(int *draw, int sprt_dim, int screen_x)
{
	draw[2] = -sprt_dim / 2 + HEIGHT / 2;
	if (draw[2] < 0)
		draw[2] = 0;
	draw[3] = sprt_dim / 2 + HEIGHT / 2;
	if (draw[3] >= HEIGHT)
		draw[3] = HEIGHT - 1;
	draw[0] = -sprt_dim / 2 + screen_x;
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = sprt_dim / 2 + screen_x;
	if (draw[1] >= WIDTH)
		draw[1] = WIDTH - 1;
}

static void	conclude_s_cast(t_img *img, int x, int y, int color)
{
	if ((color & 0x00FFFFFF) != 0)
		img_pixel_put(img, x, y, color);
}

/*
	draw[0] = draw_x_start,
	draw[1] = draw_x_end,
	draw[2] = draw_y_start,
	draw[3] = draw_y_end,
	tools[0] = x,
	tools[1] = y,
	tools[2] = texX,
*/
static void	do_s_cast(t_data *d, t_sprite *s, t_vector tr, int screen_x)
{
	int			draw[4];
	int			sprt_dim;
	int			tools[3];

	sprt_dim = abs((int)(HEIGHT / (tr.y)));
	(init_draw(draw, sprt_dim, screen_x), tools[0] = draw[0] - 1);
	while (++tools[0] < draw[1])
	{
		tools[2] = (256 * (tools[0] - (-sprt_dim / 2 + screen_x))
				* s->img.width / sprt_dim) / 256;
		if (tr.y > 0 && tools[0] > 0 && tools[0] < WIDTH
			&& tr.y < d->map.graphic.zbuffer[tools[0]])
		{
			tools[1] = draw[2] - 1;
			while (++tools[1] < draw[3])
				conclude_s_cast(&d->window.img, WIDTH - tools[0], tools[1],
					get_pixel(&s->img, tools[2],
						(((tools[1] * 256 - HEIGHT * 128 + sprt_dim * 128)
								* s->img.height) / sprt_dim) / 256));
		}
	}
}

void	spritecasting(t_data *d)
{
	const t_player	*p;
	t_sprite	*s;
	t_vector	tr;
	int			screen_x;

	p = &d->player;
	sort_sprites(&d->map.graphic.sprite, p->pos);
	s = d->map.graphic.sprite;
	while (s)
	{
		screen_x = init_s_cast(p, s, &tr);
		do_s_cast(d, s, tr, screen_x);
		s = s->next;
	}
}
