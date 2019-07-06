#include <iostream>
#include <string>
#include "Logger.h"
#include "LoggerSettings.h"
#include "DateTime.h"
#include "Entrega3.h"

using std::string;
using namespace ULLogger;
using ULLoggerSettings::LoggerSettings;
using ULDateTime::DateTimeFormat;
using std::cout;
using std::endl;

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
	cout<<finalContent<<endl;
	return elementoXml.substr(inicioContent,finalContent);
}

LoggerSettings* CreateLoggerSetting(string xmlLoggerSetting){
	string loggerEtiqueta = GetLogger(xmlLoggerSetting);
	string dateTimeFormat = GetAttributeValue(loggerEtiqueta, "dateTimeFormat");
	DateTimeFormat Format = ULDateTime::DateTimeFormatFromString(dateTimeFormat);
	LoggerSettings* logger = ULLoggerSettings::Create(Format);
	string contenido = GetContent(xmlLoggerSetting);
	cout<<contenido<<endl;
	//cout<<ULLoggerSettings::ToXml(logger)<<endl;
	return 0;
}

Logger* CreateLogger(LoggerSettings* setting){
}

Logger* BuildLoggerFromConfigFile(string pathConfigFile){

}

Logger* ULEntrega::BuildLogger(string xmlLoggerSetting){
	return CreateLogger(CreateLoggerSetting(xmlLoggerSetting));
}
