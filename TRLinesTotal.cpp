/*
 * TRLinesTotal.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: sarahradzihovsky
 *
 *  Superclass that sums together many individual TRLine
 *  segments and using their Zin's and Zload to find
 *  the total reflection coefficient.
 */

#include "TRLinesTotal.h"
#include "TRLine.h"
#include "TRLineXSect.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <complex>
using namespace std;

TRLinesTotal::TRLinesTotal(vector <TRLine> TRLines, vector <int> lengths,
		complex <double>  zLoad, double y) {
	this -> TRLines = TRLines;
	this -> lengths = lengths;
	this -> zLoad = zLoad;
	this -> y = y;
}

TRLinesTotal::~TRLinesTotal() {
}

complex <double> TRLinesTotal::getZinTotal(double f){
	complex <double> temp = zLoad;
	for(int j = 0; j < TRLines.size(); j++){
		complex <double> zIn = getZin(f, j, temp);

		/*Updates the Zin to equal Zload of the new segment*/
		temp = zIn;
	}
	return temp;
}

complex <double> TRLinesTotal::getZin(double f, int j, complex <double> temp){

	/*Finds current TRLine segment and then extracts the corresponding TRXSect*/
	TRLine current = TRLines.at(j);

	/*This manipulation of eqs is necessary to avoid error with imaginary numbers*/
	complex <double> num = 1i * (current.getZ0()) *
			tan(current.getBeta(f)) * lengths.at(j);
	num  = num + temp;
	complex <double> denom = 0.0 + 1i;
	denom = denom *	(temp * tan(current.getBeta(f) * (lengths.at(j))));
	denom = current.getZ0() + denom;
	return (current.getZ0()) * (num / denom);
}

complex <double> TRLinesTotal::getGammaTotal(double f){
	TRLine first = TRLines.at(0);
	return ((this -> getZinTotal(f)) - (first.getZ0())) /
			((this -> getZinTotal(f)) + (first.getZ0()));
}

vector <TRLine> TRLinesTotal::getSegments(int start, int end){
	vector <TRLine> pinched;
	for(int i = start; i <= end; i++){
		pinched.push_back(TRLines(i));
	}
	return pinched;
}
