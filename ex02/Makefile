NAME	=	PmergeMe
CC		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++20 -ggdb3
SRCS	=	sources/main.cpp \
			sources/utils.cpp \
			sources/PmergeMe.cpp \
			sources/sort_vector.cpp \
			sources/sort_list.cpp
HEADER  =	includes/PmergeMe.hpp \
			includes/utils.hpp
TEMPLATE =	sources/utils.tpp
OBJS	=	$(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp $(HEADER) $(TEMPLATE)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean rey
