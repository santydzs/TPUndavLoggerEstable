#include <string>
#include "LoggerSettings.h"
#include "DateTime.h"
#include "AppenderSettings.h"

using std::to_string;
using ULDateTime::DateTimeFormat;
using ULAppenderSettings::AppenderSettings;
using ULLoggerSettings::LoggerSettings;

struct Nodo{
	AppenderSettings* item;
	Nodo* siguiente;
};

struct Lista{
	Nodo* primero;
};

struct ULLoggerSettings::LoggerSettings{
	DateTimeFormat DateFormat;
	Lista* listaAppenderSettings;
};

Nodo* CrearNodo(AppenderSettings* item, Nodo* proximo){
	Nodo* nuevoNodo = new Nodo;
	nuevoNodo->item = item;
	nuevoNodo->siguiente = proximo;
	return nuevoNodo;
}

//Precondicion: primerElemento es una instancia valida de @Nodo
//Postcondicion: Devuelve una instancia valida de @Lista con el primer elemento cargado
Lista* CrearListaAppenders(Nodo* primerElemento){
	Lista* nuevaLista = new Lista;
	nuevaLista ->primero = primerElemento;
	return nuevaLista;
}

//Precondicion: item es una instancia de @AppenderSettings valida, y proximo una instancia de @Nodo valido
//PostCondicion: se devolvera una instancia valida de @Nodo
Nodo* ObtenerUltimoNodoo(Lista* lista){
	Nodo* iterador = lista->primero;
	while(iterador->siguiente != NULL){
		iterador = iterador->siguiente;
	}
	return iterador;
}



LoggerSettings* ULLoggerSettings::Create(DateTimeFormat dateTimeFormat){
	LoggerSettings* nuevoLoggerSettings = new LoggerSettings;
	nuevoLoggerSettings->DateFormat = dateTimeFormat;
	nuevoLoggerSettings->listaAppenderSettings = CrearListaAppenders(NULL);
	return nuevoLoggerSettings;
}

void ULLoggerSettings::AddAppenderSetting(LoggerSettings* setting, AppenderSettings* appenderSetting){
	if(setting->listaAppenderSettings->primero == NULL){
		setting->listaAppenderSettings->primero = CrearNodo(appenderSetting, NULL);
	}
	else{
		Nodo* ultimoNodo = ObtenerUltimoNodoo(setting->listaAppenderSettings);
		ultimoNodo->siguiente = CrearNodo(appenderSetting, NULL);
	}
}

string ULLoggerSettings::ToXml(const LoggerSettings* setting){
	string Xml = "<logger dateTimeFormat=\"" + ULDateTime::DateTimeFormatAsString(setting->DateFormat) +  "\" />";
	Nodo* iterador = setting->listaAppenderSettings->primero;
	while(iterador != NULL){
		Xml += "\n\t<appender logLevel=\""+ ULAppenderSettings::GetLogLevelAsString(iterador->item) + "\"";
		Xml += " type= \""+ ULAppenderSettings::GetAppenderTypeAsString(iterador->item) + "\" />";
		iterador = iterador->siguiente;
	}
	Xml += "\n</logger>";
	return Xml;
}

void ULLoggerSettings::Destroy(LoggerSettings* setting){
	Nodo* iterador = setting->listaAppenderSettings->primero;
	Nodo* auxiliar;
	while(iterador != NULL){
		auxiliar = iterador;
		iterador = iterador->siguiente;
		delete auxiliar;
	}
	delete setting;
}

DateTimeFormat ULLoggerSettings::ObtenerDateTimeFormat(LoggerSettings* setting){
	return setting->DateFormat;
}
