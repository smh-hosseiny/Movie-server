CC = g++ -std=c++11
CFLAG= -c
all: System.out
System.out: main.o Netflix.o UsersRepository.o MoviesRepository.o Member.o  Movie.o \
			Publisher.o Customer.o Interface.o
	${CC}  main.o Netflix.o UsersRepository.o MoviesRepository.o Member.o Movie.o Publisher.o \
			 Customer.o Interface.o -o System.out 


main.o: main.cpp 
	${CC} ${CFLAG} main.cpp -o main.o
	

Netflix.o: Netflix.h Netflix.cpp UsersRepository.h MoviesRepository.h Member.h
	${CC} ${CFLAG} Netflix.cpp -o Netflix.o


UsersRepository.o: UsersRepository.h UsersRepository.cpp MoviesRepository.h Member.h \
					Publisher.h Customer.h
	${CC} ${CFLAG} UsersRepository.cpp -o UsersRepository.o

MoviesRepository.o: MoviesRepository.h MoviesRepository.cpp Movie.h
	${CC} ${CFLAG} MoviesRepository.cpp -o MoviesRepository.o


Movie.o: Movie.h Movie.cpp 
	${CC} ${CFLAG} Movie.cpp -o Movie.o

Member.o: Member.h Member.cpp 
	${CC} ${CFLAG} Member.cpp -o Member.o

Publisher.o: Publisher.h Publisher.cpp 
	${CC} ${CFLAG} Publisher.cpp -o Publisher.o

Customer.o: Publisher.h Publisher.cpp 
	${CC} ${CFLAG} Customer.cpp -o Customer.o


Interface.o: Interface.h Interface.cpp Netflix.h
	${CC} ${CFLAG} Interface.cpp -o Interface.o


.PHONY: clean
clean:
	rm -r *.o
