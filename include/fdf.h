#ifndef FDF_H
#define FDF_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "minilibx-linux/mlx.h"

#define HEIGHT 500
#define WIDTH 500

typedef struct s_scene
{
    int width;
    int height;

    void *mlx_ptr;
    void *win_ptr;

}               t_scene;

typedef struct s_vec3d
{
    float x, y, z;
}               t_vec3d;

typedef struct s_triangle
{
    t_vec3d p[3];
}               t_triangle;

typedef struct s_map
{
    t_triangle *map;
}               t_map;

typedef struct s_mat4x4
{
    float m[4][4];
}               t_mat4x4;

typedef struct s_frame
{
    void    *ptr;
    unsigned int *buffer;
    int info[3];
}               t_frame;

#endif