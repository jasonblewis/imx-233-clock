#!/bin/bash

gpio=/sys/class/gpio/gpio

declare -A spipins
spipins=(  ["lat"]="13" 
           ["oebar"]="12"
           ["clk"]="11"
           ["din"]="10")

lat=/sys/class/gpio/gpio13/value
oebar=/sys/class/gpio/gpio12/value
clk=/sys/class/gpio/gpio11/value
din=/sys/class/gpio/gpio10/value

function uninitialise {
    for i in "${spipins[@]}"
    do
        if [[ ! -L /sys/class/gpio/gpio$i ]]
        then
            #        echo exporting gpio $i
            echo $i > /sys/class/gpio/export
            echo in > /sys/class/gpio/gpio $i/direction
            #   echo 0 > /sys/class/gpio/gpio$i/value
        fi    
    done
}


# initialise 
function initialise {
    #for i in 1 2 4 5 6 7 16 51
    for i in "${spipins[@]}"
    do
        if [[ ! -L /sys/class/gpio/gpio$i ]]
        then
            #        echo exporting gpio $i
            echo $i > /sys/class/gpio/export
            echo out > /sys/class/gpio/gpio $i/direction
            
        fi    
    done
    echo 0 > $clk
    echo 0 > $lat
}


# set clock to 0
# set lat to 0
# for i in 1..288
#  set data bit
#  set clock
#  clear clock
#  rotate data left
# end for
# set lat
# clear lat


function all_on {
    for i in {{1..288}}; do
        echo 1 > $din
        echo 1 > $clk
        echo 0 > $clk
    done
    echo 1 > $lat
    echo 0 > $lat
} 

function all_off {
    for i in {{1..288}}; do
        echo 0 > $din
        echo 1 > $clk
        echo 0 > $clk
    done
    echo 1 > $lat
    echo 0 > $lat
} 

function usage {
    echo usage;
}

while :
do
    case "$1" in 
        -h | --help | -\? | help)
            usage
            exit 0
            ;;
        -u | --uninit)
            uninitialise
            exit 0
            ;;
        -i | --init)
            initialise
            exit 0
            ;;
        all_on )
            all_on
            exit 0
            ;;
        all_off )
            all_off
            exit 0
            ;;
        *) # no more options
            break
            ;;
    esac
done
