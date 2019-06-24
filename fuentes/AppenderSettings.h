#ifndef APPENDERSETTINGS_H_
#define APPENDERSETTINGS_H_

#include <string>
#include "AppenderType.h"
#include "LogLevel.h"

using std::string;

namespace ULAppenderSettings{
	struct AppenderSettings;

	/*
	 * Precondicion: Ninguna
	 * Postcondicion: Devuelve una instancia valida de un setting de tipo consola
	 * que tiene una configuracion @logLevel
	 */
	AppenderSettings* CreateAppenderConsoleSetting(LogLevel logLevel);

	/*
	 * Precondicion: Ninguna
	 * Postcondicion: Devuelve una instancia valida de un setting de tipo archivo
	 * que tiene una configuracion @logLevel y un @pathFile
	 */
	AppenderSettings* CreateAppenderFileSetting(LogLevel logLevel, string pathFile);

	/*
	 * Precondicion: @setting es una instancia valida
	 * Postcondicion: Devuelve el LogLevel que tiene asociado @settings
	 */
	LogLevel GetLogLevel(const AppenderSettings* settings);

	string GetLogLevelAsString(const AppenderSettings* settings);

	/*
	 * Precondicion: @setting es una instancia valida
	 * Postcondicion: Devuelve el AppenderType que tiene asociado @settings
	 */
	AppenderType GetAppenderType(const AppenderSettings* settings);

	string GetAppenderTypeAsString(const AppenderSettings* settings);

	/*
	 * Precondicion: @setting es una instancia valida
	 * Postcondicion: Devuelve el path de archivo que tiene asociado @settings.
	 * Si no tiene asociado ningun path de archivo devuelve un string vacio
	 */
	string GetPathFile(const AppenderSettings* settings);

	/*
	 * Precondicion: @setting es una instancia valida
	 * Postcondicion: Libera todos los recursos asociados de @setting
	 */
	void Destroy(AppenderSettings* setting);
}

#endif
