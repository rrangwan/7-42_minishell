# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 14:00:31 by nali              #+#    #+#              #
#    Updated: 2022/05/30 05:46:21 by nali             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT	= libft

SRCS	= main.c ft_utils.c ft_lexer.c ft_expander.c ft_strjoin_new.c ft_sub_split.c  
OBJS	= ${SRCS:.c=.o}

CC		= gcc

CFLAGS	= -Wall 

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