CXX=		g++

ZIA_NAME	= zia_example

MODULE_NAME	= zia_logger.so

API_FILES	= ACore.cpp		\
		http/Uri.cpp		\
		utils/GenModule.cpp

API_SRC		= $(addprefix ../src/, $(API_FILES))

ZIA_SRC		= main.cpp $(API_SRC)

MODULE_SRC	= TestModule.cpp

ZIA_OBJ		= $(ZIA_SRC:.cpp=.o)

CXXFLAGS	= --std=c++14 -W -Wall -Wextra -I../src/

LDFLAGS		= -ldl

$(ZIA_NAME):	$(ZIA_OBJ)
	$(CXX) -o $(ZIA_NAME) $(ZIA_OBJ) $(LDFLAGS)

$(MODULE_NAME):
	$(CXX) -fPIC -shared -o $(MODULE_NAME) $(MODULE_SRC) $(CXXFLAGS)

all:	$(ZIA_NAME) $(MODULE_NAME)

clean:
	rm -f $(ZIA_OBJ) $(MODULE_OBJ)

fclean:	clean
	rm $(ZIA_NAME) $(MODULE_NAME)

re:	fclean all

.PHONY:	all clean fclean re