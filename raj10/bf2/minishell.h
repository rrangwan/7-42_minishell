/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:00:58 by nali              #+#    #+#             */
/*   Updated: 2022/06/17 08:46:59 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
//# include <stddef.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "LIBFT/libft.h"
# include <signal.h>
//# include <sys/wait.h>
//# include <sys/stat.h>

//extern	int	err_code;
int	g_err;

typedef struct s_var
{
	char	prompt[11];
	char	**env_var;
	//t_cmd	*cmd_lst;
}t_var;


void	built_in2(char **cmd, t_var *vars);
int		built_in1(char **cmd, t_var *vars);
void	ft_echo(char **cmd);
void 	ft_cd(char **cmd, t_var *vars);
void	ft_cd3(char **cmd, t_var *vars, char *dir, char *old_pwd);
void	ft_cd4(t_var *vars, char *new_pwd, char *old_pwd);
char	*ft_cd1(t_var *vars);
void	ft_newpwd(t_var *vars, char *new_pwd);
void	ft_oldpwd(t_var *vars, char *old_pwd);
void	ft_pwd(void);
void	ft_env(t_var *vars);
void	ft_free_env(t_var *vars);
void	ft_init_vars(t_var	*vars, char **envp);
void	ft_unset2(int j, t_var *vars);
void	ft_unset(char **cmd, t_var *vars);
int 	ft_is_export(char **cmd);
char 	*ft_is_export2(char **cmd);
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
void	ft_exit(char **cmd, t_var *vars);
int		ft_exitb(char **cmd);
int		ft_array_len(char **cmd);
void	ft_sig(int sig);
//void	ft_sig2(int sig);
#endif
