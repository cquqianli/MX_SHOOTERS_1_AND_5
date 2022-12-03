#ifndef robcfg_H
#define robcfg_H


#define hero

#define taskperi 2.f //ms
#define taskfreq 1000.f/taskperi //ms

#ifdef infa
#define pitmaxangle 40.f
#define pitminangle -40.f
#define fricshootspeed 500.f
#define fricdirection 1.f
#define forknum 8.f
#define maxshootfreq 15
#define magaspeed 120.f
#define magadirection 1.f

#define pit_reduc 2.f
#define yaw_reduc 1.5f


#endif

#ifdef hero
#define pitmaxangle 35.f
#define pitminangle -18.f
#define fricshootspeed 500.f
#define fricdirection 1.f
#define forknum 6.f
#define maxshootfreq 1.f

#define pit_reduc 1.f
#define yaw_reduc 2.f

#define robot_power_limit_0 50.f
#define robot_power_limit_1 70.f
#define robot_power_limit_2 90.f
#define robot_power_limit_3 120.f

#define yawid 0x206
#define trigid 0x205
#define pitid 0x203
#define fric0id 0x201
#define firc1id 0x202

#endif


#define pitmaxspeed 450.f //rpm
#define yawmaxspeed 450.f //rpm


#define runspeed 500.f //rpm
#define rotspeedPPV 30.f  //rpm
#define rotspeedSV 90.f  //rpm


#define reductiongearratio_3508 3591.f/187.f
#define current_maxvalue_3508 0x4fff
#define current_max_3508 20.f
#define speed_max_rpm_3508 500.f

#define reductiongearratio_2006 36.f
#define current_maxvalue_2006 10000
#define current_max_2006 20.f
#define speed_max_rpm_2006 500.f

#define reductiongearratio_6020 1.f
#define current_maxvalue_6020 30000
#define current_max_6020 1.f
#define speed_max_rpm_6020 300.f

#ifdef infa

#define yawinfo_default_config \
{ \
	{ \
		{-180.f,180.f}, \
		speed_max_rpm_6020, \
		{current_maxvalue_6020,current_max_6020}, \
		1.5f, \
		0.f, \
		0.f, \
		2, \
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		{0.f,0.f}, \
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
	}, \
	{ \
		0.f, \
		0.f, \
		{0.f,0.f,0.f,0.f,0.f}, \
	}, \
} \

#define chasis_default_config \
{ \
		0x00, \
	{ \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		40.f, \
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		40.f, \
		60.f, \
	}, \
} \

#endif

#ifdef hero

#define yawinfo_default_config \
{ \
	{ \
		{-180.f,180.f}, \
		speed_max_rpm_6020, \
		{current_maxvalue_6020,current_max_6020}, \
		2.f, \
		0.f, \
		-72.342f, \
		5, \
		0x0,\
		0x1,\
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		{0.f,0.f}, \
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
	}, \
	{ \
		0.f, \
		0.f, \
		{0.f,0.f,0.f,0.f,0.f}, \
	}, \
} \

#define chasis_default_config \
{ \
		0x00, \
	{ \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		50.f, \
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		50.f, \
		60.f, \
	}, \
} \

#endif

#define wheel_default_config \
{ \
	{ \
		{-180.f,180.f}, \
		speed_max_rpm_3508, \
		{current_maxvalue_3508,current_max_3508}, \
		reductiongearratio_3508, \
		0.f, \
		0.f, \
		2, \
		0x0,\
		0x0,\
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		{0.f,0.f}, \
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
	}, \
	{ \
		0.f, \
		0.f, \
		{0.f,0.f,0.f,0.f,0.f}, \
	}, \
} \

#define wheel_default_pid \
{ \
	0.f, \
	0.f, \
	{0.f,0.f}, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	current_maxvalue_3508, \
	current_maxvalue_3508/10, \
	current_maxvalue_3508, \
	0.f, \
	current_maxvalue_3508, \
} \

#define spin_default_pid \
{ \
	0.f, \
	0.f, \
	{0.f,0.f}, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	speed_max_rpm_3508, \
	speed_max_rpm_3508, \
	speed_max_rpm_3508, \
	0.f, \
	speed_max_rpm_3508, \
} \

#define scapsinfo_default_config \
{ \
	0.f, \
	12.f, \
	0.f, \
	40.f, \
} \

#endif
