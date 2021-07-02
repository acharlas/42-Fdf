#include "../include/fdf.h"

t_scene *initScene(void)
{
    t_scene *scene;
    
    scene = malloc(sizeof(t_scene));
    // set of H/W should be moved
    scene->height = HEIGHT;
    scene->width = WIDTH;

    scene->mlx_ptr = mlx_init();
    scene->win_ptr = mlx_new_window(scene->mlx_ptr, WIDTH, HEIGHT, "Fdf");

    return(scene);
}

t_mat4x4 *initMat4x4(void)
{
    t_mat4x4 *matrix = malloc(sizeof(t_mat4x4));
    int i = 0;
    int j = 0;

    while(i < 4)
    {
        while(j < 4)
        {
            matrix->m[i][j] = 0;
            j++;
        }
        i++;
    }
    return(matrix);
}

t_vec3d multiplyMatrixVector(t_vec3d vect, t_mat4x4 mat)
{
    t_vec3d ret;

    ret.x = vect.x * mat.m[0][0] + vect.y * mat.m[1][0] + vect.z * mat.m[2][0] + mat.m[3][0];
    ret.y = vect.x * mat.m[0][1] + vect.y * mat.m[1][1] + vect.z * mat.m[2][1] + mat.m[3][1];
    ret.z = vect.x * mat.m[0][2] + vect.y * mat.m[1][2] + vect.z * mat.m[2][2] + mat.m[3][2];
    float w = vect.x * mat.m[0][3] + vect.y * mat.m[1][3] + vect.z * mat.m[2][3] + mat.m[3][3];
    if(w != 0.0f)
    {
        ret.x /= w;
        ret.y /= w;
        ret.z /= w;
    }
    return ret;
}

t_mat4x4 *initProjMat(void)
{
    t_mat4x4 *projectMatrix = initMat4x4();

    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFov = 90.0f;
    float fAspectRatio = (float)HEIGHT / (float)WIDTH;
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

    projectMatrix->m[0][0] = fAspectRatio;
    projectMatrix->m[1][1] = fFovRad;
    projectMatrix->m[2][2] = fFar / (fFar - fNear);
    projectMatrix->m[3][2] = (-fFar * fNear) / (fFar - fNear);
    projectMatrix->m[2][3] = 1.0f;
    return projectMatrix;
}

t_frame *initFrame(t_scene *scene)
{
    t_frame *frame;

    frame = malloc(sizeof(t_frame));
    frame->ptr = mlx_new_image(scene->mlx_ptr, scene->width, scene->height);
    frame->buffer = (unsigned int *)mlx_get_data_addr(frame->ptr, &frame->info[0], &frame->info[1], &frame->info[2]);
    return frame;
}

unsigned int drawLine(int x, int y, float x1, float y1, float x2, float y2)
{
    float m = (y2 - y1) / (x2 - x1);
    float b = y1 - (m * x1);

    if (y == m*x + b)
        return(0xFFFFFF);
    return(0x000000);
}


void render(t_scene *scene)
{
    t_frame *frame;
    unsigned int color = 0xFFFFFF;

    int x = 0;
    t_mat4x4 *projectMatrix = initProjMat();
    t_vec3d temp1;
    temp1.x = 1.f;
    temp1.y = 1.f;
    temp1.z = 2.f;

    t_vec3d temp2;
    temp2.x = 0.f;
    temp2.y = -1.f;
    temp2.z = 3.f;

    temp1 = multiplyMatrixVector(temp1, *projectMatrix);
    temp2 = multiplyMatrixVector(temp2, *projectMatrix);

    temp1.x += 1.f;
    temp1.y += 1.f;
    temp2.x += 1.f;
    temp2.y += 1.f;

    temp1.x *= 0.5f * (float)WIDTH;
    temp1.y *= 0.5f * (float)WIDTH;
    temp2.x *= 0.5f * (float)WIDTH;
    temp2.y *= 0.5f * (float)WIDTH;

    frame = initFrame(scene);
    while(x < scene->width)
    {
        int y = 0;
        while(y < scene->height)
        {

            frame->buffer[x + y * frame->info[1] / 4] = drawLine(x, y, temp1.x, temp1.y, temp2.x, temp2.y);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, frame->ptr, 0, 0);
    mlx_destroy_image(scene->mlx_ptr, frame->ptr);
}



int main(void)
{
    t_scene *scene = initScene();

    render(scene);
    mlx_loop(scene->mlx_ptr);
    //projection 
    //t_mat4x4 *projectMatrix = initProjMat;


    
    //initWindow(scene);
}