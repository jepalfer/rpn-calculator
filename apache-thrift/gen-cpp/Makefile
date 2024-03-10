CXX = g++
CXXFLAGS = -Wall -std=c++11

THRIFT_DIR = /usr/local
THRIFT_INCLUDE = $(THRIFT_DIR)/include/thrift
THRIFT_LIB = $(THRIFT_DIR)/lib

CLIENT_SRC = cliente.cpp calculadora_constants.cpp calculadora_types.cpp
SERVER_SRC = servidor.cpp calculadora_constants.cpp calculadora_types.cpp
THRIFT_SRC = Calculadora.cpp
CLIENT_BIN = cliente
SERVER_BIN = servidor

.PHONY: all clean

all: $(CLIENT_BIN) $(SERVER_BIN)

$(CLIENT_BIN): $(CLIENT_SRC) $(THRIFT_SRC)
	$(CXX) $(CXXFLAGS) -I$(THRIFT_INCLUDE) -L$(THRIFT_LIB) $(CLIENT_SRC) $(THRIFT_SRC) -D'CALCULADORA_NAMESPACE=CalculadoraCPP' -lthrift -o $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_SRC) $(THRIFT_SRC)
	$(CXX) $(CXXFLAGS) -I$(THRIFT_INCLUDE) -L$(THRIFT_LIB) $(SERVER_SRC) $(THRIFT_SRC) -D'CALCULADORA_NAMESPACE=CalculadoraCPP' -lthrift -o $(SERVER_BIN)

clean:
	rm -f $(CLIENT_BIN) $(SERVER_BIN)