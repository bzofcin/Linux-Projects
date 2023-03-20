function handler(){
    pkill leib
    return -1
}

# -------------------------------------------
trap handler SIGINT

if [[  $1 = 'firefox' ]]; then
    firefox &
    VAL=$(pgrep firefox)
    # VAL=$(echo $!)
elif [[ $1 = 'cpu' ]]; then
    gcc -std=c99 -o leib cpu_bound.c
    ./leib 1 &
    VAL=$(pgrep leib)
elif [[ $1 = 'io' ]]; then
    gcc -std=c99 -o leib io_bound.c
    ./leib 1 &
    VAL=$(pgrep leib)
else
    echo "No input given"
fi
# gcc -std=c99 -g -pthread -o leib leib_par.c

echo $VAL

while [[ -f /proc/$VAL/sched ]]
do
cat /proc/$VAL/sched
sleep 2
done

rm leib