CC = g++
CPPFLAGS = -g -std=c++11 -Wall -pedantic
OUTPUT_PATH := bin

.PHONY: all clean
all: app

main: main_clean.cpp
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/main
podado: main_podas.cpp
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/podado

kesimo: main_tp_ej1.cpp
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/kesimo

clean:
	rm -f *.o
	rm -rf $(OUTPUT_PATH)