# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 15:35:05 by gda_cruz          #+#    #+#              #
#    Updated: 2023/02/28 14:51:31 by gda_cruz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN		=	\033[0;32m
GREEN_BOLD	=	\033[1;32m
RED			=	\033[0;31m
YELLOW		=	\033[0;33m
BLUE		=	\033[0;34m
BLUE_BACK	=	\033[0;44m
RESET		=	\033[0m

NAME 		=	minishell

LIBFT_DIR		=	lib

SRC			= 	$(shell find srcs/ -name '*.c')

OBJ			=	$(SRC:.c=.o)

INC_DIR		=	inc
BUILD_DIR	=	./build

CC			=	gcc

CFLAGS		=	-g -Wall -Wextra -Werror
LDFLAGS		=	-lreadline
LIBFT_FLAGS	=	-L$(LIBFT_DIR) -lft

.o.c:
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $(<:.c=.o)
	@printf "$(YELLOW)[OK]     "$@"$(RESET)\n"

all: $(NAME)

$(NAME):	$(BUILD_DIR) $(OBJ)
	@echo "\n$(BLUE)Compiling libft...$(RESET)"
	@make -s -C $(LIBFT_DIR)
	@echo "$(YELLOW)[Libft successfully compiled!]\n$(RESET)"
	@echo "$(BLUE)Compiling minishell...$(RESET)"
	@$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@mv $(OBJ) $(BUILD_DIR)
	@printf "$(GREEN)------------------------\n$(RESET)"
	@printf "$(GREEN_BOLD)[minishell ready to use]\n$(RESET)"
	@printf "$(GREEN)------------------------\n$(RESET)"

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	@make clean -s -C $(LIBFT_DIR)
	@rm -rf $(BUILD_DIR)

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -rf build minishell
	@echo "$(RED)[All minishell files removed]$(RESET)"

re: fclean all

.PHONY: all clean fclean re
