/*
 * StriplineXSection.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: sarahradzihovsky
 */

#include "StriplineXSection.h"
#include "TRLineXSect.h"
#include <iostream>
#include <math.h>
using namespace std;

/* Constants */

const double eps0 = 8.854 * pow(10.0 , -12.0);
const double mu0 = 4.0 * M_PI * pow(10.0 , -7.0);

StriplineXSection::StriplineXSection(double w, double b, double t, double eps) {
	this -> w = w;
	this -> b = b;
	this -> t = t;
	this -> eps = eps;
}

StriplineXSection::~StriplineXSection() {
}

/* Given F and eta, calculates Z0*/
double StriplineXSection::getZ0(){
	double F = getF();
	double eta = getEta();
	return F * eta;
}

/*
 * Given width and height of stripline, and thickness of material,
 * calculates F
 */
double StriplineXSection::getF(){
	if ((w / (b - t)) <= 0.35) {
		double logInput = 8.0 / (((M_PI * w) / b) + (t / b) * (1.0 + log((4.0 * M_PI * w)/b)));
		return ((1.0 / (2.0 * M_PI)) * log(logInput));
	} else {
		double x = (b / (b - t)) * log((2.0 * b - t) / t);
		double y = 1.0 * log((t * ((2.0 * b) - t)) / (pow ((b - t), 2)));
		return 1 / (((4.0 * w) / (b - t)) + (4 / M_PI)*(x + y));
	}
}

/* Given permittivity, calculates Eta*/
double StriplineXSection::getEta(){
	return sqrt(mu0 / (eps * eps0));
}

/*Given permittivity and frequency*/
double StriplineXSection::getBeta(double f){
	return ((2.0 * M_PI) * f * sqrt(mu0 * eps * eps0));
}

void StriplineXSection::setOuterRadius(double R0){
	//R = R0;
}










