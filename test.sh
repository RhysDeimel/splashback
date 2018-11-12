while true; do
    val=$(( ( RANDOM % 2 )))
    echo "ldoor:$val|g\nrdoor:$val|g\nldr:$val|g\n"
    echo -ne "ldoor:$val|g\nrdoor:$val|g\nldr:$val|g\n" | nc -C -w 1 -u 10.1.242.161 8125
    sleep 10
done
