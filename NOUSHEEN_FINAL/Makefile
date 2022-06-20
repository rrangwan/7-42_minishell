# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nali <nali@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 14:00:31 by nali              #+#    #+#              #
#    Updated: 2022/06/20 10:05:45 by nali             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT	= libft

SRCS	= main.c ft_utils.c ft_check_pipe.c ft_lexer.c ft_free.c ft_expander.c \
		ft_strjoin_new.c ft_envp.c ft_split_redirection_pipe.c ft_split_helper.c \
		ft_trim.c ft_parser.c ft_list.c ft_redirections.c ft_input_redirection.c \
		ft_output_redirection.c ft_utils2.c ft_error.c ft_cmd_path.c get_next_line.c \
		get_next_line_utils.c ft_pipex.c ft_pipex_utils.c ft_pipex_process.c ft_dup.c \
		builtin.c ft_echo_env.c ft_pwd_exit.c ft_unset.c ft_cd.c ft_cd2.c \
		ft_export.c ft_export2.c ft_export3.c signal.c
		

OBJS	= ${SRCS:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -I /usr/local/opt/readline/include

READ_LIB = -L /usr/local/opt/readline/lib 

OFLAGS  = -L/usr/local/lib -I/usr/local/include -lreadline

LIBS	= libft.a

RM		= rm -f

all:	${NAME}

.c.o:	${CC} ${CFLAGS} -I -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C ${LIBFT}
			cp libft/libft.a .
			$(CC) ${CFLAGS} -g ${SRCS} ${OFLAGS} ${LIBS} ${READ_LIB} -lreadline -o $(NAME)


clean:
			${RM} ${OBJS}
			${RM} tmp_file
			make clean -C ${LIBFT}

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFT}/libft.a libft.a

re:			fclean all

.PHONY:		all clean fclean re .c.o
