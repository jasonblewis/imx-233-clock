gpio=/sys/class/gpio/gpio51
echo 51 > /sys/class/gpio/export
echo out > $gpio/direction
while true
do
  echo $(($(cat $gpio/value) ^ 1)) > $gpio/value
  cat $gpio/value
  sleep 1
done
