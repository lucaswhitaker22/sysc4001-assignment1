#include "device.h"
#include <ctype.h>
#include <time.h>
int main(int argc, char *argv[])
{
    int client_fifo_fd;
    struct data_to_pass_st my_data;
    int times_to_send;
    char client_fifo[256] = {};
    sleep(1);
    int server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
    if (server_fifo_fd == -1)
    {
        printf("%i",server_fifo_fd);
        fprintf(stderr, "Sorry, no server\n");
        exit(EXIT_FAILURE);
    }
    my_data.threshold = atoi(argv[1]);
    my_data.client_pid = getpid();
    sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
    if (mkfifo(client_fifo, 0777) == -1)
    {
        fprintf(stderr, "Sorry, can’t make %s\n", client_fifo);
        exit(EXIT_FAILURE);
    }
    printf("Sensor with ID %d created with threshold of %f\n", my_data.client_pid, my_data.threshold);
    while(1)
    {   
            srand(time(NULL));
            float val = rand()%1000;
        my_data.some_data[0] = val;
        sprintf(my_data.some_data, "%f", val);
        write(server_fifo_fd, &my_data, sizeof(my_data));
        client_fifo_fd = open(client_fifo, O_RDONLY);
        if (client_fifo_fd != -1)
        {

            if (read(client_fifo_fd, &my_data, sizeof(my_data)) > 0)
            {
                printf("Sensor with ID %d reading value %f\n", my_data.client_pid, val);
                if(val > my_data.threshold)
                {
                    action(my_data.client_pid);
                    break;
                }
            }

            close(client_fifo_fd);
            sleep(1);
        }
    }
    close(server_fifo_fd);
    
    unlink(client_fifo);
    exit(EXIT_SUCCESS);
}