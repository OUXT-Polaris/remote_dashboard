/*******************************************************************************/
/*Application: Dashboard for WAM-V                                             */
/*File Description: This class show dashboard panel                            */
/*                                                                             */
/*Author     : Github: @JadeEtoile                                             */
/*Date       : 2018-09-01                                                      */
/*                                                                             */
/*****Version*****                                                             */
/*Version:     Date:         Author:          Description:                     */
/*0.1          2018-09-01    JadeEtoile       New                              */
/*******************************************************************************/
#ifndef DASHBOARD_PANEL_HPP
#define DASHBOARD_PANEL_HPP

/*Include Qt Module*/
#include <QApplication>
#include <QMainWindow>
#include <QtGui>
#include <QDateTime>
#include <QMutex>

#include <QtSvg/QSvgRenderer>
#include <QString>
#include <QPainter>
#include <QImage>
#include <QFont>
#include <QColor>
#include <QPalette>
#include <QPaintEvent>

#include "dashboard_panel_define.h"
#include <cmath>

/*Define Class*/
class clsDashboardPanel : public QMainWindow
{
	Q_OBJECT


	
/***Constructor***/
public:
	clsDashboardPanel():
		/*Constants*/
		colorBg( QColor(60,60,60,255) ), /*R,G,B,A*/
		colorPanel( QColor(0, 4, 37, 255) ),
		colorNormal( QColor(43, 255, 201, 255) ),
		colorWarn( QColor(255, 128, 0, 255) ),
		colorError( QColor(255, 36, 0, 255) ),
		colorPort( QColor(23, 255, 0, 255) ),
		colorStbd( QColor(255, 36, 0, 255) ),

		svgpath("svg/panel.svg"),
		azimuthfig_path( "png/azimuth_78x200.png" ),
		rollfig_path( "png/roll_156x52.png" ),
		pitchfig_path( "png/pitch_156x32.png" ),
		hdgfig_path( "png/hdg_150x48.png" ),

		meter12v_min(11.7),/*V*/
		meter12v_low(11.9),/*V*/
		meter12v_max(12.2),/*V*/
		meter24v_min(23.0),/*V*/
		meter24v_low(24.0),/*V*/
		meter24v_max(27.0),/*V*/

		meterspeed_max(20),/*kt*/
		
		panel_position( QRect(0, 0, 1920, 1080) ),

		update_time(100),/*ms*/

		widget_palette( QPalette( QColor(90, 90, 90, 255), QColor(0, 4, 37, 255) ) ),
		drawfont( QFont("Saira", 26, 0, false) )
		
	{
		/*Initalize Variables*/
		panelvalue =
			{
				0.0,
				0.0,
				0.0,
				0.0,
				DASHBOARD_PANEL_WAMV_CONTROL_MODE_ESTOP,
				0.0,
				
				0.0,
				0.0,
				0.0,
				
				0.0,
				0.0,
				0.0,
				
				DASHBOARD_PANEL_GPS_N,
				0,
				0.0000,
				DASHBOARD_PANEL_GPS_E,
				0,
				0.0000,
				0
			};
		
		/*Initialize Timer for Refresh*/
		refresh_timer = new QTimer(this);
		connect(refresh_timer, SIGNAL(timeout()), this, SLOT(update()) );
		refresh_timer -> start(update_time);
		
		/*Initialize SVG Engine*/
		front_panel_handler = new QSvgRenderer(svgpath);

		/*Initialize Window*/
		QMainWindow::resize( QSize(1920,1080) );
		QMainWindow::setAutoFillBackground(true);
		QMainWindow::setPalette(widget_palette);

		/*Set Click Event*/
		
	}

	
/***Destructor***/
public:
	~clsDashboardPanel()
	{
		delete refresh_timer;
		delete front_panel_handler;
	}


	

/***Constants***/
private:
	/**Color**/
	const QColor colorBg;
	const QColor colorPanel;
	const QColor colorNormal;
	const QColor colorWarn;
	const QColor colorError;
	const QColor colorPort;
	const QColor colorStbd;

	/**path**/
	const QString svgpath;
	const QString azimuthfig_path;
	const QString rollfig_path;
	const QString pitchfig_path;
	const QString hdgfig_path;

	/**Meter Objects**/
	/*Voltage Meter*/
	const float meter12v_min;
	const float meter12v_low;
	const float meter12v_max;
	const float meter24v_min;
	const float meter24v_low;
	const float meter24v_max;

	/*Voltage Speed*/
	const float meterspeed_max;

	/*Front Panel*/
	const QRect panel_position;

	/*Function*/
	const unsigned int update_time;

public:
	/**Palette**/
	const QPalette widget_palette;





/***Variables***/
private:
	QTimer* refresh_timer;
	QSvgRenderer* front_panel_handler;

	
	QMutex mutex;
	T_Dashboard_Panel_Data panelvalue;
	QDateTime current_time;
	QString datestr;
	QString timestr;
	QFont drawfont;


/***Method***/
private:

	
public:
/*Accessor*/
	void setValueThruster(float port_throttle, float port_azimuth_angle, float stbd_throttle, float stbd_azimuth_angle);
	void setValueMode(unsigned int mode);
	void setValueNavinfo(float ground_speed);
	void setValueGps(unsigned int n_s, unsigned int alt_deg, float alt_min, unsigned int e_w, unsigned int lon_deg, float lon_min, unsigned int satellite);
	void setValueVolage(float ctrl_battery, float motor_battery, float ctrl_input);
	void setValueImu(float roll, float pitch, float yaw);


	
/***Override Method***/
protected:
	void keyPressEvent(QKeyEvent *event);
	void paintEvent(QPaintEvent *);


};


#endif
