#include "main.h"

/*-------------------------------------
* 函数名：测试用波形发生器
* 描述  ：波形发生器
* 输入  ：dddd
* 输出  ：dddd
作者：LPGUAIA
日期：2021.7.7
-----------------------------------------*/
wave_HandleTypeDef sinwave={0x01,\
														1000,\
														5,\
														90};

float wavegenerator (wave_HandleTypeDef *SinWave)
{
	uint16_t samplenum = SinWave->waveperiod/SinWave->taskperiod;
	static uint16_t count;
	float output;
	
	if(count<samplenum)
		count++;
	else
		count=0;
	
	switch(SinWave->wavetpye)
	{
		case asinwave:
			output=SinWave->amplitude*sin(2*PI*count/samplenum);break;
		case atriwave:
			output=SinWave->amplitude*count/samplenum;break;
		case stepwave:
			output=SinWave->amplitude*((int)((2*count-1)/samplenum));break;
		default:
			output=SinWave->amplitude*sin(2*PI*count/samplenum);break;
	}
	
	return output;
}



/*-------------------------------------
* 函数名：减速电机角度解算
* 描述  ：计算减速后的角度
* 输入  ：电机结构体
* 输出  ：无

作者：LPGUAIA
日期：2021.4.27
-----------------------------------------*/ 

void gearmotor_angledecoder(MotorInfo *Motor)
{
	
	Motor->tempdata.anglechanged=Motor->tempdata.temp_angle[1] - Motor->tempdata.temp_angle[0];
	Motor->tempdata.temp_angle[0]=Motor->tempdata.temp_angle[1];
	
	
	if(ABS(Motor->tempdata.anglechanged)<=300)
		Motor->tempdata.anglechanged=Motor->tempdata.anglechanged/Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged>300)
		Motor->tempdata.anglechanged = (Motor->tempdata.anglechanged-360) / Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged<-300)
		Motor->tempdata.anglechanged = (360 + Motor->tempdata.anglechanged) / Motor->parameter.reductiongearratio;
	
	
	if(ABS(Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle)<180)
		Motor->curmotorctrlinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle;
	else if(Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle<=-180)
		Motor->curmotorctrlinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle + 360;
	else if(Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle>=180)
		Motor->curmotorctrlinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle - 360;
}
/*-------------------------------------
* 函数名：减速电机角度解算
* 描述  ：计算减速后的累计角度
* 输入  ：电机结构体
* 输出  ：无

作者：LPGUAIA
日期：2021.4.27
-----------------------------------------*/ 
void gearmotor_angledecoder_sum(MotorInfo *Motor)
{
	
	Motor->tempdata.anglechanged=Motor->tempdata.temp_angle[1] - Motor->tempdata.temp_angle[0];
	Motor->tempdata.temp_angle[0]=Motor->tempdata.temp_angle[1];
	
	
	if(ABS(Motor->tempdata.anglechanged)<=300)
		Motor->tempdata.anglechanged=Motor->tempdata.anglechanged/Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged>300)
		Motor->tempdata.anglechanged = (Motor->tempdata.anglechanged-360) / Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged<-300)
		Motor->tempdata.anglechanged = (360 + Motor->tempdata.anglechanged) / Motor->parameter.reductiongearratio;
	
		Motor->curmotorctrlinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle;

}

/*-------------------------------------
* 函数名：线性斜坡加速整形
* 描述  ：用来对控制轮子和其他奇奇怪怪的东西输入输出整形防止打滑的
* 输入  ：数据结构体
* 输出  ：无

作者：LPGUAIA
日期：2021.4.27
-----------------------------------------*/ 
void k_shaper(kshaper_handle *kdata)
{
	if(ABS((kdata->data-kdata->lastdata)/kdata->sampleperi)<=kdata->k)
	{
		kdata->outdata=kdata->data;
		kdata->lastdata=kdata->data;
	}
	else if ((kdata->data-kdata->lastdata)/kdata->sampleperi<-kdata->k)
	{
		kdata->outdata=kdata->lastdata-kdata->k*kdata->sampleperi;
		kdata->lastdata=kdata->outdata;
	}
	else if ((kdata->data-kdata->lastdata)/kdata->sampleperi>kdata->k)
	{
		kdata->outdata=kdata->lastdata+kdata->k*kdata->sampleperi;
		kdata->lastdata=kdata->data;
	}
	
}

float anglecircle(float angle)
{
	if(angle>180.f)
		angle=angle-360.f;
	else if(angle<-180.f)
		angle=angle+360.f;

	return angle;
}

float anglelimit(float angle,float anglemax,float anglemin)
{
	if(angle>anglemax)
		angle=anglemax;
	else if(angle<anglemin)
		angle=anglemin;

	return angle;
}
