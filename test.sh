while true; do
    val1=$(( ( RANDOM % 2 )))
    val2=$(( ( RANDOM % 2 )))
    val3=$(( ( RANDOM % 2 )))
    echo "occupancy.left,ldr=$val3:$val1|g\noccupancy.right,ldr=$val3:$val2|g\n"
    #echo -ne "ldoor:$val1|g\nrdoor:$val2|g\nldr:$val3|g\n" | nc -C -w 1 -u 10.1.242.161 8125
    echo -ne "occupancy.left,ldr=$val3:$val1|g\noccupancy.right,ldr=$val3:$val2|g\n" | nc -C -w 1 -u 10.1.242.161 8125
    sleep 30
done
