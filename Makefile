all:
	g++ ./src/main.cpp -o ./main
lc:
	find ./src/* | xargs wc -l