
/* File generated by gen_cfile.py. Should not be modified. */

#include "MyMaster.h"

/**************************************************************************/
/* Declaration of mapped variables                                        */
/**************************************************************************/
UNS8 INPUT_FROM_GCAN = 0x0;		/* Mapped at index 0x2000, subindex 0x00 */
UNS8 OUTPUT_TO_GCAN = 0x0;		/* Mapped at index 0x2001, subindex 0x00 */

/**************************************************************************/
/* Declaration of value range types                                       */
/**************************************************************************/

#define valueRange_EMC 0x9F /* Type for index 0x1003 subindex 0x00 (only set of value 0 is possible) */
UNS32 MyMaster_valueRangeTest (UNS8 typeValue, void * value)
{
  switch (typeValue) {
    case valueRange_EMC:
      if (*(UNS8*)value != (UNS8)0) return OD_VALUE_RANGE_EXCEEDED;
      break;
  }
  return 0;
}

/**************************************************************************/
/* The node id                                                            */
/**************************************************************************/
/* node_id default value.*/
UNS8 MyMaster_bDeviceNodeId = 0x00;

/**************************************************************************/
/* Array of message processing information */

const UNS8 MyMaster_iam_a_slave = 0;

TIMER_HANDLE MyMaster_heartBeatTimers[1];

/*
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                               OBJECT DICTIONARY

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
*/

/* index 0x1000 :   Device Type. */
                    UNS32 MyMaster_obj1000 = 0x0;	/* 0 */
                    subindex MyMaster_Index1000[] = 
                     {
                       { RO, uint32, sizeof (UNS32), (void*)&MyMaster_obj1000 }
                     };

/* index 0x1001 :   Error Register. */
                    UNS8 MyMaster_obj1001 = 0x0;	/* 0 */
                    subindex MyMaster_Index1001[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&MyMaster_obj1001 }
                     };

/* index 0x1003 :   Pre-defined Error Field */
                    UNS8 MyMaster_highestSubIndex_obj1003 = 0; /* number of subindex - 1*/
                    UNS32 MyMaster_obj1003[] = 
                    {
                      0x0	/* 0 */
                    };
                    ODCallback_t MyMaster_Index1003_callbacks[] = 
                     {
                       NULL,
                       NULL,
                     };
                    subindex MyMaster_Index1003[] = 
                     {
                       { RW, valueRange_EMC, sizeof (UNS8), (void*)&MyMaster_highestSubIndex_obj1003 },
                       { RO, uint32, sizeof (UNS32), (void*)&MyMaster_obj1003[0] }
                     };

/* index 0x1005 :   SYNC COB ID. */
                    UNS32 MyMaster_obj1005 = 0x40000080;	/* 1073741952 */
                    ODCallback_t MyMaster_Index1005_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex MyMaster_Index1005[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&MyMaster_obj1005 }
                     };

/* index 0x1006 :   Communication / Cycle Period. */
                    UNS32 MyMaster_obj1006 = 0x2710;	/* 10000 */
                    ODCallback_t MyMaster_Index1006_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex MyMaster_Index1006[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&MyMaster_obj1006 }
                     };

/* index 0x100C :   Guard Time */ 
                    UNS16 MyMaster_obj100C = 0x0;   /* 0 */

/* index 0x100D :   Life Time Factor */ 
                    UNS8 MyMaster_obj100D = 0x0;   /* 0 */

/* index 0x1014 :   Emergency COB ID */
                    UNS32 MyMaster_obj1014 = 0x80 + 0x00;   /* 128 + NodeID */

/* index 0x1016 :   Consumer Heartbeat Time */
                    UNS8 MyMaster_highestSubIndex_obj1016 = 0;
                    UNS32 MyMaster_obj1016[]={0};

/* index 0x1017 :   Producer Heartbeat Time. */
                    UNS16 MyMaster_obj1017 = 0x3E8;	/* 1000 */
                    ODCallback_t MyMaster_Index1017_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex MyMaster_Index1017[] = 
                     {
                       { RW, uint16, sizeof (UNS16), (void*)&MyMaster_obj1017 }
                     };

/* index 0x1018 :   Identity. */
                    UNS8 MyMaster_highestSubIndex_obj1018 = 4; /* number of subindex - 1*/
                    UNS32 MyMaster_obj1018_Vendor_ID = 0x0;	/* 0 */
                    UNS32 MyMaster_obj1018_Product_Code = 0x0;	/* 0 */
                    UNS32 MyMaster_obj1018_Revision_Number = 0x0;	/* 0 */
                    UNS32 MyMaster_obj1018_Serial_Number = 0x0;	/* 0 */
                    subindex MyMaster_Index1018[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&MyMaster_highestSubIndex_obj1018 },
                       { RO, uint32, sizeof (UNS32), (void*)&MyMaster_obj1018_Vendor_ID },
                       { RO, uint32, sizeof (UNS32), (void*)&MyMaster_obj1018_Product_Code },
                       { RO, uint32, sizeof (UNS32), (void*)&MyMaster_obj1018_Revision_Number },
                       { RO, uint32, sizeof (UNS32), (void*)&MyMaster_obj1018_Serial_Number }
                     };

/* index 0x1280 :   Client SDO 1 Parameter. */
                    UNS8 MyMaster_highestSubIndex_obj1280 = 3; /* number of subindex - 1*/
                    UNS32 MyMaster_obj1280_COB_ID_Client_to_Server_Transmit_SDO = 0x602;	/* 1538 */
                    UNS32 MyMaster_obj1280_COB_ID_Server_to_Client_Receive_SDO = 0x582;	/* 1410 */
                    UNS8 MyMaster_obj1280_Node_ID_of_the_SDO_Server = 0x2;	/* 2 */
                    subindex MyMaster_Index1280[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&MyMaster_highestSubIndex_obj1280 },
                       { RW, uint32, sizeof (UNS32), (void*)&MyMaster_obj1280_COB_ID_Client_to_Server_Transmit_SDO },
                       { RW, uint32, sizeof (UNS32), (void*)&MyMaster_obj1280_COB_ID_Server_to_Client_Receive_SDO },
                       { RW, uint8, sizeof (UNS8), (void*)&MyMaster_obj1280_Node_ID_of_the_SDO_Server }
                     };

/* index 0x1400 :   Receive PDO 1 Parameter. */
                    UNS8 MyMaster_highestSubIndex_obj1400 = 6; /* number of subindex - 1*/
                    UNS32 MyMaster_obj1400_COB_ID_used_by_PDO = 0x182;	/* 386 */
                    UNS8 MyMaster_obj1400_Transmission_Type = 0x0;	/* 0 */
                    UNS16 MyMaster_obj1400_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 MyMaster_obj1400_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 MyMaster_obj1400_Event_Timer = 0x0;	/* 0 */
                    UNS8 MyMaster_obj1400_SYNC_start_value = 0x0;	/* 0 */
                    subindex MyMaster_Index1400[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&MyMaster_highestSubIndex_obj1400 },
                       { RW, uint32, sizeof (UNS32), (void*)&MyMaster_obj1400_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&MyMaster_obj1400_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&MyMaster_obj1400_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&MyMaster_obj1400_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&MyMaster_obj1400_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&MyMaster_obj1400_SYNC_start_value }
                     };

/* index 0x1600 :   Receive PDO 1 Mapping. */
                    UNS8 MyMaster_highestSubIndex_obj1600 = 1; /* number of subindex - 1*/
                    UNS32 MyMaster_obj1600[] = 
                    {
                      0x20000008	/* 536870920 */
                    };
                    subindex MyMaster_Index1600[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&MyMaster_highestSubIndex_obj1600 },
                       { RW, uint32, sizeof (UNS32), (void*)&MyMaster_obj1600[0] }
                     };

/* index 0x1800 :   Transmit PDO 1 Parameter. */
                    UNS8 MyMaster_highestSubIndex_obj1800 = 6; /* number of subindex - 1*/
                    UNS32 MyMaster_obj1800_COB_ID_used_by_PDO = 0x202;	/* 514 */
                    UNS8 MyMaster_obj1800_Transmission_Type = 0x1;	/* 1 */
                    UNS16 MyMaster_obj1800_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 MyMaster_obj1800_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 MyMaster_obj1800_Event_Timer = 0x0;	/* 0 */
                    UNS8 MyMaster_obj1800_SYNC_start_value = 0x0;	/* 0 */
                    ODCallback_t MyMaster_Index1800_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex MyMaster_Index1800[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&MyMaster_highestSubIndex_obj1800 },
                       { RW, uint32, sizeof (UNS32), (void*)&MyMaster_obj1800_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&MyMaster_obj1800_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&MyMaster_obj1800_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&MyMaster_obj1800_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&MyMaster_obj1800_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&MyMaster_obj1800_SYNC_start_value }
                     };

/* index 0x1A00 :   Transmit PDO 1 Mapping. */
                    UNS8 MyMaster_highestSubIndex_obj1A00 = 1; /* number of subindex - 1*/
                    UNS32 MyMaster_obj1A00[] = 
                    {
                      0x20010008	/* 536936456 */
                    };
                    subindex MyMaster_Index1A00[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&MyMaster_highestSubIndex_obj1A00 },
                       { RW, uint32, sizeof (UNS32), (void*)&MyMaster_obj1A00[0] }
                     };

/* index 0x2000 :   Mapped variable INPUT_FROM_GCAN */
                    subindex MyMaster_Index2000[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&INPUT_FROM_GCAN }
                     };

/* index 0x2001 :   Mapped variable OUTPUT_TO_GCAN */
                    subindex MyMaster_Index2001[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&OUTPUT_TO_GCAN }
                     };

/**************************************************************************/
/* Declaration of pointed variables                                       */
/**************************************************************************/

const indextable MyMaster_objdict[] = 
{
  { (subindex*)MyMaster_Index1000,sizeof(MyMaster_Index1000)/sizeof(MyMaster_Index1000[0]), 0x1000},
  { (subindex*)MyMaster_Index1001,sizeof(MyMaster_Index1001)/sizeof(MyMaster_Index1001[0]), 0x1001},
  { (subindex*)MyMaster_Index1005,sizeof(MyMaster_Index1005)/sizeof(MyMaster_Index1005[0]), 0x1005},
  { (subindex*)MyMaster_Index1006,sizeof(MyMaster_Index1006)/sizeof(MyMaster_Index1006[0]), 0x1006},
  { (subindex*)MyMaster_Index1017,sizeof(MyMaster_Index1017)/sizeof(MyMaster_Index1017[0]), 0x1017},
  { (subindex*)MyMaster_Index1018,sizeof(MyMaster_Index1018)/sizeof(MyMaster_Index1018[0]), 0x1018},
  { (subindex*)MyMaster_Index1280,sizeof(MyMaster_Index1280)/sizeof(MyMaster_Index1280[0]), 0x1280},
  { (subindex*)MyMaster_Index1400,sizeof(MyMaster_Index1400)/sizeof(MyMaster_Index1400[0]), 0x1400},
  { (subindex*)MyMaster_Index1600,sizeof(MyMaster_Index1600)/sizeof(MyMaster_Index1600[0]), 0x1600},
  { (subindex*)MyMaster_Index1800,sizeof(MyMaster_Index1800)/sizeof(MyMaster_Index1800[0]), 0x1800},
  { (subindex*)MyMaster_Index1A00,sizeof(MyMaster_Index1A00)/sizeof(MyMaster_Index1A00[0]), 0x1A00},
  { (subindex*)MyMaster_Index2000,sizeof(MyMaster_Index2000)/sizeof(MyMaster_Index2000[0]), 0x2000},
  { (subindex*)MyMaster_Index2001,sizeof(MyMaster_Index2001)/sizeof(MyMaster_Index2001[0]), 0x2001},
};

const indextable * MyMaster_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks)
{
	int i;
	*callbacks = NULL;
	switch(wIndex){
		case 0x1000: i = 0;break;
		case 0x1001: i = 1;break;
		case 0x1005: i = 2;*callbacks = MyMaster_Index1005_callbacks; break;
		case 0x1006: i = 3;*callbacks = MyMaster_Index1006_callbacks; break;
		case 0x1017: i = 4;*callbacks = MyMaster_Index1017_callbacks; break;
		case 0x1018: i = 5;break;
		case 0x1280: i = 6;break;
		case 0x1400: i = 7;break;
		case 0x1600: i = 8;break;
		case 0x1800: i = 9;*callbacks = MyMaster_Index1800_callbacks; break;
		case 0x1A00: i = 10;break;
		case 0x2000: i = 11;break;
		case 0x2001: i = 12;break;
		default:
			*errorCode = OD_NO_SUCH_OBJECT;
			return NULL;
	}
	*errorCode = OD_SUCCESSFUL;
	return &MyMaster_objdict[i];
}

/* 
 * To count at which received SYNC a PDO must be sent.
 * Even if no pdoTransmit are defined, at least one entry is computed
 * for compilations issues.
 */
s_PDO_status MyMaster_PDO_status[1] = {s_PDO_status_Initializer};

const quick_index MyMaster_firstIndex = {
  0, /* SDO_SVR */
  6, /* SDO_CLT */
  7, /* PDO_RCV */
  8, /* PDO_RCV_MAP */
  9, /* PDO_TRS */
  10 /* PDO_TRS_MAP */
};

const quick_index MyMaster_lastIndex = {
  0, /* SDO_SVR */
  6, /* SDO_CLT */
  7, /* PDO_RCV */
  8, /* PDO_RCV_MAP */
  9, /* PDO_TRS */
  10 /* PDO_TRS_MAP */
};

const UNS16 MyMaster_ObjdictSize = sizeof(MyMaster_objdict)/sizeof(MyMaster_objdict[0]); 

CO_Data MyMaster_Data = CANOPEN_NODE_DATA_INITIALIZER(MyMaster);

