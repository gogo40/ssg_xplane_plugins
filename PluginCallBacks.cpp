/*
 * PluginCallBacks.cpp
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
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



