/*
 * displayer.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: Iuri Andrade
 */

#include "displayer.h"

void Displayer::setDisplayedCloud(const CloudXYZ::ConstPtr &cloud)
{
	viewer_.showCloud(cloud);
}

bool Displayer::wasStopped()
{
	return viewer_.wasStopped();
}
