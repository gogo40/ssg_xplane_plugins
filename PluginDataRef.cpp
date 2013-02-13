/*
 * PluginDataRef.cpp
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#include "PluginDataRef.h"
#include "PluginCallBacks.h"
#include "PluginData.h"

namespace SSG_B748 {

//================================================================================================//
/*
PLUGIN DATA REF CLASS
*/

PluginDataRef::PluginDataRef()
	: XPCProcess()
{
	create();
	get();
}

PluginDataRef::~PluginDataRef()
{
	unregister();
}

void PluginDataRef::get()
{
	m_mach_num = XPLMFindDataRef("sim/flightmodel/misc/machno");
	m_temp_OAT = XPLMFindDataRef("sim/cockpit2/temperature/outside_air_temp_degc");
	m_air_speed = XPLMFindDataRef("sim/flightmodel/position/indicated_airspeed");
	m_ground_speed = XPLMFindDataRef("sim/flightmodel/position/groundspeed");
}

void PluginDataRef::set()
{
	XPLMSetDataf(m_mach_num, m_mach_num_data);
	XPLMSetDataf(m_temp_OAT, m_temp_OAT_data);
	XPLMSetDataf(m_air_speed, m_air_speed_data);
	XPLMSetDataf(m_ground_speed, m_ground_speed_data);

	XPLMSetDataf(m_true_spd, m_true_spd_data);
	XPLMSetDataf(m_true_mach, m_true_mach_data);
	XPLMSetDataf(m_true_OAT, m_true_OAT_data);
	XPLMSetDataf(m_true_IAS, m_true_IAS_data);
	XPLMSetDataf(m_true_GNDSPD, m_true_GNDSPD_data);
}

void PluginDataRef::create()
{
	/* register datarefs */
	m_true_spd = PluginAddFloat("SSG/AirData/TAS", &m_true_spd_data);
	m_true_mach = PluginAddFloat("SSG/AirData/mach", &m_true_mach_data);
	m_true_OAT = PluginAddFloat("SSG/AirData/OAT", &m_true_OAT_data);
	m_true_IAS = PluginAddFloat("SSG/AirData/IAS", &m_true_IAS_data);
	m_true_GNDSPD = PluginAddFloat("SSG/AirData/GNDSPD", &m_true_GNDSPD_data);
}

void PluginDataRef::update()
{
	/*sim data*/
	m_mach_num_data = XPLMGetDataf(m_mach_num);
	m_temp_OAT_data = XPLMGetDataf(m_temp_OAT);
	m_air_speed_data = XPLMGetDataf(m_air_speed);
	m_ground_speed_data = XPLMGetDataf(m_ground_speed);

	/*specific plugin data*/
	m_true_spd_data = XPLMGetDataf(m_true_spd);
	m_true_mach_data = XPLMGetDataf(m_true_mach);
	m_true_OAT_data = XPLMGetDataf(m_true_OAT);
	m_true_IAS_data	= XPLMGetDataf(m_true_IAS);
	m_true_GNDSPD_data = XPLMGetDataf(m_true_GNDSPD);
}

void PluginDataRef::unregister()
{
	if (m_true_spd) {
		XPLMUnregisterDataAccessor(m_true_spd);
		XPLMUnregisterDataAccessor(m_true_mach);
		XPLMUnregisterDataAccessor(m_true_OAT);
		XPLMUnregisterDataAccessor(m_true_IAS);
		XPLMUnregisterDataAccessor(m_true_GNDSPD);
	}
}

void PluginDataRef::DoProcessing(float inElapsedSinceLastCall,
								 float inElapsedTimeSinceLastFlightLoop,
								 int inCounter)
{
	m_true_spd_data = 661.47 * m_mach_num_data * sqrt((m_temp_OAT_data + 273.15) / 288.15);
	m_true_mach_data = m_true_spd_data / 38.967854 * sqrt(m_temp_OAT_data + 273.15);
	m_true_GNDSPD_data = m_ground_speed_data * 60 * 60 / 1000 * 0.62137119;
	m_true_IAS_data = m_air_speed_data;

	set();
}

} // namespace SSG_B748
