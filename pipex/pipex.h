/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:59:21 by nali              #+#    #+#             */
/*   Updated: 2022/02/08 23:15:32 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	5
# endif

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct input
{
	int		argc;
	char	**argv;
	char	**envp;
	int		file1;
	int		file2;
	int		**fds;
	int		status1;
	int		status2;
}	t_input;

//pipex_bonus.c
void	ft_free_mem_close_fd(t_input info, int num);
void	ft_close_fds(int f1, int f2);
//pipex_utils.c
void	ft_execute_command(char **paths, char **cmd_list, char *envp[]);
char	**ft_get_path_variable(char *envp[]);
//cmd_formating.c
char	**ft_get_command_list(char *command);
char	**ft_strip_leading_trailing_space(char **cmd_list);
//process.c
int		ft_child_process_frst_b(int *fd_wr, int file1, char *cmd, t_input info);
int		ft_child_process_last_b(int *fd_r, int file2, char *cmd, t_input info);
int		ft_child_process_mid_b(int *fd_r, int *fd_wr, char *cmd, t_input info);
void	ft_error_code(int id, int status);
//pipex_bonus_utils.c
int		**ft_open_pipes_b(int argc);
void	ft_close_pipes_b(int **fd, int argc);
void	ft_free_fd_b(int **fd, int argc);
int		ft_strcmp(char *s1, char *s2);
void	ft_free_mem_stdin(char *line, char *trim_line);
//handle_stdin.c
int		ft_handle_stdin_function(int argc, char **argv, char **envp);
//get next line
char	*get_next_line(int fd);
int		ft_findlen(const char *s);
char	*str_concat(char *s1, const char *s2);

#endif