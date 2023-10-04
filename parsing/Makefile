NAME	= parsing.a
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
		utils.c\
		utils1.c\
		utils2.c\

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "make parsing"

clean:
	@rm -f $(OBJS)
	@echo "clean parsing"

fclean: clean
	@rm -f $(NAME)
	@echo "fclean parsing"

re: fclean $(NAME)
	@echo "re execution"

.PHONY: clean fclean re all