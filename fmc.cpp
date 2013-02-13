/*
 * fmc.cpp
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#include "utils.h"
#include "fmc.h"
#include "PluginCallBacks.h"
#include "PluginDataRef.h"

//================================================================================================//
/*PLUGIN DATA*/
/* File to write data to. */
FILE* g_output_file;
//================================================================================================//
/* Data refs we will record. */
PluginDataRef* g_data_ref = 0;

//================================================================================================//
/*PLUGIN ENTRY*/
PLUGIN_API int XPluginStart(
	char* outName,
	char* outSig,
	char* outDesc)
{
	char	 outputPath[255];

	#if APL && __MACH__
	char outputPath2[255];
	int Result = 0;
	#endif

	strcpy(outName, PluginName);
	strcpy(outSig, PluginSig);
	strcpy(outDesc, PluginDesc);

	/* Open a file to write to.  We locate the X-System directory
	 * and then concatenate our file name.  This makes us save in
	 * the X-System directory.  Open the file.
	 */
	XPLMGetSystemPath(outputPath);
	strcat(outputPath, PluginNameLog);

	#if APL && __MACH__
	Result = ConvertPath(outputPath, outputPath2, sizeof(outputPath));
	if (Result == 0)
		strcpy(outputPath, outputPath2);
	else
		XPLMDebugString("RicardoPlugin - Unable to convert path\n");
	#endif

	g_output_file = fopen(outputPath, "w");

	/* Find the data refs we want to record. */
	g_data_ref = new PluginDataRef;

	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	/* Unregister the callback */
	XPLMUnregisterFlightLoopCallback(PluginFlightLoopCallback, NULL);

	/* Unregister data */
	if (g_data_ref) {
		delete g_data_ref;
		g_data_ref = 0;
	}

	/* Close the file */
	fclose(g_output_file);
}

PLUGIN_API void XPluginDisable(void)
{
	fflush(g_output_file);
}

PLUGIN_API int XPluginEnable(void)
{
	return 1;
}

PLUGIN_API void XPluginReceiveMessage(
	XPLMPluginID	inFromWho,
	long	 inMessage,
	void* inParam)
{
}

