/*
 * PluginDataRef.cpp
 *
 * SSG PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#include "utils.h"

#include "PluginManagement.h"
#include "PluginCallBacks.h"
#include "PluginData.h"

namespace SSG_PLUGIN {

//================================================================================================//
/*
PLUGIN DATA REF CLASS
*/

PluginManagement::PluginManagement()
	: XPCProcess()
{
}

PluginManagement::~PluginManagement()
{
	PLUGINDEBUGBEGIN("~PluginManagement");

	unregister();

	PLUGINDEBUGEND("~PluginManagement");
}

void PluginManagement::get()
{
	PLUGINDEBUGBEGIN("PluginManagement::get");

	m_mach_num = XPLMFindDataRef("sim/flightmodel/misc/machno");
	m_temp_OAT = XPLMFindDataRef("sim/cockpit2/temperature/outside_air_temp_degc");
	m_air_speed = XPLMFindDataRef("sim/flightmodel/position/indicated_airspeed");
	m_ground_speed = XPLMFindDataRef("sim/flightmodel/position/groundspeed");

	PLUGINDEBUGEND("PluginManagement::get");
}

void PluginManagement::set()
{
	PLUGINDEBUGBEGIN("PluginManagement::set");

	XPLMSetDataf(m_mach_num, m_mach_num_data);
	XPLMSetDataf(m_temp_OAT, m_temp_OAT_data);
	XPLMSetDataf(m_air_speed, m_air_speed_data);
	XPLMSetDataf(m_ground_speed, m_ground_speed_data);

	XPLMSetDataf(m_true_spd, m_true_spd_data);
	XPLMSetDataf(m_true_mach, m_true_mach_data);
	XPLMSetDataf(m_true_OAT, m_true_OAT_data);
	XPLMSetDataf(m_true_IAS, m_true_IAS_data);
	XPLMSetDataf(m_true_GNDSPD, m_true_GNDSPD_data);

	PLUGINDEBUGEND("PluginManagement::set");

}

void PluginManagement::create()
{
	/* register datarefs */
	PLUGINDEBUGBEGIN("PluginManagement::create");

	m_true_spd = PluginLoadFloat("SSG/AirData/TAS");
	m_true_mach = PluginLoadFloat("SSG/AirData/mach");
	m_true_OAT = PluginLoadFloat("SSG/AirData/OAT");
	m_true_IAS = PluginLoadFloat("SSG/AirData/IAS");
	m_true_GNDSPD = PluginLoadFloat("SSG/AirData/GNDSPD");

	PLUGINDEBUGEND("PluginManagement::create");
}

void PluginManagement::update()
{
	PLUGINDEBUGBEGIN("PluginManagement::update");

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

	PLUGINDEBUGEND("PluginManagement::update");
}

#if DEBUGMODE
static void PrintData(char* buffer, const char* name, float v)
{
	sprintf(buffer, "[PluginManagement::dump] %s = %lf\n", name, v);
	PLUGINDEBUG(buffer);
}

void PluginManagement::dump()
{
	char buffer[100];

	PrintData(buffer, "m_mach_num_data", m_mach_num_data);
	PrintData(buffer, "m_temp_OAT_data", m_temp_OAT_data);
	PrintData(buffer, "m_air_speed_data", m_air_speed_data);
	PrintData(buffer, "m_ground_speed_data", m_ground_speed_data);

	PrintData(buffer, "m_true_spd_data", m_true_spd_data);
	PrintData(buffer, "m_true_mach_data", m_true_mach_data);
	PrintData(buffer, "m_true_OAT_data", m_true_OAT_data);
	PrintData(buffer, "m_true_IAS_data", m_true_IAS_data);
	PrintData(buffer, "m_true_GNDSPD_data", m_true_GNDSPD_data);
}
#endif

void PluginManagement::unregister()
{
	PLUGINDEBUGBEGIN("PluginManagement::unregister");

	if (m_true_spd) {
		PluginRemoveFloat("SSG/AirData/TAS");
		PluginRemoveFloat("SSG/AirData/mach");
		PluginRemoveFloat("SSG/AirData/OAT");
		PluginRemoveFloat("SSG/AirData/IAS");
		PluginRemoveFloat("SSG/AirData/GNDSPD");
	}

	PLUGINDEBUGEND("PluginManagement::unregister");
}

void PluginManagement::DoProcessing(float inElapsedSinceLastCall,
								 float inElapsedTimeSinceLastFlightLoop,
								 int inCounter)
{
	PLUGINDEBUGBEGIN("PluginManagement::DoProcessing");

	update();
	m_true_spd_data = 661.47f * m_mach_num_data * static_cast<float>(sqrt((m_temp_OAT_data + 273.15f) / 288.15f));
	m_true_mach_data = m_true_spd_data / 38.967854f * static_cast<float>(sqrt(m_temp_OAT_data + 273.15f));
	m_true_GNDSPD_data = m_ground_speed_data * 60 * 60 / 1000 * 0.62137119f;
	m_true_IAS_data = m_air_speed_data;
	m_true_OAT_data = m_temp_OAT_data;
	set();

	PLUGINDEBUGDOOPERATION(update(); dump(););

	PLUGINDEBUGEND("PluginManagement::DoProcessing");
}

} // namespace SSG_PLUGIN
