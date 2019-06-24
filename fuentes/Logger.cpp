#include "Logger.h"

#include "DateTime.h"
#include "LogLevel.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using ULAppender::Appender;
using ULDateTime::DateTime;
using ULDateTime::DateTimeFormat;
using namespace ULLogger;

struct Nodo
{
    Appender *item;
    Nodo *siguiente;
    LogLevel logLevel;
};

struct Lista
{
    Nodo *nodo;
};

struct ULLogger::Logger
{
    DateTimeFormat dateFormat;
    Lista *listaAppenders;
};

Nodo *CrearNodo(Appender *item, Nodo *proximo);

Lista *CrearLista(Nodo *primerElemento);

Nodo *ObtenerNodo(Lista *lista);

Nodo *ObtenerUltimoNodo(Lista *lista);

Nodo *CrearNodo(Appender *item, Nodo *proximo)
{
    Nodo *nuevoNodo = new Nodo;
    nuevoNodo->item = item;
    nuevoNodo->siguiente = proximo;
    return nuevoNodo;
}

Lista *CrearLista(Nodo *primerElemento)
{
    Lista *nuevaLista = new Lista;
    nuevaLista->nodo = primerElemento;
    return nuevaLista;
}

Nodo *ObtenerUltimoNodo(Lista *lista)
{
    Nodo *iterador = lista->nodo;
    while (iterador->siguiente != NULL)
    {
        iterador = iterador->siguiente;
    }
    return iterador;
}

void DestruirNodo(Nodo *nodo)
{
    delete nodo;
}

Logger* ULLogger::Create(DateTimeFormat dateTimeFormat)
{
    ULLogger::Logger *newLogger = new Logger;
    newLogger->dateFormat = dateTimeFormat;
    newLogger->listaAppenders = CrearLista(NULL);
    return newLogger;
}

void ULLogger::SetDateTimeFormat(Logger *logger, DateTimeFormat dateTimeFormat)
{
    logger->dateFormat = dateTimeFormat;
}

DateTimeFormat ULLogger::GetDateTimeFormat(const Logger *logger)
{
    return logger->dateFormat;
}

/*
	 * Precondicion: @logger construido con la primitiva CreateLogger.
	 * @appender construido con alguna de sus primitivas de construccion.
	 * Postcondicion: Si no existe el @appender, lo agrega en @logger y le asocia el @level al mismo @appender.
	 * Si ya existe el @appender, lo elimina y lo reemplaza.
	 * Dos appender de tipo consola siempre son iguales. Dos appender de tipo archivo son iguales si tienen el mimsmo path file.
	 */
void ULLogger::AddAppender(Logger *logger, Appender *appender, LogLevel level)
{
    if (logger->listaAppenders == NULL)
    {
        logger->listaAppenders->nodo = CrearNodo(appender, NULL);
        logger->listaAppenders->nodo->logLevel = level;
    }
    else
    {
    	bool fueReemplazado=false;
    	Nodo* iterador = logger->listaAppenders->nodo;
    	while (iterador!=NULL){
			if (ULAppender::SonIguales(appender, iterador->item)){
				ULAppender::Destroy(iterador->item);
				iterador->item=appender;
				fueReemplazado =true;
			}

			iterador = iterador->siguiente;
    	}
    	if(fueReemplazado!= true){
    		logger->listaAppenders->nodo = CrearNodo(appender,logger->listaAppenders->nodo);
    	}
    }
}


// Postcondicion : Si el @appender existe en @logger lo elimina(ya no se puede logear mas en ese appender).
// *Si el @appender no existe, no se realiza ninguna accion
void ULLogger::RemoveAppender(Logger *logger, Appender *appender)
{
    if (logger->listaAppenders != NULL)
    {
        Nodo *aux_borrar;
        Nodo *anterior = NULL;

        aux_borrar = logger->listaAppenders->nodo;

        while ((aux_borrar != NULL) && (aux_borrar->item != appender))
        {
            anterior = aux_borrar;
            aux_borrar = aux_borrar->siguiente;
        }

        if (aux_borrar == NULL)
        {
            cout << "El elemento no ha sido encontrado";
        }
        else if (anterior == NULL)
        {
            logger->listaAppenders->nodo = logger->listaAppenders->nodo->siguiente;
            delete aux_borrar;
        }
        else
        {
            anterior->siguiente = aux_borrar->siguiente;
            delete aux_borrar;
        }
    }
}

void ULLogger::LogFatalMessage(Logger *logger, string message)
{
    if (logger->listaAppenders != NULL)
    {
        string formatedMessage = "";
        DateTime *now = ULDateTime::Now();
        Nodo* iterador = logger->listaAppenders->nodo;
        while (iterador->siguiente != NULL)
        {
            if (iterador->logLevel != LogLevel::OFF)
            {
                formatedMessage = "[" + ULDateTime::ToFormat(now, logger->dateFormat) + "] [FATAL]: " + message;
                ULAppender::Write(iterador->item, formatedMessage);
            }
            iterador = iterador->siguiente;
        }
    }
}

void ULLogger::LogErrorMessage(Logger *logger, string message)
{
    if (logger->listaAppenders != NULL)
    {
        LogLevel level;
        string formatedMessage = "";
        DateTime *now = ULDateTime::Now();
        Nodo* iterador = logger->listaAppenders->nodo;
        while (iterador->siguiente != NULL)
        {
            level = iterador->logLevel;
            if (level == LogLevel::DEBUG || level == LogLevel::WARN || level == LogLevel::INFO || level == LogLevel::TRACE || level == LogLevel::ERROR)
            {
                formatedMessage = "[" + ULDateTime::ToFormat(now, logger->dateFormat) + "] [ERROR]: " + message;
                ULAppender::Write(iterador->item, formatedMessage);
            }
            iterador = iterador->siguiente;
        }

    }
}

void ULLogger::LogWarningMessage(Logger *logger, string message)
{
    if (logger->listaAppenders != NULL)
    {
        LogLevel level;
        string formatedMessage = "";
        DateTime *now = ULDateTime::Now();
        Nodo* iterador = logger->listaAppenders->nodo;
        while (iterador->siguiente != NULL)
        {
            level = iterador->logLevel;
            if (level == LogLevel::DEBUG || level == LogLevel::WARN || level == LogLevel::INFO || level == LogLevel::TRACE)
            {
                formatedMessage = "[" + ULDateTime::ToFormat(now, logger->dateFormat) + "] [WARN]: " + message;
                ULAppender::Write(iterador->item, formatedMessage);
            }
            iterador = iterador->siguiente;
        }
    }
}

void ULLogger::LogInfoMessage(Logger *logger, string message)
{
    if (logger->listaAppenders != NULL)
    {
        LogLevel level;
        string formatedMessage = "";
        DateTime *now = ULDateTime::Now();
        Nodo* iterador = logger->listaAppenders->nodo;
        while (iterador->siguiente != NULL)
        {
            level = iterador->logLevel;
            if (level == LogLevel::DEBUG || level == LogLevel::INFO || level == LogLevel::TRACE)
            {
                formatedMessage = "[" + ULDateTime::ToFormat(now, logger->dateFormat) + "] [INFO]: " + message;
                ULAppender::Write(iterador->item, formatedMessage);
            }
            iterador = iterador->siguiente;
        }
    }
}

void ULLogger::LogDebugMessage(Logger *logger, string message)
{
    if (logger->listaAppenders != NULL)
    {
        LogLevel level;
        string formatedMessage = "";
        DateTime *now = ULDateTime::Now();
        Nodo* iterador = logger->listaAppenders->nodo;
        while (iterador->siguiente != NULL)
        {
            level = iterador->logLevel;
            if (level == LogLevel::DEBUG || level == LogLevel::TRACE)
            {
                formatedMessage = "[" + ULDateTime::ToFormat(now, logger->dateFormat) + "] [DEBUG]: " + message;
                ULAppender::Write(iterador->item, formatedMessage);
            }
            iterador = iterador->siguiente;
        }
    }
}

void ULLogger::LogTraceMessage(Logger *logger, string message)
{
    if (logger->listaAppenders != NULL)
    {
        LogLevel level;
        string formatedMessage = "";
        DateTime *now = ULDateTime::Now();
        Nodo* iterador = logger->listaAppenders->nodo;
        while (iterador->siguiente != NULL)
        {
            level = iterador->logLevel;
            if (level == LogLevel::TRACE)
            {
                formatedMessage = "[" + ULDateTime::ToFormat(now, logger->dateFormat) + "] [TRACE]: " + message;
                ULAppender::Write(iterador->item, formatedMessage);
            }
            iterador = iterador->siguiente;
        }
    }
}

void ULLogger::Destroy(Logger *logger)
{
    delete logger;
}
