NAME = minishell
LIB = libft.a
SRC = src
INC = inc	
LIB_F = libft
OBJ = obj
CC := gcc
CFLAGS := -Wall -Wextra -Werror -g -I$(INC) 
SRC_F = $(wildcard $(SRC)/*.c)
OBJ_F = $(SRC_F:.c=.o)
OBJS = $(subst $(SRC),$(OBJ),$(OBJ_F))

GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;34m
DEF_COLOR = \033[0;39m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIB_F)/$(LIB)
	@$(CC)  -lreadline  $^ -o $(NAME)
	@echo "$(GREEN)minishell compiled!$(DEF_COLOR)"

$(OBJ)/%.o:	$(SRC)/%.c $(OBJ)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ): 
	@mkdir -p $(OBJ)
	@make -C $(LIB_F)
	@echo "$(BLUE)libft is done!$(DEF_COLOR)"

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_F)
	@echo "$(YELLOW)Evrything was cleaned $(DEF_COLOR)"

re: fclean all