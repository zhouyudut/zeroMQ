gcc -o event event.c -lzmq -I /usr/local/lib
gcc -o worker worker.c -lzmq -I /usr/local/lib
gcc -o sinker sinker.c -lzmq -I /usr/local/lib
