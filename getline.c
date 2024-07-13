#include "main.h"
#define BUFFER_SIZE 1024
/**
 * _getline - custom getline function to read a line from stream
 * @lineptr: pointer to the buffer that will store the line
 * @n: pointer to the size of the buffer
 * @stream: the input stream to read from
 * Return: number of characters read, or -1 on failure or EOF
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream) {
    static char buffer[BUFFER_SIZE];
    static int buffer_pos = 0;
    static int buffer_size = 0;
    char *line = *lineptr; 
    size_t line_size = *n;
 
    if (line == NULL || line_size == 0) {
        line_size = BUFFER_SIZE; 
        line = (char *)malloc(line_size);
        if (line == NULL) {
            return -1;
        }
    }
    while (1) {
        if (buffer_pos >= buffer_size) {
            buffer_size = fread(buffer, 1, BUFFER_SIZE, stream);
            buffer_pos = 0;
            if (buffer_size == 0) {
                break; 
            }
        }

        for (; buffer_pos < buffer_size; ++buffer_pos) {
            if (buffer[buffer_pos] == '\n') {
                ++buffer_pos;
                break;
            }
            if (line_size <= line_size + 1) {
                line_size *= 2;
                line = realloc(line, line_size);
                if (!line) {
                    return (-1);
                }
            }
            line[line_size++] = buffer[buffer_pos];
        }
        if (buffer_pos < buffer_size && buffer[buffer_pos - 1] == '\n') {
            break;
        }
    }
    line[line_size] = '\0';

    *lineptr = line;
    *n = line_size;
    return (line_size);
}
