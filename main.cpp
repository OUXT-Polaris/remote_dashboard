#include "dashboard_panel.hpp"
#include <QSize>
#include <QThread>

int main(int argv, char* argc[])
{
	QApplication app(argv, argc);

	clsDashboardPanel window;
	window.resize( QSize(1920,1080) );
	window.setAutoFillBackground(true);
	window.setPalette(window.widget_palette);
	window.setWindowTitle("WAM-V Control Dashboard");

	//window.showFullScreen();
	window.show();
	return app.exec();
}
