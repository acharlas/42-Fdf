#include "../include/fdf.h"

char ***createMap(char *file)
{
    int fd = open(file, O_RDONLY);
    char ***map;
    char *line;
    int i = 0;

    line = NULL;
    
    //ADD COUNT WORD WITH \n
    map = malloc(sizeof(char **) * 25 + 1);
   
    while(get_next_line(fd, &line) > 0 || ft_strlen(line) > 0)
    {
        map[i] = ft_split(line, ' ');
        free(line);
        i++;
    }
    map[i] = NULL;
    return(map);
}