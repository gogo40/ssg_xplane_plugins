/*
 * PluginCallBacks.cpp
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 */

#include "PluginCallBacks.h"
#include "PluginDataRef.h"

//================================================================================================//
/*Plugin callback*/

float PluginGetFloat(void* refcon)
{
  float* my_var = static_cast<float*>(refcon);
  return *my_var;
}

void  PluginSetFloat(void* inRefcon, float inValue)
{
	float* my_var = static_cast<float*>(inRefcon);
	*my_var = inValue;
}


float	PluginFlightLoopCallback(
	float inElapsedSinceLastCall,
	float inElapsedTimeSinceLastFlightLoop,
	int inCounter,
	void* inRefcon)
{
	/* Do calculation*/
	PluginCalc();

	return 1.0;
}



