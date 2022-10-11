gcc build server.c -o server
gcc build client.c -o client
./server &
for i in 1 2 3 4 5
do
./client &
do
