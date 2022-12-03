#ifndef robcfg_H
#define robcfg_H


#define infa

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

#define yawid 0x206
#define trigid 0x205
#define pitid 0x203
#define fric0id 0x201
#define firc1id 0x202

#endif


#define pitmaxspeed 30.f //rpm
#define yawmaxspeed 250.f //rpm


#define runspeed 500.f //rpm
#define rotspeedPPV 100.f  //rpm
#define rotspeedSV 150.f  //rpm

#define reductiongearratio_3508 3591.f/187.f
#define current_maxvalue_3508 16384.f
#define current_max_3508 20.f
#define speed_max_rpm_3508 500.f

#define reductiongearratio_2006 36.f
#define current_maxvalue_2006 10000
#define current_max_2006 20.f
#define speed_max_rpm_2006 500.f

#define reductiongearratio_6020 1.f
#define current_maxvalue_6020 30000
#define current_max_6020 1.f
#define speed_max_rpm_6020 400.f

#define roboctrl_default_config \
{ \
	{ \
		0x00, \
		0x00, \
	}, \
	{ \
		0x00, \
		0.f, \
		0.f, \
	}, \
	{ \
		0x00, \
		0.f, \
		0.f, \
		0.f, \
	}, \
} \

#ifdef infa

#define yawinfo_default_config \
{ \
	{ \
		{-180.f,180.f}, \
		speed_max_rpm_6020, \
		{current_maxvalue_6020,current_max_6020}, \
		yaw_reduc, \
		0.f, \
		0.f, \
		2, \
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

#define pitinfo_default_config \
{ \
	{ \
		{-180.f,180.f}, \
		speed_max_rpm_6020, \
		{current_maxvalue_6020,current_max_6020}, \
		pit_reduc, \
		0.f, \
		0.f, \
		2, \
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

#define trig_default_config \
{ \
	{ \
		{-180.f,180.f}, \
		speed_max_rpm_2006, \
		{current_maxvalue_2006,current_max_2006}, \
		reductiongearratio_2006, \
		0.f, \
		0.f, \
		2, \
		0x1,\
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

#define trig_angle_pid \
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
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	maxshootfreq/forknum*60.f, \
} \

#define trig_speed_pid \
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
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	current_maxvalue_2006, \
} \

#define pit_angle_pid \
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
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	speed_max_rpm_6020, \
} \

#define pit_speed_pid \
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
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	current_maxvalue_6020, \
} \

#define yaw_angle_pid \
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
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	speed_max_rpm_6020/yaw_reduc, \
} \

#define yaw_speed_pid \
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
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	current_maxvalue_6020, \
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
		0.f, \
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

#define pitinfo_default_config \
{ \
	{ \
		{-pitminangle,pitmaxangle}, \
		speed_max_rpm_3508, \
		{current_maxvalue_3508,current_max_3508}, \
		reductiongearratio_3508, \
		0.f, \
		0.f, \
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

#define trig_default_config \
{ \
	{ \
		{-180.f,180.f}, \
		speed_max_rpm_3508, \
		{current_maxvalue_3508,current_max_3508}, \
		reductiongearratio_3508, \
		0.f, \
		0.f, \
		2, \
		0x1,\
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

#define trig_angle_pid \
{ \
	0.f, \
	0.f, \
	{0.f,0.f}, \
	0.5f, \
	0.f, \
	0.3f, \
	0.f, \
	0.f, \
	0.f, \
	maxshootfreq/forknum*60.f, \
	maxshootfreq/forknum*60.f, \
	maxshootfreq/forknum*60.f, \
	0.f, \
	maxshootfreq/forknum*60.f, \
} \

#define trig_speed_pid \
{ \
	0.f, \
	0.f, \
	{0.f,0.f}, \
	350.f, \
	15.f, \
	125.f, \
	0.f, \
	0.f, \
	0.f, \
	current_maxvalue_3508, \
	current_maxvalue_3508, \
	current_maxvalue_3508, \
	0.f, \
	current_maxvalue_3508, \
} \

#define pit_angle_pid \
{ \
	0.f, \
	0.f, \
	{0.f,0.f}, \
	4.f, \
	0.f, \
	10.f, \
	0.f, \
	0.f, \
	0.f, \
	speed_max_rpm_3508/5, \
	speed_max_rpm_3508/5, \
	speed_max_rpm_3508/5, \
	0.f, \
	speed_max_rpm_3508/5, \
} \

#define pit_speed_pid \
{ \
	0.f, \
	0.f, \
	{0.f,0.f}, \
	200.f, \
	3.f, \
	125.f, \
	0.f, \
	0.f, \
	0.f, \
	current_maxvalue_3508, \
	current_maxvalue_3508/10, \
	current_maxvalue_3508, \
	0.f, \
	current_maxvalue_3508, \
} \

#define yaw_angle_pid \
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
	speed_max_rpm_6020/yaw_reduc, \
	speed_max_rpm_6020/yaw_reduc, \
	speed_max_rpm_6020/yaw_reduc, \
	0.f, \
	speed_max_rpm_6020/yaw_reduc, \
} \

#define yaw_speed_pid \
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
	current_maxvalue_6020, \
	current_maxvalue_6020, \
	current_maxvalue_6020, \
	0.f, \
	current_maxvalue_6020, \
} \

#endif

#define fric_default_config \
{ \
	{ \
		{-180.f,180.f}, \
		speed_max_rpm_3508, \
		{current_maxvalue_3508,current_max_3508}, \
		reductiongearratio_3508, \
		0.f, \
		0.f, \
		3, \
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

#define maga_default_config \
{ \
	{ \
		{-180.f,180.f}, \
		speed_max_rpm_2006, \
		{current_maxvalue_2006,current_max_2006}, \
		reductiongearratio_2006, \
		0.f, \
		0.f, \
		2, \
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

#define maga_angle_pid \
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
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	speed_max_rpm_2006, \
} \

#define maga_speed_pid \
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
	current_maxvalue_2006, \
	current_maxvalue_2006, \
	current_maxvalue_2006, \
	0.f, \
	current_maxvalue_2006, \
} \

#define fric_default_pid \
{ \
	0.f, \
	0.f, \
	{0.f,0.f}, \
	500.f, \
	20.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	current_maxvalue_3508, \
	current_maxvalue_3508, \
	current_maxvalue_3508, \
	0.f, \
	current_maxvalue_3508, \
} \






#endif
