#include "DateTime.h"

#include <string>
#include <cstddef>
#include <time.h>

using std::string;
using std::to_string;
using ULDateTime::DateTimeFormat;
using ULDateTime::DateTime;

struct ULDateTime::DateTime{
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int seconds;
};

//PreCondicion: el timpo debe ser un puntero hacia una estructura tm valida
//PostCondicion: Se devolvera una estructura DateTime parseada a partir de tm
DateTime* CreateTM(tm* tiempo);

//PostCondicion: devuelve un string con el numero del parametro, en caso de ser de 1 digito, le antepone 0
string ParsearDosDigitos(int numero);

//PreCondicion: la hora debe ser entre 0 y 23
//PostCondicion: devuelve si es antes del mediodia o despues la hora
string HoraMediodia(int hora);

//PreCondicion: datetime valido,
//formato = true, muestra la hora en formato de 12 horas
//formato = false, muestra la hora en formato de 24 horas
//PostCondicion: devuelve solamente el parseo de fecha y hora para los casos (sin pm o am)
// - YYYYMMDD_HHmmss: 2019-04-27 19:01:10
// - YYYYMMDD_hhmmss: 2019-04-27 07:01:10 p.m.
string PrimerParseoFechaHora(const DateTime* dateTime, bool formato);

//PreCondicion: datetime valido
//formato = true, muestra la hora en formato de 12 horas
//formato = false, muestra la hora en formato de 24 horas
//PostCondicion: devuelve solamente el parseo de fecha y hora para los casos (sin pm o am)
// - DDMMYYYY_hhmmss: 27-04-2019 07:01:10 p.m.
// - DDMMYYYY_HHmmss: 27-04-2019 19:01:10
string SegundoParseoFechaHora(const DateTime* dateTime, bool formato);

//PreCondicion: datetime valido
//formato = true, muestra la hora en formato de 12 horas
//formato = false, muestra la hora en formato de 24 horas
//PostCondicion: devuelve solamente el parseo de fecha y hora para los casos (sin pm o am)
// - YYMD_Hms: 19-4-27 19:1:10
// - YYMD_hms: 19-4-27 7:1:10 p.m.
string TercerParseoFechaHora(const DateTime* dateTime, bool formato);

//PreCondicion: datetime valido
//formato = true, muestra la hora en formato de 12 horas
//formato = false, muestra la hora en formato de 24 horas
//PostCondicion: devuelve solamente el parseo de fecha y hora para los casos (sin pm o am)
// - DMYY_hms: 27-4-19 7:1:10 p.m.
// - DMYY_Hms: 27-4-19 19:1:10
string CuartoParseoFechaHora(const DateTime* dateTime, bool formato);

string ULDateTime::DateTimeFormatAsString(DateTimeFormat format){
	string formatString;
	switch(format){
		case ULDateTime::YYYYMMDD_HHmmss:
			formatString="YYYYMMDD_HHmmss";
			break;
		case ULDateTime::YYYYMMDD_hhmmss:
			formatString="YYYYMMDD_hhmmss";
			break;
		case ULDateTime::DDMMYYYY_hhmmss:
			formatString="DDMMYYYY_hhmmss";
			break;
		case ULDateTime::DDMMYYYY_HHmmss:
			formatString="DDMMYYYY_HHmmss";
			break;
		case ULDateTime::YYYYMMDDHHmmss:
			formatString="YYYYMMDDHHmmss";
			break;
		case ULDateTime::YYMD_Hms:
			formatString="YYMD_Hms";
			break;
		case ULDateTime::YYMD_hms:
			formatString="YYMD_hms";
			break;
		case ULDateTime::DMYY_hms:
			formatString="DMYY_hms";
			break;
		case ULDateTime::DMYY_Hms:
			formatString="DMYY_Hms";
			break;
	}
	return formatString;
}

DateTimeFormat ULDateTime::DateTimeFormatFromString(string format){
	DateTimeFormat formatString;
	if(format == "YYYYMMDD_HHmmss") formatString=YYYYMMDD_HHmmss;
	if(format == "YYYYMMDD_hhmmss") formatString=YYYYMMDD_hhmmss;
	if(format == "DDMMYYYY_hhmmss") formatString=DDMMYYYY_hhmmss;
	if(format == "DDMMYYYY_HHmmss") formatString=DDMMYYYY_HHmmss;
	if(format == "YYYYMMDDHHmmss") formatString=YYYYMMDDHHmmss;
	if(format == "YYMD_Hms") formatString=YYMD_Hms;
	if(format == "YYMD_hms") formatString=YYMD_hms;
	if(format == "DMYY_hms") formatString=DMYY_hms;
	if(format == "DMYY_Hms") formatString=DMYY_Hms;
	return formatString;
}

DateTime* ULDateTime::Now(){
	tm* tiempoLocal;
	time_t tiempo = time(0);
	tiempoLocal = localtime(&tiempo);
	return CreateTM(tiempoLocal);
}

DateTime* ULDateTime::UTCNow(){
	tm* tiempoUTC;
	time_t tiempo = time(0);
	tiempoUTC = gmtime(&tiempo);
	return CreateTM(tiempoUTC);
}

DateTime* ULDateTime::Create(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, int minutes, int seconds){
	DateTime* nuevoDateTime = NULL;
	if((month < 12 && month >= 0) && (day < 32 && day > 0) && year > 0){
		if(hour < 24 && minutes < 60 && seconds < 60){
			nuevoDateTime = new DateTime;
			nuevoDateTime->day = day;
			nuevoDateTime->hour = hour;
			nuevoDateTime->minute = minutes;
			nuevoDateTime->month = month;
			nuevoDateTime->seconds = seconds;
			nuevoDateTime->year = year;
		}
	}
	return nuevoDateTime;
}

unsigned int ULDateTime::GetYear(const DateTime* dateTime){
	return dateTime->year;
}

unsigned int ULDateTime::GetMonth(const DateTime* dateTime){
	return dateTime->month;
}

unsigned int ULDateTime::GetDay(const DateTime* dateTime){
	return dateTime->day;
}

unsigned int ULDateTime::GetHour(const DateTime* dateTime){
	return dateTime->hour;
}

unsigned int ULDateTime::GetMinutes(const DateTime* dateTime){
	return dateTime->minute;
}

unsigned int ULDateTime::GetSeconds(const DateTime* dateTime){
	return dateTime->seconds;
}

string ULDateTime::ToFormat(const DateTime* dateTime, DateTimeFormat format){
	string resultado = to_string(dateTime->day) + " " + to_string(dateTime->month) + " " + to_string(dateTime->year);

	switch(format){
		case YYYYMMDD_HHmmss:
			resultado = PrimerParseoFechaHora(dateTime, false);
			break;
		case YYYYMMDD_hhmmss:
			resultado = PrimerParseoFechaHora(dateTime, true) + " " + HoraMediodia(dateTime->hour);
			break;
		case DDMMYYYY_hhmmss:
			resultado = SegundoParseoFechaHora(dateTime, true) + " " + HoraMediodia(dateTime->hour);
			break;
		case DDMMYYYY_HHmmss:
			resultado = SegundoParseoFechaHora(dateTime, false);
			break;
		case YYYYMMDDHHmmss:
			resultado = to_string(dateTime->year) + ParsearDosDigitos(dateTime->month) + ParsearDosDigitos(dateTime->day) + ParsearDosDigitos(dateTime->hour)
						+ ParsearDosDigitos(dateTime->minute) + ParsearDosDigitos(dateTime->seconds);
			break;
		case YYMD_Hms:
			resultado = TercerParseoFechaHora(dateTime, false);
			break;
		case YYMD_hms:
			resultado = TercerParseoFechaHora(dateTime, true) + " " + HoraMediodia(dateTime->hour);
			break;
		case DMYY_hms:
			resultado = CuartoParseoFechaHora(dateTime, true) + " " + HoraMediodia(dateTime->hour);
			break;
		case DMYY_Hms:
			resultado = CuartoParseoFechaHora(dateTime, false);
			break;
	}
	return resultado;
}

void ULDateTime::Destroy(DateTime* dateTime){
	delete dateTime;
}

DateTime* CreateTM(tm* tiempo){
	DateTime* nuevoDateTime = ULDateTime::Create(tiempo->tm_year + 1900,
			tiempo->tm_mon,
			tiempo->tm_mday,
			tiempo->tm_hour,
			tiempo->tm_min,
			tiempo->tm_sec
			);
	return nuevoDateTime;
}

string ParsearDosDigitos(int numero){
	string texto;
	if(numero < 10){
		texto = "0" + to_string(numero);
	}
	else{
		texto = to_string(numero);
	}
	return texto;
}

string HoraMediodia(int hora){
	return hora < 10 ? "a.m" : "p.m";
}

string PrimerParseoFechaHora(const DateTime* dateTime, bool formato){
	string tiempo = ParsearDosDigitos(dateTime->year) + "-" + ParsearDosDigitos(dateTime->month)
				+ "-" + ParsearDosDigitos(dateTime->day) + " ";
	if(formato && dateTime->hour > 12){
		tiempo += ParsearDosDigitos(dateTime->hour - 12);
	}else{
		tiempo += ParsearDosDigitos(dateTime->hour);
	}
	tiempo += ":" + ParsearDosDigitos(dateTime->minute) + ":" + ParsearDosDigitos(dateTime->seconds);
	return tiempo;
}

string SegundoParseoFechaHora(const DateTime* dateTime, bool formato){
	string tiempo = ParsearDosDigitos(dateTime->day) + "-" + ParsearDosDigitos(dateTime->month) + "-"
			+ ParsearDosDigitos(dateTime->year) + " ";
	if(formato && dateTime->hour > 12){
		tiempo += ParsearDosDigitos(dateTime->hour - 12);
	}else{
		tiempo += ParsearDosDigitos(dateTime->hour);
	}
	tiempo += ":" + ParsearDosDigitos(dateTime->minute) + ":" + ParsearDosDigitos(dateTime->seconds);
	return tiempo;
}

string TercerParseoFechaHora(const DateTime* dateTime, bool formato){
	string tiempo = to_string(dateTime->year).substr(2,3) + "-" + to_string(dateTime->month) + "-" + to_string(dateTime->day) + " ";
	if(formato && dateTime->hour > 12){
		tiempo += to_string(dateTime->hour - 12);
	}else{
		tiempo += to_string(dateTime->hour);
	}
	tiempo += ":" + to_string(dateTime->minute) + ":" + to_string(dateTime->seconds);
	return tiempo;
}

string CuartoParseoFechaHora(const DateTime* dateTime, bool formato){
	string tiempo = to_string(dateTime->day) + "-" + to_string(dateTime->month) + "-" + to_string(dateTime->year).substr(2,3) + " ";
		if(formato && dateTime->hour > 12){
			tiempo += to_string(dateTime->hour - 12);
		}else{
			tiempo += to_string(dateTime->hour);
		}
		tiempo += ":" + to_string(dateTime->minute) + ":" + to_string(dateTime->seconds);
		return tiempo;
}
