/*
 * PluginDataRef.h
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 */

#ifndef _PLUGINDATAREF_H_
#define _PLUGINDATAREF_H_


#include <cstdio>
#include <cstring>
#include <cmath>

#include <XPLMPlugin.h>
#include <XPLMProcessing.h>
#include <XPLMDataAccess.h>
#include <XPLMUtilities.h>
#include <XPLMMenus.h>

//================================================================================================//
/*PLUGIN DATAREF CLASS*/
class PluginDataRef {
public:
	PluginDataRef() {}

	void set();
	void get();
	void create();
	void update();
	void unregister();

	void calc();

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
};

void PluginLoadDataRef();
void PluginUnloadDataRef();
void PluginCalc();

#endif //_PLUGINDATAREF_H_

