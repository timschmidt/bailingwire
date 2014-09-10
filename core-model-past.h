#ifndef CORE_MODEL_PAST_H
#define CORE_MODEL_PAST_H

// log of changes in machine state - all per-axis state values throughout the firmware are derived from these numbers
// timestamped snapshots of machine status starting now, and older.  entries only made on state change
// calculate length of buffer based on struct size, available ram at compile time 

// use this dataset for all CONTROL function calculations - must pack well in ram, be efficient to search

#endif // CORE_MODEL_PAST_H
