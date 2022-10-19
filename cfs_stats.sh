function handler(){
    pkill leib
    return -1
}

trap handler SIGINT

gcc -std=c99 -o leib io_bound.c
# gcc -std=c99 -o leib cpu_bound.c
# gcc -std=c99 -g -pthread -o leib leib_par.c
./leib 1 &
VAL=$(pgrep leib)
echo $VAL

while [[ -f /proc/$VAL/sched ]]
do
cat /proc/$VAL/sched
sleep 2
done

rm leib
