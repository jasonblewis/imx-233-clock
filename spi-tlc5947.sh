#!/bin/bash

gpio=/sys/class/gpio/gpio

declare -A spipins
segments=( ["lat"]="13"
           ["oebar"]="12"
           ["clk"]="11"
           ["din"]="10"


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
            #   echo 0 > /sys/class/gpio/gpio$i/value
        fi    
    done
}

function


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
        a | b | c | d | e | f | g | dp)
            initialise
            toggle_segment "$1"
            shift
            ;;
        0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9)
            initialise
            display_number "$1"
            shift
            ;;
        *) # no more options
            break
            ;;
    esac
done
