/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_events_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:04:34 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/25 08:09:10 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol_bonus.h"

//====<[ events_handler: ]>=====================================================
void	events_handler(t_img *img)
{
	mlx_key_hook(img->var->win, on_press_button, img);
	mlx_mouse_hook(img->var->win, zoom, img);
	mlx_hook(img->var->win, 17, 0, close_window, img);
	mlx_loop_hook(img->var->mlx, shift_color, img);
}

//====<[ close_window: ]>=======================================================
int	close_window(t_img *img)
{
	exit(mlx_destroy_window(img->var->mlx, img->var->win) * 0);
}

//====<[ zoom: ]>===============================================================
int	zoom(int code, int x, int y, t_img *img)
{
	double	new_xc;
	double	new_yc;

	img->p->old_xc = -img->p->b + ((double) x * slope(img)) + img->p->dx;
	img->p->old_yc = img->p->b - ((double) y * slope(img)) + img->p->dy;
	if (img->fractal == BURNING_SHIP)
		img->p->old_yc = -img->p->b + ((double) y * slope(img)) + img->p->dy;
	if (code == SCROLL_DOWN || code == SCROLL_UP)
	{
		img->p->a /= 1.3 * (code == 4) + (1 / 1.4) * (code == 5);
		img->p->b /= 1.3 * (code == 4) + (1 / 1.3) * (code == 5);
		new_xc = -img->p->b + (((double) x) * slope(img));
		new_yc = img->p->b - (((double) y) * slope(img));
		if (img->fractal == BURNING_SHIP)
			new_yc *= -1;
		img->p->dx = img->p->old_xc - new_xc;
		img->p->dy = img->p->old_yc - new_yc;
	}
	display_fractal(img, 0, 0);
	return (0);
}

//====<[ on_press_button: ]>====================================================
int	on_press_button(int code, t_img *img)
{
	if ((code == J || code == K || code == F || code == D)
		&& img->fractal == JULIASET)
	{
		img->julia->cr += 0.01 * ((code == J) - (code == K));
		img->julia->ci += 0.01 * ((code == F) - (code == D));
	}
	if (code == ESC)
		close_window(img);
	if (code == PLUS || code == MINUS)
		img->nmax += 5 * ((code == PLUS) - (code == MINUS));
	if (code == RESET)
		mlx_create_image(img->var, img, img->julia, img->p);
	if (code >= RIGHT && code <= UP)
	{
		img->p->dx += (img->p->a / 10.0) * ((code == RIGHT) - (code == LEFT));
		if (img->fractal == BURNING_SHIP)
			img->p->dy += (img->p->b / 10.0) * ((code == UP) - (code == DOWN));
		else
			img->p->dy += (img->p->b / 10.0) * ((code == DOWN) - (code == UP));
	}
	display_fractal(img, 0, 0);
	return (0);
}
