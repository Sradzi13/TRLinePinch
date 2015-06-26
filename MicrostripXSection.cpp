/*
 * MicrostripXSection.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: sarahradzihovsky
 */

#include "MicrostripXSection.h"
#include "TRLineXSect.h"
#include <iostream>
#include <math.h>
using namespace std;

/* Constants */

const double eps0 = 8.854e-12;
const double mu0 = (4.0 * M_PI)*1E-7;

MicrostripXSection::MicrostripXSection(double w, double h, double t, double eps) {
	this -> w = w;
	this -> h = h;
	this -> t = t;
	this -> eps = eps;
}

MicrostripXSection::~MicrostripXSection() {
}

/*Finds Z0 through eta and F*/
double MicrostripXSection::getZ0(){
	double F = getF();
	double eta = getEta();
	return F * eta;
}

/*Given width and height of Microstrip, F is found*/
double MicrostripXSection::getF(){
	if ((w / h) <= 1) {
		double logInput = ((8.0 * h) / w) + (w / (4.0 * h));
		return ((1.0 / (2.0 * M_PI)) * log(logInput));
	} else {
		double alpha = 0.667 * log((w / h) + 1.444);
		return 1 / ((w / h) + 1.393 + alpha);
	}
}

/*Given permittivity, Eta is found*/
double MicrostripXSection::getEta(){
	return sqrt(mu0 / (eps * eps0));
}

/*Given permittivity and frequency, Eta is found*/
double MicrostripXSection::getBeta(double f){
	return ((2.0 * M_PI) * f * sqrt(mu0 * eps * eps0));
}

