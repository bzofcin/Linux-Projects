gcc -std=c99 -Wall -g -pthread -o leib leib_par.c
./leib 1 &
VAL=$(pgrep leib)
# echo $VAL

while :
do
cat /proc/$VAL/sched
sleep 2
done
pkill leib