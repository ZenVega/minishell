#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>

int g_signal;



// Private storage function
static int get_fd(int new_fd, int set) 
{
    static int fd = -1;
    if (set) fd = new_fd;
    return fd;
}

void sigint_handler_child(int sig) 
{
    int fd = get_fd(0, 0);  // retrieve fd
    if (fd >= 0) {
        close(fd);
        write(STDOUT_FILENO, "Child: Closed file descriptor\n", 30);
    }
    _exit(0);
}

void sigint_handler_parent(int sig) 
{
    g_signal = 130;
    write(STDOUT_FILENO, "Parent received SIGINT\n", 24);
}

void disable_ctrl_c_echo() 
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;  // Disable echoing of control characters like ^C
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int main() 
{
    disable_ctrl_c_echo();
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) 
    {
        perror("open");
        return 1;
    }

    get_fd(fd, 1);  // store fd
    g_signal = 0;
    pid_t pid = fork();

    if (pid < 0) 
    {
        perror("fork");
        return 1;
    } 
    else if (pid == 0)
    {
        signal(SIGINT, sigint_handler_child);
        pause();  // wait for SIGINT
    } 
    else 
    {
        signal(SIGINT, sigint_handler_parent);
        //waitpid etc 

        //checking for SIGINT
        //waiting for SIGINT
        while (1)
        {
            if (g_signal == 130)
            {
                close(fd);
                break ;
            }
            
        }
    }

    return 0;
}
