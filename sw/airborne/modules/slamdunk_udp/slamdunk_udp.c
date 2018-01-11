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
 * @file "modules/slamdunk_udp/slamdunk_udp.c"
 * @author kevindehecker
 * Communication to SLAMdunk over udp
 */

#include "modules/slamdunk_udp/slamdunk_udp.h"

#include "pprzlink/pprz_transport.h"
#include "mcu_periph/udp.h"
#include "subsystems/abi.h"

#include "subsystems/datalink/telemetry.h"
#include "subsystems/datalink/downlink.h"

#include "generated/flight_plan.h"

#include <stdio.h>

static struct slamdunk_t slamdunk = {
  .device = (&((SLAMDUNK_PORT).device)),
  .msg_available = false
};

static uint8_t mp_msg_buf[128]  __attribute__((aligned));   ///< The message buffer


void slamdunk_init(void) {
  printf("--- SALMDUNK init\n");
  pprz_transport_init(&slamdunk.transport);
}


void slamdunk_periodic(void) {
  printf("--- SALMDUNK periodic\n");



  struct PPRZ2SlamdunkPackage s2k_package;
  s2k_package.test1 = 11;

  //printf("pprz_msg_send_PAYLOAD this line causes seg fault.\n");


  unsigned char bla[6] ;
  pprz_msg_send_PAYLOAD(&(slamdunk.transport.trans_tx), slamdunk.device,
    1, sizeof(struct PPRZ2SlamdunkPackage),  bla);

  /*pprz_msg_send_PAYLOAD(&(slamdunk.transport.trans_tx), slamdunk.device,
    1, sizeof(struct PPRZ2SlamdunkPackage), (unsigned char *)(&s2k_package));
    //struct transport_tx *trans, struct link_device *dev, uint8_t ac_id, float *_test_field)
    */
}


/* Parse the message */
static inline void slamdunk_parse_msg(void) {
/* Parse the kalamos message */
  uint8_t msg_id = mp_msg_buf[1];

  switch (msg_id) {
    case PPRZ_MSG_ID_PAYLOAD:
      break;

    default:
      break;
  }
}


void slamdunk_event() {
  // Check if we got some message from the Kalamos
  //printf("--- SALMDUNK event\n");
  pprz_check_and_parse(slamdunk.device, &slamdunk.transport, mp_msg_buf, &slamdunk.msg_available);

  // If we have a message we should parse it
  if (slamdunk.msg_available) {
    slamdunk_parse_msg();
    slamdunk.msg_available = false;
  }
}

void slamdunk_periodic_start(void) {}
void slamdunk_periodic_stop(void) {}
