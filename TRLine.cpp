/*
 * TRLine.cpp
 *
 *  Created on: Jun 18, 2015
 *      Author: sarahradzihovsky
 */

#include "TRLine.h"
#include "TRLineXSect.h"
#include <iostream>
#include <math.h>
#include <complex>
#include <vector>

using namespace std;

TRLine::TRLine(complex <double> zLoad, TRLineXSect *trXSect, double l) {
	this -> zLoad = zLoad;
	this -> trXSect = trXSect;
	this -> l = l;
}

TRLine::~TRLine() {
}

/*
 * Given the Z0 of the chosen XSection and the load impedance, the reflection
 * coeff is calculated
 */
complex <double>  TRLine::getGamma(){
	return (zLoad - (trXSect -> getZ0())) / (zLoad + (trXSect -> getZ0()));
}

/*
 * Given the Z0 of the chosen XSection and the load impedance, the reflection
 * coeff is calculated
 */
complex <double> TRLine::getZin(double f){

	/*This manipulation of eqs is necessary to avoid error with imaginary numbers*/
	complex <double> num = 1i * (trXSect -> getZ0() * tan(trXSect -> getBeta(f) * l));
	num = num + zLoad;
	complex <double> denom = 0.0 + 1i;
	denom = denom * zLoad * tan(trXSect -> getBeta(f) * l);
	denom = trXSect -> getZ0() + denom;
	return (trXSect -> getZ0()) * (num / denom);
}

double TRLine::getZ0(){
	return trXSect -> getZ0();
}

double TRLine::getBeta(double f){
	return trXSect -> getBeta(f);
}

TRLineXSect* TRLine::getXSections(){
	return trXSect;
}

