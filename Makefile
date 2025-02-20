# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 13:59:30 by aalahyan          #+#    #+#              #
#    Updated: 2025/02/20 18:00:15 by aalahyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror
LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
BIN=bin
MANDATORY=mandatory
BONUS=bonus
NAME_BONUS=pipex_bonus
BONUS_HEADERFILE=$(BONUS)/pipex_bonus.h
HEADERFILE=$(MANDATORY)/pipex.h

CFILES=		$(MANDATORY)/main.c \
			$(MANDATORY)/assets.c\
			$(MANDATORY)/execute_command.c\
			$(MANDATORY)/ft_split_pipex.c\
			$(MANDATORY)/get_command_array.c\
			$(MANDATORY)/valid_command.c\

CFILES_BONUS= 	$(BONUS)/main_bonus.c\
				$(BONUS)/ft_split_pipex_bonus.c\
				$(BONUS)/valid_command_bonus.c\
				$(BONUS)/get_command_array_bonus.c\
				$(BONUS)/multiple_pipes_bonus.c\
				$(BONUS)/assets_bonus.c\
				$(BONUS)/exec_pipes_bonus.c\
				$(BONUS)/here_doc_bonus.c

OFILES=$(CFILES:$(MANDATORY)/%.c=$(BIN)/%.o)
OFILES_BONUS=$(CFILES_BONUS:$(BONUS)/%.c=$(BIN)/%.o)



NAME=pipex

all: libft $(NAME)

$(NAME): $(BIN) $(OFILES) 
	$(CC) $(OFILES) -L$(LIBFT_DIR) -lft -o $@

bonus: libft $(NAME_BONUS)

$(NAME_BONUS): $(BIN) $(OFILES_BONUS)
	$(CC) $(OFILES_BONUS) -L$(LIBFT_DIR) -lft -o $@
$(BIN)/%.o: mandatory/%.c $(HEADERFILE)
	$(CC) $(CFLAGS) -c $< -o $@
$(BIN)/%.o: $(BONUS)/%.c $(BONUS_HEADERFILE)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):
	mkdir -p $@
libft:
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(BIN)

fclean:	clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME) $(NAME_BONUS)
re:fclean all
.PHONY: all clean fclean libft re

