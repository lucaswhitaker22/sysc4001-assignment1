#include "device.h"
#include <time.h>
#include <ctype.h>
int main()
{
    int server_fifo_fd, client_fifo_fd;
    struct data_to_pass_st my_data;
    int read_res;
    char client_fifo[256];
    char *tmp_char_ptr;
    mkfifo(SERVER_FIFO_NAME, 0777);
    server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY);
    if (server_fifo_fd == -1)
    {
        fprintf(stderr, "Server fifo failure\n");
        exit(EXIT_FAILURE);
    }
    do
    {
        read_res = read(server_fifo_fd, &my_data, sizeof(my_data));
        if(read_res > 0) {
            sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
            client_fifo_fd = open(client_fifo, O_WRONLY);
            if (client_fifo_fd != -1)
            {
                write(client_fifo_fd, &my_data, sizeof(my_data));
                close(client_fifo_fd);
            }
        }
    } while (read_res > 0);
    close(server_fifo_fd);
    unlink(SERVER_FIFO_NAME);
    exit(EXIT_SUCCESS);
}
