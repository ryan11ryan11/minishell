
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:46:54 by junhhong          #+#    #+#             */
/*   Updated: 2024/07/08 22:32:08 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <sys/types.h>
# include <dirent.h>

# define SUCCESS 1
# define FAIL 0
# define STDERR 2
# define STDOUT 1

typedef struct s_envlist
{
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

typedef struct s_data
{
	struct s_envlist	*envlist;
}	t_data;


void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_echo(char *argv[]);
void		ft_cd(char *argv[]);
int 		ft_pwd(void);
int			ft_export(char *argv[], t_envlist *envlist);
void		ft_env(void);
t_envlist	*ft_lstnew(void *content);
void		envlist_addback(t_envlist **lst, t_envlist *new);
t_envlist	*envlist_new(void *content);
t_envlist	*ft_lstlast(t_envlist *lst);
t_envlist	*ft_envlast(t_envlist *lst);
int			ft_strcmp2(const char *s1, const char *s2);
int			ft_isalnum(int c);
void		ft_putstr_fd(char *s, int fd);
int			ft_unset(t_data *data, char *argv[]);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);




#endif