NAME 		=	PmergeMe

CXX 		=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address

INCS		=	./PmergeMe.hpp\
				../Colors.hpp\
				
SRCS		=	./main.cpp\
				./PmergeMe.cpp\
				../Colors.cpp\

OBJS		=	$(SRCS:%.cpp=%.o)

RM			=	rm -f

all:	$(NAME)

$(NAME): $(OBJS) $(INCS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%o:	%.cpp $(INCS)
	$(CXX) $(CXXFLAGS) $(INCS) -c $^ -o $@

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re