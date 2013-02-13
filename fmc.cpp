/*
 * fmc.cpp
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#include "SSGB748.h"

#include "utils.h"
#include "fmc.h"
#include "PluginCallBacks.h"
#include "PluginDataRef.h"

namespace SSG_B748 {

//================================================================================================//
/*PLUGIN DATA*/
/* File to write data to. */
FILE* g_output_file;
//================================================================================================//
/* Data refs we will record. */
PluginDataRef* g_data_ref = 0;

} // namespace SSG_B748

//================================================================================================//
/*PLUGIN ENTRY*/
extern "C" PLUGIN_API int XPluginStart(
	char* outName,
	char* outSig,
	char* outDesc)
{
	char	 outputPath[255];

	#if APL && __MACH__
	char outputPath2[255];
	int Result = 0;
	#endif

	strcpy(outName, SSG_B748::PluginName);
	strcpy(outSig, SSG_B748::PluginSig);
	strcpy(outDesc, SSG_B748::PluginDesc);

	/* Open a file to write to.  We locate the X-System directory
	 * and then concatenate our file name.  This makes us save in
	 * the X-System directory.  Open the file.
	 */
	XPLMGetSystemPath(outputPath);
	strcat(outputPath, SSG_B748::PluginNameLog);

	#if APL && __MACH__
	Result = ConvertPath(outputPath, outputPath2, sizeof(outputPath));
	if (Result == 0)
		strcpy(outputPath, outputPath2);
	else
		XPLMDebugString("RicardoPlugin - Unable to convert path\n");
	#endif

	SSG_B748::g_output_file = fopen(outputPath, "w");

	/* Find the data refs we want to record. */
	SSG_B748::g_data_ref = new SSG_B748::PluginDataRef;

	return 1;
}

extern "C" PLUGIN_API void	XPluginStop(void)
{
	/* Unregister data */
	if (SSG_B748::g_data_ref) {
		delete SSG_B748::g_data_ref;
		SSG_B748::g_data_ref = 0;
	}

	/* Close the file */
	fclose(SSG_B748::g_output_file);
}

extern "C" PLUGIN_API void XPluginDisable(void)
{
	fflush(SSG_B748::g_output_file);
}

extern "C" PLUGIN_API int XPluginEnable(void)
{
	return 1;
}

extern "C" PLUGIN_API void XPluginReceiveMessage(
	XPLMPluginID	inFromWho,
	long	 inMessage,
	void* inParam)
{
}

