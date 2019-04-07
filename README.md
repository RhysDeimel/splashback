Lessons learned:

ESP8266 wants 3.3v power to the CHPD (chip enabled) pin, otherwise it doesn't work

These chips aren't set to a baud rate of 9600, so the UNO has problems. For a once off test, set ESP hardware serial to 115200 and debug serial to 9600. You should be able to `AT` and receive and `OK`. From there you can set the ESP-01 baud to 9600 with `AT+CIOBAUD=9600`. At which point it will stop responding until you switch the hardware and debug serial around.

If you'd like to permanently set the baudrate, you should use `AT+UART_DEF=9600,8,1,0,0`, where the expanded form is: AT+ UART_DEF=<baudrate>,<databits>,<stopbits>,<parity>,<flow control>

Send udp packet on nix with 
`echo -n "Hello, World!" > /dev/udp/<address>/<port>`

or on localhost:
`echo -ne "ldoor:1|g\nrdoor:1|g\nldr:1|g\n" | nc -C -w 1 -u localhost 8125`






Need to setup statsd plugin
https://docs.influxdata.com/telegraf/v1.8/plugins/inputs/
https://www.influxdata.com/blog/getting-started-with-sending-statsd-metrics-to-telegraf-influxdb/

```
telegraf -sample-config -input-filter processes:swap:system:cpu:disk:diskio:kernel:mem:statsd -output-filter influxdb | sudo tee /etc/telegraf/telegraf.conf
sudo sudo systemctl start telegraf
```

then edit telegraf.conf so it listens on 0.0.0.0:8125

Install plugin to do math on single stat panel (for lights off)
`grafana-cli plugins install blackmirror1-singlestat-math-panel`
