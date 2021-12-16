/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:25:06 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/16 15:17:59 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <signal.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

# ifndef OPEN_MAX
#  define OPEN_MAX  10240
# endif

# define CMD_NOT_FOUND 127
# define REDIRECTION_ERROR 258
# define INVALID_ARG 128
# define ERROR_EXE 126
# define BUILT_IN_ERROR 2
# define ARGS_COUNT_ERR 6
# define DOUBLE_PIPE 7
# define EMPTY_PIPE 8

# define NULLPTR 0
# define ERROR 1
# define SUCCESS 0
# define FALSE 0
# define FAIL -1
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define BUFF_SIZE 1024
# define UP 4283163
# define LEFT 4479771
# define RIGHT 4414235
# define DOWN 4348699
# define BACKS 127
# define CTRLD 4

# define CFLAG 0b00000001
# define NONE_F 0b00000000
# define EXIT_F 0b00000100
# define ERROR_F 0b00000010

typedef struct s_list
{
	char *str;
	char *id;
	int	rev_flag;
	struct s_list *pre;
	struct s_list *next;
}	t_list;

typedef struct s_builtin
{
	struct s_list *cmd;
	struct s_builtin *pre;
	struct s_builtin *next;
}	t_builtin;

typedef struct s_ms
{
	int	history_count;
	int	sig;
	int	status;
	int status_prec;
	int	pip[2];
	char *input;
	t_list *venv;
	int	len;
	int	pos;
	struct termios term;
	struct termios save;
	t_list *history;
	t_list *first;
	t_builtin *builtin;
	pid_t	pid;
}	t_ms;

typedef int				t_bool;
t_ms *g_ms;

// ################# MAIN and TERMINAL ##################

int				main(int ac, char **av, char **env);
void			ft_loop(t_list *venv);
void			ft_reset(void);
void			ft_term_init(void);
void			ft_prompt(void);
void			ft_history_add(void);
void			ft_backs(int *pos, int *len);
void			ft_down(int *pos, int *len);
void			ft_up(int *pos, int *len);
void			ft_right(int *pos);
void			ft_left(int *pos);
int				ft_putchr(int c);

// ##################### UTILS #########################

char			*ft_strchr2(const char *s, int c);
char			*ft_add_one_char(char **str, int pos, char c);
char			*ft_del_one_char(char **str, int pos);
char			*ft_strdup2(const char *s, int len);
void			*ft_calloc(size_t v, size_t size);
int				ft_malloc(void *v, int size);
void			ft_freebuilt(t_builtin **node);
t_list			*ft_gotofirst(t_list *list);
t_builtin		*ft_build_and_save(t_list *list);
t_builtin		*ft_build_and_save2(t_list *list);
void			ft_error(char *str);
void			ft_error2(char *name, char *msg);
void			ft_errorsyntax(char c);
int				ft_strlen2(char **av);
void			ft_freen(char **s, int n);
void			ft_free(void *s);
char			**ft_venvtoa(t_list *venv);
char			**ft_ltoa(t_list *list);
void			ft_listdelone(t_list **list);
void			ft_delbuilt(t_builtin **node);
void			ft_listadd_back(t_list **list, t_list **new);
int				ft_lstcount(t_list	*list);
void			ft_freelist(t_list **list);
t_list			*ft_list_save(t_list *list);
void			ft_listadd_tail(t_list **list, t_list **new);
void			ft_listadd_front(t_list **list, t_list **new);
t_list			*ft_listnew(char *str, char *id);
int				ft_strncmpms2(const char *c1, const char *c2, size_t n);
int				ft_strncmpms(const char *c1, const char *c2, int n);
int				ft_isnum(const char *s);
char			*ft_strchr1(const char *s, char c);
void			ft_freehistory(t_list **list);

// ################### READ and Parse #####################

void			ft_builtin_split(t_builtin	*node, char *s);
void			ft_remove_space2(t_builtin *node);
void			ft_remove_space(t_builtin *node);
void			ft_add_space(t_builtin *node);
int				ft_check_input(char *input);
int				ft_special_char(char *input, int *f, int *i);
int				ft_check_first_arg(char *input);
void			ft_read(void);
void			ft_read_init(int *len, int *pos);
void			ft_prompt_print(int c, int *pos, int *len);
void			ft_remove_space3(t_builtin *node);
void			ft_remove_q(t_list *list);
t_list			*ft_tokenize(char *input);
void			ft_init_tok(t_list **tok, char **start, int *q_f, int *q_t);
void			ft_replace_venv(t_list *list, t_list *venv);
int				ft_replace_venv2(t_list *list, t_list *venv, int *i);
void			ft_skip_quotes(char *s, int *i);

// ################### Execute #####################

int				ft_cmd_exit(t_builtin *node);
int				ft_close(int fd);
int				ft_exe(t_builtin *node, t_list **venv);
int				ft_exe2(t_builtin *node, t_list **venv, int *fd);
int				ft_execve(t_builtin *node, t_list *venv);
void			ft_manager(t_list **venv, t_builtin *node);
void			ft_parent(int *status, pid_t pid);
void			ft_close_child(int **fd, int in, int out);
void			ft_close_parent(int **fd, int order);
int				ft_check_status(int status);
int				**ft_pip_free(int ***pip, int size);
int				**ft_pip_init(int size);
int				ft_pip_count(t_builtin *node);
int				ft_pip_size(int **fd);
int				ft_pipexe(t_builtin *node, t_list **venv, int **fd, int order);
int				ft_check_redi(t_builtin	*node, int i);
int				ft_redirection1(t_builtin *node, char c, int *fd);
int				ft_redirection2(t_builtin *node);
int				ft_redirection3(t_builtin *node, int *fd);
void			ft_exit_checker(int i);
void			ft_signal_pip(void);
void			ft_handler_pip(int sig);
void			ft_signal(void);
void			ft_handler(int sig);

// ################### Builtins #####################

int				ft_builtin(t_builtin *node, t_list **venv);
int				ft_cmd_cd(t_builtin *node, t_list **venv);
int				ft_cmd_echo(t_builtin *node/*, t_list *venv*/);
int				ft_cmd_env(t_builtin *node, t_list *venv);
void			ft_show_env2(t_list *l, char *s);
void			ft_show_env(t_list *venv, char *name);
int				ft_cmd_export(t_builtin *node, t_list **venv);
int				ft_cmd_pwd(t_builtin *node);
int				ft_cmd_unset(t_builtin *node, t_list **venv);
t_list			*ft_init_env(char **env);
void			ft_rem_env(t_list **venv, char *var);
int				ft_add_venv(t_list **venv, char *var, char *val);
char			*ft_getvenv(t_list *venv, const char *var, int len);
int				ft_envlist(char c);

#endif
