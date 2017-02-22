# include "fdf.h"

int		main(void)
{
	void *mlx_ptr;
	void *win_ptr;
	int x;
	int y;

	// mlx pointer : connection avec serveur graphique
	mlx_ptr = mlx_init();

	// identify window
	win_ptr = mlx_new_window(mlx_ptr, 780, 540, "mlx 42");

	
	

	y = 50;
	while (y < 150)
	{
		x = 50;
		while (x < 680)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xAAFFFFFF);		
			x++;
		}
		y++;
	}
	mlx_loop(mlx_ptr);

	// ouvrir fenetre, créer dessin
	

	// ft_putstr("Reached main.c\n");
	// ft_putchar('a');
	return (0);
}