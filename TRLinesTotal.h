/*
 * TRLinesTotal.h
 *
 *  Created on: Jun 22, 2015
 *      Author: sarahradzihovsky
 *
 *  Superclass that sums together many individual TRLine
 *  segments and using their Zin's and Zload to find
 *  the total reflection coefficient.
 */

#ifndef TRLINESTOTAL_H_
#define TRLINESTOTAL_H_
#include <vector>
#include "TRLine.h"
#include "TRLineXSect.h"
#include <complex>
using namespace std;

class TRLinesTotal {
public:

	/*
	 * Constructor: TRLinesTotal
	 * -----------------------
	 * Links function parameters with privately declared variables
	 */

	TRLinesTotal(vector <TRLine> TRLines, vector <int> lengths,
			complex <double> zLoad, double y);

	/*
	 * Destructor: ~TRLinesTotal
	 * ------------------
	 * The destructor deallocates the storage for this whole TRLine.
	 * It must be declared virtual to ensure that the correct subclass
	 * destructor is called when deleting an expression.
	 */
	virtual ~TRLinesTotal();

	/*
	 * Method: getZinTotal
	 * Usage: total.getZinTotal(f);
	 * ----------------------------
	 * Iterates through each TRLine segment and condenses the line into an
	 * equivalent segment by finding the Zin of the first segment.
	 */
	complex <double> getZinTotal(double f);

	/*
	 * Method: getZin
	 * Usage: getZin(f, j, temp);
	 * ----------------------------
	 * Helps getZinTotal iterate through the line with each segment by finding
	 * the Zin given the zLoad of each segment (the Zin of the previous segment).
	 */
	complex <double> getZin(double f, int j, complex <double> temp);


	/*
	 * Method: getGammaTotal
	 * Usage:total.getGammaTotal(f);
	 * ----------------------------
	 * Given the ultimate ZinTotal found in getZinTotal, calculates the
	 * reflection coefficient.
	 */
	complex <double> getGammaTotal(double f);

	vector <TRLine> getSegments(int start, int end);

private:

	vector <TRLine> TRLines;
	vector <int> lengths;
	complex <double>  zLoad;
	double y;
};

#endif /* TRLINESTOTAL_H_ */
