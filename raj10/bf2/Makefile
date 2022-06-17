# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 14:00:31 by nali              #+#    #+#              #
#    Updated: 2022/06/17 09:04:02 by rrangwan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT	= libft

SRCS	= builtin2.c builtin.c main.c builtin3.c builtin4.c builtin5.c builtin6.c builtin7.c signal.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

OFLAGS  = -L/usr/local/lib -I/usr/local/include -lreadline

LIBS	= libft.a

RM		= rm -f

all:	${NAME}

.c.o:	${CC} ${CFLAGS} -I -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C ${LIBFT}
			cp libft/libft.a .
			$(CC) ${CFLAGS} -g ${SRCS} ${OFLAGS} -L. ${LIBS} -o $(NAME)


clean:
			${RM} ${OBJS}
			make clean -C ${LIBFT}

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFT}/libft.a libft.a

re:			fclean all

.PHONY:		all clean fclean re .c.o
