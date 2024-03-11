int	loop_hook(t_window *param)
{
	int	x;

	double posX = 7, posY = 7;
	double dirX = 1, dirY = 0;
	double planeX = 0, planeY = 0.66;

	(void) param;
	x = -1;
	while (++x < WIDTH)
	{
		// double camX = 2 * x / (double) WIDTH;
		double rayDirX = dirX + planeX * WIDTH;
		double rayDirY = dirY + planeY * WIDTH;
		int mapX = posX;
		int mapY = posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirX == 0) ? -1 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? -1 : fabs(1 / rayDirY);

		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		while(hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if(map[mapX][mapY] > 0) hit = 1;
		}
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
		draw_line(&param->image, drawStart, drawEnd, x);
		printf(" line at %d from %d to %d\tlen=%d\n", x, drawStart, drawEnd, drawStart - drawEnd);
	}
	mlx_put_image_to_window(param->mlx, param->ptr, param->image.addr, 0, 0);
	printf("image put to window\n");
	return (0);
}