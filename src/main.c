#include "../include/fdf.h"

t_frame *initFrame(t_scene *scene)
{
    t_frame *frame;

    frame = malloc(sizeof(t_frame));
    frame->ptr = mlx_new_image(scene->mlx_ptr, scene->width, scene->height);
    frame->buffer = (unsigned int *)mlx_get_data_addr(frame->ptr, &frame->info[0], &frame->info[1], &frame->info[2]);
    return frame;
}


void render(t_scene *scene)
{
    t_frame *frame;

    int x = 0;
    t_mat4x4 projectMatrix = initProjMat();


    //frame = initFrame(scene);
    // while(x < scene->width)
    // {
    //     int y = 0;
    //     while(y < scene->height)
    //     {

    //         frame->buffer[x + y * frame->info[1] / 4] = 0x000000;
    //         y++;
    //     }
    //     x++;
    // }
    
    // mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, frame->ptr, 0, 0);

    t_mat4x4 matRotZ, matRotX, matRotY;
    float theta = 0;
    float alpha = 1;
    float beta = 0;
    
    matRotX.m[0][0] = 1;
    matRotX.m[1][1] = cosf(alpha );
    matRotX.m[1][2] = sinf(alpha );
    matRotX.m[2][1] = -sinf(alpha );
    matRotX.m[2][2] = cosf(alpha );
    matRotX.m[3][3] = 1;

    matRotY.m[0][0] = cosf(beta);
    matRotY.m[0][2] = -sinf(beta);
    matRotY.m[1][1] = 1;
    matRotY.m[2][0] = sinf(beta);
    matRotY.m[2][2] = cosf(beta);
    matRotY.m[3][3] = 1;
  
    matRotZ.m[0][0] = cosf(theta);
    matRotZ.m[0][1] = sinf(theta);
    matRotZ.m[1][0] = -sinf(theta);
    matRotZ.m[1][1] = cosf(theta);
    matRotZ.m[2][2] = 1;
    matRotZ.m[3][3] = 1;

    

    int i = 0;
    t_triangle t1;
    t_triangle t2;
    while (scene->map[i + 1])
    {
        int j = 0;
        while(scene->map[i][j + 1])
        {
            //left triangle, can optimize
            t1.p[0].x = (float)(i + 1);
            t1.p[0].y = (float)atof(scene->map[i + 1][j]);
            t1.p[0].z = (float)(j);

            t1.p[1].x = (float)(i);
            t1.p[1].y = (float)atof(scene->map[i][j]);
            t1.p[1].z = (float)(j);

            t1.p[2].x = (float)(i);
            t1.p[2].y = (float)atof(scene->map[i][j + 1]);
            t1.p[2].z = (float)(j + 1);

            t1.p[0] = multiplyMatrixVector(t1.p[0], matRotZ);
            t1.p[1] = multiplyMatrixVector(t1.p[1], matRotZ);
            t1.p[2] = multiplyMatrixVector(t1.p[2], matRotZ);

            t1.p[0] = multiplyMatrixVector(t1.p[0], matRotX);
            t1.p[1] = multiplyMatrixVector(t1.p[1], matRotX);
            t1.p[2] = multiplyMatrixVector(t1.p[2], matRotX);

            t1.p[0] = multiplyMatrixVector(t1.p[0], matRotY);
            t1.p[1] = multiplyMatrixVector(t1.p[1], matRotY);
            t1.p[2] = multiplyMatrixVector(t1.p[2], matRotY);

            t1.p[0].z += 25.0f;
            t1.p[1].z += 25.0f;
            t1.p[2].z += 25.0f;

            t1.p[0] = multiplyMatrixVector(t1.p[0], projectMatrix);
            t1.p[1] = multiplyMatrixVector(t1.p[1], projectMatrix);
            t1.p[2] = multiplyMatrixVector(t1.p[2], projectMatrix);

            //scale
                t1.p[0].x += 1.f; t1.p[0].y += 1.f;
                t1.p[1].x += 1.f; t1.p[1].y += 1.f;
                t1.p[2].x += 1.f; t1.p[2].y += 1.f;


                t1.p[0].x *= 0.5f * (float)WIDTH; t1.p[0].y *= 0.5f * (float)WIDTH;
                t1.p[1].x *= 0.5f * (float)WIDTH; t1.p[1].y *= 0.5f * (float)WIDTH;
                t1.p[2].x *= 0.5f * (float)WIDTH; t1.p[2].y *= 0.5f * (float)WIDTH;
            //

            drawLine(t1.p[0].x,t1.p[0].y,t1.p[1].x,t1.p[1].y, scene);
            drawLine(t1.p[1].x,t1.p[1].y,t1.p[2].x,t1.p[2].y, scene);
           // drawLine(t1.p[2].x,t1.p[2].y,t1.p[0].x,t1.p[0].y, scene);
            
            // 
            t2 = t1;
            t2.p[1].x = (float)(i + 1);
            t2.p[1].y = (float)atof(scene->map[i+ 1][j+ 1]);
            t2.p[1].z = (float)(j+ 1);

            t2.p[1] = multiplyMatrixVector(t2.p[1], matRotZ);
            t2.p[1] = multiplyMatrixVector(t2.p[1], matRotX);
            t2.p[1] = multiplyMatrixVector(t2.p[1], matRotY);
           
            t2.p[1].z += 25.0f;
            
            t2.p[1] = multiplyMatrixVector(t2.p[1], projectMatrix);
           

            //scale
              
                t2.p[1].x += 1.f; t2.p[1].y += 1.f;
              
                t2.p[1].x *= 0.5f * (float)WIDTH; t2.p[1].y *= 0.5f * (float)WIDTH;
               
            //

            drawLine(t2.p[0].x,t2.p[0].y,t2.p[1].x,t2.p[1].y, scene);
            drawLine(t2.p[1].x,t2.p[1].y,t2.p[2].x,t2.p[2].y, scene);
            //drawLine(t2.p[2].x,t2.p[2].y,t2.p[0].x,t2.p[0].y, scene);
            j++;
        }
        i++;
    }
    //mlx_destroy_image(scene->mlx_ptr, frame->ptr);
}



int main(int argc, char **argv)
{
    (void)argc;
    t_scene *scene = initScene();

    

    scene->map = createMap(argv[1]);
    
    // printf("------MAP------\n");
    // int i = 0;
    // while (scene->map[i])
    // {
    //     int j = 0;
    //     while(scene->map[i][j])
    //     {
    //         printf("%s ",scene->map[i][j]);
    //         j++;
    //     }
    //     printf("\n");
    //     i++;
    // }
    // printf("---------------\n");
    // printf("----TRIANGLE---\n");
    //  i = 0;
    // while (scene->map[i + 1])
    // {
    //     int j = 0;
    //     while(scene->map[i][j + 1])
    //     {
    //         printf("%s,",scene->map[i + 1][j]);
    //         printf("%s,",scene->map[i][j]);
    //         printf("%s\n",scene->map[i][j + 1]);

    //         printf("%s,",scene->map[i][j + 1]);
    //         printf("%s,",scene->map[i + 1][j + 1]);
    //         printf("%s\n",scene->map[i + 1][j]);
    //         printf("\n");
    //         j++;
    //     }
    //     i++;
    // }
    // printf("---------------\n");
    
    //
   
    render(scene);
    mlx_loop(scene->mlx_ptr);
    //projection 
    //t_mat4x4 *projectMatrix = initProjMat;


    
    //initWindow(scene);
}