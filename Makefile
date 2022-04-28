NAME = containers.ft
NAME_STD = containers.std


STD_SRCS = main.cpp
FT_SRCS = main.cpp


FLAGS = -Wall -Werror -Wextra -std=c++98
STD_OBJS = $(STD_SRCS:.cpp=.o)
FT_OBJS = $(FT_SRCS:.cpp=.o)
CC = c++ -g $(FLAGS)
INC = -I./includes/vector -I./includes/utils  -I./includes/stack -I./includes/map 


# This is a minimal set of ANSI/VT100 color codes
_END=$'\e[0m
_BOLD=$'\e[1m
_UNDER=$'\e[4m
_REV=$'\e[7m
_LIGHT=$'\e[2m

# Colors
_GREY=$'\e[30m
_RED=$'\e[31m
_GREEN=$'\e[0;32m
_YELLOW=$'\e[33m
_BLUE=$'\e[34m
_PURPLE=$'\e[35m
_CYAN=$'\e[36m
_WHITE=$'\e[37m
_LBLUE=$'\e[94m
_ORANGE=$'\e[38;5;215m
_PINK=$'\e[38;5;95m
_GRASS=$'\e[38;5;119m
_UNICORN= $'\360\237\246\204
_UNIC=$'🦄
_LETTER = $'💌

WP = `pwd | sed 's!.*/!!'`


all : message $(NAME) $(NAME_STD)
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_GRASS)$(_BOLD)%s$(_END)\n" [$(WP)] "✅	Your $(NAME) is ready."

message :
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_WHITE)$(_LIGHT)%s$(_END)\n" [$(WP)] "Your $(NAME) files are compiling..."

$(NAME): $(FT_OBJS)
	$(CC) $(INC) $(FT_OBJS) -o $(NAME)

$(NAME_STD): $(STD_OBJS)
	$(CC) $(INC) $(STD_OBJS) -o $(NAME_STD)

$(STD_OBJS): 
	$(CC) $(INC) -D NM=std -c $< -o $@

$(FT_OBJS): 
	$(CC) $(INC) -D NM=ft -c $< -o $@

clean:
	@rm -f $(OBJS)
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_LIGHT)%s\n$(_END)" [$(WP)] "Your .o files have been deleted."

fclean: clean
	@rm -f $(NAME)
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_BOLD)%s\n$(_END)" [$(WP)] "🗑️	Your $(NAME) have been deleted. "

re: fclean all

.PHONY: all clean re