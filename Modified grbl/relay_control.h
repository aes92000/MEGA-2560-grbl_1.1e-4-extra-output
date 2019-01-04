/*
  coolant_control.h - spindle control methods
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

#ifndef relay_control_h
#define relay_control_h


#define RELAY_NO_SYNC     false
#define RELAY_FORCE_SYNC  true

#define RELAY_STATE_DISABLE   0  // Must be zero
#define RELAY_STATE_TWO     bit(0)

#define RELAY_STATE_ONE     bit(1)
#define RELAY_STATE_TWO     bit(2)
#define RELAY_STATE_FOUR    bit(3)
#define RELAY_STATE_THREE    bit(4)
#define RELAY_STATE_FOUR    bit(5)

// Initializes relay control pins.
void relay_init();

// Returns current relay output state. Overrides may alter it from programmed state.
uint8_t relay_get_state();

// Immediately disables relay pins.
void relay_stop();

// Sets the relay pins according to state specified.
void relay_set_state(uint8_t mode);

// G-code parser entry-point for setting elay states. Checks for and executes additional conditions.
void relay_sync(uint8_t mode);

#endif
