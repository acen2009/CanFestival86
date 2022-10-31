/*
This file is part of CanFestival, a library implementing CanOpen Stack.

Copyright (C): Edouard TISSERANT and Francis DUPIN

See COPYING file for copyrights details.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>		/* for NULL */
#include <errno.h>

#include "config.h"

#include "can_driver.h"

#include "vortex/can.h"

/*********functions which permit to communicate with the board****************/
UNS8 canReceive_driver (CAN_HANDLE hd, Message * m){
    UNS8 ret;

    if(can_QueryRxQueue(hd) > 0){        
        CANFrame package;
        if(!can_Read(hd, &package)){
            printf("read failed!\n");
            return false;
        }
        m->cob_id = package.identifier;
        m->len = package.length;
        memcpy(m->data, package.Data.byte, package.length);
        m->rtr = (package.type - 0) / 2;
        // m->rtr:0 for only standard mode. 
        // don't know if canfestival support extented frame??
    }
    else
        return false;

    return true;
}


/***************************************************************************/
UNS8 canSend_driver (CAN_HANDLE hd, Message const * m){
    CANFrame package;
    package.identifier = m->cob_id;
    package.length = m->len;
    memcpy(package.Data.byte, m->data, m->len);
    package.type = 0 + m->rtr * 2; 
    // m->rtr:0 for only standard mode. 
    // don't know if canfestival support extented frame??

    //mao: the return definition are different canfestival and vortex can library, 
    //canfestival expect to return a error, however vortex library return if send success
    //now I temporarily use a not !, to reverse it, that is, if success return no error!
    return !can_Write(hd, &package);
}

/***************************************************************************/
#ifdef RTCAN_SOCKET
int
TranslateBaudRate (const char *optarg)
{
  int baudrate;
  int val, len;
  char *pos = NULL;

  len = strlen (optarg);
  if (!len)
    return 0;

  switch ((int) optarg[len - 1])
    {
    case 'M':
      baudrate = 1000000;
      break;
    case 'K':
      baudrate = 1000;
      break;
    default:
      baudrate = 1;
      break;
    }
  if ((sscanf (optarg, "%i", &val)) == 1)
    baudrate *= val;
  else
    baudrate = 0;;

  return baudrate;
}
#endif

UNS8 canChangeBaudRate_driver( CAN_HANDLE fd, char* baud)
{
	printf("canChangeBaudRate not yet supported by this driver\n");
	return 0;
}

/***************************************************************************/
CAN_HANDLE canOpen_driver (s_BOARD * board){
    void *ptr_can = CreateCANBus(board->busname, IO_USE_PORTIO);
    ((CAN_Bus*)ptr_can)->BitTime = board->baudrate;
    if(can_Init(ptr_can) == false){
        can_Close(ptr_can);
        return NULL;
    }
    can_SetBPS(ptr_can, board->baudrate);
    can_SetTimeOut(ptr_can, 0L, 500L);
    /* receive all the data in Rx Buffer */
    can_EnableBypass(ptr_can);

    return ptr_can;
}

/***************************************************************************/
int canClose_driver (CAN_HANDLE hd){
    can_Close(hd);
    return 0;
}
