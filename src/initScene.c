#include "../include/fdf.h"

t_scene *initScene(void)
{
    t_scene *scene;
    
    scene = malloc(sizeof(t_scene));
    // set of H/W should be moved
    scene->height = HEIGHT;
    scene->width = WIDTH;

    scene->map = NULL;

    scene->mlx_ptr = mlx_init();
    scene->win_ptr = mlx_new_window(scene->mlx_ptr, WIDTH, HEIGHT, "Fdf");

    return(scene);
}