/* Notices:
 *
 * Copyright 2018 United States Government as represented by the Administrator
 * of the National Aeronautics and Space Administration. All Rights Reserved.
 *
 * Disclaimers:
 *
 * No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY
 * OF ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT
 * LIMITED TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO
 * SPECIFICATIONS, ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE
 * SUBJECT SOFTWARE WILL BE ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF
 * PROVIDED, WILL CONFORM TO THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN
 * ANY MANNER, CONSTITUTE AN ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR
 * RECIPIENT OF ANY RESULTS, RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR
 * ANY OTHER APPLICATIONS RESULTING FROM USE OF THE SUBJECT SOFTWARE. FURTHER,
 * GOVERNMENT AGENCY DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING
 * THIRD-PARTY SOFTWARE, IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES
 * IT "AS IS."
 *
 * Waiver and Indemnity: RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
 * THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS
 * ANY PRIOR RECIPIENT. IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS IN
 * ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH USE,
 * INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM, RECIPIENT'S
 * USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD HARMLESS THE
 * UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS ANY
 * PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW. RECIPIENT'S SOLE REMEDY FOR
 * ANY SUCH MATTER SHALL BE THE IMMEDIATE, UNILATERAL TERMINATION OF THIS
 * AGREEMENT.
 */

/*=======================================================================================
** File Name:  cratous_app.h
**
** Title:  Header File for CRATOUS Application
**
** $Author:   Paul Coen & Winston Smith
** $Revision: 2.0 $
** $Date:     2018-06-14
**
** Purpose:  To define CRATOUS's internal macros, data types, global variables and
**           function prototypes
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2018-06-28 | Winston Smith | 2.0: Major Refactor of all I/O
**   2018-06-14 | Paul Coen | 1.0: Code Started
**
**=====================================================================================*/

#ifndef _CRATOUS_APP_H_
#define _CRATOUS_APP_H_

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L

#include "cratous_platform_cfg.h"
#include "cratous_mission_cfg.h"
#include "cratous_private_ids.h"
#include "cratous_private_types.h"
#include "cratous_perfids.h"
#include "cratous_msgids.h"
#include "cratous_msg.h"


// Defined includes for the CRATOUS module
#include <stdlib.h>
#include <unistd.h> //syscalls
#include <stdio.h> //I/O
#include <string.h> //string functions
#include <errno.h> //access to errno variable and related enums
#include <sys/types.h> //socket types
#include <sys/socket.h> //socket
#include <netinet/in.h> //internet communication
#include <arpa/inet.h> //internet communication
#include <pthread.h> //pthreads

//cfe Includes
#include "cfe.h"
#include "cfe_evs.h"
#include "cfe_error.h"
#include "cfe_sb.h"
#include "cfe_es.h"

#include "msgdef/ardupilot_msg.h"
#include "msgdef/trajectory_msg.h"
#include "msgids/ardupilot_msgids.h"
#include "msgids/trajectory_msgids.h"
#include "network_includes.h"

/*
** Local Defines
*/
#define CRATOUS_TIMEOUT_MSEC    1000

//#define DEBUG_MODE true

/*
** Local Structure Declarations
*/
typedef struct
{
    /* CFE Event table */
    CFE_EVS_BinFilter_t  EventTbl[CRATOUS_EVT_CNT];

    /* CFE scheduling pipe */
    CFE_SB_PipeId_t  SchPipeId;
    uint16           usSchPipeDepth;
    char             cSchPipeName[OS_MAX_API_NAME];

    /* CFE command pipe */
    CFE_SB_PipeId_t  CmdPipeId;
    uint16           usCmdPipeDepth;
    char             cCmdPipeName[OS_MAX_API_NAME];

    /* CFE telemetry pipe */
    CFE_SB_PipeId_t  TlmPipeId;
    uint16           usTlmPipeDepth;
    char             cTlmPipeName[OS_MAX_API_NAME];

    /* Task-related */
    uint32  uiRunStatus;

    /* ILoad table-related */
    CFE_TBL_Handle_t  ILoadTblHdl;
    CRATOUS_ILoadTblEntry_t*  ILoadTblPtr;

    /* Input data - from I/O devices or subscribed from other apps' output data.
       Data structure should be defined in cratous/fsw/src/cratous_private_types.h */
    CRATOUS_InData_t   InData;

    /* Output data - to be published at the end of a Wakeup cycle.
       Data structure should be defined in cratous/fsw/src/cratous_private_types.h */
    CRATOUS_OutData_t  OutData;

    /* Housekeeping telemetry - for downlink only.
       Data structure should be defined in cratous/fsw/src/cratous_msg.h */
    CRATOUS_HkTlm_t  HkTlm;

} CRATOUS_AppData_t;

/*
** Global Variables
*/

//Buffer to read core functionality messages into; must be equal
//to or greater than (max_message_length + 1) - max_message_length
//is defined in cratous_app.c
char messageBuffer[65536];

//Smaller buffer to read authentication handshake messages
char buffer[1000];

//Storage for the ICAROUS->UxAS thread of CRATOUS
pthread_t thread_id;

CFE_SB_PipeId_t messagePipe;

/*
** Local Function Prototypes
*/
int32  CRATOUS_InitApp(void);
int32  CRATOUS_InitEvent(void);
int32  CRATOUS_InitData(void);
int32  CRATOUS_InitPipe(void);

void  CRATOUS_AppMain(void);

void  CRATOUS_CleanupCallback(void);

int32  CRATOUS_RcvMsg(int32 iBlocking);

void  CRATOUS_ProcessNewData(void);
void  CRATOUS_ProcessNewCmds(void);
void  CRATOUS_ProcessNewAppCmds(CFE_SB_Msg_t*);

void  CRATOUS_ReportHousekeeping(void);
void  CRATOUS_SendOutData(void);

boolean  CRATOUS_VerifyCmdLength(CFE_SB_Msg_t*, uint16);

void *ICAROUS_listener(int *var);

//Messages to be published
flightplan_t         fpdata;
geofence_t           geodata;
position_t           postndata;
attitude_t           attdata;
object_t             objdata;
argsCmd_t            comndata;
missionItemReached_t wprchdata;

//Path planner integration messages
trajectory_request_t trajreqdata;

//Variables to help with in-place resets
geofence_t geodata_backup[64];
int wpreached;

#endif /* _CRATOUS_APP_H_ */

/*=======================================================================================
** End of file cratous_app.h
**=====================================================================================*/
