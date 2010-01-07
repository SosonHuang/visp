/****************************************************************************
 *
 * $Id$
 *
 * Copyright (C) 1998-2010 Inria. All rights reserved.
 *
 * This software was developed at:
 * IRISA/INRIA Rennes
 * Projet Lagadic
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * http://www.irisa.fr/lagadic
 *
 * This file is part of the ViSP toolkit.
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech AS of Norway and appearing in the file
 * LICENSE included in the packaging of this file.
 *
 * Licensees holding valid ViSP Professional Edition licenses may
 * use this file in accordance with the ViSP Commercial License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Contact visp@irisa.fr if any conditions of this licensing are
 * not clear to you.
 *
 * Description:
 * Time management and measurement.
 *
 * Authors:
 * Eric Marchand
 * Fabien Spindler
 *
 *****************************************************************************/


#ifndef vpTime_h
#define vpTime_h

/*!
  \file vpTime.h
  \brief Time management and measurement

*/

#include <visp/vpConfig.h>

/*!
  \class vpTime
  \ingroup Time
  \brief Time management and measurement.

  The example below shows how to synchronize a loop to a given framerate.

  \code
#include <visp/vpTime.h>

int main()
{
  double t;
  while(1) {
    t = vpTime::measureTimeMs();
    ...
    vpTime::wait(t, 40); // Loop time is set to 40 ms, ie 25 Hz
  }
}
  \endcode

*/

class VISP_EXPORT vpTime
{
public:
  static double minTimeForUsleepCall;

  static double measureTimeSecond() ;
  static double measureTimeMs() ;
  static double measureTimeMicros() ;
  static int  wait(double t0, double t) ;
  static void wait(double t) ;
} ;

#endif
