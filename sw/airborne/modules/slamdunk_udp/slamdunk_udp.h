/*
 * Copyright (C) kevindehecker
 *
 * This file is part of paparazzi
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 * @file "modules/slamdunk_udp/slamdunk_udp.h"
 * @author kevindehecker
 * Communication to SLAMdunk over udp
 */

#ifndef SLAMDUNK_UDP_H
#define SLAMDUNK_UDP_H

#include "generated/airframe.h"
#include "pprzlink/pprz_transport.h"


struct slamdunk_t {
  struct link_device *device;           ///< The device which is uses for communication
  struct pprz_transport transport;      ///< The transport layer (PPRZ)
  //struct OrientationReps imu_to_mag;    ///< IMU to magneto translation
  bool msg_available;                 ///< If we received a message
};


struct PPRZ2SlamdunkPackage {
    int test1;
}__attribute__((__packed__));

/*struct PPRZ2SlamdunkPackage {
  int test1;
}__attribute__((__packed__));
*/

struct Slamdunk2PPRZPackage {
  int test2;
} __attribute__((__packed__));

extern struct Slamdunk2PPRZPackage s2p_package;

extern void slamdunk_init(void);
extern void slamdunk_periodic(void);
extern void slamdunk_event(void);
//extern void slamdunk_callback(void);
extern void slamdunk_periodic_start(void);
extern void slamdunk_periodic_stop(void);

#endif

