/****************************************************************************
 *
 * This file is part of the ViSP software.
 * Copyright (C) 2005 - 2015 by Inria. All rights reserved.
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * ("GPL") version 2 as published by the Free Software Foundation.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact Inria about acquiring a ViSP Professional
 * Edition License.
 *
 * See http://visp.inria.fr for more information.
 *
 * This software was developed at:
 * Inria Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 *
 * If you have questions regarding the use of this file, please contact
 * Inria at visp@inria.fr
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Description:
 * Test for image roi display.
 *
 * Authors:
 * Fabien Spindler
 *
 *****************************************************************************/

/*!
  \example testDisplayRoi.cpp

  Test display of an image roi.

*/

#include <stdlib.h>

#include <visp3/core/vpImage.h>
#include <visp3/core/vpDisplayX.h>
#include <visp3/core/vpDisplayGTK.h>
#include <visp3/core/vpDisplayGDI.h>
#include <visp3/core/vpDisplayD3D.h>
#include <visp3/core/vpDisplayOpenCV.h>
#include <visp3/core/vpParseArgv.h>
#include <visp3/core/vpRect.h>

// List of allowed command line options
#define GETOPTARGS	"cdh"

void usage(const char *name, const char *badparam);
bool getOptions(int argc, const char **argv, bool &click_allowed, bool &display);

/*!

  Print the program options.

  \param name : Program name.
  \param badparam : Bad parameter name.

 */
void usage(const char *name, const char *badparam)
{
  fprintf(stdout, "\n\
Read an image on the disk, display it using X11, display some\n\
features (line, circle, caracters) in overlay and finaly write \n\
the image and the overlayed features in an image on the disk.\n\
\n\
SYNOPSIS\n\
  %s [-c] [-d] [-h]\n", name);

  fprintf(stdout, "\n\
OPTIONS:                                               Default\n\
  -c\n\
     Disable the mouse click. Useful to automate the \n\
     execution of this program without humain intervention.\n\
\n\
  -d                                             \n\
     Disable the image display. This can be useful \n\
     for automatic tests using crontab under Unix or \n\
     using the task manager under Windows.\n\
\n\
  -h\n\
     Print the help.\n\n");

  if (badparam) {
    fprintf(stderr, "ERROR: \n" );
    fprintf(stderr, "\nBad parameter [%s]\n", badparam);
  }

}

/*!

  Set the program options.

  \param argc : Command line number of parameters.
  \param argv : Array of command line parameters.
  \param click_allowed : Enable/disable mouse click.
  \param display : Set as true, activates the image display. This is
  the default configuration. When set to false, the display is
  disabled. This can be useful for automatic tests using crontab
  under Unix or using the task manager under Windows.

  \return false if the program has to be stopped, true otherwise.

*/
bool getOptions(int argc, const char **argv, bool &click_allowed, bool &display)
{
  const char *optarg_;
  int	c;
  while ((c = vpParseArgv::parse(argc, argv, GETOPTARGS, &optarg_)) > 1) {

    switch (c) {
    case 'c': click_allowed = false; break;
    case 'd': display = false; break;
    case 'h': usage(argv[0], NULL); return false; break;

    default:
      usage(argv[0], optarg_); return false; break;
    }
  }

  if ((c == 1) || (c == -1)) {
    // standalone param or error
    usage(argv[0], NULL);
    std::cerr << "ERROR: " << std::endl;
    std::cerr << "  Bad argument " << optarg_ << std::endl << std::endl;
    return false;
  }

  return true;
}

int main(int argc, const char ** argv)
{
#ifdef VISP_HAVE_DISPLAY
  bool opt_click_allowed = true;
  bool opt_display = true;

  // Read the command line options
  if (getOptions(argc, argv, opt_click_allowed, opt_display) == false) {
    exit (-1);
  }

  if (opt_display) {

    vpImage<unsigned char> I(480,640,255);

#if defined(VISP_HAVE_X11)
    vpDisplayX d;
#elif defined(VISP_HAVE_GTK)
    vpDisplayGTK d;
#elif defined(VISP_HAVE_GDI)
    vpDisplayGDI d;
#elif defined(VISP_HAVE_D3D9)
    vpDisplayD3D d;
#elif defined(VISP_HAVE_OPENCV)
    vpDisplayOpenCV d;
#endif
    d.init(I);
    vpDisplay::display(I);
    vpDisplay::flush(I);

    I = 0;

    vpRect roi(I.getWidth()/4, I.getHeight()/4, I.getWidth()/2, I.getHeight()/2);
    vpDisplay::displayROI(I, roi);
    vpDisplay::flush(I);
    if (opt_click_allowed) {
      std::cout << "A click in the image to continue..." << std::endl;
      vpDisplay::getClick(I);
    }
    vpDisplay::close(I);

    vpImage<vpRGBa> C(480,640,vpRGBa(255,0,0,0));

    //vpDisplayX d;
    d.init(C);
    vpDisplay::display(C);
    vpDisplay::flush(C);

    C = vpRGBa(0,255,0,0);

    vpDisplay::displayROI(C, roi);
    vpDisplay::flushROI(C, roi);
    if (opt_click_allowed) {
      std::cout << "A click in the image to exit..." << std::endl;
      vpDisplay::getClick(C);
    }
  }
#else
  (void)argc;
  (void)argv;
#endif
  return 0;
}