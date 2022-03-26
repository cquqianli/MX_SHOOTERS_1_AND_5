#ifndef robcfg_H
#define robcfg_H


#define infa

#define taskperi 2 //ms
#define taskfreq 1000.f/taskperi //ms

#ifdef infa
#define pitmaxangle 40.f
#define pitminangle -40.f
#define fricshootspeed 500.f
#define fricdirection 1.f
#define forknum 8
#define maxshootfreq 15
#define magaspeed 120.f
#define magadirection 1.f
#endif

#ifdef hero
#define pitmaxangle 40.f
#define pitminangle -40.f
#define fricshootspeed 500.f
#define fricdirection 1.f
#define forknum 8
#define maxshootfreq 1
#endif


#define pitmaxspeed 450.f //rpm
#define yawmaxspeed 450.f //rpm


#define runspeed 500.f //rpm
#define rotspeedPPV 100.f  //rpm
#define rotspeedSV 150.f  //rpm



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



#endif
