#include <stdio.h>

#include "public/emu_gss_v1.h"
#include "emu_gss/emu_gss_pus_service129.h"
#include "public/icuasw_pus_services_iface_v1.h"
#include <public/emu_uah_exp_kinematics.h>
// Metemos 8 porque cada float son 4 bytes
#define TC_129_APPDATA_LENGTH 8

EmuGSS_TCProgram129_1::EmuGSS_TCProgram129_1(uint32_t uniTime2YK,
		const char * brief,  float CVx, float CVy)
                        :EmuGSS_TCProgram(uniTime2YK,129,1,
                        		TC_129_APPDATA_LENGTH,brief){
	sCVx = CVx;
	sCVy = CVy;
    NewProgram(this);
}

void EmuGSS_TCProgram129_1::BuildTCAppData(tc_descriptor_t &tc_descriptor){

	SetNextFloat(sCVx);
	SetNextFloat(sCVy);

}


EmuGSS_TCProgram129_2::EmuGSS_TCProgram129_2(uint32_t uniTime2YK,
		const char * brief,  float Kpx, float Kpy)
                        :EmuGSS_TCProgram(uniTime2YK,129,2,
                        		TC_129_APPDATA_LENGTH,brief){
	sKpx = Kpx;
	sKpy = Kpy;
    NewProgram(this);
}

void EmuGSS_TCProgram129_2::BuildTCAppData(tc_descriptor_t &tc_descriptor){

	SetNextFloat(sKpx);
	SetNextFloat(sKpy);

}
