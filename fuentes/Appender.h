/*
 * Appender.h
 *
 *  Created on: 5 may. 2019
 *      Author: administrator
 */

#ifndef APPENDER_H_
#define APPENDER_H_

#include <string>

using std::string;

namespace ULAppender{

	struct Appender;
	/*
	 * Precondicion: Ninguna
	 * Postcondicion: Si @pathFile es un path invalido devuelve NULL.
	 * Si @pathFile es valido devuelve una instancia de Appender del tipo archivo. Si el archivo ya existia no lo debe truncar (borrar el contenido)
	 * Parametros:
	 * 		@pathFile: ruta y nombre del archivo donde se desea escribir
	 * 		@return: Instancia de Appender lista para ser utilizada por las primitivas del TDA Appender
	 */
	Appender* CreateFileAppender(string pathFile);

	/*
	 * Precondicion: Ninguna
	 * Postcondicion: Devuelve una instancia de Appender del tipo consola.
	 * Parametros:
	 * 		@return: Instancia de Appender lista para ser utilizada por las primitivas del TDA Appenders
	 */
	Appender* CreateConsoleAppender();

	/*
	 * Precondicion: @appender fue creado con alguna de las primitivas: CreateFileAppender o CreateConsoleAppender
	 * Postcondicion: Si el @appender es del tipo Consola escribe @message en una nueva linea en la salida estandard
	 * Si @appender es del tipo archivo escribe @message en una nueva linea al final del archivo
	 * Parametros:
	 * 		@appender: Instancia de Appender donde se desea escribir el @message
	 * 		@message: Mensaje que se desea escribir en el log.
	 */
	void Write(Appender* appender, string message);

	/*
	 * Precondicion: @appender fue creado con alguna de las primitivas: CreateFileAppender o CreateConsoleAppender
	 * Postcondicion: Libera los rescursos asociados a @appender.
	 * Parametros:
	 * 		@appender: Instancia de Appender que se desea destruir
	 */
	void Destroy(Appender* appender);

	bool SonIguales(const Appender* appender, const Appender* appender2);
}

#endif
