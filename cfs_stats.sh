#!/bin/bash

function handler(){
    pkill leib
    return -1
}

OUTPUT_IO="io_leib"
OUTPUT_CPU="cpu_leib"
OUTPUT_PAR="par_leib"
OUTPUT_NIC="nic_leib"

# -------------------------------------------
trap handler SIGINT

if [[  $1 = 'internet' ]]; then # Change command to launch internet browser
    VAL=$(cmd.exe /c start microsoft-edge:http://www.google.com/ & echo $!)
elif [[ $1 = 'io' ]]; then
    ./object/$OUTPUT_IO 1 &
    VAL=$(pgrep $OUTPUT_IO)
elif [[ $1 = 'cpu' ]]; then
    ./object/$OUTPUT_CPU 1 &
    VAL=$(pgrep $OUTPUT_CPU)
elif [[ $1 = 'nice' ]]; then
    ./object/$OUTPUT_NIC 1 &
    VAL=$(pgrep $OUTPUT_NIC)
    renice -n -20 -p $VAL
else
    echo "No input given"
fi

echo $VAL

while [[ -f /proc/$VAL/sched ]] do
    cat /proc/$VAL/sched
    sleep 2
done
