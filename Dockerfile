FROM ubuntu:16.04

RUN apt-get update && apt-get install -y vim curl build-essential cmake pkg-config apt-utils less lsb-release

# qt,qmake (https://github.com/thoughtbot/capybara-webkit/wiki/Installing-Qt-and-compiling-capybara-webkit#debian--ubuntu)
# mosquitto (https://jpinjpblog.wordpress.com/2017/12/18/installing-mqtt-for-c-on-raspberry-pi/)
RUN apt-get update \
 && apt-get install -y qt5-default libqt5webkit5-dev gstreamer1.0-plugins-base gstreamer1.0-tools gstreamer1.0-x libqt5svg5-dev \
 && apt-get install -y libmosquitto-dev libmosquittopp-dev libssl-dev \
 && rm -rf /var/lib/apt/lists/*

ADD . /target/

WORKDIR /target
RUN qmake && make

CMD ./exec
