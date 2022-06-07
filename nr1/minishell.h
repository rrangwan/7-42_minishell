/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:00:58 by nali              #+#    #+#             */
/*   Updated: 2022/06/07 20:39:17 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../LIBFT/libft.h"

extern	int	err_code;

typedef struct s_cmd
{
	char			**cmd;
	char			*in_fd;
	char			*out_fd;
	// char			*path;
	// int				redirect;
	// int				redir_stdin;
	// int				redir_stdout;
	// pid_t			pid;
	// int				std_in;
	// int				std_out;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_var
{
	char	prompt[11];
	char	**env_var;
	t_cmd	*cmd_lst;
}t_var;

//ft_lexer.c
void	ft_lexer(char *input, t_var	*vars);
void	ft_check_if_quote(char *s, int i, int *qval, int *openq);
// ft_utils.c
int		ft_strcmp(char *s1, char *s2);
void	ft_print_list(t_cmd *cmd_lst);
//ft_free.c
void	ft_free_env(t_var *vars);
void	ft_print_tokens(char **tokens);
void	ft_free_tokens(char **tokens);
//ft_expander.c
void	ft_expander(char **tokens, t_var *vars);
//ft_strjoin_new.c
char	*ft_strjoin_new(char *s1, char *s2);
//ft_envp.c
char	*ft_handle_dollar(char *str, int p, t_var *vars, int qval);
//ft_split_pipe.c
char	**ft_split_redirection_pipe(char **tokens);
//ft_trim.c
char	**ft_trim(char **tokens);
// ft_parser.c
void    ft_parser(char **tokens, t_var *vars);
//ft_list.c
void	ft_create_list(char **tokens, t_var *vars);
//Raj buitin.c
void	built_in2(char **cmd, t_var *vars);
int		built_in1(char **cmd, t_var *vars);
void	ft_echo(char **cmd);
void ft_cd(char **cmd, t_var *vars);
void	ft_newpwd(t_var vars, char *new_pwd);
void	ft_oldpwd(t_var vars, char *old_pwd);
void	ft_pwd(void);
void	ft_env(t_var *vars);
//Raj buitin2.c
void	ft_unset2(int j, t_var *vars);
void	ft_unset(char **cmd, t_var *vars);
void	ft_export(char **cmd, t_var *vars);
char *ft_is_export(char **cmd, t_var *vars);
void	ft_export3(char *cmd, int j, t_var *vars);
void	ft_export4(char *name, char *new, t_var *vars);
void	ft_export2(t_var *vars);
void	ft_exit(char **cmd, t_var *vars);
#endif
