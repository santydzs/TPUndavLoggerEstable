#ifndef LOGGER_H_
#define LOGGER_H_

#include "Appender.h"
#include "DateTime.h"
#include "LogLevel.h"
#include <string>

using std::string;
using ULAppender::Appender;
using ULDateTime::DateTimeFormat;

namespace ULLogger{

	struct Logger;

	/*
	 * Precondicion: Ninguna
	 * Postcondicion: Obtiene una instancia de Logger valida
	 * y lista para ser utilizada con las primitivas de UndavLogger.
	 */
	Logger* Create(DateTimeFormat dateTimeFormat = ULDateTime::DDMMYYYY_hhmmss);

	/*
	 * Precondicion: @logger es una instancia valida
	 * Postcondicion: Establece el tipo de formato de fecha y hora del logger
	 */
	void SetDateTimeFormat(Logger* logger, DateTimeFormat dateTimeFormat);

	/*
	 * Precondicion: @logger es una instancia valida
	 * Postcondicion: Obtiene el tipo de formato de fecha y hora asociado al logger
	 */
	DateTimeFormat GetDateTimeFormat(const Logger* logger);

	/*
	 * Precondicion: @logger construido con la primitiva CreateLogger.
	 * @appender construido con alguna de sus primitivas de construccion.
	 * Postcondicion: Si no existe el @appender, lo agrega en @logger y le asocia el @level al mismo @appender.
	 * Si ya existe el @appender, lo elimina y lo reemplaza.
	 * Dos appender de tipo consola siempre son iguales. Dos appender de tipo archivo son iguales si tienen el mimsmo path file.
	 */
	void AddAppender(Logger* logger, Appender* appender, LogLevel level);

	/*
	 * Precondicion: @logger construido con la primitiva CreateLogger.
	 * @appender construido con alguna de sus primitivas de construccion.
	 * Postcondicion: Si el @appender existe en @logger lo elimina (ya no se puede logear mas en ese appender).
	 * Si el @appender no existe, no se realiza ninguna accion
	 */
	void RemoveAppender(Logger* logger, Appender* appender);

	/*
	 * Precondicion: @logger construido con la primitiva CreateLogger
	 * Postcondicion: Si el @logger no tiene appenders no realiza acción.
	 * Si hay appenders chequea en cada appender si el 'Log level' asociado al appender es distinto de 'OFF'
	 * entonces escribe en el appender el mensaje dado por parametro en @message.
	 * El formato del 'log' que escribe el logger en cada appender debe ser: "[datetime] [FATAL]: @message"
	 * donde [datetime] es la fecha y hora actual en el formato configurado
	 */
	void LogFatalMessage(Logger* logger, string message);

	/*
	 * Precondicion: @logger construido con la primitiva CreateLogger
	 * Postcondicion:  Si el @logger no tiene appenders no realiza acción.
	 * Si hay appenders chequea en cada appender si el 'Log level' asociado al appender es
	 * 'ERROR' o 'WARN' o 'INFO' o 'DEBUG' o 'TRACE' entonces escribe
	 * en el appender el mensaje dado por parametro en  @message.
	 * El formato del 'log' que escribe el logger debe ser: "[datetime] [ERROR]: @message"
	 * donde [datetime] es la fecha y hora actual en el formato configurado
	 */
	void LogErrorMessage(Logger* logger, string message);

	/*
	 * Precondicion: @logger construido con la primitiva CreateLogger
	 * Postcondicion: Si el @logger no tiene appenders no realiza acción.
	 * Si hay appenders chequea en cada appender si el 'Log level' asociado al appender es
	 * 'WARN' o 'INFO' o 'DEBUG' o 'TRACE' entonces escribe
	 * en el appender el mensaje dado por parametro en @message.
	 * El formato del 'log' que escribe el logger debe ser: "[datetime] [WARN]: @message"
	 * donde [datetime] es la fecha y hora actual en el formato configurado
	 */
	void LogWarningMessage(Logger* logger, string message);

	/*
	 * Precondicion: @logger construido con la primitiva CreateLogger
	 * Postcondicion: Si el @logger no tiene appenders no realiza acción.
	 * Si hay appenders chequea en cada appender si el 'Log level' asociado al appender es
	 * 'INFO' o 'DEBUG' o 'TRACE' entonces escribe
	 * en el appender el mensaje dado por parametro en @message.
	 * El formato del 'log' que escribe el logger debe ser: "[dd-mm-aaaa HH:mm:ss] [INFO]: @message"
	 * donde [datetime] es la fecha y hora actual en el formato configurado
	 */
	void LogInfoMessage(Logger* logger, string message);

	/*
	 * Precondicion: @logger construido con la primitiva CreateLogger
	 * Postcondicion: Si el @logger no tiene appenders no realiza acción.
	 * Si hay appenders chequea en cada appender si el 'Log level' asociado al appender es
	 * 'DEBUG' o 'TRACE' entonces escribe
	 * en el appender el mensaje dado por parametro en @message.
	 * El formato del 'log' que escribe el logger debe ser: "[dd-mm-aaaa HH:mm:ss] [DEBUG]: @message"
	 * donde [datetime] es la fecha y hora actual en el formato configurado
	 */
	void LogDebugMessage(Logger* logger, string message);

	/*
	 * Precondicion: @logger construido con la primitiva CreateLogger
	 * Postcondicion: Si el @logger no tiene appenders no realiza acción.
	 * Si hay appenders chequea en cada appender si el 'Log level' asociado al appender es 'TRACE' entonces escribe
	 * en el appender el mensaje dado por parametro en @message.
	 * El formato del 'log' que escribe el logger debe ser: "[dd-mm-aaaa HH:mm:ss] [TRACE]: @message"
	 * donde [datetime] es la fecha y hora actual en el formato configurado
	 */
	void LogTraceMessage(Logger* logger, string message);

	/*
	 * Precondicion: @logger construido con la primitiva CreateLogger
	 * Postcondicion: Libera los recursos de @logger e invalida la instancia
	 */
	void Destroy(Logger* logger);
}

#endif
