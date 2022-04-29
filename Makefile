NAME = containers.ft
NAME_STD = containers.std


SRCS = main.cpp srcs/map_tests.cpp 

CPPFLAGS = -Wall -Werror -Wextra -std=c++98
STD_OBJ  =       $(SRCS:%.cpp=std_out/%.o)
FT_OBJ  =       $(SRCS:%.cpp=ft_out/%.o)
CC = c++ -g $(FLAGS)
INC = -I./includes/vector -I./includes/utils  -I./includes/stack -I./includes/map 


$(NAME): CPPFLAGS += -D NM=ft
$(NAME_STD): CPPFLAGS += -D NM=std

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


$(NAME) $(NAME_STD):
		$(CC) $^ -o $@ $(CPPFLAGS) $(INC)

$(NAME) : $(FT_OBJ)
$(NAME_STD): $(STD_OBJ)


message :
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_WHITE)$(_LIGHT)%s$(_END)\n" [$(WP)] "Your $(NAME) files are compiling..."

std_out/%.o: %.cpp
		mkdir -p $(@D)
		$(CC) $(CPPFLAGS) $(INC) -c -o $@ $<

ft_out/%.o: %.cpp
		mkdir -p $(@D)
		$(CC) $(CPPFLAGS) $(INC) -c -o $@ $<

clean:
	@rm -f $(FT_OBJS)
	@rm -f $(STD_OBJS)
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_LIGHT)%s\n$(_END)" [$(WP)] "Your .o files have been deleted."

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_STD)
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_BOLD)%s\n$(_END)" [$(WP)] "🗑️	Your $(NAME) snd $(NAME_STD) have been deleted. "

re: fclean all

.PHONY: all clean re