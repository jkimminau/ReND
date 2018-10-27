# minilibx
MinilibX with my small additions

Welcome to the minilibx wiki!

MinilibX is a fantastic graphics library. However, when digging for leaks in fdf and fractol, I noticed that it leaked when freeing the mlx pointer from mlx_init(). So I added an mlx_free() function that properly frees that pointer. MinilibX smartly only makes your code handle void pointers so it makes sense to have mlx_free take a void pointer so you don't have to do much extra work.
