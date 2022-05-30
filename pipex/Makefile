# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nali <nali@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 15:24:06 by nali              #+#    #+#              #
#    Updated: 2022/02/08 23:15:04 by nali             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex.a

SRCS	= pipex.c ft_pipex_utils.c ft_cmd_formating.c 

SRCS_B	= pipex_bonus.c ft_pipex_bonus_utils.c ft_process_bonus.c ft_handle_stdin.c \
		get_next_line.c get_next_line_utils.c ft_cmd_formating.c ft_pipex_utils.c

LIBFT 	= libft
		
OBJS	= ${SRCS:.c=.o}

OBJS_B	= ${SRCS_B:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra

RM		= rm -f

all:	${NAME}

.c.o:	${CC} ${CFLAGS} -I -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C ${LIBFT}
			cp libft/libft.a ./${NAME}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}
			${CC} pipex.c -L. ${NAME} -o pipex

			
bonus:		${OBJS_B}
			make -C ${LIBFT}
			cp libft/libft.a ./${NAME}
			ar rc ${NAME} ${OBJS_B}
			ranlib ${NAME}
			${CC} pipex_bonus.c -L. ${NAME} -o pipex	

clean:		
			${RM} ${OBJS} ${OBJS_B}
			make clean -C ${LIBFT}

fclean:		clean
			${RM} ${NAME}
			${RM} pipex
			${RM} ${LIBFT}/libft.a

re:			fclean all

.PHONY:		all clean fclean re .c.o