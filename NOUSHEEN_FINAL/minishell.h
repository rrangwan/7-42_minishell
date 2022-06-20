/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:00:58 by nali              #+#    #+#             */
/*   Updated: 2022/06/20 12:34:16 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "LIBFT/libft.h"

extern int	g_err;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	5
# endif

typedef struct s_cmd
{
	char			**cmd;
	char			*cmd_path;
	int				in_fd;
	int				out_fd;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_var
{
	char	prompt[11];
	char	**env_var;
	t_cmd	*cmd_lst;
	int		cmd_count;
	int		pipe_count;
	int		**pipe_fds;
	int		num;
}t_var;

//ft_lexer.c
void	ft_lexer(char *input, t_var	*vars);
void	ft_check_if_quote(char *s, int i, int *qval, int *openq);
// ft_utils.c
int		ft_strcmp(char *s1, char *s2);
int		ft_chk_not_space_tab_newline(int ch);
void	ft_init_var_zero(int *i, int *j, int *q0, int *q1);
void	ft_print_list(t_cmd *cmd_lst);
void	ft_print_tokens(char **tokens);
//ft_free.c
void	ft_free_env(t_var *vars);
void	ft_free_tokens(char **tokens);
void	ft_free_list(t_var *vars);
void	ft_free_array(char **arr);
void	ft_free(char *buf, t_var *vars);
//ft_expander.c
void	ft_expander(char **tokens, t_var *vars);
void	ft_skip_till_next_quote(char *s, int *j, int *qval, int *open_quote);
//ft_strjoin_new.c
char	*ft_strjoin_new(char *s1, char *s2);
//ft_envp.c
char	*ft_handle_dollar(char *str, int p, t_var *vars);
//ft_split_pipe.c
char	**ft_split_redirection_pipe(char **tokens);
// ft_split_helper.c 
int		ft_split_count(char **tokens);
int		ft_check_symbols(char *str, int *index, int count);
void	ft_handle_non_symbols(char *token, int *j, int *qv, int *open_quote);
//ft_trim.c
char	**ft_trim(char **tokens);
// ft_parser.c
void	ft_parser(char **tokens, t_var *vars);
void	ft_free_paths(char **paths);
//ft_list.c
void	ft_create_list(char **tokens, t_var *vars);
//ft_redirections.c
t_cmd	*ft_redirections(t_cmd *cmd_node);
//ft_input_redirection.c
char	**ft_remove_redirection(char **cmd, int c, int index);
char	**ft_input_redirection(char **cmd, int index, int *fd);
char	**ft_heredoc(char **cmd, int index, int *fd);
// ft_output_redirection.c  
char	**ft_output(char **str, int index, t_cmd *lst_node);
// ft_check_pipe.c
char	*ft_check_pipe(char *buf);
char	*ft_add_newline(char *buf);
//ft_error.c
void	ft_malloc_error(void);
void	ft_parse_error(void);
void	ft_cmd_error(char *cmd);
//ft_utils2.c
int		ft_count_cmd(t_cmd *cmd_lst);
//ft_cmd_path.c
char	**ft_get_path_variable(char	**env_var);
char	*ft_get_cmd_path(t_cmd	*cmd_lst, char **paths);
int		ft_set_cmd_path(t_cmd *cmd_node, t_var *vars);
//ft_pipex.c
void	ft_pipex(t_var *vars);
// ft_pipex_utils.c
int		**ft_open_pipes(int p);
void	ft_close_pipes(int **fd, int p);
void	ft_close_fds(t_cmd *cmd_lst);
void	ft_free_pipes(int **fd, int p);
// ft_pipex_process.c  
void	ft_child_process(int i, t_var *vars);
//ft_dup.c
int		ft_dup(int i, t_cmd	*cmd_node, int	**pipe_fds);
// get_next_line
char	*get_next_line(int fd);
int		ft_findlen(const char *s);
char	*str_concat(char *s1, const char *s2);
// //Raj buitin.c

void	built_in2(char **cmd, t_var *vars);
int		built_in1(char **cmd, t_var *vars);
void	ft_echo(char **cmd);
void	ft_cd(char **cmd, t_var *vars);
void	ft_cd3(char **cmd, t_var *vars, char *dir, char *old_pwd);
void	ft_cd4(t_var *vars, char *new_pwd, char *old_pwd);
char	*ft_cd1(t_var *vars, char *old_pwd);
void	ft_cd5(char	*new_pwd, char **cmd);
void	ft_newpwd(t_var *vars, char *new_pwd);
void	ft_oldpwd(t_var *vars, char *old_pwd);
void	ft_pwd(void);
void	ft_env(t_var *vars, char **cmd);
//// void	ft_free_env(t_var *vars);
// // void	ft_init_vars(t_var	*vars, char **envp);
void	ft_unset2(int j, t_var *vars);
void	ft_unset(char **cmd, t_var *vars);
int		ft_is_export(char **cmd);
char	*ft_is_export2(char **cmd);
void	ft_export2c(char **array, t_var *vars);
int		ft_is_export3(char *cmd);
void	ft_export(char **cmd, t_var *vars);
char	**ft_export2b(t_var *vars);
void	ft_export2(t_var *vars);
void	ft_export3(char *cmd, t_var *vars);
void	ft_export4(char *name, char *new, t_var *vars);
void	ft_export4b(t_var *vars, char *new);
char	*ft_export5(char *cmd);
char	*ft_export6(char *cmd);
int		ft_export7(char *cmd);
void	ft_exit(char **cmd);
int		ft_exitb(char **cmd);
int		ft_array_len(char **cmd);
void	ft_sig(int sig);
void	ft_shell_lvl(t_var *vars);
//signal.c
void	ft_sig_handler(int signal);
#endif
