CC=g++
CFLAGS=--std=c++11 -lpthread
# SRC=
EXEC=bin/exo1 bin/exo2 bin/exo3
DIRS=bin

all: $(EXEC)

bin/exo1: src/ThreadPool.cpp src/exo1.cpp
	$(CC) -o bin/exo1 src/ThreadPool.cpp src/exo1.cpp $(CFLAGS)

bin/exo2: src/Pipeline.cpp src/exo2.cpp
	$(CC) -o bin/exo2 src/Pipeline.cpp src/exo2.cpp $(CFLAGS)

bin/exo3: src/MD5/md5.cpp src/Decryptor.cpp src/exo3.cpp
	$(CC) -o bin/exo3 src/MD5/md5.cpp src/Decryptor.cpp src/exo3.cpp $(CFLAGS)

clean:
	rm -rf bin

# will create all necessary directories after the Makefile is parsed
$(shell mkdir -p $(DIRS))