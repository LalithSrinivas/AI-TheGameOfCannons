OUTFILE= "./Cannon-AI/run.out"
SrcDir= "./Cannon-AI/"

compile:
	@echo "Compiling..."
	@g++ -I ./headers/ -o $(OUTFILE) ./code/*.cpp
	@echo "Compilation finished. Please run the '.out' file."

runServer:
	@echo "Starting server..."
	@python server.py 10000 -n 8 -m 8 -NC 2 -TL 150 -LOG server.log

runPlayer1_rand:
	@echo "Starting Player-1 ..."
	@export PATH=$PATH:'/Users/chinmaisainagendrakokku/Downloads/'
	@python client.py 0.0.0.0 10000 RandomPlayer.py -mode GUI

runPlayer1:
	@echo "Starting Player-1 ..."
	@export PATH=$PATH:'/Users/chinmaisainagendrakokku/Downloads/'
	@python client.py 0.0.0.0 10000 ./run.sh -mode GUI

runPlayer2_rand:
	@echo "Starting Player-2 ..."
	@export PATH=$PATH:'/Users/chinmaisainagendrakokku/Downloads/'
	@python client.py 0.0.0.0 10000 RandomPlayer.py

runPlayer2:
	@echo "Starting Player-2 ..."
	@export PATH=$PATH:'/Users/chinmaisainagendrakokku/Downloads/'
	@python client.py 0.0.0.0 10000 ./run.sh

clean1:
	rm *.out