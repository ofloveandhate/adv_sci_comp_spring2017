 #!/bin/bash

prog=${1:-a.out} #program name is a.out by default
numtimes=${2:-10} # number in outer loop is 10 by default

counter=1
while [ $counter -le $numtimes ]
do
	export OMP_NUM_THREADS=$counter
    echo num threads: $counter
    time ./$prog 
    ((counter++))
done
