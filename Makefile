NAME = minishell
LIB_F = libft
LIB = libft.a
SRC = src
OBJ = obj
INC = inc
CFLAGS = -Wall -Wextra -Werror -g -I$(INC)
RM = rm -rf
CC = gcc
SRCS = src/b_exit.c src/builtins.c src/cd.c src/checkers.c src/cmd.c src/destroy.c src/echo.c src/env.c src/env_builtins.c src/env_utils.c src/execute.c src/execute_log.c src/execute_utils.c src/export.c src/export_print.c src/here_doc.c src/int_list.c src/lexer.c src/lexer_utils.c src/lexical_errors.c src/lexical_errors_utils.c src/log_group.c src/main.c src/open_extentions.c src/open_quotes.c src/parse.c src/parse_actions.c src/pipe_group.c src/print_check.c src/read_input.c src/recursion_depth.c src/redirect.c src/sig_handle.c src/signals.c src/str_list.c src/token.c src/token_delim_logic.c src/token_delim_pipe.c src/utilits.c src/wildcard.c src/wildcard_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB_F)/$(LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_F)/$(LIB) -o $(NAME) -lreadline

$(LIB_F)/$(LIB):
	@make -C $(LIB_F)
	@echo "libft is done!"

clean:
	@$(RM) $(OBJS)
	rm -rf obj 
	@echo "successfuly cleaned"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIB_F)
	@echo "executable removed successfuly"

re: fclean all
