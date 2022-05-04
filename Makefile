NAME = containers.ft
NAME_STD = containers.std
VECTOR = vector.ft
VECTOR_STD = vector.std
MAP = map.ft
MAP_STD = map.std

SRCS = main.cpp srcs/comparative_tests_map.cpp srcs/comparative_tests_vector.cpp srcs/comparative_tests_set.cpp srcs/comparative_tests_stack.cpp

CPPFLAGS = -Wall -Werror -Wextra -std=c++98
STD_OBJ  =       $(SRCS:%.cpp=objs/std_out/%.o)
FT_OBJ  =       $(SRCS:%.cpp=objs/ft_out/%.o)
CC = c++ -g $(FLAGS)
INC = -I./includes/vector -I./includes/utils -I./includes/stack -I./includes/map -I./includes/set


$(NAME): CPPFLAGS += -D NM=ft -D test=all
$(NAME_STD): CPPFLAGS += -D NM=std -D test=all
$(VECTOR): CPPFLAGS += -D vec -D NM=ft
$(VECTOR_STD): CPPFLAGS += -D vec -D NM=std
$(MAP): CPPFLAGS += -D map_macro -D NM=ft
$(MAP_STD): CPPFLAGS += -D map_macro -D NM=std


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
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_GRASS)$(_BOLD)%s$(_END)\n" [$(WP)] "✅	Your $(NAME) and $(NAME_STD) are ready."

$(NAME) $(NAME_STD):
		$(CC) $^ -o $@ $(CPPFLAGS) $(INC)

$(VECTOR) $(VECTOR_STD):
		$(CC) $^ -o $@ $(CPPFLAGS) $(INC)

$(MAP) $(MAP_STD):
		$(CC) $^ -o $@ $(CPPFLAGS) $(INC)

$(NAME) : $(FT_OBJ)
$(NAME_STD): $(STD_OBJ)
$(VECTOR) : $(FT_OBJ)
$(VECTOR_STD): $(STD_OBJ)
$(MAP) : $(FT_OBJ)
$(MAP_STD): $(STD_OBJ)

message :
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_WHITE)$(_LIGHT)%s$(_END)\n" [$(WP)] "Your $(NAME) ans $(NAME_STD) files are compiling..."

objs/std_out/%.o: %.cpp
		mkdir -p $(@D)
		$(CC) $(CPPFLAGS) $(INC) -c -o $@ $<

objs/ft_out/%.o: %.cpp
		mkdir -p $(@D)
		$(CC) $(CPPFLAGS) $(INC) -c -o $@ $<

clean:
	@rm -rf objs
	@rm -f my_output.txt std_output.txt diffs.txt my_vector.txt std_vector.txt diffs_vector.txt my_map.txt std_map.txt diffs_map.txt
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_LIGHT)%s\n$(_END)" [$(WP)] "Your .o and .txt files have been deleted."

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_STD)
	@printf "$(_BOLD)$(_PINK)%-30s$(_END) $(_BOLD)%s\n$(_END)" [$(WP)] "🗑️	Your $(NAME) snd $(NAME_STD) have been deleted. "

test: all
	@( time ./$(NAME) ) > my_output.txt 2>&1
	@( time ./$(NAME_STD) ) > std_output.txt 2>&1
	@diff my_output.txt std_output.txt > diffs.txt || true
	cat diffs.txt

vector: fclean $(VECTOR) $(VECTOR_STD)
	@( time ./$(VECTOR) ) > my_vector.txt 2>&1
	@( time ./$(VECTOR_STD) ) > std_vector.txt 2>&1
	@rm -rf objs
	@rm -rf  $(VECTOR) $(VECTOR_STD)
	@diff my_vector.txt std_vector.txt > diffs_vector.txt || true
	cat diffs_vector.txt

map: fclean $(MAP) $(MAP_STD)
	@( time ./$(MAP)) > my_map.txt 2>&1
	@( time ./$(MAP_STD) ) > std_map.txt 2>&1
	@rm -rf $(MAP) $(MAP_STD)
	@rm -rf objs
	@diff my_map.txt std_map.txt  > diffs_map.txt || true
	cat diffs_map.txt

re: fclean all

.PHONY: all clean re
