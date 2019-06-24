#include <iostream>
#include <fstream>
#include "Appender.h"


using namespace std;
using ULAppender::Appender;

enum Types {file, console};

struct ULAppender::Appender{
	Types type;
	string pathFile;
};

ULAppender::Appender* ULAppender::CreateFileAppender(string pathFile){
	ULAppender::Appender* newAppender = NULL;
	    bool pathFileValido = (pathFile != "");
	    if (pathFileValido){
	        newAppender = new ULAppender::Appender;
	        newAppender->type = Types::file;
	        newAppender->pathFile = pathFile;
	    }

	    return newAppender;
};

ULAppender::Appender* ULAppender::CreateConsoleAppender(){
    Appender* newAppender = new Appender;
    newAppender->type = Types::console;
    newAppender->pathFile = "Console Application";

    return newAppender;
};


void escribirArchivo(string pathFile, string message) {

	ofstream file;

    file.open(pathFile, ios::app);

    if (file.fail())
    {
        cout << "The file could not be opened." << endl;
        exit(1);
    }

    file<<message<<endl;
    file.close();
};

void ULAppender::Write(Appender* appender, string message){

	if (appender->type == Types::console)
	    {
	        cout<<message<<endl;
	    } else if (appender->type == Types::file)
	    {
	        // escribe @message en una nueva linea al final del archivo
	        // appender->pathFile es la ruta del archivo donde se desea escribir
	        escribirArchivo(appender->pathFile, message);
	    }
};

void ULAppender::Destroy(Appender* appender){

	delete appender;

};

bool ULAppender::SonIguales(const Appender* appender, const Appender* appender2){
	bool sonIguales =false;
	if (appender->type == appender2->type){
		if(appender->type == console){
			sonIguales = true;
		}
		else
			if (appender->pathFile == appender2->pathFile){
				sonIguales = true;
			}
	}

	return sonIguales;

};
