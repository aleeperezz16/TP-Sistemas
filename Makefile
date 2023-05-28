CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lpthread

BUILD_DIR = ./build

TARGET = ContarPalabras
TEST_TARGET = UnitTests

OBJECTS = HashMapConcurrente.o CargarArchivos.o

all: build $(BUILD_DIR)/$(TARGET)

test: build $(BUILD_DIR)/$(TEST_TARGET)
	$(BUILD_DIR)/$(TEST_TARGET)

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

$(BUILD_DIR)/%: src/%.cpp $(OBJECTS:%=$(BUILD_DIR)/%)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all test build clean debug

build:
	@mkdir -p $(BUILD_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

clean:
	-@rm -rvf $(BUILD_DIR)/*

maximo:
	$(CXX) $(CXXFLAGS) src/exp/Maximo.cpp src/HashMapConcurrente.cpp src/CargarArchivos.cpp -o $(BUILD_DIR)/maximo $(LDFLAGS)

archivos:
	$(CXX) $(CXXFLAGS) src/exp/CargarArchivos.cpp src/HashMapConcurrente.cpp src/CargarArchivos.cpp -o $(BUILD_DIR)/archivos $(LDFLAGS)

paralelo:
	$(CXX) $(CXXFLAGS) src/exp/MaximoParalelo.cpp src/HashMapConcurrente.cpp src/CargarArchivos.cpp -o $(BUILD_DIR)/paralelo $(LDFLAGS)

