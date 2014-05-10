#!/bin/bash

f () { 
    for i
    do
        (( i > 1 && i < 65 )) && echo "$i good"
    done 
}

function usage {
    echo Usage: 
}

function testpin {
    echo testpin: "$1"
    if [[ ! -L /sys/class/gpio/gpio$1 ]]
    then
	echo echoing "$1" to /sys/class/gpio/export
	echo "$1" > /sys/class/gpio/export
        #        echo exporting gpio $1
        echo out > /sys/class/gpio/gpio$1/direction
    else
	echo /sys/class/gpio/gpio$1 exists
    fi    
}

function untestpin {
    echo untestpin: "$1"
    if [[ -L /sys/class/gpio/gpio$1 ]]
    then
        echo in > /sys/class/gpio/gpio$1/direction
	echo "$1" > /sys/class/gpio/unexport
    fi    
}

while :
do
    case "$1" in 
        -h | --help | -\? | help)
            usage
            exit 0
            ;;
        -t )
          testpin "$2"
	    shift 2
            exit 0
            ;;
        -u )
          untestpin "$2"
	    shift 2
            exit 0
            ;;
	* ) 
	    echo unknown option $1
	    shift
	    exit 0
    esac
done
