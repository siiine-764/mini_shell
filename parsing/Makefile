NAME	= parsing
CC		= cc
CFLAGS 	= -Wall -Wextra -Werror

SRCS =	aft_dollar.c\
		free_all.c\
		lexer_utils.c\
		lexer.c\
		parse_utils.c\
		parse.c\
		str_collect.c\
		unquoted_str.c\

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 
	@echo "make it"

clean:
	@rm -f $(OBJS)
	@echo "clean parsing"

fclean: clean
	@rm -f $(NAME)
	@echo "fclean parsing"

re: fclean $(NAME)

.PHONY: clean fclean re all