#!/bin/bash

# Pseudo TICK stack
#   - influxdb
#   - telegraf
#   - grafana

# add the InfluxData repository
curl -sL https://repos.influxdata.com/influxdb.key | sudo apt-key add -
source /etc/lsb-release
echo "deb https://repos.influxdata.com/${DISTRIB_ID,,} ${DISTRIB_CODENAME} stable" | sudo tee /etc/apt/sources.list.d/influxdb.list


# install & start influxdb
sudo apt-get update && sudo apt-get install influxdb
sudo service influxdb start

# install & start telegraf
sudo apt-get update && sudo apt-get install telegraf
sudo service telegraf start

# install grafana
wget https://grafanarel.s3.amazonaws.com/builds/grafana_3.1.1-1470047149_amd64.deb
sudo apt-get install -y adduser libfontconfig
sudo dpkg -i grafana_3.1.1-1470047149_amd64.deb
rm grafana_3.1.1-1470047149_amd64.deb

# start grafana
sudo systemctl daemon-reload
sudo systemctl start grafana-server
# sudo systemctl status grafana-server
sudo systemctl enable grafana-server.service

# default port is 3000
# default user and group is admin
# telegraf creates a default db called telegraf