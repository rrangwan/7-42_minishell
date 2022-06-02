/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:00:58 by nali              #+#    #+#             */
/*   Updated: 2022/06/02 19:32:05 by nali             ###   ########.fr       */
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
	char	prompt[11];
	char	**env_var;
}t_var;

//ft_lexer.c
void	ft_lexer(char *input, t_var	*vars);
// ft_utils.c
int		ft_strcmp(char *s1, char *s2);
//ft_free.c
void	ft_free_env(t_var *vars);
void	ft_print_tokens(char **tokens);
void	ft_free_tokens(char **tokens);


#endif