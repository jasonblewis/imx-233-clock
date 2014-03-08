#!/bin/bash
gpio=/sys/class/gpio/gpio$1

if [[ ! -L $gpio ]]
then   
    echo $1 > /sys/class/gpio/export
    echo out > $gpio/direction
fi

while true
do
    gpio_value=$(cat $gpio/value)
    if [[ $gpio_value -ne 0 ]]
    then
#    echo gpio: $gpio/value
	echo 0 > $gpio/value
    else
	echo 1 > $gpio/value
    fi
    #    echo $(( $gpio_value ^ 1)) > $gpio/value
    echo "Old gpio value: $gpio_value. New gpio value: " $(cat $gpio/value)
    sleep 1
done

