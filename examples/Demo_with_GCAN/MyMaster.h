
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef MYMASTER_H
#define MYMASTER_H

#include "data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 MyMaster_valueRangeTest (UNS8 typeValue, void * value);
const indextable * MyMaster_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks);

/* Master node data struct */
extern CO_Data MyMaster_Data;
extern UNS8 INPUT_FROM_GCAN;		/* Mapped at index 0x2000, subindex 0x00*/
extern UNS8 OUTPUT_TO_GCAN;		/* Mapped at index 0x2001, subindex 0x00*/

#endif // MYMASTER_H