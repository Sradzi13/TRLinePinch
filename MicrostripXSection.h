/*
 * MicrostripXSection.h
 *
 *  Created on: Jun 15, 2015
 *      Author: sarahradzihovsky
 */

#ifndef MICROSTRIPXSECTION_H_
#define MICROSTRIPXSECTION_H_
#include "TRLineXSect.h"
using namespace std;

class MicrostripXSection : public TRLineXSect {
public:

	/*
	 * Constructor: MicrostripXSection
	 * Usage: trXSect = new MicrostripXSection (w, h, t, eps);
	 * -----------------------
	 * Links function parameters with privately declared variables
	 */
	MicrostripXSection(double w, double h, double t, double eps);

	/*
	 * Destructor: ~MicrostripXSection
	 * ------------------
	 * The destructor deallocates the storage for this MicrostripXSection.
	 * It must be declared virtual to ensure that the correct subclass
	 * destructor is called when deleting an expression.
	 */
	virtual ~MicrostripXSection();

	/*
	 * Method: getZ0
	 * Usage: trXSect -> getZ0();
	 * ----------------------------
	 * Despite what type of XSection, this method will pass back Z0
	 * of a XSection given its given dimensions (in this case: width,
	 * height, strip thickness and permittivity).
	 */
	double getZ0();

	/*
	 * Method: getF
	 * Usage: getF();
	 * ----------------------------
	 * Used to calculate Z0. Given width and height, finds F,
	 * which is a factor of Z0.
	 */
	double getF();

	/*
	 * Method: getEta
	 * Usage: getEta();
	 * ----------------------------
	 * Used to calculate Z0. Given the XSection's permittivity,
	 * finds Eta, which is a factor of Z0.
	 */
	double getEta();

	/*
	 * Method: getBeta
	 * Usage: trXSect -> getBeta();
	 * ----------------------------
	 * Despite what type of XSection, this method will pass back Z0
	 * of a XSection, calculated from its given dimensions (in this
	 * case: frequency and permittivity).
	 */
	double getBeta(double f);

private:

	double w, h, t, eps;

};

#endif /* MICROSTRIPXSECTION_H_ */
