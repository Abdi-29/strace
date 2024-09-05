#ifndef TRACE_H
#define TRACE_H

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/reg.h> // For register constants
#include <sys/signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Constants
#define SYSCALL_BUFFER_SIZE 256
#define ARCH_64BIT 1
#define ARCH_32BIT 2

typedef struct s_trace_data {
    pid_t pid;
    int architecture;
    struct user_regs_struct regs; // Structure register values
} t_trace_data;

int start_trace(char **commands);
void trace_process(t_trace_data *trace_data);
void handle_signal(t_trace_data *trace_data, int signal);
void handle_syscall(t_trace_data *trace_data);
int detect_architecture(pid_t pid);
void error_exit(const char *msg);

#endif // TRACE_H