NAME = libft.a
AR = ar rcs
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC_F = $(wildcard *.c)
INC_F = $(wildcard *.h)
OBJ_F = $(SRC_F:.c=.o)
OBJS = $(subst $(SRC),$(OBJ),$(OBJ_F))

all: $(NAME)

test: $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS) 

$(OBJ)/%.o:    $(SRC)/%.c $(OBJ)
	@$(CC) $(CFLAGS)  -c $< -o $@

bonus: all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
re: fclean all