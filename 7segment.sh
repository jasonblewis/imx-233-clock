#!/bin/bash

gpio=/sys/class/gpio/gpio


declare -A segments
segments=( ["sega"]="16"
    ["segb"]="7"
    ["segc"]="6"
    ["segd"]="5"
    ["sege"]="4"
    ["segf"]="51"
    ["segg"]="2"
    ["segdp"]="1")

function all_off {
    for i in "${segments[@]}"
    do 
        #echo turning off gpio "$i"
        echo 0 > $gpio"$i"/value
    done
}

function all_on {
    for i in "${segments[@]}"
    do 
        #echo turning on gpio "$i"
        echo 1 > $gpio"$i"/value
    done
}

function usage {
    echo "Usage: a to toggle the a segment"
}

function toggle_segment {
    #echo toggle segment $1
    #echo toggling "${segments[seg$1]}"
    echo $(( $(cat $gpio"${segments[seg$1]}"/value) ^ 1 )) > $gpio"${segments[seg$1]}"/value
}

# initialise 
#for i in 1 2 4 5 6 7 16 51
for i in "${segments[@]}"
do
    if [[ ! -L /sys/class/gpio/gpio$i ]]
    then
#        echo exporting gpio $i
        echo $i > /sys/class/gpio/export
        echo out > /sys/class/gpio/gpio$i/direction
        #   echo 0 > /sys/class/gpio/gpio$i/value
    fi    
done


while :
do
    case "$1" in 
        -h | --help | -\? | help)
            usage
            exit 0
            ;;
        a | b | c | d | e | f | g | dp)
            toggle_segment "$1"
            shift
            ;;
        *) # no more options
            break
            ;;
    esac
done
