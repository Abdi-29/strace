#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <sys/types.h>
#include <sys/user.h> 
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define T_NONE   0
#define T_INT    1
#define T_BUFF   2
#define T_ULINT  3
#define T_LINT   4
#define T_STR    5
#define T_ADDR   6
#define T_HEX    7
#define T_UINT   8
#define T_LLINT 9
#define T_ULLINT 10
#define T_CADDR_T 11
#define T_E_PTRACE_REQUEST 12
#define T_UNKNOWN 13

// Maximum number of arguments a system call can have
#define MAX_SYSCALL_ARGS 6

typedef struct s_syscall_entry {
    int number;
    const char *name;
    int arg_types[6];
    void (*handler)(void);
} t_syscall_entry;

void init_syscall_table(void);
const t_syscall_entry *get_syscall_entry(int syscall_number);
void print_syscall_details(struct user_regs_struct *regs, int architecture);
unsigned long get_syscall_arg(struct user_regs_struct *regs, int arg_index, int architecture);

#endif // SYSCALLS_H
