COMPILER = g++ -c
LINKER = g++

OBJ = main.o 
EXE = app.exe

CLEAN = del $(OBJ) $(EXE)

test: $(OBJ)
	$(LINKER) $(OBJ) -o $(EXE)
	./$(EXE)
	$(CLEAN)

$(OBJ): %.o : %.cpp
	$(COMPILER) -o $@ $<
