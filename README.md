Lessons learned:

ESP8266 wants 3.3v power to the CHPD (chip enabled) pin, otherwise it doesn't work

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
