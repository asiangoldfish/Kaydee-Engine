#ifndef __ENTRY_POINT_H__
#define __ENTRY_POINT_H__

#include "Application.h"

Kaydee::Application*
Kaydee::createApplication();

int
main(int argc, char** argv);

void
usage();

void
version();

#endif
