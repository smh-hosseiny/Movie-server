CC = g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template
CFLAG= -c

all: $(BUILD_DIR) server.out
server.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/Netflix.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/Command_Handler.o $(BUILD_DIR)/POST_Handler.o $(BUILD_DIR)/GET_Handler.o \
	$(BUILD_DIR)/Admin.o $(BUILD_DIR)/MovieGraph.o $(BUILD_DIR)/UsersRepository.o $(BUILD_DIR)/MoviesRepository.o $(BUILD_DIR)/Member.o  $(BUILD_DIR)/Movie.o \
	$(BUILD_DIR)/Publisher.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/BadRequest.o $(BUILD_DIR)/PermissionDenied.o $(BUILD_DIR)/NotFound.o \
	$(BUILD_DIR)/my_server.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o \
	$(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o

	$(CC) $(CF) $(BUILD_DIR)/main.o $(BUILD_DIR)/Netflix.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/Command_Handler.o $(BUILD_DIR)/POST_Handler.o $(BUILD_DIR)/GET_Handler.o \
	$(BUILD_DIR)/Admin.o $(BUILD_DIR)/MovieGraph.o $(BUILD_DIR)/UsersRepository.o $(BUILD_DIR)/MoviesRepository.o $(BUILD_DIR)/Member.o $(BUILD_DIR)/Movie.o \
	$(BUILD_DIR)/Publisher.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/BadRequest.o $(BUILD_DIR)/PermissionDenied.o $(BUILD_DIR)/NotFound.o \
	$(BUILD_DIR)/my_server.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o \
  	$(BUILD_DIR)/template_parser.o  -o server.out 

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp \
utils/request.hpp utils/include.hpp main.cpp Interface.h
	$(CC) $(CF) ${CFLAG} main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Interface.o: Interface.h Interface.cpp Netflix.h Exception.h BadRequest.h \
	PermissionDenied.h NotFound.h POST_Handler.h GET_Handler.h
	$(CC) $(CF) ${CFLAG} Interface.cpp -o $(BUILD_DIR)/Interface.o

$(BUILD_DIR)/Command_Handler.o: Command_Handler.h Command_Handler.cpp
	$(CC) $(CF) ${CFLAG} Command_Handler.cpp -o $(BUILD_DIR)/Command_Handler.o

$(BUILD_DIR)/POST_Handler.o: POST_Handler.h POST_Handler.cpp Command_Handler.h Netflix.h
	$(CC) $(CF) ${CFLAG} POST_Handler.cpp -o $(BUILD_DIR)/POST_Handler.o

$(BUILD_DIR)/GET_Handler.o: GET_Handler.h GET_Handler.cpp Command_Handler.h Netflix.h
	$(CC) $(CF) ${CFLAG} GET_Handler.cpp -o $(BUILD_DIR)/GET_Handler.o

$(BUILD_DIR)/Netflix.o: Netflix.h Netflix.cpp UsersRepository.h MoviesRepository.h Member.h Exception.h \
 BadRequest.h PermissionDenied.h NotFound.h Admin.h
	$(CC) $(CF) ${CFLAG} Netflix.cpp -o $(BUILD_DIR)/Netflix.o

$(BUILD_DIR)/UsersRepository.o: UsersRepository.h UsersRepository.cpp MoviesRepository.h Member.h \
Publisher.h Exception.h BadRequest.h PermissionDenied.h NotFound.h
	$(CC) $(CF) ${CFLAG} UsersRepository.cpp -o $(BUILD_DIR)/UsersRepository.o

$(BUILD_DIR)/MoviesRepository.o: MoviesRepository.h MoviesRepository.cpp MovieGraph.h Movie.h Exception.h \
 BadRequest.h PermissionDenied.h NotFound.h
	$(CC) $(CF) ${CFLAG} MoviesRepository.cpp -o $(BUILD_DIR)/MoviesRepository.o

$(BUILD_DIR)/Movie.o: Movie.h Movie.cpp Comment.h Exception.h BadRequest.h PermissionDenied.h NotFound.h
	$(CC) $(CF) ${CFLAG} Movie.cpp -o $(BUILD_DIR)/Movie.o

$(BUILD_DIR)/Member.o: Member.h Member.cpp Exception.h BadRequest.h PermissionDenied.h NotFound.h
	$(CC) $(CF) ${CFLAG} Member.cpp -o $(BUILD_DIR)/Member.o

$(BUILD_DIR)/Publisher.o: Publisher.h Publisher.cpp 
	$(CC) $(CF) ${CFLAG} Publisher.cpp -o $(BUILD_DIR)/Publisher.o

$(BUILD_DIR)/Comment.o: Comment.h Comment.cpp
	$(CC) $(CF) ${CFLAG} Comment.cpp -o $(BUILD_DIR)/Comment.o

$(BUILD_DIR)/Exception.o: Exception.h Exception.cpp
	$(CC) $(CF) ${CFLAG} Exception.cpp -o $(BUILD_DIR)/Exception.o

$(BUILD_DIR)/BadRequest.o: BadRequest.h BadRequest.cpp
	$(CC) $(CF) ${CFLAG} BadRequest.cpp -o $(BUILD_DIR)/BadRequest.o

$(BUILD_DIR)/PermissionDenied.o: PermissionDenied.h PermissionDenied.cpp
	$(CC) $(CF) ${CFLAG} PermissionDenied.cpp -o $(BUILD_DIR)/PermissionDenied.o

$(BUILD_DIR)/NotFound.o: NotFound.h NotFound.cpp
	$(CC) $(CF) ${CFLAG} NotFound.cpp -o $(BUILD_DIR)/NotFound.o

$(BUILD_DIR)/Admin.o: Admin.h Admin.cpp
	$(CC) $(CF) ${CFLAG} Admin.cpp -o $(BUILD_DIR)/Admin.o

$(BUILD_DIR)/MovieGraph.o: MovieGraph.h MovieGraph.cpp
	$(CC) $(CF) ${CFLAG} MovieGraph.cpp -o $(BUILD_DIR)/MovieGraph.o



$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp \
 utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) ${CFLAG} utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) ${CFLAG} utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) ${CFLAG} utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) ${CFLAG} utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp \
 utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) ${CFLAG} server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp \
 utils/request.hpp utils/include.hpp
	$(CC) $(CF) ${CFLAG} server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp\
 utils/request.hpp utils/include.hpp Exception.h Movie.h Interface.h Netflix.h
	$(CC) $(CF) ${CFLAG} handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp\
 utils/request.hpp utils/include.hpp
	$(CC) $(CF) ${CFLAG} my_server.cpp -o $(BUILD_DIR)/my_server.o


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null