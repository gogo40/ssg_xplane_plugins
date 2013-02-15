/*
 * PluginDataRef.h
 *
 * SSG PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#ifndef _PLUGINMANAGEMENT_H_
#define _PLUGINMANAGEMENT_H_


#include <cstdio>
#include <cstring>
#include <cmath>


#include <XPLMPlugin.h>
#include <XPLMProcessing.h>
#include <XPLMDataAccess.h>
#include <XPLMUtilities.h>
#include <XPLMMenus.h>
#include <XPCProcessing.h>

#include "utils.h"

namespace SSG_PLUGIN {

//================================================================================================//
/*PLUGIN DATAREF CLASS*/
class PluginManagement : public XPCProcess {
public:
	PluginManagement();

	virtual ~PluginManagement();

	virtual	void		DoProcessing(
							float 				inElapsedSinceLastCall,
							float				inElapsedTimeSinceLastFlightLoop,
							int 				inCounter);
	void set();
	void get();
	void create();
	void update();
	void unregister();

#if DEBUGMODE
	void dump();
#endif

private:
	/*sim data*/
	XPLMDataRef	m_mach_num;
	XPLMDataRef	m_temp_OAT;
	XPLMDataRef	m_air_speed;
	XPLMDataRef	m_ground_speed;

	float m_mach_num_data;
	float m_temp_OAT_data;
	float m_air_speed_data;
	float m_ground_speed_data;

	/*specific plugin data*/
	XPLMDataRef	m_true_spd;
	XPLMDataRef	m_true_mach;
	XPLMDataRef	m_true_OAT;
	XPLMDataRef	m_true_IAS;
	XPLMDataRef	m_true_GNDSPD;

	float m_true_spd_data;
	float m_true_mach_data;
	float m_true_OAT_data;
	float m_true_IAS_data;
	float m_true_GNDSPD_data;

	DISALLOW_COPY_AND_ASSIGN(PluginManagement);
};

} // namespace SSG_PLUGIN

#endif //_PLUGINDATAREF_H_

