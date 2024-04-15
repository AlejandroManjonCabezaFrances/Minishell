# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 09:03:02 by amanjon-          #+#    #+#              #
#    Updated: 2024/04/15 11:30:24 by amanjon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I /libft/ft_printf/include -I /libft/gnl/include -I /libft/Libft/include
# DEBUG = -g3 -fsanitize=leak
RM = rm -f
SRC = main.c main_utils.c lexer.c lexer_utils.c list_utils.c list_utils_2.c error.c \
		parser.c parser_utils.c parser_utils_2.c parser_utils_3.c \
		parser_utils_4.c parser_utils_5.c parser_utils_6.c env.c heredoc.c exec.c \
		exec_utils.c exec_utils_2.c exec_utils_3.c signals.c utils_builtins_1.c utils_builtins_2.c utils_builtins_3.c \
		utils_builtins_4.c builtins/cd_1.c builtins/cd_2.c builtins/cd_3.c builtins/echo.c builtins/environment.c \
		builtins/exit.c builtins/export_1.c builtins/export_2.c builtins/export_3.c builtins/unset.c \
		builtins/builtins.c builtins/pwd.c \

# 42 # **********************
# READLINE 
RLINE_INC	= -I/sgoinfre/students/$(USER)/homebrew/opt/readline/include
RLINE_L		= -lreadline -L /sgoinfre/students/$(USER)/homebrew/opt/readline/lib

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

SRC_DIR = ./src/
OBJ_DIR = ./obj/
OBJ_BUILTINS = ./obj/builtins/

OBJ_FILES = $(SRC:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# COLOURS
GREEN = \033[0;32m
COLOR_OFF = \033[0m

# RULES
all: $(OBJ_DIR) $(LIBFT_DIR) $(NAME)

$(LIBFT): $(LIBFT_DIR)
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_BUILTINS)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(RLINE_INC) -c $< -o $@

# basic library compiled
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) $(LIBFT) $(RLINE_L) -o $(NAME)
	@echo "$(GREEN)#### minishell ####$(COLOR_OFF)"
	@echo "    -Has been compiled ✅"

# all .o files removed
clean:
	@$(RM) $(OBJ)
	@make clean -C libft
	@rm -rf $(OBJ_DIR)

# library .a file removed
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft
	@rm -rf $(OBJ_DIR)

re:	fclean all

.PHONY:	all clean fclean re
