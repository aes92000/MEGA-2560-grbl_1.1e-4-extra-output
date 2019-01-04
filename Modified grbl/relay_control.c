/*
  coolant_control.c - coolant control methods
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grbl.h"


void relay_init()
{
  RELAY_ONE_DDR |= (1 << RELAY_ONE_BIT); // Configure as output pin.
  RELAY_TWO_DDR |= (1 << RELAY_TWO_BIT); // Configure as output pin.
  RELAY_FOUR_DDR |= (1 << RELAY_FOUR_BIT); // Configure as output pin.
  RELAY_THREE_DDR |= (1 << RELAY_THREE_BIT); // Configure as output pin.
  relay_stop();
}

uint8_t relay_get_state()
{
  uint8_t rly_state = RELAY_STATE_DISABLE;

  if ((RELAY_ONE_PORT |= (1 << RELAY_ONE_BIT))) {
    rly_state |= RELAY_STATE_ONE;
    return (rly_state);

  }
  else if ((RELAY_TWO_PORT |= (1 << RELAY_TWO_BIT))) {
    rly_state |= RELAY_STATE_TWO;
    return (rly_state);

  }
  else if ((RELAY_THREE_PORT |= (1 << RELAY_THREE_BIT))) {
    rly_state |= RELAY_STATE_THREE;
    return (rly_state);

  }
  else if ((RELAY_FOUR_PORT |= (1 << RELAY_FOUR_BIT))) {
    rly_state |= RELAY_STATE_FOUR;
    return (rly_state);

  }
  //return (rly_state);
}

// Main program only. Immediately sets relay state,
// if enabled. Also sets a flag to report an update to a relay state.
// Called by coolant toggle override, parking restore, parking retract, sleep mode, g-code
// parser program end, and g-code parser coolant_sync().
void relay_set_state(uint8_t mode)
{
  if (sys.abort) {
    return;  // Block during abort.
  }
  if (mode == RELAY_DISABLE) {
    relay_stop();
  }
  else {
    if ( mode == RELAY_ONE_CHANGE) {
      RELAY_ONE_PORT ^= (1 << RELAY_ONE_BIT);
    }
    else if (mode == RELAY_TWO_CHANGE) {
      RELAY_TWO_PORT ^= (1 << RELAY_TWO_BIT);
    }
    else if ( mode == RELAY_FOUR_CHANGE) {
      RELAY_FOUR_PORT ^= (1 << RELAY_FOUR_BIT);
    }
    else if ( mode == RELAY_THREE_CHANGE) {
      RELAY_THREE_PORT ^= (1 << RELAY_THREE_BIT);
    }
  }
  //sys.report_ovr_counter = 0; // Set to report change immediately
}

void relay_stop()
{
  RELAY_ONE_PORT &= ~(1 << RELAY_ONE_BIT);
  RELAY_TWO_PORT &= ~(1 << RELAY_TWO_BIT);
  RELAY_FOUR_PORT &= ~(1 << RELAY_FOUR_BIT);
  RELAY_THREE_PORT &= ~(1 << RELAY_THREE_BIT);
}

// G-code parser entry-point for setting relay state. Forces a planner buffer sync and bails
// if an abort or check-mode is active.
void relay_sync(uint8_t mode)
{
  if (sys.state == STATE_CHECK_MODE) {
    return;
  }
  protocol_buffer_synchronize(); // Ensure relay turns on when specified in program.
  relay_set_state(mode);
}
