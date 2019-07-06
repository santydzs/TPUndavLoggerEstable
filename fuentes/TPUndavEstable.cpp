#include <iostream>
#include "DateTime.h"
#include "Logger.h"
#include "Appender.h"
#include "AppenderSettings.h"
#include "LoggerSettings.h"
#include "LogLevel.h"
#include "AppenderType.h"
#include "Entrega3.h"

using namespace std;
using namespace ULLogger;
using namespace ULAppenderSettings;
using namespace ULLoggerSettings;

void PruebasSettings();
void PruebasLogger();
void PruebasLoggerOff();
void PruebasLoggerFatal();
void PruebasLoggerError();
void PruebasLoggerWarn();
void PruebasLoggerInfo();
void PruebasLoggerDebug();
void PruebasLoggerTrace();

int main() {
	/*PruebasLogger();
	PruebasSettings();*/
	string settings =
			"<logger dateTimeFormat=\"YYMD_Hms\">"
				"\n\t<appender type=\"console\" logLevel=\"INFO\"/>"
				"\n\t<appender type=\"file\" logLevel=\"DEBUG\" path=\"logFile1.log\"/>"
			"\n</logger>";
	//cout<<settings<<endl;
	Logger* logger1 = ULEntrega::BuildLogger(settings);
	//Logger* logger2 = BuildLoggerFromConfigFile("config.txt");

}

void PruebasSettings(){
	LoggerSettings* settings = ULLoggerSettings::Create(ULDateTime::YYMD_hms);
	AddAppenderSetting(settings, ULAppenderSettings::CreateAppenderConsoleSetting(FATAL));
	AddAppenderSetting(settings, ULAppenderSettings::CreateAppenderFileSetting(OFF, "off.log"));
	AddAppenderSetting(settings, ULAppenderSettings::CreateAppenderFileSetting(FATAL, "fatal.log"));
	AddAppenderSetting(settings, ULAppenderSettings::CreateAppenderFileSetting(WARN, "warn.log"));
	AddAppenderSetting(settings, ULAppenderSettings::CreateAppenderFileSetting(TRACE, "trace.log"));
	AddAppenderSetting(settings, ULAppenderSettings::CreateAppenderFileSetting(TRACE, "info.log"));
	AddAppenderSetting(settings, ULAppenderSettings::CreateAppenderFileSetting(INFO, "info.log"));
	AddAppenderSetting(settings, ULAppenderSettings::CreateAppenderConsoleSetting(DEBUG));
	cout<<"Configuracion del logger"<<endl;
	cout<<ULLoggerSettings::ToXml(settings)<<endl;
	ULLoggerSettings::Destroy(settings);
}

void PruebasLogger()
{
    PruebasLoggerOff();
    PruebasLoggerFatal();
    PruebasLoggerError();
    PruebasLoggerWarn();
    PruebasLoggerInfo();
    PruebasLoggerDebug();
    PruebasLoggerTrace();
}

void PruebasLoggerOff()
{
	cout<<"Iniciando Pruebas Logger en 'Off level'..."<<endl<<endl;

	Logger *logger = Create();
	Appender* appender1 = ULAppender::CreateConsoleAppender();
	Appender* appender2 = ULAppender::CreateFileAppender("SalidaLogger.txt");
	AddAppender(logger, appender1, OFF);
	AddAppender(logger, appender2, OFF);

	//No deberia logear nada
	LogFatalMessage(logger, "FALLO EL TEST DE LOGGER EN 'OFF LEVEL'. No deberia mostrar 'Fatal' logs");
	LogErrorMessage(logger, "FALLO EL TEST DE LOGGER EN 'OFF LEVEL'. No deberia mostrar 'Error' logs");
	LogWarningMessage(logger, "FALLO EL TEST DE LOGGER EN 'OFF LEVEL'. No deberia mostrar 'Warning' logs");
	LogInfoMessage(logger, "FALLO EL TEST DE LOGGER EN 'OFF LEVEL'. No deberia mostrar 'Info' logs");
	LogDebugMessage(logger, "FALLO EL TEST DE LOGGER EN 'OFF LEVEL'. No deberia mostrar 'Debug' logs");
	LogTraceMessage(logger, "FALLO EL TEST DE LOGGER EN 'OFF LEVEL'. No deberia mostrar 'Trace' logs");

	Destroy(logger);

	cout<<"Finalizadas Pruebas Logger en 'Off level'. No se debio visualizar ningun log."<<endl<<endl;
}

void PruebasLoggerFatal()
{
	cout<<"Iniciando Pruebas Logger en 'FATAL level' ..."<<endl<<endl;

	Logger *logger = Create();
	Appender* appender1 = ULAppender::CreateConsoleAppender();
	Appender* appender2 = ULAppender::CreateFileAppender("SalidaLogger.txt");
	AddAppender(logger, appender1, FATAL);
	AddAppender(logger, appender2, FATAL);

	// Deberia mostrar este mensaje
	LogFatalMessage(logger, "Prueba 1 - Deberia mostrar este log 'fatal'");

	//No deberia mostrar estos mensajes
	LogErrorMessage(logger, "FALLO EL TEST DE LOGGER EN 'FATAL LEVEL'. No deberia mostrar 'Error' logs");
	LogWarningMessage(logger, "FALLO EL TEST DE LOGGER EN 'FATAL LEVEL'. No deberia mostrar 'Warning' logs");
	LogInfoMessage(logger, "FALLO EL TEST DE LOGGER EN 'FATAL LEVEL'. No deberia mostrar 'Info' logs");
	LogDebugMessage(logger, "FALLO EL TEST DE LOGGER EN 'FATAL LEVEL'. No deberia mostrar 'Debug' logs");
	LogTraceMessage(logger, "FALLO EL TEST DE LOGGER EN 'FATAL LEVEL'. No deberia mostrar 'Trace' logs");

	Destroy(logger);

	cout<<"Finalizadas Pruebas Logger 'FATAL level'. Se debió visualizar 1 solo log"<<endl<<endl;
}

void PruebasLoggerError()
{
	cout<<"Iniciando Pruebas Logger en 'ERROR level' ..."<<endl<<endl;

	Logger *logger = Create();
	Appender* appender1 = ULAppender::CreateConsoleAppender();
	Appender* appender2 = ULAppender::CreateFileAppender("SalidaLogger.txt");
	AddAppender(logger, appender1, ERROR);
	AddAppender(logger, appender2, ERROR);

	// Deberia mostrar estos mensajes
	LogFatalMessage(logger, "Prueba 1 - Deberia mostrar este log 'fatal'");
	LogErrorMessage(logger, "Prueba 2 - Deberia mostrar este log 'error'");

	//No deberia mostrar estos mensajes
	LogWarningMessage(logger, "FALLO EL TEST DE LOGGER EN 'ERROR LEVEL'. No deberia mostrar 'Warning' logs");
	LogInfoMessage(logger, "FALLO EL TEST DE LOGGER EN 'ERROR LEVEL'. No deberia mostrar 'Info' logs");
	LogDebugMessage(logger, "FALLO EL TEST DE LOGGER EN 'ERROR LEVEL'. No deberia mostrar 'Debug' logs");
	LogTraceMessage(logger, "FALLO EL TEST DE LOGGER EN 'ERROR LEVEL'. No deberia mostrar 'Trace' logs");

	Destroy(logger);

	cout<<"Finalizadas Pruebas Logger 'ERROR level'. Se debió visualizar 2 logs."<<endl<<endl;
}

void PruebasLoggerWarn()
{
	cout<<"Iniciando Pruebas Logger en 'WARN level' ..."<<endl<<endl;

	Logger *logger = Create();
	Appender* appender1 = ULAppender::CreateConsoleAppender();
	Appender* appender2 = ULAppender::CreateFileAppender("SalidaLogger.txt");
	AddAppender(logger, appender1, WARN);
	AddAppender(logger, appender2, WARN);

	// Deberia mostrar estos mensajes
	LogFatalMessage(logger, "Prueba 1 - Deberia mostrar este log 'fatal'");
	LogErrorMessage(logger, "Prueba 2 - Deberia mostrar este log 'error'");
	LogWarningMessage(logger, "Prueba 3 - Deberia mostrar este log 'warning'");

	//No deberia mostrar estos mensajes
	LogInfoMessage(logger, "FALLO EL TEST DE LOGGER EN 'WARN LEVEL'. No deberia mostrar 'Info' logs");
	LogDebugMessage(logger, "FALLO EL TEST DE LOGGER EN 'WARN LEVEL'. No deberia mostrar 'Debug' logs");
	LogTraceMessage(logger, "FALLO EL TEST DE LOGGER EN 'WARN LEVEL'. No deberia mostrar 'Trace' logs");

	Destroy(logger);

	cout<<"Finalizadas Pruebas Logger 'WARN level'. Se debió visualizar 3 logs."<<endl<<endl;
}

void PruebasLoggerInfo()
{
	cout<<"Iniciando Pruebas Logger en 'INFO level' ..."<<endl<<endl;

	Logger *logger = Create();
	Appender* appender1 = ULAppender::CreateConsoleAppender();
	Appender* appender2 = ULAppender::CreateFileAppender("SalidaLogger.txt");
	AddAppender(logger, appender1, INFO);
	AddAppender(logger, appender2, INFO);

	// Deberia mostrar estos mensajes
	LogFatalMessage(logger, "Prueba 1 - Deberia mostrar este log 'fatal'");
	LogErrorMessage(logger, "Prueba 2 - Deberia mostrar este log 'error'");
	LogWarningMessage(logger, "Prueba 3 - Deberia mostrar este log 'warning'");
	LogInfoMessage(logger, "Prueba 4 - Deberia mostrar este log 'info'");

	//No deberia mostrar estos mensajes
	LogDebugMessage(logger, "FALLO EL TEST DE LOGGER EN 'INFO LEVEL'. No deberia mostrar 'Debug' logs");
	LogTraceMessage(logger, "FALLO EL TEST DE LOGGER EN 'INFO LEVEL'. No deberia mostrar 'Trace' logs");

	Destroy(logger);

	cout<<"Finalizadas Pruebas Logger 'INFO level'. Se debió visualizar 4 logs."<<endl<<endl;
}
void PruebasLoggerDebug()
{
	cout<<"Iniciando Pruebas Logger en 'DEBUG level' ..."<<endl<<endl;

	Logger *logger = Create();
	Appender* appender1 = ULAppender::CreateConsoleAppender();
	Appender* appender2 = ULAppender::CreateFileAppender("SalidaLogger.txt");
	AddAppender(logger, appender1, DEBUG);
	AddAppender(logger, appender2, DEBUG);


	// Deberia mostrar estos mensajes
	LogFatalMessage(logger, "Prueba 1 - Deberia mostrar este log 'fatal'");
	LogErrorMessage(logger, "Prueba 2 - Deberia mostrar este log 'error'");
	LogWarningMessage(logger, "Prueba 3 - Deberia mostrar este log 'warning'");
	LogInfoMessage(logger, "Prueba 4 - Deberia mostrar este log 'info'");
	LogDebugMessage(logger, "Prueba 5 - Deberia mostrar este log 'debug'");

	//No deberia mostrar estos mensajes
	LogTraceMessage(logger, "FALLO EL TEST DE LOGGER EN 'DEBUG LEVEL'. No deberia mostrar 'Trace' logs");

	Destroy(logger);

	cout<<"Finalizadas Pruebas Logger 'DEBUG level'. Se debió visualizar 5 logs."<<endl<<endl;
}

void PruebasLoggerTrace()
{
	cout<<"Iniciando Pruebas Logger en 'TRACE level' ..."<<endl<<endl;

	Logger *logger = Create();
	Appender* appender1 = ULAppender::CreateConsoleAppender();
	Appender* appender2 = ULAppender::CreateFileAppender("SalidaLogger.txt");
	AddAppender(logger, appender1, TRACE);
	AddAppender(logger, appender2, TRACE);

	// Deberia mostrar todos los mensajes
	LogFatalMessage(logger, "Prueba 1 - Deberia mostrar este log 'fatal'");
	LogErrorMessage(logger, "Prueba 2 - Deberia mostrar este log 'error'");
	LogWarningMessage(logger, "Prueba 3 - Deberia mostrar este log 'warning'");
	LogInfoMessage(logger, "Prueba 4 - Deberia mostrar este log 'info'");
	LogDebugMessage(logger, "Prueba 5 - Deberia mostrar este log 'debug'");
	LogTraceMessage(logger, "Prueba 6 - Deberia mostrar este log 'debug'");

	Destroy(logger);

	cout<<"Finalizadas Pruebas Logger 'TRACE level'. Se debió visualizar 6 logs."<<endl<<endl;
}
