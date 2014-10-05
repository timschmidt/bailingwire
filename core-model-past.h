/*
 *  This file is part of the bailingwire firmware.
 *
 *  Bailingwire is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Bailingwire is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Bailingwire.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef CORE_MODEL_PAST_H
#define CORE_MODEL_PAST_H

// Replace with per-axis position tracking + mapping from per-axis positions to cartesian coordinates - how?

// log of changes in machine state - all per-axis state values throughout the firmware are derived from these numbers
// timestamped snapshots of machine status starting now, and older.  entries only made on state change
// calculate length of buffer based on struct size, available ram at compile time 

// use this dataset for all CONTROL function calculations - must pack well in ram, be efficient to search

#endif // CORE_MODEL_PAST_H
