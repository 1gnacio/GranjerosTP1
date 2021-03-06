/*
 * Configuracion.cpp
 *
 *  Created on: 25 abr. 2018
 *      Author: administrador
 */

#include <string>
#include <cstdlib>

#include "configuracion.h"
#include "fileParser.h"

using namespace std;

Dificultad Configuracion::dificultad = FACIL;
unsigned int Configuracion::cantidadJugadores = 0;
unsigned int Configuracion::parametroN = 0;
unsigned int Configuracion::parametroM = 0;
unsigned int Configuracion::cantidadTurnos = 0;
Lista<Cultivo*>* Configuracion::cultivos = NULL;
Lista<Destino*>* Configuracion::destinos = NULL;

Configuracion::Configuracion(){

}

void Configuracion::inicializar(ParametroConfiguracion parametros){

	dificultad = parametros.obtenerDificultad();
	cantidadJugadores = parametros.obtenerCantidadJugadores();
	parametroN = parametros.obtenerParametroN();
	parametroM = parametros.obtenerParametroM();
	cantidadTurnos = parametros.obtenerCantidadTurnos();

	cargarCultivos();
	cargarDestinos();
}

void Configuracion::cargarCultivos(){

	cultivos = new Lista<Cultivo*>();

	FileParser parser("resources/cultivos.txt", ",", 6);
	parser.abrir();

	while(!parser.esFinArchivo()){

		string* lineaParseada = parser.leerLinea();

		Cultivo* cultivo = new Cultivo(lineaParseada[0], atoi(lineaParseada[1].c_str()), atoi(lineaParseada[2].c_str()), atoi(lineaParseada[3].c_str()),
										atoi(lineaParseada[4].c_str()), atoi(lineaParseada[5].c_str()));

		cultivos->agregar(cultivo);
	}

	parser.cerrar();
}

void Configuracion::cargarDestinos(){

	destinos = new Lista<Destino*>();

	FileParser parser("resources/destinos.txt", ",", 4);
	parser.abrir();

	while(!parser.esFinArchivo()){

		string* lineaParseada = parser.leerLinea();

		Destino* destino = new Destino(lineaParseada[0], atoi(lineaParseada[1].c_str()), atoi(lineaParseada[2].c_str()), lineaParseada[3]);

		destinos->agregar(destino);
	}

	parser.cerrar();
}

unsigned int Configuracion::obtenerCoeficienteDificultad(){

	unsigned int coeficienteDificultad;

	switch(dificultad){

	case FACIL:
		coeficienteDificultad = 10;
		break;
	case MEDIO:
		coeficienteDificultad = 5;
		break;
	case DIFICIL:
		coeficienteDificultad = 2;
		break;
	}

	return coeficienteDificultad;
}

Dificultad Configuracion::obtenerDificultad(){
	return dificultad;
}

unsigned int Configuracion::obtenerCantidadJugadores(){
	return cantidadJugadores;
}

unsigned int Configuracion::obtenerLargoTerreno(){
	return parametroN;
}

unsigned int Configuracion::obtenerAnchoTerreno(){
	return parametroM;
}

unsigned int Configuracion::obtenerCreditosIniciales(){
	return 2 * parametroN * parametroM * obtenerCoeficienteDificultad();
}

unsigned int Configuracion::obtenerCapacidadInicialTanque(){
	return parametroN * parametroM * obtenerCoeficienteDificultad();
}

unsigned int Configuracion::obtenerCantidadTurnos(){
	return cantidadTurnos;
}

unsigned int Configuracion::obtenerCapacidadInicialAlmacen(){
	return 2 * (parametroN + parametroM) * obtenerCoeficienteDificultad();
}

Lista<Cultivo*>* Configuracion::obtenerCultivos(){

	return cultivos;
}

Cultivo* Configuracion::obtenerCultivo(string nombreCultivo){


	Cultivo* cultivo = NULL;

	Lista<Cultivo*>* cultivosDisponibles = Configuracion::obtenerCultivos();
	cultivosDisponibles->iniciarCursor();

	while(cultivosDisponibles->avanzarCursor() && cultivo == NULL){

		Cultivo* cultivoActual = cultivosDisponibles->obtenerCursor();
		if(cultivoActual->obtenerNombre() == nombreCultivo){

			cultivo = cultivoActual;
		}
	}

	return cultivo;
}

Lista<Destino*>* Configuracion::obtenerDestinos(){

	return destinos;
}

Destino* Configuracion::obtenerDestino(Cultivo* cultivo){

	Destino* destino = NULL;

	Lista<Destino*>* destinosDisponibles = Configuracion::obtenerDestinos();
	destinosDisponibles->iniciarCursor();

	while(destinosDisponibles->avanzarCursor() && destino == NULL){

		Destino* destinoActual = destinosDisponibles->obtenerCursor();
		if(destinoActual->obtenerNombreCultivo() == cultivo->obtenerNombre()){

			destino = destinoActual;
		}
	}

	return destino;
}

void Configuracion::destruirCultivos(){

	if(!cultivos->estaVacia()){

		cultivos->iniciarCursor();

		while(!cultivos->avanzarCursor()){
			delete cultivos->obtenerCursor();
		}
	}

	delete cultivos;
}

void Configuracion::destruirDestinos(){

	if(!destinos->estaVacia()){

		destinos->iniciarCursor();

		while(!destinos->avanzarCursor()){
			delete destinos->obtenerCursor();
		}
	}

	delete destinos;
}

Configuracion::~Configuracion() {

	destruirCultivos();
	destruirDestinos();
}

