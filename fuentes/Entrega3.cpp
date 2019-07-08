#include <iostream>
#include <string>
#include "Logger.h"
#include "LoggerSettings.h"
#include "DateTime.h"
#include "Entrega3.h"
#include "AppenderSettings.h"
#include "LogLevel.h"
#include "AppenderType.h"

using std::string;
using namespace ULLogger;
using ULLoggerSettings::LoggerSettings;
using ULDateTime::DateTimeFormat;
using std::cout;
using std::endl;
using ULAppenderSettings::AppenderSettings;

string GetAttributeValue(string elementoXml, string nombreAtributo){
	int largoAtributo = nombreAtributo.length();
	int atributoInicio = elementoXml.find(nombreAtributo + "=\"");
	int comienzoValue = atributoInicio + largoAtributo + 2;
	string auxElementoXml = elementoXml.substr(comienzoValue, elementoXml.length());
	int finalValue = auxElementoXml.find("\"");
	return elementoXml.substr(comienzoValue,finalValue);
}


string GetLogger(string elementoXml){
	int largoLogger = 6; //es el largo de la cadena "logger" + 1
	int comiezoLogger = elementoXml.find("logger");
	string auxElementoXml = elementoXml.substr(comiezoLogger + largoLogger, elementoXml.length());
	int finalEtiqueta = elementoXml.find(">");
	return elementoXml.substr(comiezoLogger,finalEtiqueta - 1);
}

string GetContent(string elementoXml){
	int inicioContent = elementoXml.find("\">") + 2;
	int finalContent =elementoXml.find("/>");
	return elementoXml.substr(inicioContent,finalContent);
}

string GetAppender(string* elementoXml){
	string appenderString = "<appender";
	string appernderStringF = "\n";
 	int Inicioapp = elementoXml->find(appenderString);
 	string aux_elementoXml = elementoXml->substr(Inicioapp, elementoXml->length());
 	int finalApp = aux_elementoXml.find(appernderStringF);
 	*elementoXml = elementoXml->substr(finalApp, elementoXml->length());
 	//cout<<*elementoXml<<endl;
 	return aux_elementoXml.substr(0, finalApp);

}

AppenderSettings* ParseAppender(string appender){
	string loglevelString = "logLevel=\"";
	string typeString = "type=\"";
	string PathString = "";
	int largologString = loglevelString.length();
	int largotypeString = typeString.length();
	int logInicio = appender.find(loglevelString);
	int TypeInicio = appender.find(typeString);
	string aux1 = appender.substr(TypeInicio + largotypeString,appender.length());
	int fintypeString = aux1.find("\"");
	string TypeString = aux1.substr(0, fintypeString);
	string aux2 = appender.substr(logInicio + largologString,appender.length());
	int finLogString = aux2.find("\"");
	string logString = aux2.substr(0, finLogString);
	if(TypeString == "file"){
		string pathString = "path=\"";
		int pathStringLargo = pathString.length();
		int iniciopath = appender.find(pathString);
		string aux3 = appender.substr(iniciopath + pathStringLargo, appender.length());
		int finalpath = aux3.find("\"");
		PathString = aux3.substr(0,finalpath);
	}

	AppenderType type = ULAppenderSettings::GetAppenderTypeFromString(TypeString);
	LogLevel log = ULAppenderSettings::GetLogLevelFromString(logString);
	AppenderSettings* appenderSettings = 0;
	if(type == Console){
		appenderSettings = ULAppenderSettings::CreateAppenderConsoleSetting(log);
	}
	else{
		appenderSettings = ULAppenderSettings::CreateAppenderFileSetting(log,PathString);
	}

	return appenderSettings;
}

bool SearchAtribute(string elementoXml, string atributo){
	int aux = elementoXml.find(atributo);
	bool resultado = true;
	if(aux == -1){
		resultado = false;
	}
	return resultado;
}

LoggerSettings* CreateLoggerSetting(string xmlLoggerSetting){
	string loggerEtiqueta = GetLogger(xmlLoggerSetting);
	string dateTimeFormat = GetAttributeValue(loggerEtiqueta, "dateTimeFormat");
	DateTimeFormat Format = ULDateTime::DateTimeFormatFromString(dateTimeFormat);
	LoggerSettings* logger = ULLoggerSettings::Create(Format);
	string contenido = GetContent(xmlLoggerSetting);
	while(SearchAtribute(xmlLoggerSetting,"appender")){
		string appender = GetAppender(&xmlLoggerSetting);
		cout<<appender<<endl;
		AppenderSettings* appenderr = ParseAppender(appender);
		ULLoggerSettings::AddAppenderSetting(logger,appenderr);
	}
	cout<<ULLoggerSettings::ToXml(logger)<<endl;
	return logger;
}

Logger* CreateLogger(LoggerSettings* setting){
	Logger* logger = ULLogger::Create(ULLoggerSettings::ObtenerDateTimeFormat(setting));
	return logger;
}

Logger* BuildLoggerFromConfigFile(string pathConfigFile){

}

Logger* ULEntrega::BuildLogger(string xmlLoggerSetting){
	return CreateLogger(CreateLoggerSetting(xmlLoggerSetting));
}
