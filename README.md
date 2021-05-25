# Nightwing

An adversial search gaming bot
compile:
make compile

run server:
cd Cannon-AI
python server.py 10000 -n <rows> -m <columns> -NC 2 -TL <time_allocated> -LOG <log_file>

run client:
cd Cannon-AI
export PATH=$PATH:'<chrome_driver directory>
python client.py 0.0.0.0 10000 ./run.sh -mode GUI
