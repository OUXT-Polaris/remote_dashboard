#include "dashboard_panel.hpp"
#include <QSize>
#include <QThread>
#include <mosquitto.h>
#include <iostream>

// https://qiita.com/n-yamanaka/items/ca3a7df30d12bf92cc5b
void on_connect(struct mosquitto *mosq, void *obj, int result) {
  mosquitto_subscribe(mosq, NULL, "topic/test", 0);
}

void on_disconnect(struct mosquitto *mosq, void *obj, int result) {}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {
  if (message->payloadlen) {
    std::cout<<"[message] "<<message->topic<<std::endl;
  }
}

int main(int argv, char* argc[])
{
	QApplication app(argv, argc);

	clsDashboardPanel window;
	window.resize( QSize(1920,1080) );
	window.setAutoFillBackground(true);
	window.setPalette(window.widget_palette);
	window.setWindowTitle("WAM-V Control Dashboard");

	//window.showFullScreen();

  mosquitto_lib_init();
  bool clean_session = true;
  struct mosquitto *mosq = mosquitto_new("wamv-control-dashboard", clean_session, NULL);
  if(!mosq) {
    std::cout<<"!mosq"<<std::endl;
    mosquitto_lib_cleanup();
    return -1;
  }
  mosquitto_connect_callback_set(mosq, on_connect);
  mosquitto_disconnect_callback_set(mosq, on_disconnect);
  mosquitto_message_callback_set(mosq, on_message);

  if(mosquitto_connect_bind(mosq, "broker", 1883, 60, NULL)) {
    std::cout<<"!bind"<<std::endl;
    return -1;
  }
  std::cout<<"loop started"<<std::endl;
  mosquitto_loop_start(mosq);

  window.setValueNavinfo(999.922);

  // run Qt application
	window.show();
  const int ret = app.exec();

  // clean up
  std::cout<<"clean up"<<std::endl;
  mosquitto_disconnect(mosq);
  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();

	return ret;
}
