# Makefile for building coupled dynamical systems tools

CC = g++
OUTPUT = cds
SRC = cds.cc lattice.cc
FLAGS = -std=c++0x

cds: $(SRC)
	$(CC) -o $(OUTPUT) $(SRC) $(FLAGS)
