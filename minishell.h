/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:36:29 by jbober            #+#    #+#             */
/*   Updated: 2024/10/24 14:19:47 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h> 
# include <termios.h>
# include <unistd.h>

typedef struct s_data		t_data;
typedef struct s_heredoc	t_heredoc;
typedef struct s_list		t_list;
typedef struct s_node		t_node;

extern int					g_lastexit;

typedef struct s_data
{
	int					redisplay;
	char				**currstr;
	t_list				*lstart;
	t_list				*currmds;
	t_heredoc			*heredoc;
	char				*currinput;
	int					num_envp;
	char				**env;
	int					errcode;
	int					env_set;
	int					num_pipe;
	char				**patharr;
	int					num_ndata;
	int					**pipe;
	char				**new_envp;
	struct s_envlist	*envlist;
	pid_t				*pid;
}	t_data;

typedef struct s_heredoc
{
	char				buffer[2048];
	int					total_byte;
	int					byte_read;
	char				*delimiter;
	char				*last_word;
	int					fd[2];
	pid_t				pid;
}	t_heredoc;

typedef struct s_list
{
	t_node				*content;
	struct s_list		*next;
}	t_list;

typedef struct s_node
{
	char				**cmd;
	char				*path;
	char				**infd;
	char				**outfd;
	int					*status;
	int					oper;
}	t_node;

typedef struct s_envlist
{
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

/*
	--- asd ---
*/

// error

extern void		ms_error(t_data *data, char *str, int brexit);
extern void		ms_error_woexit(t_data *data, int brexit);

// free

extern void		ms_free(t_data *data, int modus);

// minishell

extern int		main(int argc, char **argv, char **envp);

/*
	--- parse ---
*/

// parse

extern char		*ms_parse_ctrl(t_data *data, char **envp);

// parsefk1 + b

extern char		*ms_parsefk1_ctrl(t_data *data);

extern char		*ms_add_32(char *str, int weakqt, int strongqt);

// parsefk2 + b

extern char		*ms_parsefk2_ctrl(t_data *data);
extern int		ms_get_lenterm(char *str, int l);
extern char		*ms_get_value(t_data *data, char *str, int l, int lenterm);

extern char		*ms_replace_term(t_data *data, char *str1ng, int l);

// parsefk4

extern char		*ms_parsefk4_ctrl(t_data *data);

// parsefk5 + b + c

extern char		*ms_parsefk5_ctrl(t_data *data, int i, int k);

extern char		*ms_deqtfy_nodes(t_data *data, t_list *iamhere);
extern char		*ms_cleanqt(char *str, int weakqt, int strongqt, int modus);
extern int		ms_allocstatus(t_node *content, int noutfd);

extern int		ms_fillnodexta(t_data *data, t_node *content, int i, int k);

// ut1ls

extern char		*ms_speciasplit(t_data *data, char *str);
extern int		ms_check_qt(char c, int *weakqt, int *strongqt);
extern int		ms_envp(t_data *data, char **envp);

// ut2ls

extern int		ms_strncmp(char	*set, char *str, int len);
extern char		*ms_strdup(char *str);
extern int		ms_strlen(char *str);
extern int		ms_checkmds(t_data *data);

// ut3ls

extern t_list	*ms_lstnew(t_data *data);
extern void		ms_lstadd_back(t_data *data, t_list **lst);

// ut4ls

char			*ms_itoa(int n);
int				ms_cinset(char c, char *set, int modus);

/*

	--- execution ---

*/

// builtin_control

int				count_arg(t_data *data);
int				builtin(t_data *data, t_list *list);
int				ft_strcmp2(const char *s1, const char *s2);
int				builtin_exception2(char *arr);
int				builtin_exception(t_list *node);

//envlistclear

void			envlistclear(t_envlist *envlist);

//envp_list_maker

t_envlist		*ft_envlast(t_envlist *lst);
void			envlist_addback(t_envlist **lst, t_envlist *new);
t_envlist		*envlist_new(void *content);
int				env_size_checker(char *env[]);
int				envlistmaker(t_data *data, char *env[]);

//ft_cd

int				no_argument(t_node *content);
int				slash_up(t_node *argvt, char *input);
int				ft_cd(t_list *list);

//ft_echo

char			**filearr_maker(int file_num);
char			**filename_arr_maker(DIR *dir);
int				print_directory(void);
int				print_argv(t_node *argvt, int i);
int				ft_echo(t_data *data, t_list *node);

//ft_echo2

char			**argv_maker(char *line);
int				ft_strcmp3(const char *s1, const char *s2, int size);
int				all_n(char *txt, int len);
int				filenum_count(void);

//ft_env

int				ft_env(t_data *data);

//ft_export

int				ft_export(t_data *data, t_list *list);
void			print_all(t_envlist *envlist);
char			*quo_add(char *arr);
int				add_to_list(char **arr, t_data *data);
int				name_check(char *arr);

//ft_export2

int				underbar_alphabet(char *msg);
int				is_empty(char *msg);
int				is_alphabet(char *name);
int				is_duplicate(char *name, t_envlist *envlist, char *arr);
int				add_newblock(t_envlist **envlist, char *content);

//ft_export3

void			ft_envlist_back(t_envlist **lst, t_envlist *new);
void			fix_arr(char **arr);
char			*remove_quo(char *arr);

//ft_pwd

int				ft_pwd(void);

//ft_unset

void			delete_node(t_envlist **head, t_envlist *node_to_delete);
t_envlist		*find_value_envlist(t_envlist *envlist, char *arr);
int				ft_unset(t_data *data, t_list *list);

//herdoc_signal

void			heredoc_ctrl_c(int signum);
void			exec_pipe(t_data *data, t_list *list, int i);
void			free_pipe(t_data *info);

//pipe

void			init_pipe(t_data *data);

//pipe2

int				count_pipe(t_data *data);
int				**assign_pipe(int num_pipe);

//signal

void			set_terminal_print_on(void);
void			set_terminal_print_off(void);
void			ctrl_c(int signum);
void			ft_signal(void);

//util

int				ft_strlcmp_limited(const char *s1, const char *s2);
char			*ft_strcat(char *s1, char *s2);

//pipe_util10
int				only_num_pm(char *s);
int				get_code(t_data *data);
int				terminatation(t_data *data);
void			free_cwd_new(char *s1, char *s2);
int				is_path(t_data *data);

//pipe_utils9
void			child_ctrl_c(int signum);
void			child_signal(void);

//pipe_utils8

int				path_check(t_list *list, int i);
void			node_work(t_data *data, t_list *crt_node, int i);
void			child_process(t_data *data, t_list *crt_node, int i);
void			parent_process(t_data *data);
int				exec_command_errcheck(t_data *data);

//pipe_utils7

void			heredoc_read(t_heredoc *hrd);
void			child_ctrl_c(int signum);
void			child_signal(void);
void			case_heredoc(t_data *data, t_list *list);
int				case_infile(t_list *list);
t_list			*prv_list_finder(t_data *data, t_list *current_node);
void			exit_diff_code(int code);

//pipe_utils6

void			case_outfile(t_node *argvt);
char			*get_last_word(char *buffer, int index);
void			heredoc_parent(int *fd, int pid);
void			heredoc_struc_init(t_data *data, t_list *list);

//pipe_utils5

pid_t			*assign_pid(int num_args);
char			*absolute_path(t_data *data);

//pipe_utils4

int				all_component_check(t_data *data);
int				all_component_check2(t_list *list, t_data *data, int i);
void			all_pipe_close(t_data *data);
char			*new_path_maker(char *input);
void			builtin_situation(t_data *data, t_list *list);

//pipe_utils3

void			error_exit(char *msg, int error_number);
int				parent_process_exec(t_data *data);
int				is_pipe(t_data *data);
int				pipe_oper_exeption(t_data *data);
void			exec_command(t_data *data);

//pipe_utils2

char			*pathfinder(char *command, t_data *data);
void			count_lstart(t_data *data);
void			doublearr_free(char ***arr);
char			*ft_get_env(t_data *data);
void			data_setting(t_data *data);

//pipe_utils

int				count_envplist(t_data *data);
int				envp_setting(t_data *data);
void			envp_maker(t_data *data);
char			*slashadd(char *path);
char			*commandadd(char *slashadded, char *command);

//ft_lib

char			**ft_split(char const *s, char c);
void			ft_putstr_fd(const char *s, int fd);
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *s, int ch);

//ft_lib2

char			*ft_strncpy(char *dest, const char *src, size_t len);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
void			*ft_memset(void *s, int c, size_t n);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strdup(const char *src);

//ft_lib3

char			*ft_substr(char const *s, unsigned int start, size_t len);

//utils

char			*without_data(char *str);
void			print_current_path(void);
void			free_data(t_data *data);

// ft_atoi

long			ft_atoi(char *nptr);
int				ft_isdigit(int arg);

//remove!
int				all_component_check2(t_list *list, t_data *data, int i);
int				path_check(t_list *list, int i);
int				ft_isdigit(int arg);
void			envlist_free(t_data *data, t_envlist *head);
void			display_changer(t_data *data, t_list *list, int i);
void			test_print(t_data *data);
int				case_exit(char *line);
void			free_cwd_new(char *s1, char *s2);

#endif