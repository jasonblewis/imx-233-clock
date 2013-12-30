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

# mapping of segments to numbers
#   a b c d e f g dp
declare -A d0=(["sega"]="0" ["segb"]="0" ["segc"]="0" ["segd"]="0" ["sege"]="0" ["segf"]="0" ["segg"]="0" ["segdp"]="0" )
declare -A d1=(["sega"]="0" ["segb"]="1" ["segc"]="1" ["segd"]="0" ["sege"]="0" ["segf"]="0" ["segg"]="0" ["segdp"]="0" )
declare -A d2=(["sega"]="1" ["segb"]="1" ["segc"]="0" ["segd"]="1" ["sege"]="1" ["segf"]="0" ["segg"]="1" ["segdp"]="0" )
declare -A d3=(["sega"]="1" ["segb"]="1" ["segc"]="1" ["segd"]="1" ["sege"]="0" ["segf"]="0" ["segg"]="1" ["segdp"]="0" )
declare -A d4=(["sega"]="0" ["segb"]="1" ["segc"]="1" ["segd"]="0" ["sege"]="0" ["segf"]="1" ["segg"]="1" ["segdp"]="0" )
declare -A d5=(["sega"]="1" ["segb"]="0" ["segc"]="1" ["segd"]="1" ["sege"]="0" ["segf"]="1" ["segg"]="1" ["segdp"]="0" )
declare -A d6=(["sega"]="1" ["segb"]="0" ["segc"]="1" ["segd"]="1" ["sege"]="1" ["segf"]="1" ["segg"]="1" ["segdp"]="0" )
declare -A d7=(["sega"]="1" ["segb"]="1" ["segc"]="1" ["segd"]="0" ["sege"]="0" ["segf"]="0" ["segg"]="0" ["segdp"]="0" )
declare -A d8=(["sega"]="1" ["segb"]="1" ["segc"]="1" ["segd"]="0" ["sege"]="0" ["segf"]="1" ["segg"]="1" ["segdp"]="0" )
declare -A d9=(["sega"]="1" ["segb"]="1" ["segc"]="1" ["segd"]="1" ["sege"]="1" ["segf"]="1" ["segg"]="0" ["segdp"]="0" )

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

function display_number {
    all_off
    echo showing number $1
    for i in ${!segments[@]}
    do
        echo segment $i is ${ ${d[$1]}[$i] }
    done
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
        0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9)
            display_number "$1"
            shift
            ;;
        *) # no more options
            break
            ;;
    esac
done
