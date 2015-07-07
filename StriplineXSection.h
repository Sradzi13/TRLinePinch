/*
 * StriplineXSection.h
 *
 *  Created on: Jun 15, 2015
 *      Author: sarahradzihovsky
 */

#ifndef STRIPLINEXSECTION_H_
#define STRIPLINEXSECTION_H_
#include "TRLineXSect.h"
using namespace std;

class StriplineXSection : public TRLineXSect {
public:

	/*
	 * Constructor: StriplineXSection
	 * Usage: trXSect = new StriplineXSection (w, b, t, eps);
	 * -----------------------
	 * Links function parameters with privately declared variables
	 */
	StriplineXSection(double w, double b, double t, double eps);

	/*
	 * Destructor: ~StriplineXSection
	 * ------------------
	 * The destructor deallocates the storage for this StriplineXSection.
	 * It must be declared virtual to ensure that the correct subclass
	 * destructor is called when deleting an expression.
	 */
	virtual ~StriplineXSection();

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
	 * Used to calculate Z0. Given width, strip thickness, and height, finds F,
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

	void setOuterRadius(double R0);

private:

	double w, b, t, eps;
};

#endif /* STRIPLINEXSECTION_H_ */
