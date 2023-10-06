NAME = parsing.a
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

SRCS =	\
		./aft_dollar.c\
		./free_all.c\
		./lexer_utils.c\
		./lexer.c\
		./parse_utils.c\
		./parse.c\
		./str_collect.c\
		./unquoted_str.c\
		./utils1.c\
		./utils2.c\

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all