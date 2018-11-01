# mqtt broker image
FROM ubuntu:16.04

RUN apt-get update && apt-get install -y vim curl build-essential cmake pkg-config apt-utils less lsb-release

# mosquitto (https://jpinjpblog.wordpress.com/2017/12/18/installing-mqtt-for-c-on-raspberry-pi/
# and https://qiita.com/kyoro353/items/b862257086fca02d3635)
RUN apt-get update \
 && apt-get install -y libmosquitto-dev libmosquittopp-dev libssl-dev \
                       mosquitto mosquitto-clients \
 && rm -rf /var/lib/apt/lists/*

