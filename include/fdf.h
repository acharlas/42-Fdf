#ifndef FDF_H
#define FDF_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include "minilibx-linux/mlx.h"
#include "libft/libft.h"

#define HEIGHT 1000
#define WIDTH 1000

typedef struct s_scene
{
    int width;
    int height;

    char ***map;

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

t_scene *initScene(void);
t_mat4x4 initMat4x4(void);
t_vec3d multiplyMatrixVector(t_vec3d vect, t_mat4x4 mat);
t_mat4x4 initProjMat(void);
char ***createMap(char *file);
void drawLine(int x1, int y1, int x2, int y2, t_scene *scene);

#endif