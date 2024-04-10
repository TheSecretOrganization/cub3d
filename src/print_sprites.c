/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:12:40 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/10 11:25:49 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_sprites_to_image(t_data *d)
{
	t_player	*p;
	t_sprite	*s;
	// t_vector	sprite;
	// float		invDet;
	// t_vector	transform;
	// int			spriteScreenX;
	// int			spriteDim;
	// int			drawX[2];
	// int			drawY[2];
	// int			tex[2];
	// int			color;

	p = &d->player;
	sort_sprites(&d->map.graphic.sprite, p->pos);
	s = d->map.graphic.sprite;
	while (s)
	{
		float spriteX = s->pos.x - p->pos.x;
		float spriteY = s->pos.y - p->pos.y;

		float invDet = 1.0 / (p->plane.x * p->direction.y - p->direction.x * p->plane.y); //required for correct matrix multiplication

		float transformX = invDet * (p->direction.y * spriteX - p->direction.x * spriteY);
		float transformY = invDet * (-p->plane.y * spriteX + p->plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(HEIGHT / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + HEIGHT / 2;
		if(drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

		//calculate width of the sprite
		int spriteWidth = abs( (int) (HEIGHT / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= WIDTH) drawEndX = WIDTH - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * s->img.width / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) d->map.graphic.zbuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < d->map.graphic.zbuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int dada = (y) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((dada * s->img.height) / spriteHeight) / 256;
				int	color = get_pixel(&s->img, texX, texY);
				// Uint32 color = texture[sprite[spriteOrder[i]].texture][s->img.width * texY + texX];
				if((color & 0x00FFFFFF) != 0)
					img_pixel_put(&d->window.img, stripe, y, color);
			// buffer[y][stripe] = color;
			}
		}
		s = s->next;
	}
}
