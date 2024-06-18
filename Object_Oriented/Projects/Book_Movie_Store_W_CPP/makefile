CXXFLAGS = -std=c++11

all: clean compile run

compile: Catalog.cpp Entry.cpp FieldFormat.cpp main.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ $(CXXFLAGS) -o test Catalog.cpp Entry.cpp FieldFormat.cpp main.cpp -lm

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
