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
//#include "CkCsv.h"
using namespace std;

/* Function Prototypes */

TRLineXSect* getXSect(string type, double f);
vector <TRLine> makeTRLineVector(int N, TRLine sum);
vector <int> makeLengthsVector(int N, double l);

int main() {

	cout << "This program simulates the pinch of an entire TRLines of"
			" the parameters you choose." << endl;


	/*Only runs this code if entire TRLine is being calculated*/
	double f, l, y, R0;
	int N;
	complex <double> zLoad;

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

	cout << "Number of TRLine Segments in full line:" << endl;
	cin >> N;
	cout << "length of pinched region:" << endl;
	cin >> y;
	cout << "Radius of pinched region (m):" << endl;
	cin >> R0;

	/*Creates 2 vectors containing TRLine segments and length of segments respectively*/
	vector <TRLine> TRLines = makeTRLineVector(N, sum);
	vector <int> lengths = makeLengthsVector(N, l);

	TRLinesTotal total(TRLines, lengths, zLoad);

	cout<< "Before pinch: " << endl;
	cout << "Zin (ohms), Reflection Coefficient = " << total.getZinTotal(f) << endl;
	cout										<< ", " << total.getGammaTotal(f) << endl;

	//sorts through all possible finger positions
	for(int i = 0; i < N - y; i++){
		double x = i + (y/2);
		vector <TRLine> pinchedSeg = total.getSegments(i, i + y);

		//sorts through each pinched segment and changes their outer radius
		for (int j = 0; j < pinchedSeg.size(); j++){

			//ARE THE RADII BEING RESET to normal size FOR EACH FINGER POSITION???????????????????????
			//???????????????????
			//?????????????????
			// how to you output a CSV file to make the presentation of these outcomes neater?
			TRLine desiredSeg = pinchedSeg.at(j);
			TRLineXSect* desiredXSect = desiredSeg.getXSections();
			desiredXSect = (CoaxXSection *) desiredXSect;
			desiredXSect -> setOuterRadius(R0);

			//return segments to vector of complete XSections and recalculate Zin and Gamma
			vector <TRLine> updated = TRLines;
			updated.at(i + j) = pinchedSeg.at(j);

		}
		vector <int> pinchedLengths;
		for (int k = 0; k < y; k++){
			pinchedLengths.push_back(lengths.at(i + k));
		}

		//prints out Zin and Gamma for each finger segment which consists of multiple TRLine segments
		TRLinesTotal fingerPinch(pinchedSeg, pinchedLengths, zLoad);
		cout << "Zin (ohms), Reflection Coefficient = " << fingerPinch.getZinTotal(f)
																					<< ", " << fingerPinch.getGammaTotal(f) << endl;
		cout << "center of finger at " << x << "meters from end" << endl;

		//CSV file headers and opening of file
//		ofstream Pinch_Data ("TRLine_Pinch_Data");
//		Pinch_Data << "Finger Location, Internal Impedance, Reflection Coefficient" << "/n";
//		Pinch_Data << x << ";" << fingerPinch.getZinTotal << ";" << fingerPinch.getGammaTotal(f) << "/n";
//		Pinch_Data.close();
//		if (!Pinch_Data) {
//			cout << "Error opening file" << endl;
//			return -1;
//		}


		//		TRLine seg = TRLine(zLoad, desiredXSect, lengths.at(i));
		//		cout << i << "Inner Impedance (ohms), Reflection Coefficient = " << seg.getZin(f)
		//													<< ", " << seg.getGamma() << endl;
	}
	//prints out new total Zin and reflection coeff after TRLine is pinched
	TRLinesTotal newTotal(TRLines, lengths, zLoad);
	cout << "Zin (ohms), Reflection Coefficient = " << newTotal.getZinTotal(f)
																			<< ", " << newTotal.getGammaTotal(f) << endl;
	return 20;
}


/*
 *  Finds desired trXSect based on dimensions chosen by user
 * (includes Z0 and Beta).
 */
TRLineXSect* getXSect(string type, double f){
	double r, R, eps, w, h, t, b;
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

		cout << "Small Radius (m):"<< endl;
		cin >> r;
		cout << "Large Radius (m):"<< endl;
		cin >> R;
		cout << "Permittivity:"<< endl;
		cin >> eps;

		return trXSect = new CoaxXSection (r, R, eps);
	}
}

/*
 * Adds TRLine segments to this vector starting with the segment next to the load
 * impedance and continuing through the rest of the segments consecutively
 */
vector <TRLine> makeTRLineVector(int N, TRLine sum){
	vector <TRLine> TRLines;
	for (int i = 0; i < N; i++){
		TRLines.push_back(sum);
	}
	return TRLines;
}

/*Adds the lengths corresponding to the TRLine segments in TRLines*/
vector <int> makeLengthsVector(int N, double l){
	vector <int> lengths;
	for (int i = 0; i < N; i++){
		lengths.push_back(l);
	}
	return lengths;
}
