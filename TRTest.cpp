/*
 * TRTest.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: sarahradzihovsky
 */

#include "TRLinesTotal.h"
#include "TRLineXSect.h"
#include "TRLine.h"
#include "CoaxXSection.h"
#include "StriplineXSection.h"
#include "MicrostripXSection.h"
#include <iostream>
#include <math.h>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

/* Function Prototypes */

TRLineXSect* getXSect(string type, double f);
vector <TRLine> makeTRLineVector(TRLine sum);
vector <int> makeLengthsVector(double l);

int main() {

	cout << "This program simulates the pinch of an entire TRLines of"
			" the parameters you choose." << endl;


	/*Only runs this code if entire TRLine is being calculated*/
	double f, l, y;
	int N;
	complex <double> zLoad;
	vector <TRLine> TRLines;
	vector <int> lengths;

	cout << "Frequency (Hz):"<< endl;
	cin >> f;

	/*User chooses what type of XSection they would like to find values for*/
	string type = "";
	cout << "Type of XSection? ((1)Microstrip, (2)Stripline, (3)Coax)" << endl;
	cin >> type;

	TRLineXSect *trXSect = NULL;
	trXSect = getXSect(type, f);

	/*Outputs Z0 and Beta of chosen XSection*/
	cout << "Z0, Beta = "  << trXSect -> getZ0() << "ohms, "
			<< trXSect -> getBeta(f) << " rad/m" << endl;

	/*Given length and load impedance, inner impedance and reflection coeff is found*/
	cout << "Load Impedance (ohms):" << endl;
	cin >> zLoad;
	cout << "Length (m):" << endl;
	cin >> l;

	TRLine sum = TRLine (zLoad, trXSect, l);

	cout << "Inner Impedance (ohms), Reflection Coefficient = " << sum.getZin(f)
																							<< ", " << sum.getGamma() << endl;

	/*Creates 2 vectors containing TRLine segments and length of segments respectively*/
	TRLines = makeTRLineVector(N, sum);
	lengths = makeLengthsVector(N, l);

	cout << "Number of TRLine Segments in full line:" << endl;
	cin >> N;
	cout << "length of pinched region:" << endl;
	cin >> y;


	TRLinesTotal total(TRLines, lengths, zLoad, y);

	cout << "Zin (ohms), Reflection Coefficient = " << total.getZinTotal(f)
													<< ", " << total.getGammaTotal(f) << endl;

	for(int i = 0; i < N - y; i++){
		vector <TRLine> pinchedSeg = getSegments(i, i + y);
		for (int j = 0; j < pinchedSeg.size(); j++){
			TRLine desiredSeg = pinchedSeg.at(i);
			CoaxXSection desiredXSect = desiredSeg.getXSections();
			desiredXSect.setOuterRadius(R0);
			//NOW WE HAVE TO UPDATE THE VECTOR OF TRLINES TO SHOW THIS PINCHED REGION
		}
	}
	return 20;
}


/*
 *  Finds desired trXSect based on dimensions chosen by user
 * (includes Z0 and Beta).
 */
TRLineXSect* getXSect(string type, double f){
	double r, R, R0, eps, w, h, t, b;
	TRLineXSect *trXSect = NULL;

	/*If calculating microstrip Xsect, takes in width, height, strip thickness, and permittivity*/
	if (type == "1"){
		/*for microstrip*/
		cout << "Width (m):"<< endl;
		cin >> w;
		cout << "Height (m):"<< endl;
		cin >> h;
		cout << "Thinkness of Inner Strip (m):"<< endl;
		cin >> t;
		cout << "Permittivity:"<< endl;
		cin >> eps;

		return trXSect = new MicrostripXSection (w, h, t, eps);

		/*If calculating stripline Xsect, takes in width, height, strip thickness, and permittivity*/
	} else if (type == "2"){
		/*for stripline*/
		cout << "Width (m):"<< endl;
		cin >> w;
		cout << "Height (m):"<< endl;
		cin >> b;
		cout << "Thinkness of Inner Strip (m):"<< endl;
		cin >> t;
		cout << "Permittivity:"<< endl;
		cin >> eps;

		return trXSect = new StriplineXSection (w, b, t, eps);

		/*If calculating coax Xsect, takes in the inner & outer radius and permittivity*/
	} else if (type == "3") {
		/* for coax*/
		cout << "Small Radius (m):"<< endl;
		cin >> r;
		cout << "Large Radius (m):"<< endl;
		cin >> R;
		cout << "Radius of pinched region (m):" << endl;
		cin >> R0;
		cout << "Permittivity:"<< endl;
		cin >> eps;

		return trXSect = new CoaxXSection (r, R, R0, eps);
	}
}

/*
 * Adds TRLine segments to this vector starting with the segment next to the load
 * impedance and continuing through the rest of the segments consecutively
 */
vector <TRLine> makeTRLineVector(int N, TRLine sum){
	vector <TRLine> TRLines;
	for (int i; i < N; i++){
		TRLines.push_back(sum);
	}
	return TRLines;
}

/*Adds the lengths corresponding to the TRLine segments in TRLines*/
vector <int> makeLengthsVector(int N, double l){
	vector <int> lengths;
	for (int i; i < N; i++){
		lengths.push_back(l);
	}
	return lengths;
}
