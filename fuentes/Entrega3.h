/*
 * Entrega3.h
 *
 *  Created on: 2 jul. 2019
 *      Author: santy
 */

#ifndef ENTREGA3_H_
#define ENTREGA3_H_

#include "Logger.h"

using ULLogger::Logger;

namespace ULEntrega{

	// Precondicion: @xmlLoggerSetting es un xml bien formado y valido para la configuracion de ULLogger
	// Postcondicion: Devuelve una instancia valida de Logger que tiene la configuracion dada en @xmlLoggerSetting
	Logger* BuildLogger(string xmlLoggerSetting);

	// Precondicion:  Si el archivo existe y tiene un elemento <logger>, ese elemento representa un xml valido par la configuracion de logger.
	// Postcondicion: Si el archivo en @pathConfigFile busca el contentido del tag <logger> y devuelve la instancia valida que representa esa configuracion.
	// Si el archivo no existe o no tiene el tag <logger> devuelve NULL
	Logger* BuildLoggerFromConfigFile(string pathConfigFile);

}



#endif /* ENTREGA3_H_ */
