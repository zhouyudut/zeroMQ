gcc -o server server.c -L zhelpers.h -lzmq -I /user/local/lib
gcc -o client client.c -L zhelpers.h -lzmq -I /user/local/lib
gcc -o vistor vistor.c -L zhelpers.h -lzmq -I /user/local/lib
gcc -o proxy proxy.c -L zhelpers.h -lzmq -I /user/local/lib
