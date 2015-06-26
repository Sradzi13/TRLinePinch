/*
 * TRLine.h
 *
 *  Created on: Jun 18, 2015
 *      Author: sarahradzihovsky
 */


#ifndef TRLINE_H_
#define TRLINE_H_
#include "TRLineXSect.h"
#include <complex>
using namespace std;


class TRLine {
public:

	/*
	 * Constructor: TRLine
	 * Usage: TRLine sum, TRLine current
	 * -----------------------
	 * Links function parameters with privately declared variables
	 */
	TRLine(complex <double> zLoad, TRLineXSect *trXSect, double l);

	/*
	 * Destructor: ~TRLines
	 * ------------------
	 * The destructor deallocates the storage for this TRLine segment.
	 * It must be declared virtual to ensure that the correct subclass
	 * destructor is called when deleting an expression.
	 */
	virtual ~TRLine();

	/*
	 * Method: getGamma
	 * Usage: sum.getGamma;
	 * ----------------------------
	 * Calculates the reflection coefficient from the zLoad chosen
	 * by user and Z0 calculated from XSect user designed.
	 */
	complex <double>  getGamma();

	/*
	 * Method: getZin
	 * Usage: sum.getZin(f);
	 * ----------------------------
	 * Calculates the internal impedance from the zLoad chosen
	 * by user and Z0 & Beta (phase constant) calculated from XSect user designed.
	 */

	complex <double> getZin(double f);

	/*
	 * Method: getZ0
	 * Usage: current.getZ0(f);
	 * ----------------------------
	 * Gets the internal impedance of the XSection that makes up the TRLine segment
	 */
	double getZ0();

	/*
	 * Method: getBeta
	 * Usage: current.getBeta(f);
	 * ----------------------------
	 * Gets the phase constant of the XSection that makes up the TRLine segment
	 */
	double getBeta(double f);

	TRLineXSect* getXSections();

private:
	double l;
	complex <double> zLoad;
	TRLineXSect *trXSect = NULL;
};

#endif /* TRLINE_H_ */
