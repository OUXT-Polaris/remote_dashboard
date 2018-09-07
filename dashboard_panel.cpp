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


/*Include header*/
#include "dashboard_panel.hpp"


/*Define Accessor*/
void clsDashboardPanel::setValueThruster(float port_throttle, float port_azimuth_angle, float stbd_throttle, float stbd_azimuth_angle)
{
	mutex.lock();
	panelvalue.thruster_port = port_throttle;
	panelvalue.azimuth_port = port_azimuth_angle;
	panelvalue.thruster_stbd = stbd_throttle;
	panelvalue.azimuth_stbd = stbd_azimuth_angle;
	mutex.unlock();
}

void clsDashboardPanel::setValueMode(unsigned int mode)
{
	mutex.lock();
	panelvalue.control_mode = mode;
	mutex.unlock();
}

void clsDashboardPanel::setValueNavinfo(float ground_speed)
{
	mutex.lock();
	panelvalue.ground_speed = abs(ground_speed);
	mutex.unlock();
}

void clsDashboardPanel::setValueGps(unsigned int n_s, unsigned int alt_deg, float alt_min, unsigned int e_w, unsigned int lon_deg, float lon_min, unsigned int satellite)
{
	mutex.lock();
	panelvalue.gps_altitude_n_s = n_s;
	panelvalue.gps_altitude_deg = alt_deg;
	panelvalue.gps_altitude_min = alt_min;
	panelvalue.gps_longitude_e_w = e_w;
	panelvalue.gps_longitude_deg = lon_deg;
	panelvalue.gps_longitude_min = lon_min;
	panelvalue.gps_satellite_number = satellite;
	mutex.unlock();
}

void clsDashboardPanel::setValueVolage(float ctrl_battery, float motor_battery, float ctrl_input)
{
	mutex.lock();
	panelvalue.control_battery_voltage = ctrl_battery;
	panelvalue.motor_battery_voltage = motor_battery;
	panelvalue.control_input_voltage = ctrl_input;
	mutex.unlock();
}

void clsDashboardPanel::setValueImu(float roll, float pitch, float yaw)
{
	mutex.lock();
	panelvalue.imu_roll = roll;
	panelvalue.imu_pitch = pitch;
	panelvalue.imu_yaw = yaw;
	mutex.unlock();
}


/*Define Method*/
void clsDashboardPanel::keyPressEvent(QKeyEvent *event)
{
	switch(event->key())
		{
			
		case Qt::Key_Q:
			if( event->modifiers() & Qt::ControlModifier )
				{
					qApp->quit();
				}
			break;

			
		case Qt::Key_F:
			if(this->windowState() != Qt::WindowFullScreen)
				{
					this->showFullScreen();
				}
			else
				{
					this->showNormal();
				}
			break;

		}
					
}
	
void clsDashboardPanel::paintEvent(QPaintEvent *)
{
	/*Initialize Variables*/
	QString valueText;
	QImage fig_azimuth = QImage(azimuthfig_path);
	QImage fig_roll = QImage(rollfig_path);;
	QImage fig_pitch = QImage(pitchfig_path);;
	QImage fig_hdg = QImage(hdgfig_path);;
	
	T_Dashboard_Panel_Data temp;
	mutex.lock();
	temp = panelvalue;
	mutex.unlock();

	current_time = QDateTime::currentDateTime();
	datestr = current_time.date().toString("yyyy/MM/dd  dddd");
	timestr = current_time.time().toString("hh:mm:ss");
	
	/*Initialize QPainter*/
	QPainter panel_painter(this);
	panel_painter.setRenderHint(QPainter::Antialiasing, true);
	panel_painter.setPen( QPen(Qt::NoPen) );

	/*Draw Bacground*/
	panel_painter.setBrush( QBrush(colorBg, Qt::SolidPattern) );
	panel_painter.drawRect( QRect(0, 0, 1920, 1080) );
	
	/*Draw Port Thruster*/
	if(temp.thruster_port >0)
		{
			panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(241-400/2, 840-400/2, 400, 400), 16*(240-240*temp.thruster_port/100), 16*240*temp.thruster_port/100 );
			panel_painter.drawRect( QRect(198-154/2, 891-40/2, 154, 40) );
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(363-154/2, 891-40/2, 154, 40) );
		}
	else if(temp.thruster_port < 0)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(241-400/2, 840-400/2, 400, 400), 16*(240-240*abs(temp.thruster_port)/100), 16*240*abs(temp.thruster_port)/100 );
			panel_painter.drawRect( QRect(363-154/2, 891-40/2, 154, 40) );
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(198-154/2, 891-40/2, 154, 40) );

		}
	else
		{
			;
		}

	/*Draw STBD Thruster*/
	if(temp.thruster_stbd >0)
		{
			panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1679-400/2, 840-400/2, 400, 400), 16*(240-240*temp.thruster_stbd/100), 16*240*temp.thruster_stbd/100 );
			panel_painter.drawRect( QRect(1636-154/2, 891-40/2, 154, 40) );
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1801-154/2, 891-40/2, 154, 40) );
		}
	else if(temp.thruster_stbd < 0)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1679-400/2, 840-400/2, 400, 400), 16*(240-240*abs(temp.thruster_stbd)/100), 16*240*abs(temp.thruster_stbd)/100 );
			panel_painter.drawRect( QRect(1636-154/2, 891-40/2, 154, 40) );
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1801-154/2, 891-40/2, 154, 40) );

		}
	else
		{
			;
		}

	/*Draw Speed*/
	panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
	panel_painter.drawPie( QRect(960-200/2, 750-200/2, 200, 200), 16*(225-270*abs(temp.ground_speed)/meterspeed_max), 16*270*abs(temp.ground_speed)/meterspeed_max );

	/*Draw Mode*/
	switch(temp.control_mode)
		{
		case DASHBOARD_PANEL_WAMV_CONTROL_MODE_MANUAL:
			panel_painter.setBrush( QBrush( colorWarn, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(960-670/2, 1205-670/2, 670, 670), 16*75, 16*30 );			
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawEllipse( QRect(960-580/2, 1205-580/2, 580, 580) );
			panel_painter.setBrush( QBrush( colorPanel, Qt::SolidPattern) );
			panel_painter.drawRect( QRect(960-580/2, 1080, 580, 580-(1205-1080)) );
			break;

		case DASHBOARD_PANEL_WAMV_CONTROL_MODE_AUTO:
			panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(960-670/2, 1205-670/2, 670, 670), 16*45, 16*30 );			
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawEllipse( QRect(960-580/2, 1205-580/2, 580, 580) );
			panel_painter.setBrush( QBrush( colorPanel, Qt::SolidPattern) );
			panel_painter.drawRect( QRect(960-580/2, 1080, 580, 580-(1205-1080)) );
			break;

		case DASHBOARD_PANEL_WAMV_CONTROL_MODE_ESTOP:
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(960-670/2, 1205-670/2, 670, 670), 16*105, 16*30 );			
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawEllipse( QRect(960-580/2, 1205-580/2, 580, 580) );
			panel_painter.setBrush( QBrush( colorPanel, Qt::SolidPattern) );
			panel_painter.drawRect( QRect(960-580/2, 1080, 580, 580-(1205-1080)) );
			break;

		case DASHBOARD_PANEL_WAMV_CONTROL_MODE_EMERGENCY:
			panel_painter.setBrush( QBrush( colorWarn, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(960-670/2, 1205-670/2, 670, 670), 16*75, 16*30 );
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawEllipse( QRect(960-580/2, 1205-580/2, 580, 580) );
			panel_painter.setBrush( QBrush( colorWarn, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(960-200/2, 1002-70/2, 200, 70) );
			panel_painter.setBrush( QBrush( colorPanel, Qt::SolidPattern) );
			panel_painter.drawRect( QRect(960-580/2, 1080, 580, 580-(1205-1080)) );
			break;
		}

	/*Draw Control Battery*/
	if(temp.control_battery_voltage < meter24v_min)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1440-80/2, 256-62/2, 80, 62) );
		}
	else if(temp.control_battery_voltage >= meter24v_min && temp.control_battery_voltage <meter24v_low)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1440-200/2, 285-200/2, 200, 200), 16*(240 - 240*(temp.control_battery_voltage - meter24v_min)/(meter24v_max - meter24v_min)), 16*240*(temp.control_battery_voltage - meter24v_min)/(meter24v_max - meter24v_min) );
			panel_painter.drawRect( QRect(1440-80/2, 256-62/2, 80, 62) );
		}
	else if(temp.control_battery_voltage >=meter24v_low && temp.control_battery_voltage < meter24v_max)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1440-200/2, 285-200/2, 200, 200), 16*(240 - 240* (meter24v_low- meter24v_min)/(meter24v_max - meter24v_min)), 16*240*(meter24v_low - meter24v_min)/(meter24v_max - meter24v_min) );
			panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1440-200/2, 285-200/2, 200, 200), 16*(240 - 240*(temp.control_battery_voltage - meter24v_min)/(meter24v_max - meter24v_min)), 16*240*(temp.control_battery_voltage - meter24v_low)/(meter24v_max - meter24v_min) );
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1440-80/2, 256-62/2, 80, 62) );
		}
	else
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1440-200/2, 285-200/2, 200, 200), 16*(240 - 240* (meter24v_low- meter24v_min)/(meter24v_max - meter24v_min)), 16*240*(meter24v_low - meter24v_min)/(meter24v_max - meter24v_min) );
			panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1440-200/2, 285-200/2, 200, 200), 0, 16*240*(meter24v_max - meter24v_low)/(meter24v_max - 11.0) );
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1440-80/2, 256-62/2, 80, 62) );
		}

	/*Draw Motor Battery*/
	if(temp.motor_battery_voltage < meter24v_min)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1740-80/2, 256-62/2, 80, 62) );
		}
	else if(temp.motor_battery_voltage >=meter24v_min && temp.motor_battery_voltage <meter24v_low)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1740-200/2, 285-200/2, 200, 200), 16*(240 - 240*(temp.motor_battery_voltage - meter24v_min)/(meter24v_max - meter24v_min)), 16*240*(temp.motor_battery_voltage - meter24v_min)/(meter24v_max - meter24v_min) );
			panel_painter.drawRect( QRect(1740-80/2, 256-62/2, 80, 62) );
		}
	else if(temp.motor_battery_voltage >=meter24v_low && temp.motor_battery_voltage < meter24v_max)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1740-200/2, 285-200/2, 200, 200), 16*(240 - 240* (meter24v_low- meter24v_min)/(meter24v_max - meter24v_min)), 16*240*(meter24v_low - meter24v_min)/(meter24v_max - meter24v_min) );
			panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1740-200/2, 285-200/2, 200, 200), 16*(240 - 240*(temp.motor_battery_voltage - meter24v_min)/(meter24v_max - meter24v_min)), 16*240*(temp.motor_battery_voltage - meter24v_low)/(meter24v_max - meter24v_min) );
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1740-80/2, 256-62/2, 80, 62) );
		}
	else
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1740-200/2, 285-200/2, 200, 200), 16*(240 - 240* (meter24v_low- meter24v_min)/(meter24v_max - meter24v_min)), 16*240*(meter24v_low - meter24v_min)/(meter24v_max - meter24v_min) );
			panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1740-200/2, 285-200/2, 200, 200), 0, 16*240*(meter24v_max - meter24v_low)/(meter24v_max - meter24v_min) );
			panel_painter.setBrush( QBrush( colorBg, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1740-80/2, 256-62/2, 80, 62) );
		}

		/*Draw Control Input Voltage*/
	if(temp.control_input_voltage < meter12v_min)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1440-25/2, 515-82/2, 25, 82) );
		}
	else if(temp.control_input_voltage >=meter12v_min && temp.control_input_voltage <meter12v_low)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1440-200/2, 538-200/2, 200, 200), 16*(240 - 240*(temp.control_input_voltage - meter12v_min)/(meter12v_max - meter12v_min)), 16*240*(temp.control_input_voltage - meter12v_min)/(meter12v_max - meter12v_min) );
			panel_painter.drawRect( QRect(1440-25/2, 515-82/2, 25, 82) );
		}
	else if(temp.control_input_voltage >=meter12v_low && temp.control_input_voltage < meter12v_max)
		{
			panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1440-200/2, 538-200/2, 200, 200), 16*(240 - 240*(temp.control_input_voltage - meter12v_min)/(meter12v_max - meter12v_min)), 16*240*(temp.control_input_voltage - meter12v_min)/(meter12v_max - meter12v_min) );
			panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1440-25/2, 515-82/2, 25, 82) );
		}
	else
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1440-200/2, 538-200/2, 200, 200), 16*(240 - 240* (meter12v_low- meter12v_min)/(meter12v_max - meter12v_min)), 16*240*(meter12v_low - meter12v_min)/(meter12v_max - meter12v_min) );
			panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
			panel_painter.drawPie( QRect(1440-200/2, 538-200/2, 200, 200), 0, 16*240*(15.0 - meter12v_low)/(meter12v_max - meter12v_min) );
			panel_painter.setBrush( QBrush( colorNormal, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1442-25/2, 538-82/2, 25, 82) );
		}

	/*Draw Diagnosis*/
	/*GPS_Satellite*/
	if(temp.gps_satellite_number <= 3)
		{
			panel_painter.setBrush( QBrush( colorWarn, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1371-136/2, 48-36/2, 136, 36) );
		}
	/*Battery*/
	if(temp.control_battery_voltage < meter24v_low || temp.motor_battery_voltage < meter24v_low)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1371-136/2, 92-36/2, 136, 36) );
		}

	 if(temp.control_input_voltage < meter12v_low)
		{
			panel_painter.setBrush( QBrush( colorError, Qt::SolidPattern ) );
			panel_painter.drawRect( QRect(1517-136/2, 92-36/2, 136, 36) );
		}
	
	/*Draw Panel*/
	front_panel_handler->render(&panel_painter, panel_position);

	/*Draw Azimuth*/
	panel_painter.translate( QPoint(634, 841) );
	panel_painter.rotate(temp.azimuth_port);
	panel_painter.translate( -QPoint(634, 841) );
	panel_painter.drawImage( QRectF(634-78/2, 841-200/2, 78, 200), fig_azimuth );
	panel_painter.translate( QPoint(634, 841) );
	panel_painter.rotate(-temp.azimuth_port);
	panel_painter.translate( -QPoint(634, 841) );

	
	panel_painter.translate( QPoint(1286, 841) );
	panel_painter.rotate(temp.azimuth_stbd);
	panel_painter.translate( -QPoint(1286, 841) );
	panel_painter.drawImage( QRectF(1286-78/2, 841-200/2, 78, 200), fig_azimuth );
	panel_painter.translate( QPoint(1286, 841) );
	panel_painter.rotate(-temp.azimuth_stbd);
	panel_painter.translate( -QPoint(1286, 841) );

	/*Draw IMU*/
	panel_painter.translate( QPoint(115, 450) );
	panel_painter.rotate(temp.imu_roll);
	panel_painter.translate( -QPoint(115, 450) );
	panel_painter.drawImage( QRectF(115-156/2, 450-52/2, 156, 52), fig_roll );
	panel_painter.translate( QPoint(115, 450) );
	panel_painter.rotate(-temp.imu_roll);
	panel_painter.translate( -QPoint(115, 450) );

	panel_painter.translate( QPoint(330, 450) );
	panel_painter.rotate(-temp.imu_pitch);
	panel_painter.translate( -QPoint(330, 450) );
	panel_painter.drawImage( QRectF(330-156/2, 450-32/2, 156, 32), fig_pitch );
	panel_painter.translate( QPoint(330, 450) );
	panel_painter.rotate(temp.imu_pitch);
	panel_painter.translate( -QPoint(330, 450) );
	
	panel_painter.translate( QPoint(545, 450) );
	panel_painter.rotate(-temp.imu_yaw);
	panel_painter.translate( -QPoint(545, 450) );
	panel_painter.drawImage( QRectF(545-48/2, 450-150/2, 48, 150), fig_hdg );
	panel_painter.translate( QPoint(545, 450) );
	panel_painter.rotate(temp.imu_yaw);
	panel_painter.translate( -QPoint(545, 450) );


	/*Draw Letters*/


	/*Throttle*/
	drawfont.setPointSize(64);
	panel_painter.setFont( drawfont );
	
	if(temp.thruster_port < 0)
		{
			panel_painter.setPen(colorError);
		}
	else
		{
			panel_painter.setPen(colorNormal);
		}
	valueText.setNum(temp.thruster_port, 'f', 0);
	panel_painter.drawText( QRectF(311 - 248/2, 990 - 83/2, 248, 103), Qt::AlignRight|Qt::AlignBottom,  valueText+"%");

	if(temp.thruster_stbd < 0)
		{
			panel_painter.setPen(colorError);
		}
	else
		{
			panel_painter.setPen(colorNormal);
		}
	valueText.setNum(temp.thruster_stbd, 'f', 0);
	panel_painter.drawText( QRectF(1749 - 248/2, 990 - 83/2, 248, 103), Qt::AlignRight|Qt::AlignBottom,  valueText+"%");


	/*Azimuth*/
	drawfont.setPointSize(32);
	panel_painter.setFont( drawfont );
	
	if(temp.azimuth_port >= 0)
		{
			panel_painter.setPen(colorPort);
		}
	else
		{
			panel_painter.setPen(colorStbd);
		}
	valueText.setNum(temp.azimuth_port, 'f', 1);
	panel_painter.drawText( QRectF(634 - 180/2, 1028 - 60/2, 180, 60), Qt::AlignCenter|Qt::AlignVCenter,  valueText);
	drawfont.setPointSize(20);
	panel_painter.setFont( drawfont );
	panel_painter.drawText( QRectF(634 - 180/2, 1028 - 60/2, 180, 60), Qt::AlignRight|Qt::AlignTop,  "o ");

	drawfont.setPointSize(32);
	panel_painter.setFont( drawfont );
	
	if(temp.azimuth_stbd >= 0)
		{
			panel_painter.setPen(colorPort);
		}
	else
		{
			panel_painter.setPen(colorStbd);
		}
	valueText.setNum(temp.azimuth_stbd, 'f', 1);
	panel_painter.drawText( QRectF(1286 - 180/2, 1028 - 60/2, 180, 60), Qt::AlignCenter|Qt::AlignVCenter,  valueText);
	drawfont.setPointSize(20);
	panel_painter.setFont( drawfont );
	panel_painter.drawText( QRectF(1286 - 180/2, 1028 - 60/2, 180, 60), Qt::AlignRight|Qt::AlignTop,  "o ");

	/*Ground Speed*/
	drawfont.setPointSize(36);
	panel_painter.setFont( drawfont );
	panel_painter.setPen(colorNormal);

	valueText.setNum(temp.ground_speed, 'f', 1);
	panel_painter.drawText( QRectF(960 - 100/2, 740 - 78/2, 100, 78), Qt::AlignCenter|Qt::AlignVCenter,  valueText);
	drawfont.setPointSize(20);
	panel_painter.setFont( drawfont );
	panel_painter.drawText( QRectF(960 - 100/2, 700 - 78/2, 100, 78), Qt::AlignCenter|Qt::AlignVCenter,  "kt");

	/*Voltage*/
	drawfont.setPointSize(38);
	panel_painter.setFont( drawfont );
	
	if(temp.control_battery_voltage > meter24v_low)
		{
			panel_painter.setPen(colorNormal);
		}
	else
		{
			panel_painter.setPen(colorError);
		}
	valueText.setNum(temp.control_battery_voltage, 'f', 1);
	panel_painter.drawText( QRectF(1472 - 135/2, 345 - 52/2, 155, 72), Qt::AlignLeft|Qt::AlignBottom,  valueText+"V");

	
	if(temp.motor_battery_voltage > meter24v_low)
		{
			panel_painter.setPen(colorNormal);
		}
	else
		{
			panel_painter.setPen(colorError);
		}
	valueText.setNum(temp.motor_battery_voltage, 'f', 1);
	panel_painter.drawText( QRectF(1772 - 135/2, 345 - 52/2, 155, 72), Qt::AlignLeft|Qt::AlignBottom,  valueText+"V");

	
	if(temp.control_input_voltage > meter12v_low)
		{
			panel_painter.setPen(colorNormal);
		}
	else
		{
			panel_painter.setPen(colorError);
		}
	valueText.setNum(temp.control_input_voltage, 'f', 1);
	panel_painter.drawText( QRectF(1472 - 135/2, 598 - 52/2, 155, 72), Qt::AlignLeft|Qt::AlignBottom,  valueText+"V");


	/*IMU*/
	panel_painter.setPen(colorNormal);

	drawfont.setPointSize(32);
	panel_painter.setFont( drawfont );
	valueText.setNum(temp.imu_roll, 'f', 1);
	panel_painter.drawText( QRectF(115 - 180/2, 580 - 58/2,180, 58), Qt::AlignCenter|Qt::AlignVCenter,  valueText);
	drawfont.setPointSize(16);
	panel_painter.setFont( drawfont );
	panel_painter.drawText( QRectF(115 - 180/2, 580 - 58/2, 180, 58), Qt::AlignRight|Qt::AlignTop,  "o ");

	drawfont.setPointSize(32);
	panel_painter.setFont( drawfont );
	valueText.setNum(temp.imu_pitch, 'f', 1);
	panel_painter.drawText( QRectF(330 - 180/2, 580 - 58/2,180, 58), Qt::AlignCenter|Qt::AlignVCenter,  valueText);
	drawfont.setPointSize(16);
	panel_painter.setFont( drawfont );
	panel_painter.drawText( QRectF(330 - 180/2, 580 - 58/2, 180, 58), Qt::AlignRight|Qt::AlignTop,  "o ");

	drawfont.setPointSize(32);
	panel_painter.setFont( drawfont );
	valueText.setNum(temp.imu_yaw, 'f', 1);
	panel_painter.drawText( QRectF(545 - 180/2, 580 - 58/2,180, 58), Qt::AlignCenter|Qt::AlignVCenter,  valueText);
	drawfont.setPointSize(16);
	panel_painter.setFont( drawfont );
	panel_painter.drawText( QRectF(545 - 180/2, 580 - 58/2, 180, 58), Qt::AlignRight|Qt::AlignTop,  "o ");

	/*GPS*/
	panel_painter.setPen(colorNormal);
	
	/*Altitude*/
	drawfont.setPointSize(26);
	panel_painter.setFont( drawfont );
	if(temp.gps_altitude_n_s == DASHBOARD_PANEL_GPS_S)
		{
			panel_painter.drawText( QRectF(75 - 38/2, 198 - 38/2, 38, 38), Qt::AlignCenter|Qt::AlignVCenter, "S");
		}
	else if(temp.gps_altitude_n_s == DASHBOARD_PANEL_GPS_N)
		{
			panel_painter.drawText( QRectF(75 - 38/2, 198 - 38/2, 38, 38), Qt::AlignCenter|Qt::AlignVCenter, "N");
		}
	valueText.setNum(temp.gps_altitude_deg);
	panel_painter.drawText( QRectF(158 - 113/2, 198 - 38/2,113, 38), Qt::AlignCenter|Qt::AlignVCenter,  valueText);
	drawfont.setPointSize(16);
	panel_painter.setFont( drawfont );
	panel_painter.drawText( QRectF(154 - 113/2, 192 - 38/2,113, 38), Qt::AlignRight|Qt::AlignTop,  "o ");
	drawfont.setPointSize(26);
	panel_painter.setFont(drawfont );
	valueText.setNum(temp.gps_altitude_min);
	panel_painter.drawText( QRectF(410 - 360/2, 198 - 38/2, 410, 38), Qt::AlignLeft|Qt::AlignVCenter,  valueText+"\'");

	/*Longitude*/
	drawfont.setPointSize(26);
	panel_painter.setFont( drawfont );
	if(temp.gps_altitude_n_s == DASHBOARD_PANEL_GPS_E)
		{
			panel_painter.drawText( QRectF(75 - 38/2, 251 - 38/2, 38, 38), Qt::AlignCenter|Qt::AlignVCenter, "E");
		}
	else if(temp.gps_altitude_n_s == DASHBOARD_PANEL_GPS_W)
		{
			panel_painter.drawText( QRectF(75 - 38/2, 251 - 38/2, 38, 38), Qt::AlignCenter|Qt::AlignVCenter, "W");
		}
	valueText.setNum(temp.gps_longitude_deg);
	panel_painter.drawText( QRectF(158 - 113/2, 251 - 38/2,113, 38), Qt::AlignCenter|Qt::AlignVCenter,  valueText);
	drawfont.setPointSize(16);
	panel_painter.setFont( drawfont );
	panel_painter.drawText( QRectF(154 - 113/2, 245 - 38/2,113, 38), Qt::AlignRight|Qt::AlignTop,  "o ");
	drawfont.setPointSize(26);
	panel_painter.setFont( drawfont );
	valueText.setNum(temp.gps_longitude_min);
	panel_painter.drawText( QRectF(410 - 360/2, 251 - 38/2, 410, 38), Qt::AlignLeft|Qt::AlignVCenter,  valueText+"\'");


	/*Time*/
	panel_painter.setPen(colorNormal);
	drawfont.setPointSize(44);
	panel_painter.setFont( drawfont );
	panel_painter.drawText( QRectF(206 - 360/2, 85 - 82/2, 360, 82), Qt::AlignLeft|Qt::AlignBottom,  timestr);
	drawfont.setPointSize(20);
	panel_painter.setFont( drawfont );
	panel_painter.drawText( QRectF(156 - 260/2, 36 - 25/2, 260, 25), Qt::AlignLeft|Qt::AlignVCenter,  datestr);	
}

