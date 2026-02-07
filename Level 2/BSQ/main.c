#include "bsq.h"

//int fprintf(FILE *stream, const char *format, ...);
//return value = number of items written




int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        if(execute_bsq(stdin) == -1)//"“Should there be no passed arguments, your program must be able to read on the standard input."
            fprintf(stderr, "execute error!?\n");
    }
    else
    {
        for( int i = 1; i < argc; i++)//convert and add newline
        {
            if(convert_file_pointer(argv[i]) == -1)
                fprintf(stderr, "map_error");
            if(i < argc)
                fprintf(stdout, "\n");
        }
    }
    return 0;
}

//from subject: "Each solution or "map error" must be followed by a line break.
//But there should not be an extra empty line after the last map.""
//argc - 1 is the last argument
//i < argc - 1 mean when it is not the last arg