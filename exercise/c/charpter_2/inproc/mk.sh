gcc -o server server.c zhelpers.h -lpthread -lzmq -I /user/local/lib 
gcc -o client client.c -L zhelpers.h -lzmq -I /user/local/lib
