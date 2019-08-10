
all: comp run

comp: Jacobi.cpp
	clear
	gcc -g Jacobi.cpp -o launch -lstdc++
	ctags -R .

run:
	./launch

clear:
	rm launch
