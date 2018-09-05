#ifndef DASHBOARD_PANEL_DEFINE_H
#define DASHBOARD_PANEL_DEFINE_H


/*Define Constants*/
#define DASHBOARD_PANEL_WAMV_CONTROL_MODE_MANUAL (0)
#define DASHBOARD_PANEL_WAMV_CONTROL_MODE_AUTO (1)
#define DASHBOARD_PANEL_WAMV_CONTROL_MODE_ESTOP (2)
#define DASHBOARD_PANEL_WAMV_CONTROL_MODE_EMERGENCY (3)

#define DASHBOARD_PANEL_WAMV_DIAGNOSIS_NORMAL (0)
#define DASHBOARD_PANEL_WAMV_DIAGNOSIS_ACTIVE (1)

#define DASHBOARD_PANEL_GPS_N (0)
#define DASHBOARD_PANEL_GPS_S (1)

#define DASHBOARD_PANEL_GPS_E (0)
#define DASHBOARD_PANEL_GPS_W (1)

/*Define Structure*/
typedef struct
{
	float thruster_port;
	float thruster_stbd;
	float azimuth_port;
	float azimuth_stbd;
	unsigned int control_mode;
	float ground_speed;

	float imu_roll;
	float imu_pitch;
	float imu_yaw;

	float control_battery_voltage;
	float motor_battery_voltage;
	float control_input_voltage;

	unsigned int gps_altitude_n_s;
	unsigned int gps_altitude_deg;
	float gps_altitude_min;
	unsigned int gps_longitude_e_w;
	unsigned int gps_longitude_deg;
	float gps_longitude_min;
	unsigned int gps_satellite_number;
}T_Dashboard_Panel_Data;


#endif	
