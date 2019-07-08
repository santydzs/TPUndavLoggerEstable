#include "AppenderSettings.h"

#include <string>
#include "AppenderType.h"
#include "LogLevel.h"

using namespace ULAppenderSettings;
using std::string;


struct ULAppenderSettings::AppenderSettings {
    AppenderType type;
    LogLevel logLevel;
    string path;
};

AppenderSettings* ULAppenderSettings::CreateAppenderConsoleSetting(LogLevel logLevel) {
    ULAppenderSettings::AppenderSettings *newAppenderSetting = new AppenderSettings;
    newAppenderSetting->type = Console;
    newAppenderSetting->logLevel = logLevel;
    newAppenderSetting->path = "";
    return newAppenderSetting;
}

AppenderSettings* ULAppenderSettings::CreateAppenderFileSetting(LogLevel logLevel, string pathFile) {
    ULAppenderSettings::AppenderSettings* newAppenderSetting = new AppenderSettings;
    newAppenderSetting->type = File;
    newAppenderSetting->logLevel = logLevel;
    newAppenderSetting->path = pathFile;
    return newAppenderSetting;
}

LogLevel ULAppenderSettings::GetLogLevel(const AppenderSettings* settings) {
    return settings->logLevel;
}

AppenderType ULAppenderSettings::GetAppenderType(const AppenderSettings* settings) {
    return settings->type;
}

string ULAppenderSettings::GetPathFile(const AppenderSettings *settings) {
    return settings->path;
}

void ULAppenderSettings::Destroy(AppenderSettings* settings) {
    delete settings;

}

string ULAppenderSettings::GetLogLevelAsString(const AppenderSettings* settings){
	string level;
	switch (settings->logLevel){
		case FATAL:
			level= "FATAL";
			break;
		case OFF:
			level = "OFF";
			break;
		case ERROR:
			level = "ERROR";
			break;
		case WARN:
			level = "WARN";
			break;
		case INFO:
			level = "INFO";
			break;
		case DEBUG:
			level = "DEBUG";
			break;
		case TRACE:
			level = "TRACE";
			break;
	}
	return level;
}

LogLevel ULAppenderSettings::GetLogLevelFromString(const string level){
	LogLevel loglevel;
	if(level=="FATAL") loglevel = FATAL;
	if(level=="OFF") loglevel = OFF;
	if(level=="ERROR") loglevel = ERROR;
	if(level=="WARN") loglevel = WARN;
	if(level=="INFO") loglevel = INFO;
	if(level=="DEBUG") loglevel = DEBUG;
	if(level=="TRACE") loglevel = TRACE;
	return loglevel;
}

string ULAppenderSettings::GetAppenderTypeAsString(const AppenderSettings* settings){
	string type;
	switch(settings->type){
		case Console:
			type = "Console";
			break;
		case File:
			type="File";
			break;
	}
	return type;
}

AppenderType ULAppenderSettings::GetAppenderTypeFromString(const string type){
	AppenderType appenderType;
	if(type == "console") appenderType = Console;
	if(type == "file") appenderType = File;
	return appenderType;
}
