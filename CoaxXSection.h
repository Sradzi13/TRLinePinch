/* CoaxXSection.h
 *
 *  Created on: Jun 15, 2015
 *      Author: sarahradzihovsky
 */

#ifndef COAXXSECTION_H_
#define COAXXSECTION_H_
#include "TRLineXSect.h"
using namespace std;

class CoaxXSection : public TRLineXSect {
public:
	/*
	 * Constructor: CoaxXSection
	 * Usage: trXSect = new CoaxXSection (r, R, eps);
	 * -----------------------
	 * Links function parameters with privately declared variables
	 */
	CoaxXSection(double r, double R, double eps);

	/*
	 * Destructor: ~CoaxXSection
	 * ------------------
	 * The destructor deallocates the storage for this CoaxXSection.
	 * It must be declared virtual to ensure that the correct subclass
	 * destructor is called when deleting an expression.
	 */
	virtual ~CoaxXSection();

	/*
	 * Method: getZ0
	 * Usage: trXSect -> getZ0();
	 * ----------------------------
	 * Despite what type of XSection, this method will pass back Z0
	 * of a XSection given its given dimensions (in this case: inner
	 * radius, outer radius, and permittivity).
	 */
	double getZ0();

	/*
	 * Method: getF
	 * Usage: getF();
	 * ----------------------------
	 * Used to calculate Z0. Given inner and outer radius, finds F,
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

	double r, R, eps;
};

#endif /* COAXXSECTION_H_ */
