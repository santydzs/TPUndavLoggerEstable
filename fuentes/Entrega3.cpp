#include <iostream>
#include "DateTime.h"
#include "Logger.h"
#include "Appender.h"
#include "AppenderSettings.h"
#include "LoggerSettings.h"
#include "LogLevel.h"
#include "AppenderType.h"

using namespace std;
using std::string;
using namespace ULLogger;
using namespace ULAppenderSettings;
using namespace ULLoggerSettings;

int ContarApariciones(string texto, string subtexto);

int IndiceAparicion(char* texto, char* subtexto, int n);

// Precondicion: @xmlLoggerSetting es un xml bien formado y valido para la configuracion de ULLlogger
// Postcondicion: Devuelve una instacia valida de Logger que tiene la configuracion dada en @xmlLoggerSetting
Logger* BuildLogger(string xmlLoggerSetting);

// Precondicion: si el archivo existe y tiene un elemento <logger>, ese elemento representa un xml valido para la configuracion de logger.
// Postcondicion: si el archivo en @pathConfigFile busca el contenido del tag <logger> y devuelve la instancia valida que representa esa configuracion.
// Si el archivo no existe o no tiene el tag <logger> devuelve NULL
Logger* BuildLoggerFromConfigFile(string pathConfigFile);

void TestLogger(Logger* logger);

int ContarCaracteres(const string texto){
	return 0;
}

int ContarAppenderSettings(string elementoXml) {
    ContarApariciones(elementoXml, "<appender");
    // Cuento las apariciones de appender por ejemplo
}

int IndexOf(const string texto, const string textoBusqueda, int indice) {
    int caracteresTexto = ContarCaracteres(texto);
    int caracteresBusqueda = ContarCaracteres(textoBusqueda);
    for(int i = indice; i < caracteresTexto-caracteresBusqueda; ++i) {
        int j;
        for (j = 0; j < caracteresBusqueda; j++)
            if(texto[i+j] != textoBusqueda[j]) break;
        if(j==caracteresBusqueda) return i;
    }
}

string GetAttributeValue(string elementoXml, string nombreAtributo){
	//string texto = "<logger dateTimeFormat=\"YYMD_hms\" />";
    //string substring = "dateTimeFormat=\"";
    int largoSub = nombreAtributo.length();
    int comienzoString = elementoXml.find(nombreAtributo);
    int comienzoValor = comienzoString+largoSub;
    string aux_sub = elementoXml.substr(comienzoValor, elementoXml.length());
    int indiceFinal = aux_sub.find("\"");
    //cout<< aux_sub.substr(0,indiceFinal);

    return 0;
}

AppenderSettings* GetAppenderSetting(string elementoXml, int numeroAppender) {
    // retorno el appender correspondiente al numeroAppender que me envian como parametro
}

LoggerSettings* GetLoggerSetting(string elementoXml) {
    LoggerSettings* logger = ULLoggerSettings::Create(ULDateTime::DDMMYYYY_HHmmss); // creo el logger de tipo LoggerSetting
    string dateTimeFormat = ULDateTime::DateTimeFormatAsString(ULLogger::ObtenerDatetimeFormat(logger));// retorno el valor del dateTimeFormat
    int cantidadAppender = ContarAppenderSettings(elementoXml); // retorno la cantidad de appernders que tiene el string xml
    for(int i=0; i<cantidadAppender; ++i) { // Recorro la cantidad de appenders que obtengo arriba
        int indice = IndexOf(elementoXml, '<appender', indice);
        AddAppenderSetting(logger, GetAppenderSetting(elementoXml, indice)); //Añado los appender al logger, en el segundo parametro del get tiene que ir un indice
        // getAppenderSetting obtiene el appender correspondiente al indice que le envio
        //para saber a partir de donde tiene que buscar los distintos elementos
        // aca iria un indexof con indice para arrancar a buscar a partir del indice, es decir desde que se encontro la anterior aparicion
    }
}

int main() {
    string settings = "<logger dateTimeFormat=\"YYMD_Hms\">\n\t<appender type=\"console\" logLevel=\"INFO\"/>\n\t<appender type=\"file\" logLevel=\"DEBUG\" path=\"logFile1.log\"/>\n</logger>";
    cout<<settings<<endl;
    Logger* logger1 = BuildLogger(settings);
    Logger* logger2 = BuildLoggerFromConfigFile("config.txt");
}

void TestLogger(Logger* logger) {
    LogFatalMessage(logger, "Log 1 ");
    LogErrorMessage(logger, "Log 2 ");
    LogWarningMessage(logger, "Log 3 ");
    LogDebugMessage(logger, "Log 4 ");
    LogTraceMessage(logger, "Log 5 ");
    LogInfoMessage(logger, "Log 6 ");
}

Logger* BuildLogger(string xmlLoggerSetting) {
    return 0;
}

Logger* BuildLoggerFromConfigFile(string pathConfigFile) {
    // Tengo que buscar dentro del archivvo con direccion pathConfigFile la etiqueta logger y devolver un logger con dicha configuracion
}
