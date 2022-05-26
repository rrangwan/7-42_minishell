/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:00:58 by nali              #+#    #+#             */
/*   Updated: 2022/05/26 06:50:43 by nali             ###   ########.fr       */
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
# include "LIBFT/libft.h"

typedef struct s_var
{
	char	prompt[2];
	char	**env_var;
}t_var;

//ft_parser.c
void	ft_parse_args(char *buf);
//ft_utils.c
int		ft_strcmp(char *s1, char *s2);
int		ft_chk_spce_tab(char ch);
void	ft_free_memory(char **tokens);
void	ft_free_env(t_var *vars);
//ft_lexer.c
void	ft_lexer(char *input, t_var	vars);
//ft_expander.c
void	ft_expander(char **tokens, t_var vars);
//ft_strjoin_new
char	*ft_strjoin_new(char *s1, char *s2);

#endif