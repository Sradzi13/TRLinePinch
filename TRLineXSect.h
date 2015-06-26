/*
 * TRLineXSect.h
 *
 *  Created on: Jun 19, 2015
 *      Author: sarahradzihovsky
 */

#ifndef TRLINEXSECT_H_
#define TRLINEXSECT_H_

class TRLineXSect {
public:
	virtual double getZ0() = 0;

	virtual double getBeta(double f) = 0;


};

#endif /* TRLINEXSECT_H_ */
