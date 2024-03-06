# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 11:41:47 by dferreir          #+#    #+#              #
#    Updated: 2023/02/14 15:02:27 by dferreir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
GREEN		= \033[0;32m
RED 		= \033[0;31m
BOLD		= \033[1m
NORMAL		= \033[0m
UP 			= \033[A
CUT 		= \033[K

#OUTPUT
NAME		= fdf

#FILES
LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	= ./libft/
LIBFT_HEADS	= $(LIBFT_DIR)incs/

MINILIBX	= $(MINILIBX_DIR)libmlx.a
MINILIBX_DIR = ./minilibx_macos/

HEADS_LIST	= fdf.h
HEADS_DIR	= ./incs/
HEADS		= $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SRCS_DIR	= ./srcs/
SRCS_FILES	= main.c init.c utils.c controls.c keyboard_controls.c mouse_controls.c stack_filler.c draw.c colors.c projection.c
SRCS		:= ${addprefix ${SRCS_DIR}, ${SRCS_FILES}}

OBJS_DIR	= ./objs/
OBJS_FILES	:= ${SRCS_FILES:.c=.o}
OBJS		:= ${addprefix ${OBJS_DIR}, ${OBJS_FILES}}

#COMMANDS
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
MKDIR		= mkdir -p
RM			= rm -rf
LIBS		= -lmlx -lm -lft -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -framework OpenGL -framework AppKit
INCS		= -I$(HEADS_DIR) -I$(LIBFT_HEADS) -I$(MINILIBX_DIR)

all: ${NAME}

#Compile normal executable
${NAME}: ${LIBFT} ${MINILIBX} ${OBJS_DIR} ${OBJS}
	@${CC} -g ${CFLAGS} ${LIBS} ${INCS} ${OBJS} -o ${NAME}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) created and compiled object files"
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) $(BOLD)$(NAME)$(NORMAL) is ready"

#Create objects directory
${OBJS_DIR}:
	@${MKDIR} ${OBJS_DIR}

#Compile normals objects
${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@echo "$(RED)[$(BOLD)Compiling$(NORMAL)$(RED)]$(NORMAL) $<$(UP)$(CUT)"
	@${CC} -g ${CFLAGS} ${INCS} -o $@ -c $<

${LIBFT}:
	@make -C ${LIBFT_DIR}

${MINILIBX}:
	@make -C ${MINILIBX_DIR}

#Clean obj files
clean:
	@make -C ${LIBFT_DIR} clean
	@make -C ${MINILIBX_DIR} clean
	@${RM} ${OBJS_DIR}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) object files deleted"

#Clean objs files and name
fclean:	clean
#	@${RM} ${MINILIBX}
	@${RM} ${LIBFT}
	@${RM} ${NAME}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) $(BOLD)$(NAME)$(NORMAL) deleted"

#valgrind: all
#	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

re: fclean all

.PHONY: all clean fclean re #valgrind
