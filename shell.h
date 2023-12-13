#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define INFO_INIT {0}
#define WRITE_BUF_SIZE 1024
#define HIST_FILE ".hsh_history"
#define DEFAULT_FD 2
#define EXIT_SHELL_CODE -2
#define BUILTIN_NOT_FOUND -1

/**
 * Structure to hold information about the shell's state and environment.
 */
typedef struct info {
    char **argv;
    char *arg;
    char *path;
    char *fname;
    int argc;
    int status;
    int readfd;
    int line_count;
    int linecount_flag;
    int env_changed;
    int histcount;
    char **environ;
    struct list_s *history;
    struct list_s *alias;
    struct list_s *env;
    char **cmd_buf;
    int cmd_buf_type;
    int err_num;
} info_t;

/**
 * Structure for linked list nodes.
 */
typedef struct list_s {
    char *str;
    int num;
    struct list_s *next;
} list_t;

/**
 * Structure for builtin table.
 */
typedef struct {
    char *type;
    int (*func)(info_t *);
} builtin_table;

/* Function Prototypes */

/* From shell_execution.c */
int shell_main_loop(shell_info_t *shell_info, char **args);
int execute_builtin_or_command(shell_info_t *shell_info);

/* From string_utilities.c */
int calculate_string_length(char *str);
int compare_strings(char *str1, char *str2);
char *string_starts_with(const char *string, const char *substring);
char *concatenate_strings(char *destination, char *source);

/* From command_utilities.c */
char *copy_string(char *destination, char *source);
char *duplicate_string(const char *str);
void print_string(char *str);
int print_character(char c);
char *find_command_path(shell_info_t *shell_info, char *cmd);

/* From shell_command_processing.c */
void process_shell_commands(shell_info_t *shell_info);
void replace_aliases(shell_info_t *shell_info);
void replace_variables(shell_info_t *shell_info);
void replace_variable_in_command(shell_info_t *shell_info, char **command);

/* Additional utility functions from discussion (if used in refactoring) */
void reset_shell_info(shell_info_t *info);
void prompt_if_interactive(shell_info_t *info);
ssize_t fetch_user_input(shell_info_t *info);
void initialize_shell_info(shell_info_t *info, char **args);
void finalize_shell_execution(shell_info_t *info);
int determine_exit_code(shell_info_t *info, int command_status);
char *get_environment_variable(shell_info_t *info, const char *name);
void extract_path(char *pathstr, int *position, const char *cmd);
int is_direct_path(const char *cmd);
int is_executable(const char *filepath);
list_t *create_history_node(const char *entry, int index);
void add_history_node(list_t *head, const char *entry, int index);
void free_node(list_t *node);
int remove_head_node(list_t **head);


#endif /* SHELL_H */
