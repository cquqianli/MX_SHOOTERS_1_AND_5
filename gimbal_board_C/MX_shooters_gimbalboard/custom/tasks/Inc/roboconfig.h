#ifndef robcfg_H
#define robcfg_H


#define infa

#define taskperi 2 //ms

#ifdef infa
#define pitmaxangle 40.f
#define pitminangle -40.f
#endif

#ifdef heroy
#define pitmaxangle 40.f
#define pitminangle -40.f
#endif

#define runspeed 500.f //rpm
#define rotspeedPPV 100.f  //rpm
#define rotspeedSV 150.f  //rpm



#define roboctrl_default_config \
{ \
	{ \
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
