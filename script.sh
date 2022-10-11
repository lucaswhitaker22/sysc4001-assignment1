gcc controller.c -o controller
gcc sensor.c -o sensor

./controller &
./sensor 800

