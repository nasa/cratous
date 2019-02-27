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
** File Name:  cratous_app.c
**
** Title:  Function Definitions for CRATOUS Application
**
** $Author:   Winston Smith & Paul Coen
** $Revision: 1.1 $
** $Date:      2018-06-14
**
** Purpose:  This source file contains all necessary function definitions to run CRATOUS
**           application.
**
** Functions Defined:
**    Function X - Brief purpose of function X
**    Function Y - Brief purpose of function Y
**    Function Z - Brief purpose of function Z
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to all functions in the file.
**    2. List the external source(s) and event(s) that can cause the funcs in this
**       file to execute.
**    3. List known limitations that apply to the funcs in this file.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2018-06-14 | Jane Doe | Build #: Code Started
**
**=====================================================================================*/

/*
** Pragmas
*/

/*
** Include Files
*/
#include <string.h>

#include "cratous_platform_cfg.h"
#include "cratous_mission_cfg.h"
#include "cratous_app.h"



/*
** Local Defines
*/

/*
** Local Structure Declarations
*/

/*
** External Global Variables
*/

/*
** Global Variables
*/
CRATOUS_AppData_t  g_CRATOUS_AppData;

/*
** Local Variables
*/

/*
** Local Function Definitions
*/

/*=====================================================================================
** Name: CRATOUS_InitEvent
**
** Purpose: To initialize and register event table for CRATOUS application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_EVS_Register
**    CFE_ES_WriteToSysLog
**
** Called By:
**    CRATOUS_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_CRATOUS_AppData.EventTbl
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 CRATOUS_InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Create the event table */
    memset((void*)g_CRATOUS_AppData.EventTbl, 0x00, sizeof(g_CRATOUS_AppData.EventTbl));

    g_CRATOUS_AppData.EventTbl[0].EventID = CRATOUS_RESERVED_EID;
    g_CRATOUS_AppData.EventTbl[1].EventID = CRATOUS_INF_EID;
    g_CRATOUS_AppData.EventTbl[2].EventID = CRATOUS_INIT_INF_EID;
    g_CRATOUS_AppData.EventTbl[3].EventID = CRATOUS_ILOAD_INF_EID;
    g_CRATOUS_AppData.EventTbl[4].EventID = CRATOUS_CDS_INF_EID;
    g_CRATOUS_AppData.EventTbl[5].EventID = CRATOUS_CMD_INF_EID;

    g_CRATOUS_AppData.EventTbl[ 6].EventID = CRATOUS_ERR_EID;
    g_CRATOUS_AppData.EventTbl[ 7].EventID = CRATOUS_INIT_ERR_EID;
    g_CRATOUS_AppData.EventTbl[ 8].EventID = CRATOUS_ILOAD_ERR_EID;
    g_CRATOUS_AppData.EventTbl[ 9].EventID = CRATOUS_CDS_ERR_EID;
    g_CRATOUS_AppData.EventTbl[10].EventID = CRATOUS_CMD_ERR_EID;
    g_CRATOUS_AppData.EventTbl[11].EventID = CRATOUS_PIPE_ERR_EID;
    g_CRATOUS_AppData.EventTbl[12].EventID = CRATOUS_MSGID_ERR_EID;
    g_CRATOUS_AppData.EventTbl[13].EventID = CRATOUS_MSGLEN_ERR_EID;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(g_CRATOUS_AppData.EventTbl,
                               CRATOUS_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CRATOUS - Failed to register with EVS (0x%08X)\n", iStatus);
    }

    return (iStatus);
}

/*=====================================================================================
** Name: CRATOUS_InitPipe
**
** Purpose: To initialize all message pipes and subscribe to messages for CRATOUS application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_SB_CreatePipe
**    CFE_SB_Subscribe
**    CFE_ES_WriteToSysLog
**
** Called By:
**    CRATOUS_InitApp
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_CRATOUS_AppData.usSchPipeDepth
**    g_CRATOUS_AppData.cSchPipeName
**    g_CRATOUS_AppData.SchPipeId
**    g_CRATOUS_AppData.usCmdPipeDepth
**    g_CRATOUS_AppData.cCmdPipeName
**    g_CRATOUS_AppData.CmdPipeId
**    g_CRATOUS_AppData.usTlmPipeDepth
**    g_CRATOUS_AppData.cTlmPipeName
**    g_CRATOUS_AppData.TlmPipeId
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 CRATOUS_InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe */
    g_CRATOUS_AppData.usSchPipeDepth = CRATOUS_SCH_PIPE_DEPTH;
    memset((void*)g_CRATOUS_AppData.cSchPipeName, '\0', sizeof(g_CRATOUS_AppData.cSchPipeName));
    strncpy(g_CRATOUS_AppData.cSchPipeName, "CRATOUS_SCH_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to Wakeup messages */
    iStatus = CFE_SB_CreatePipe(&g_CRATOUS_AppData.SchPipeId,
                                 g_CRATOUS_AppData.usSchPipeDepth,
                                 g_CRATOUS_AppData.cSchPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(CRATOUS_WAKEUP_MID, g_CRATOUS_AppData.SchPipeId, CFE_SB_Default_Qos, 1);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("CRATOUS - Sch Pipe failed to subscribe to CRATOUS_WAKEUP_MID. (0x%08X)\n", iStatus);
            goto CRATOUS_InitPipe_Exit_Tag;
        }

    }
    else
    {
        CFE_ES_WriteToSysLog("CRATOUS - Failed to create SCH pipe (0x%08X)\n", iStatus);
        goto CRATOUS_InitPipe_Exit_Tag;
    }

    /* Init command pipe */
    g_CRATOUS_AppData.usCmdPipeDepth = CRATOUS_CMD_PIPE_DEPTH ;
    memset((void*)g_CRATOUS_AppData.cCmdPipeName, '\0', sizeof(g_CRATOUS_AppData.cCmdPipeName));
    strncpy(g_CRATOUS_AppData.cCmdPipeName, "CRATOUS_CMD_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&g_CRATOUS_AppData.CmdPipeId,
                                 g_CRATOUS_AppData.usCmdPipeDepth,
                                 g_CRATOUS_AppData.cCmdPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(CRATOUS_CMD_MID, g_CRATOUS_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("CRATOUS - CMD Pipe failed to subscribe to CRATOUS_CMD_MID. (0x%08X)\n", iStatus);
            goto CRATOUS_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_Subscribe(CRATOUS_SEND_HK_MID, g_CRATOUS_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("CRATOUS - CMD Pipe failed to subscribe to CRATOUS_SEND_HK_MID. (0x%08X)\n", iStatus);
            goto CRATOUS_InitPipe_Exit_Tag;
        }

    }
    else
    {
        CFE_ES_WriteToSysLog("CRATOUS - Failed to create CMD pipe (0x%08X)\n", iStatus);
        goto CRATOUS_InitPipe_Exit_Tag;
    }

    /* Init telemetry pipe */
    g_CRATOUS_AppData.usTlmPipeDepth = CRATOUS_TLM_PIPE_DEPTH;
    memset((void*)g_CRATOUS_AppData.cTlmPipeName, '\0', sizeof(g_CRATOUS_AppData.cTlmPipeName));
    strncpy(g_CRATOUS_AppData.cTlmPipeName, "CRATOUS_TLM_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to telemetry messages on the telemetry pipe */
    iStatus = CFE_SB_CreatePipe(&g_CRATOUS_AppData.TlmPipeId,
                                 g_CRATOUS_AppData.usTlmPipeDepth,
                                 g_CRATOUS_AppData.cTlmPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        //create pipe for messages
        //ID, depth (how many messages the buffer can hold), name
        CFE_SB_CreatePipe(&messagePipe, 256, "CRATOUS_UXAS_PIPE");

        //ADD SUBSCRIPTIONS HERE
        CFE_SB_Subscribe(ICAROUS_COMMANDS_MID , messagePipe);
        CFE_SB_Subscribe(ICAROUS_TRAJECTORY_MID , messagePipe);
    }
    else
    {
        CFE_ES_WriteToSysLog("CRATOUS - Failed to create TLM pipe (0x%08X)\n", iStatus);
        goto CRATOUS_InitPipe_Exit_Tag;
    }

CRATOUS_InitPipe_Exit_Tag:
    return (iStatus);
}

/*=====================================================================================
** Name: CRATOUS_InitData
**
** Purpose: To initialize global variables used by CRATOUS application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_SB_InitMsg
**
** Called By:
**    CRATOUS_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_CRATOUS_AppData.InData
**    g_CRATOUS_AppData.OutData
**    g_CRATOUS_AppData.HkTlm
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 CRATOUS_InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init input data */
    memset((void*)&g_CRATOUS_AppData.InData, 0x00, sizeof(g_CRATOUS_AppData.InData));

    /* Init output data */
    memset((void*)&g_CRATOUS_AppData.OutData, 0x00, sizeof(g_CRATOUS_AppData.OutData));
    CFE_SB_InitMsg(&g_CRATOUS_AppData.OutData,
                   CRATOUS_OUT_DATA_MID, sizeof(g_CRATOUS_AppData.OutData), TRUE);

    /* Init housekeeping packet */
    memset((void*)&g_CRATOUS_AppData.HkTlm, 0x00, sizeof(g_CRATOUS_AppData.HkTlm));
    CFE_SB_InitMsg(&g_CRATOUS_AppData.HkTlm,
                   CRATOUS_HK_TLM_MID, sizeof(g_CRATOUS_AppData.HkTlm), TRUE);

    return (iStatus);
}

/*=====================================================================================
** Name: CRATOUS_InitApp
**
** Purpose: To initialize all data local to and used by CRATOUS application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_ES_RegisterApp
**    CFE_ES_WriteToSysLog
**    CFE_EVS_SendEvent
**    OS_TaskInstallDeleteHandler
**    CRATOUS_InitEvent
**    CRATOUS_InitPipe
**    CRATOUS_InitData
**
** Called By:
**    CRATOUS_AppMain
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 CRATOUS_InitApp()
{
    int32  iStatus=CFE_SUCCESS;

    g_CRATOUS_AppData.uiRunStatus = CFE_ES_APP_RUN;

    iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CRATOUS - Failed to register the app (0x%08X)\n", iStatus);
        goto CRATOUS_InitApp_Exit_Tag;
    }

    if ((CRATOUS_InitEvent() != CFE_SUCCESS) ||
        (CRATOUS_InitPipe()  != CFE_SUCCESS) ||
        (CRATOUS_InitData()  != CFE_SUCCESS))
    {
        iStatus = -1;
        goto CRATOUS_InitApp_Exit_Tag;
    }

    /* Install the cleanup callback */
    OS_TaskInstallDeleteHandler((void*)&CRATOUS_CleanupCallback);

CRATOUS_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CRATOUS_INIT_INF_EID, CFE_EVS_INFORMATION,
                          "CRATOUS - Application initialized");
    }
    else
    {
        CFE_ES_WriteToSysLog("CRATOUS - Application failed to initialize\n");
    }

    return (iStatus);
}

/*=====================================================================================
** Name: CRATOUS_CleanupCallback
**
** Purpose: To handle any neccesary cleanup prior to application exit
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    TBD
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void CRATOUS_CleanupCallback()
{
    pthread_join(thread_id, NULL);
    fprintf(stdout, "Rejoined thread!\n");
}

/*=====================================================================================
** Name: CRATOUS_RcvMsg
**
** Purpose: To receive and process messages for CRATOUS application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**    CFE_ES_PerfLogEntry
**    CFE_ES_PerfLogExit
**    CRATOUS_ProcessNewCmds
**    CRATOUS_ProcessNewData
**    CRATOUS_SendOutData
**
** Called By:
**    CRATOUS_Main
**
** Global Inputs/Reads:
**    g_CRATOUS_AppData.SchPipeId
**
** Global Outputs/Writes:
**    g_CRATOUS_AppData.uiRunStatus
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 CRATOUS_RcvMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(CRATOUS_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, g_CRATOUS_AppData.SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(CRATOUS_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
        {
            case CRATOUS_WAKEUP_MID:
                CRATOUS_ProcessNewCmds();
                CRATOUS_ProcessNewData();
                CRATOUS_SendOutData();
                break;

            default:
                CFE_EVS_SendEvent(CRATOUS_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "CRATOUS - Recvd invalid SCH msgId (0x%08X)", MsgId);
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* If there's no incoming message, you can do something here, or nothing */
    }
    else
    {
        /* This is an example of exiting on an error.
        ** Note that a SB read error is not always going to result in an app quitting.
        */
        CFE_EVS_SendEvent(CRATOUS_PIPE_ERR_EID, CFE_EVS_ERROR,
                          "CRATOUS: SB pipe read error (0x%08X), app will exit",
                          iStatus);
        g_CRATOUS_AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}

/*=====================================================================================
** Name: CRATOUS_ProcessNewData
**
** Purpose: To process incoming data subscribed by CRATOUS application
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**
** Called By:
**    CRATOUS_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    None
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void CRATOUS_ProcessNewData()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   TlmMsgPtr=NULL;
    CFE_SB_MsgId_t  TlmMsgId;

    /* Process telemetry messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&TlmMsgPtr, g_CRATOUS_AppData.TlmPipeId, CFE_SB_POLL);
        if (iStatus == CFE_SUCCESS)
        {
            TlmMsgId = CFE_SB_GetMsgId(TlmMsgPtr);
            switch (TlmMsgId)
            {
                default:
                    CFE_EVS_SendEvent(CRATOUS_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "CRATOUS - Recvd invalid TLM msgId (0x%08X)",
                                      TlmMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            CFE_EVS_SendEvent(CRATOUS_PIPE_ERR_EID, CFE_EVS_ERROR,
                              "CRATOUS: CMD pipe read error (0x%08X)",
                              iStatus);
            g_CRATOUS_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}

/*=====================================================================================
** Name: CRATOUS_ProcessNewCmds
**
** Purpose: To process incoming command messages for CRATOUS application
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**    CRATOUS_ProcessNewAppCmds
**    CRATOUS_ReportHousekeeping
**
** Called By:
**    CRATOUS_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    None
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void CRATOUS_ProcessNewCmds()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;

    /* Process command messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, g_CRATOUS_AppData.CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case CRATOUS_CMD_MID:
                    CRATOUS_ProcessNewAppCmds(CmdMsgPtr);
                    break;

                case CRATOUS_SEND_HK_MID:
                    CRATOUS_ReportHousekeeping();
                    break;

                default:
                    CFE_EVS_SendEvent(CRATOUS_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "CRATOUS - Recvd invalid CMD msgId (0x%08X)",
                                      CmdMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            CFE_EVS_SendEvent(CRATOUS_PIPE_ERR_EID, CFE_EVS_ERROR,
                              "CRATOUS: CMD pipe read error (0x%08X)",
                              iStatus);
            g_CRATOUS_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}

/*=====================================================================================
** Name: CRATOUS_ProcessNewAppCmds
**
** Purpose: To process command messages targeting CRATOUS application
**
** Arguments:
**    CFE_SB_Msg_t*  MsgPtr - new command message pointer
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_GetCmdCode
**    CFE_EVS_SendEvent
**
** Called By:
**    CRATOUS_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_CRATOUS_AppData.HkTlm.usCmdCnt
**    g_CRATOUS_AppData.HkTlm.usCmdErrCnt
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void CRATOUS_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case CRATOUS_NOOP_CC:
                g_CRATOUS_AppData.HkTlm.usCmdCnt++;
                CFE_EVS_SendEvent(CRATOUS_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "CRATOUS - Recvd NOOP cmd (%d)", uiCmdCode);
                break;

            case CRATOUS_RESET_CC:
                g_CRATOUS_AppData.HkTlm.usCmdCnt = 0;
                g_CRATOUS_AppData.HkTlm.usCmdErrCnt = 0;
                CFE_EVS_SendEvent(CRATOUS_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "CRATOUS - Recvd RESET cmd (%d)", uiCmdCode);
                break;

            default:
                g_CRATOUS_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(CRATOUS_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "CRATOUS - Recvd invalid cmdId (%d)", uiCmdCode);
                break;
        }
    }
}

/*=====================================================================================
** Name: CRATOUS_ReportHousekeeping
**
** Purpose: To send housekeeping message
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    CRATOUS_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  GSFC, Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void CRATOUS_ReportHousekeeping()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&g_CRATOUS_AppData.HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_CRATOUS_AppData.HkTlm);
}

/*=====================================================================================
** Name: CRATOUS_SendOutData
**
** Purpose: To publish 1-Wakeup cycle output data
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    CRATOUS_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void CRATOUS_SendOutData()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&g_CRATOUS_AppData.OutData);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_CRATOUS_AppData.OutData);
}

/*=====================================================================================
** Name: CRATOUS_VerifyCmdLength
**
** Purpose: To verify command length for a particular command message
**
** Arguments:
**    CFE_SB_Msg_t*  MsgPtr      - command message pointer
**    uint16         usExpLength - expected command length
**
** Returns:
**    boolean bResult - result of verification
**
** Routines Called:
**    TBD
**
** Called By:
**    CRATOUS_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Jane Doe
**
** History:  Date Written  2018-06-14
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
boolean CRATOUS_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
                           uint16 usExpectedLen)
{
    boolean bResult=FALSE;
    uint16  usMsgLen=0;

    if (MsgPtr != NULL)
    {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen)
        {
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            CFE_EVS_SendEvent(CRATOUS_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "CRATOUS - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            g_CRATOUS_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}

/*=====================================================================================
** Name: CRATOUS_AppMain
**
** Purpose: To define CRATOUS application's entry point and main process loop
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_ES_RegisterApp
**    CFE_ES_RunLoop
**    CFE_ES_PerfLogEntry
**    CFE_ES_PerfLogExit
**    CFE_ES_ExitApp
**    CFE_ES_WaitForStartupSync
**    CRATOUS_InitApp
**    CRATOUS_RcvMsg
**
** Called By:
**    Executive Services via Cratous_AppInit()
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    None
**
** Limitations, Assumptions, External Events, and Notes:
**    1. Assumption: Format of messages is either cFS or follows a convention (described below) with labels and fields
**
** Algorithm:
**    Main thread: Read in message from UxAS, translate to cFS, and publish to ICAROUS
**    Pthread: Read messages from cFS, translate to LMCP, and send across socket to UxAS
**
** Author(s):  Winston Smith & Paul Coen
**
** History:    2018-06-28 major refactor of all I/O, upgrade to version 2.0
**             2018-06-14 initial version
**
**=====================================================================================*/

//Message Convention
/*
 * Messages given to CRATOUS via the socket must be in a certain format, namely:
 * (as a Cstring) "<message type name><field name><field>," with any number of fields.
 * Additionally, you must define a handler for the message in the section below the tag
 * "//Start of message type picking".
 * The handler will have to find a given Cstring in the start of your message, which should
 * be a unique 5-letter identifier at the beginning of the message (e.g. should fill the
 * <message type name> field specified above).
 */

#define PORT 5557

void CRATOUS_AppMain()
{
    //Constants for protocol exchange with UxAS
    //strlen(sharedSecret) should be greater than or equal to strlen(longest of these constants)
    const char *protocol = "ICAROUS-UxAS_LMCP";
    const char *ok = "ok ";
    const char *sharedSecret = "28a4b77b86aa32715e4c271415b28447b8c08d704fd9ffb1258bced7b7167fe0";

    //Maximum size a message can be: should be equal to (socket buffer size - 1)
    const int max_message_length = 65535;

    //IPv4 address to connect to (currently loopback to connect to UxAS on the same machine)
    const char *ipAdd = "127.0.0.1";

    /* Register the application with Executive Services */
    CFE_ES_RegisterApp();

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(CRATOUS_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (CRATOUS_InitApp() != CFE_SUCCESS)
    {
        g_CRATOUS_AppData.uiRunStatus = CFE_ES_APP_ERROR;
    } else {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(CRATOUS_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(CRATOUS_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(CRATOUS_MAIN_TASK_PERF_ID);
    }

    //Necessary variables to set up networking
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;

    //Begin setup of UxAS socket as TCP
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    fprintf(stdout,"CRATOUS: Socket File Descriptor at initialization is: %i\n", sockfd);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ipAdd);
    address.sin_port = htons(PORT); //Deal with endianness issues
    len = sizeof(address);

    //Connect to UxAS
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if(result == -1){
        fprintf(stderr, "CRATOUS: Error, could not connect to UxAS!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }


    //Begin 3-way authentication handshake with UxAS
    char buffer[strlen(sharedSecret) + 1];
    buffer[strlen(sharedSecret)] = '\0';

    //Read the protocol name
    if(read(sockfd, buffer, strlen(protocol)) <= 0){
        fprintf(stderr, "CRATOUS: Error, could not read communication protocol name from UxAS!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buffer[strlen(protocol)] = '\0'; //Null bytes are not sent across sockets

    //Make sure we received the correct protocol name
    if(strcmp(buffer, protocol)){ //strcmp==true indicates the strings are different
        fprintf(stderr, "CRATOUS: Error, UxAS sent wrong protocol name!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    //Write the password
    if(write(sockfd, sharedSecret, strlen(sharedSecret)) <= 0){
        fprintf(stderr, "CRATOUS: Error, password could not be sent to UxAS!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    //Read the confirmation
    if(read(sockfd, buffer, strlen(ok)) <= 0){
        fprintf(stderr, "CRATOUS: Error, could not read confirmation from UxAS!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[strlen(ok)] = '\0'; //Null bytes are not sent across sockets

    //Check to make sure we actually received "ok "
    if(strcmp(buffer, ok)){ //strcmp==true indicates the strings are different
        fprintf(stderr, "CRATOUS: Error, UxAS rejected password!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    //start a new thread to listen to ICAROUS and send UxAS messages
    int *pthread_arg = malloc(sizeof(int));
    *pthread_arg = sockfd;
    pthread_create(&thread_id, NULL, (void *)ICAROUS_listener, pthread_arg);

    //Initialize messages
    CFE_SB_InitMsg(&fpdata, ICAROUS_FLIGHTPLAN_MID, sizeof(fpdata), TRUE);
    CFE_SB_InitMsg(&geodata, ICAROUS_GEOFENCE_MID, sizeof(geodata), TRUE);

    while (CFE_ES_RunLoop(&g_CRATOUS_AppData.uiRunStatus) == TRUE)
    {
        //Begin communication protocol: read input from UxAS

        //Variable declarations and errno reset
        messageBuffer[0] = '\0';
        int nread = max_message_length;
        int bytesReceived = 0;
        errno = 0;

        //The DEBUG_MODE #define is located in the .h for this file. Simply uncomment it to see all the debug messages (there are a lot)
        #ifdef DEBUG_MODE
        fprintf(stdout, "CRATOUS: Reading from sockfd: %i\n", sockfd);
        #endif

        //Read any messages UxAS has posted
        while(nread == max_message_length && !errno){
            nread = read(sockfd, messageBuffer, max_message_length);
            if(nread < 0){
                fprintf(stderr, "CRATOUS: Nonfatal: error in socket read");
                nread = 0;
            }
            bytesReceived += nread;
        }
        messageBuffer[bytesReceived] = '\0'; //makes sure we never segfault

        #ifdef DEBUG_MODE
        fprintf(stdout, "CRATOUS: Bytes received: %i\n", bytesReceived);
        fprintf(stdout, "CRATOUS: Full message:\n%s", messageBuffer);
        #endif

        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        //Start of message type picking
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        char *tempMessageBuffer = messageBuffer;
        static int geoIndex = 0; //used to indicate how many geofences we have

        //Since we cut off processed substrings from the beginning of messageBuffer as we process
        //them, this "while" condition simply means "while there are more messages to process".
        //Remember, many messages can be (and usually are) received with each read() call
        while(strlen(tempMessageBuffer)){

            //Necessary variables
            char *fieldEnd; //used to point to the ',' delimiter directly after a field's value
            char throwaway[400]; //used simply to fill necessary (but useless) arguments in function calls. Must be longer than the maximum length of a single message, (~100)
            int fieldLength; //used to store the length of a field's value
            char *trackingHelper; //used to point to the beginning of a field's value

            if(!strncmp(tempMessageBuffer, "WAYPT", 5)){ //waypoints (flightplan_t)
                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: waypoint message received!\n");
                #endif

                //The following section of code finds several fields by their tags.
                //It's fairly difficult to follow, so here's a comment section explaining each line.
                //Each line of this explanation corresponds to the same line of code in each block.
                /* 1. strstr returns a pointer to the first occurence of our tag in the message
                 * 2. Use pointer arithmetic to skip past the tag
                 * 3. Find the end of the field (they're variable length) using the ',' delimiter
                 * 4. Get the length of the field via pointer arithmetic (end minus beginning)
                 * 5. Convert the field to a usable number and store it into the message to be published to cFS
                 */
                //Note: We tried to functionize this code. We spent 4 hours and had the strangest
                //issue we've ever seen, with a passed-in pointer being valid memory to access before
                //calling the function, and invalid after. We're unsure what the cause was.

                //Total # of waypoints
                trackingHelper       = strstr(tempMessageBuffer, "total");
                trackingHelper      += 5; //skip past "total"
                fieldEnd             = strchr(trackingHelper, ',');
                fieldLength          = fieldEnd - trackingHelper;
                fpdata.num_waypoints = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //This waypoint's ID
                trackingHelper  = strstr(tempMessageBuffer, "index");
                trackingHelper += 5; //skip past "index"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                int index       = atof(strncpy(throwaway, trackingHelper, fieldLength));

                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: fpdata|wayPointIndex|%i\n", index);
                #endif

                //Latitude for this waypoint
                trackingHelper                   = strstr(tempMessageBuffer, "lat");
                trackingHelper                  += 3; //skip past "lat"
                fieldEnd                         = strchr(trackingHelper, ',');
                fieldLength                      = fieldEnd - trackingHelper;
                fpdata.waypoints[index].latitude = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Longitude for this waypoint
                trackingHelper                    = strstr(tempMessageBuffer, "long");
                trackingHelper                   += 4; //skip past "long"
                fieldEnd                          = strchr(trackingHelper, ',');
                fieldLength                       = fieldEnd - trackingHelper;
                fpdata.waypoints[index].longitude = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Altitude for the waypoint in meters MSL
                trackingHelper                   = strstr(tempMessageBuffer, "alt");
                trackingHelper                  += 3; //skip past "alt"
                fieldEnd                         = strchr(trackingHelper, ',');
                fieldLength                      = fieldEnd - trackingHelper;
                fpdata.waypoints[index].altitude = atof(strncpy(throwaway, trackingHelper, fieldLength));


                fpdata.waypoints[index].wp_metric = 1; //speed
                //Speed to maintain between the previous waypoint and this one
                trackingHelper                   = strstr(tempMessageBuffer, "speed");
                trackingHelper                  += 5; //skip past "speed"
                fieldEnd                         = strchr(trackingHelper, ',');
                fieldLength                      = fieldEnd - trackingHelper;
                fpdata.waypoints[index].value_to_next_wp = atof(strncpy(throwaway, trackingHelper, fieldLength));

                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: fpdata|totalWaypoints|%i\n", fpdata.totalWayPoints);
                fprintf(stdout, "CRATOUS: fpdata|wayPointIndex|%i\n", index);
                fprintf(stdout, "CRATOUS: fpdata|latitude|%f\n", fpdata.position[index][0]);
                fprintf(stdout, "CRATOUS: fpdata|longitude|%f\n", fpdata.position[index][1]);
                fprintf(stdout, "CRATOUS: fpdata|altitude|%f\n", fpdata.position[index][2]);
                fprintf(stdout, "CRATOUS: fpdata|speed|%f\n", fpdata.speed[index]);
                #endif

                //Cut off the processed part of tempMessageBuffer using pointer arithmetic
                fieldEnd = strchr(tempMessageBuffer, '\n');
                tempMessageBuffer = fieldEnd;
                tempMessageBuffer++;

            }else if(!strncmp(tempMessageBuffer, "GEOFN", 5)){ //Keep-in / Keep-out Zones (geofence_t)
                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: geofence vertex message received!\n");
                #endif

                //This code follows essentially the same logic as for WAYPT; please
                //see that section for a guide on how to read this section

                //The major change in  this section is that each piece of information
                //is backed up into geodata_backup so that we can restore the geofences
                //whenever a soft reset command is received

                //Index of the geofence this vertex should be attached to
                /* TODO: allow vertices to be attached to geofences in any order.
                 * Currently, it's assumed everywhere in this code that once a
                 * geofence is started, it will be finished before moving to the
                 * next one.
                 */
                trackingHelper  = strstr(tempMessageBuffer, "index");
                trackingHelper += 5; //skip past "index"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                geodata.index   = atof(strncpy(throwaway, trackingHelper, fieldLength));
                geodata.index--;
                geodata_backup[geodata.index].index = geodata.index;

                //Geofence type - KEEPIN or KEEPOUT
                trackingHelper  = strstr(tempMessageBuffer, "type");
                trackingHelper += 4; //skip past "type"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                if(!strncmp(trackingHelper, "_KEEPIN_", strlen("_KEEPIN_"))){
                    geodata.type = _KEEPIN_;
                    geodata_backup[geodata.index].type = _KEEPIN_;
                }
                else if(!strncmp(trackingHelper, "_KEEPOUT_", strlen("_KEEPOUT_"))){
                    geodata.type = _KEEPOUT_;
                    geodata_backup[geodata.index].type = _KEEPOUT_;
                }

                //Total vertices in this geofence
                trackingHelper  = strstr(tempMessageBuffer, "totalvert");
                trackingHelper += 9; //skip past "totalvert"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                geodata.totalvertices = atof(strncpy(throwaway, trackingHelper, fieldLength));
                geodata_backup[geodata.index].totalvertices = geodata.totalvertices;

                //Index of this vertex
                trackingHelper  = strstr(tempMessageBuffer, "vertIndex");
                trackingHelper += 9; //skip past "vertIndex"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                int vertexIndex = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //We'll be using vertexIndex as an array index, and it was passed in as an ID,
                //so we need to decrement to be accurate
                vertexIndex--;

                //Latitude of this vertex
                trackingHelper  = strstr(tempMessageBuffer, "lat");
                trackingHelper += 3; //skip past "lat"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                geodata.vertices[vertexIndex][0] = atof(strncpy(throwaway, trackingHelper, fieldLength));
                geodata_backup[geodata.index].vertices[vertexIndex][0] = geodata.vertices[vertexIndex][0];

                //Longitude of this vertex
                trackingHelper  = strstr(tempMessageBuffer, "long");
                trackingHelper += 4; //skip past "long"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                geodata.vertices[vertexIndex][1] = atof(strncpy(throwaway, trackingHelper, fieldLength));
                geodata_backup[geodata.index].vertices[vertexIndex][1] = geodata.vertices[vertexIndex][1];

                //Floor of the geofence in meters MSL
                trackingHelper  = strstr(tempMessageBuffer, "floor");
                trackingHelper += 5; //skip past "floor"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                geodata.floor   = atof(strncpy(throwaway, trackingHelper, fieldLength));
                geodata_backup[geodata.index].floor = geodata.floor;

                //Ceiling of the geofence in meters MSL
                trackingHelper  = strstr(tempMessageBuffer, "ceil");
                trackingHelper += 4; //skip past "ceil"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                geodata.ceiling = atof(strncpy(throwaway, trackingHelper, fieldLength));
                geodata_backup[geodata.index].ceiling = geodata.ceiling;

                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: GEODATA|type|%i\n", geodata.type);
                fprintf(stdout, "CRATOUS: GEODATA|totalvertices|%i\n", geodata.totalvertices);
                fprintf(stdout, "CRATOUS: GEODATA|vertexIndex|%i\n", vertexIndex);
                fprintf(stdout, "CRATOUS: GEODATA|latitude|%f\n", geodata.vertices[vertexIndex][0]);
                fprintf(stdout, "CRATOUS: GEODATA|longitude|%f\n", geodata.vertices[vertexIndex][1]);
                fprintf(stdout, "CRATOUS: GEODATA|floor|%f\n", geodata.floor);
                fprintf(stdout, "CRATOUS: GEODATA|ceiling|%f\n", geodata.ceiling);
                fprintf(stdout, "CRATOUS: GEODATA|index|%i\n", geodata.index);
                #endif

                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: GEODATA-backup|type|%i\n", geodata.type);
                fprintf(stdout, "CRATOUS: GEODATA-backup|totalvertices|%i\n", geodata.totalvertices);
                fprintf(stdout, "CRATOUS: GEODATA-backup|vertexIndex|%i\n", vertexIndex);
                fprintf(stdout, "CRATOUS: GEODATA-backup|latitude|%f\n", geodata.vertices[vertexIndex][0]);
                fprintf(stdout, "CRATOUS: GEODATA-backup|longitude|%f\n", geodata.vertices[vertexIndex][1]);
                fprintf(stdout, "CRATOUS: GEODATA-backup|floor|%f\n", geodata.floor);
                fprintf(stdout, "CRATOUS: GEODATA-backup|ceiling|%f\n", geodata.ceiling);
                fprintf(stdout, "CRATOUS: GEODATA-backup|index|%i\n", geodata.index);
                #endif

                //Cut off the processed part of tempMessageBuffer using pointer arithmetic
                fieldEnd = strchr(tempMessageBuffer, '\n');
                tempMessageBuffer = fieldEnd;
                tempMessageBuffer++;

            }else if(!strncmp(tempMessageBuffer, "POSTN", 5)){ //heartbeat part 1 (position_t)
                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: position_t message received!\n");
                #endif

                //This code follows essentially the same logic as for WAYPT; please
                //see that section for a guide on how to read this section

                CFE_SB_InitMsg(&postndata, ICAROUS_POSITION_MID, sizeof(postndata), TRUE);

                //Time after mission start in decimal seconds
                trackingHelper      = strstr(tempMessageBuffer, "timegps");
                trackingHelper     += 7; //skip past "timegps"
                fieldEnd            = strchr(trackingHelper, ',');
                fieldLength         = fieldEnd - trackingHelper;
                postndata.time_gps  = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Current latitude of the UAV belonging to this ICAROUS instance
                trackingHelper      = strstr(tempMessageBuffer, "lat");
                trackingHelper     += 3; //skip past "lat"
                fieldEnd            = strchr(trackingHelper, ',');
                fieldLength         = fieldEnd - trackingHelper;
                postndata.latitude  = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Current longitude of the UAV belonging to this ICAROUS instance
                trackingHelper      = strstr(tempMessageBuffer, "long");
                trackingHelper     += 4; //skip past "long"
                fieldEnd            = strchr(trackingHelper, ',');
                fieldLength         = fieldEnd - trackingHelper;
                postndata.longitude = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //MSL altitude in meters of the UAV belonging to this ICAROUS instance
                trackingHelper      = strstr(tempMessageBuffer, "altabs");
                trackingHelper     += 6; //skip past "altabs"
                fieldEnd            = strchr(trackingHelper, ',');
                fieldLength         = fieldEnd - trackingHelper;
                postndata.altitude_abs = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //AGL altitude in meters of the UAV belonging to this ICAROUS instance
                trackingHelper      = strstr(tempMessageBuffer, "altrel");
                trackingHelper     += 6; //skip past "altrel"
                fieldEnd            = strchr(trackingHelper, ',');
                fieldLength         = fieldEnd - trackingHelper;
                postndata.altitude_rel = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //North velocity in meters per second of the UAV belonging to this ICAROUS instance
                trackingHelper      = strstr(tempMessageBuffer, "north");
                trackingHelper     += 5; //skip past "north"
                fieldEnd            = strchr(trackingHelper, ',');
                fieldLength         = fieldEnd - trackingHelper;
                postndata.vn        = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //East velocity in meters per second of the UAV belonging to this ICAROUS instance
                trackingHelper      = strstr(tempMessageBuffer, "east");
                trackingHelper     += 4; //skip past "east"
                fieldEnd            = strchr(trackingHelper, ',');
                fieldLength         = fieldEnd - trackingHelper;
                postndata.ve        = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Down velocity in meters per second of the UAV belonging to this ICAROUS instance
                trackingHelper      = strstr(tempMessageBuffer, "down");
                trackingHelper     += 4; //skip past "down"
                fieldEnd            = strchr(trackingHelper, ',');
                fieldLength         = fieldEnd - trackingHelper;
                postndata.vd        = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Vertical velocity is passed in as "positive up, negative down," but ICAROUS
                //uses "positive down, negative up," so we need to adjust the value
                postndata.vd *= -1;

                //Horizontal position accuracy for the UAV belonging to this ICAROUS instance
                trackingHelper      = strstr(tempMessageBuffer, "hdop");
                trackingHelper     += 4; //skip past "hdop"
                fieldEnd            = strchr(trackingHelper, ',');
                fieldLength         = fieldEnd - trackingHelper;
                postndata.hdop      = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Vertical position accuracy for the UAV belonging to this ICAROUS instance
                trackingHelper      = strstr(tempMessageBuffer, "vdop");
                trackingHelper     += 4; //skip past "vdop"
                fieldEnd            = strchr(trackingHelper, ',');
                fieldLength         = fieldEnd - trackingHelper;
                postndata.vdop      = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Number of satellites feeding positional data to the UAV belonging to this ICAROUS instance
                trackingHelper      = strstr(tempMessageBuffer, "numsats");
                trackingHelper     += 7; //skip past "numsats"
                fieldEnd            = strchr(trackingHelper, ',');
                fieldLength         = fieldEnd - trackingHelper;
                postndata.numSats   = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //ID of the UAV belonging to this ICAROUS instance
                postndata.aircraft_id = CFE_PSP_GetSpacecraftId();


                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: POSTNDATA|aircraft_id|%i\n", postndata.aircraft_id);
                fprintf(stdout, "CRATOUS: POSTNDATA|time_gps|%f\n", postndata.time_gps);
                fprintf(stdout, "CRATOUS: POSTNDATA|latitude|%f\n", postndata.latitude);
                fprintf(stdout, "CRATOUS: POSTNDATA|longitude|%f\n", postndata.longitude);
                fprintf(stdout, "CRATOUS: POSTNDATA|altitude_abs|%f\n", postndata.altitude_abs);
                fprintf(stdout, "CRATOUS: POSTNDATA|altitude_rel|%f\n", postndata.altitude_rel);
                fprintf(stdout, "CRATOUS: POSTNDATA|vn|%f\n", postndata.vn);
                fprintf(stdout, "CRATOUS: POSTNDATA|ve|%f\n", postndata.ve);
                fprintf(stdout, "CRATOUS: POSTNDATA|vd|%f\n", postndata.vd);
                fprintf(stdout, "CRATOUS: POSTNDATA|hdop|%f\n", postndata.hdop);
                fprintf(stdout, "CRATOUS: POSTNDATA|vdop|%f\n", postndata.vdop);
                fprintf(stdout, "CRATOUS: POSTNDATA|numSats|%i\n", postndata.numSats);
                #endif

                //Send the constructed message to the rest of ICAROUS
                CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &postndata);
                CFE_SB_SendMsg((CFE_SB_Msg_t *) &postndata);

                //Cut off the processed part of tempMessageBuffer using pointer arithmetic
                fieldEnd = strchr(tempMessageBuffer, '\n');
                tempMessageBuffer = fieldEnd;
                tempMessageBuffer++;

            }else if(!strncmp(tempMessageBuffer, "ATTUD", 5)){ //heartbeat part 2 (attitude_t)
                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: attitude_t message received!\n");
                #endif

                //This code follows essentially the same logic as for WAYPT; please
                //see that section for a guide on how to read this section

                CFE_SB_InitMsg(&attdata, ICAROUS_ATTITUDE_MID, sizeof(attdata), TRUE);

                //Current roll in degrees per second for the UAV belonging to this ICAROUS instance
                trackingHelper  = strstr(tempMessageBuffer, "roll");
                trackingHelper += 4; //skip past "roll"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                attdata.roll    = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Current pitch in degrees per second for the UAV belonging to this ICAROUS instance
                trackingHelper  = strstr(tempMessageBuffer, "pitch");
                trackingHelper += 5; //skip past "pitch"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                attdata.pitch   = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Current yaw in degrees per second for the UAV belonging to this ICAROUS instance
                trackingHelper  = strstr(tempMessageBuffer, "yaw");
                trackingHelper += 3; //skip past "yaw"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                attdata.yaw     = atof(strncpy(throwaway, trackingHelper, fieldLength));


                //Cut off the processed part of tempMessageBuffer using pointer arithmetic
                fieldEnd = strchr(tempMessageBuffer, '\n');
                tempMessageBuffer = fieldEnd;
                tempMessageBuffer++;

                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: ATTDATA|roll|%f\n", attdata.roll);
                fprintf(stdout, "CRATOUS: ATTDATA|pitch|%f\n", attdata.pitch);
                fprintf(stdout, "CRATOUS: ATTDATA|yaw|%f\n", attdata.yaw);
                #endif

                //Send the constructed message to the rest of ICAROUS
                CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &attdata);
                CFE_SB_SendMsg((CFE_SB_Msg_t *) &attdata);

            }else if(!strncmp(tempMessageBuffer, "OBJCT", 5)){ //heartbeat part 3 (object_t)
                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: object_t message received!\n");
                #endif

                //This code follows essentially the same logic as for WAYPT; please
                //see that section for a guide on how to read this section

                CFE_SB_InitMsg(&objdata, ICAROUS_TRAFFIC_MID, sizeof(objdata), TRUE);

                //Type of entity being sent: TRAFFIC (other aircraft) or OBSTACLE (physical object, e.g. a mountain)
                trackingHelper        = strstr(tempMessageBuffer, "type");
                trackingHelper       += 4; //skip past "type"
                fieldEnd              = strchr(trackingHelper, ',');
                fieldLength           = fieldEnd - trackingHelper;
                if(!strncmp(trackingHelper, "_TRAFFIC_", strlen("_TRAFFIC_"))){
                    objdata.type      = _TRAFFIC_;
                }
                else if(!strncmp(trackingHelper, "_OBSTACLE_", strlen("_OBSTACLE_"))){
                    objdata.type      = _OBSTACLE_;
                }

                //Current latitude of the entity
                trackingHelper        = strstr(tempMessageBuffer, "lat");
                trackingHelper       += 3; //skip past "lat"
                fieldEnd              = strchr(trackingHelper, ',');
                fieldLength           = fieldEnd - trackingHelper;
                objdata.latitude      = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Current longitude of the entity
                trackingHelper        = strstr(tempMessageBuffer, "long");
                trackingHelper       += 4; //skip past "long"
                fieldEnd              = strchr(trackingHelper, ',');
                fieldLength           = fieldEnd - trackingHelper;
                objdata.longitude     = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Current altitude in meters MSL of the entity
                trackingHelper        = strstr(tempMessageBuffer, "alt");
                trackingHelper       += 3; //skip past "alt"
                fieldEnd              = strchr(trackingHelper, ',');
                fieldLength           = fieldEnd - trackingHelper;
                objdata.altitude      = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //North velocity in meters per second for the entity
                trackingHelper        = strstr(tempMessageBuffer, "north");
                trackingHelper       += 5; //skip past "north"
                fieldEnd              = strchr(trackingHelper, ',');
                fieldLength           = fieldEnd - trackingHelper;
                objdata.vn            = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //East velocity in meters per second for the entity
                trackingHelper        = strstr(tempMessageBuffer, "east");
                trackingHelper       += 4; //skip past "east"
                fieldEnd              = strchr(trackingHelper, ',');
                fieldLength           = fieldEnd - trackingHelper;
                objdata.ve            = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Down velocity in meters per second for the entity
                trackingHelper        = strstr(tempMessageBuffer, "down");
                trackingHelper       += 4; //skip past "down"
                fieldEnd              = strchr(trackingHelper, ',');
                fieldLength           = fieldEnd - trackingHelper;
                objdata.vd            = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Vertical velocity is passed in as "positive up, negative down," but ICAROUS
                //uses "positive down, negative up," so we need to adjust the value
                postndata.vd *= -1;

                //Index of the entity
                trackingHelper        = strstr(tempMessageBuffer, "index");
                trackingHelper       += 5; //skip past "index"
                fieldEnd              = strchr(trackingHelper, ',');
                fieldLength           = fieldEnd - trackingHelper;
                objdata.index         = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Cut off the processed part of tempMessageBuffer using pointer arithmetic
                fieldEnd = strchr(tempMessageBuffer, '\n');
                tempMessageBuffer = fieldEnd;
                tempMessageBuffer++;

                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: OBJDATA|type|%i\n", objdata.type);
                fprintf(stdout, "CRATOUS: OBJDATA|index|%i\n", objdata.index);
                fprintf(stdout, "CRATOUS: OBJDATA|latitude|%f\n", objdata.latitude);
                fprintf(stdout, "CRATOUS: OBJDATA|longitude|%f\n", objdata.longitude);
                fprintf(stdout, "CRATOUS: OBJDATA|altitude|%f\n", objdata.altitude);
                fprintf(stdout, "CRATOUS: OBJDATA|vn|%f\n", objdata.vn);
                fprintf(stdout, "CRATOUS: OBJDATA|ve|%f\n", objdata.ve);
                fprintf(stdout, "CRATOUS: OBJDATA|vd|%f\n", objdata.vd);
                #endif

                //Send the constructed message to the rest of ICAROUS
                CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &objdata);
                CFE_SB_SendMsg((CFE_SB_Msg_t *) &objdata);

            }else if(!strncmp(tempMessageBuffer, "WPRCH", 5)){ //A given waypoint has been reached and should no longer be considered
                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: WPRCH message received!\n");
                #endif

                //This code follows essentially the same logic as for WAYPT; please
                //see that section for a guide on how to read this section

                //This variable is only needed for in-place resets; see that section for what it does/means
                wpreached++;

                CFE_SB_InitMsg(&wprchdata, ICAROUS_WPREACHED_MID, sizeof(wprchdata), TRUE);

                //ID of the waypoint that has been reached
                trackingHelper            = strstr(tempMessageBuffer, "id");
                trackingHelper           += 2; //skip past "id"
                fieldEnd                  = strchr(trackingHelper, ',');
                fieldLength               = fieldEnd - trackingHelper;
                wprchdata.reachedwaypoint = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Message is ignored if this is not set
                wprchdata.feedback = TRUE;

                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: WPRCH|id|%i\n", wprchdata.reachedwaypoint);
                #endif

                //Cut off the processed part of tempMessageBuffer using pointer arithmetic
                fieldEnd = strchr(tempMessageBuffer, '\n');
                tempMessageBuffer = fieldEnd;
                tempMessageBuffer++;

                //Send the constructed message to the rest of ICAROUS
                CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &wprchdata);
                CFE_SB_SendMsg((CFE_SB_Msg_t *) &wprchdata);

            }else if(!strncmp(tempMessageBuffer, "COMND", 5)){ //command message from UxAS (e.g. "mission start")
                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: command message received!\n");
                #endif

                //Determine the type of command received
                trackingHelper  = strstr(tempMessageBuffer, "type");
                trackingHelper += 4; //skip past "type"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;

                if(!strncmp(trackingHelper, "START_MISSION", strlen("START_MISSION"))){ //Start the mission
                    //Send flight plan
                    fpdata.id[0] = 'U';
                    fpdata.id[1] = 'x';
                    fpdata.id[2] = 'A';
                    fpdata.id[3] = 'S';
                    fpdata.id[4] = 'p';
                    fpdata.id[5] = 'l';
                    fpdata.id[6] = 'a';
                    fpdata.id[7] = 'n';

                    //Send the constructed flight plan message for this UAV to the rest of ICAROUS
                    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &fpdata);
                    CFE_SB_SendMsg((CFE_SB_Msg_t *) &fpdata);

                    //Start mission
                    CFE_SB_InitMsg(&comndata, ICAROUS_STARTMISSION_MID, sizeof(comndata), TRUE);
                    comndata.param1 = 1;

                    #ifdef DEBUG_MODE
                    fprintf(stdout, "CRATOUS: COMNDATA|START_MISSION|param1|%f\n", comndata.param1);
                    #endif

                    //Send the constructed START_MISSION message to the rest of ICAROUS
                    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &comndata);
                    CFE_SB_SendMsg((CFE_SB_Msg_t *) &comndata);
                }
                else if(!strncmp(trackingHelper, "GEOFN_SEND", strlen("GEOFN_SEND"))){ //Send a geofence to the rest of ICAROUS
                    #ifdef DEBUG_MODE
                    fprintf(stdout, "CRATOUS: COMNDATA|GEOFN_SEND|index|%i\n", geodata.index);
                    #endif

                    //Send the constructed message to the rest of ICAROUS
                    geodata.index = geoIndex++;
                    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &geodata);
                    CFE_SB_SendMsg((CFE_SB_Msg_t *) &geodata);

                    //Re-initialize the message to be sent again
                    CFE_SB_InitMsg(&geodata, ICAROUS_GEOFENCE_MID, sizeof(geodata), TRUE);
                }
                else if(!strncmp(trackingHelper, "RESET_SFT", strlen("RESET_SFT"))){ //Do an "in-place" reset
                    //An in-place reset is meant to interrupt the return-to-path behavior of default ICAROUS,
                    //which allows the program on the other side of this protocol to dictate its own return-to-path.

                    //This section of code cleans up waypoints we've reached for consistency with UxAS, which is
                    //the initial use-case for CRATOUS. If you have some other software that doesn't need the WPs
                    //cleaned up, feel free to comment out this "else if" section, other than the parts that send
                    //the reset and start messages (that is, lines that mention comndata or resetdata)

                    #ifdef DEBUG_MODE
                    fprintf(stdout, "CRATOUS: COMNDATA|RESET_SFT|lat|%f|long|%f|alt|%f\n");
                    #endif

                    flightplan_t fpdata_backup;
                    int totalWP = fpdata.num_waypoints;
                    int WPtoCopy = (totalWP - wpreached);
                    if(wpreached){ //We should copy an additional waypoint, to allow tasks to be resumed if interrupted
                        WPtoCopy++;
                    }
                    //Copy the relevant waypoints from fpdata into the backup
                    int j = 0;
                    for(int i = totalWP - WPtoCopy; i < totalWP; i++){
                        fpdata_backup.waypoints[j].latitude = fpdata.waypoints[i].latitude;
                        fpdata_backup.waypoints[j].longitude = fpdata.waypoints[i].longitude;
                        fpdata_backup.waypoints[j].altitude = fpdata.waypoints[i].altitude;
                        fpdata_backup.waypoints[j].wp_metric = fpdata.waypoints[i].wp_metric;
                        fpdata_backup.waypoints[j].value_to_next_wp = fpdata.waypoints[i].value_to_next_wp;
                        j++;
                    }

                    if(wpreached){
                        //Desired new latitude of the most recently-reached waypoint
                        trackingHelper  = strstr(tempMessageBuffer, "lat");
                        trackingHelper += 3; //skip past "lat"
                        fieldEnd        = strchr(trackingHelper, ',');
                        fieldLength     = fieldEnd - trackingHelper;
                        fpdata_backup.waypoints[0].latitude = atof(strncpy(throwaway, trackingHelper, fieldLength));

                        //Desired new longitude of the most recently-reached waypoint
                        trackingHelper  = strstr(tempMessageBuffer, "long");
                        trackingHelper += 4; //skip past "long"
                        fieldEnd        = strchr(trackingHelper, ',');
                        fieldLength     = fieldEnd - trackingHelper;
                        fpdata_backup.waypoints[0].longitude = atof(strncpy(throwaway, trackingHelper, fieldLength));

                        //Desired new altitude MSL in meters of the most recently-reached waypoint
                        trackingHelper  = strstr(tempMessageBuffer, "alt");
                        trackingHelper += 3; //skip past "alt"
                        fieldEnd        = strchr(trackingHelper, ',');
                        fieldLength     = fieldEnd - trackingHelper;
                        fpdata_backup.waypoints[0].altitude = atof(strncpy(throwaway, trackingHelper, fieldLength));
                    }

                    //Send reset command to ICAROUS
                    noArgsCmd_t resetdata;
                    CFE_SB_InitMsg(&resetdata, ICAROUS_RESET_MID, sizeof(resetdata), TRUE);
                    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &resetdata);
                    CFE_SB_SendMsg((CFE_SB_Msg_t *) &resetdata);

                    //Reset fpdata and geodata
                    CFE_SB_InitMsg(&fpdata, ICAROUS_FLIGHTPLAN_MID, sizeof(fpdata), TRUE);
                    CFE_SB_InitMsg(&geodata, ICAROUS_GEOFENCE_MID, sizeof(geodata), TRUE);

                    //Restore the geofences to ICAROUS
                    for(int i = 0; i < geoIndex; i++){
                        geodata.index = i;
                        geodata.type = geodata_backup[i].type;
                        geodata.totalvertices = geodata_backup[i].totalvertices;

                        for(int vertexIndex = 0; vertexIndex < geodata.totalvertices; vertexIndex++){
                            geodata.vertices[vertexIndex][0] = geodata_backup[i].vertices[vertexIndex][0];
                            geodata.vertices[vertexIndex][1] = geodata_backup[i].vertices[vertexIndex][1];
                        }

                        geodata.floor   = geodata_backup[i].floor;
                        geodata.ceiling = geodata_backup[i].ceiling;

                        //Send the reconstructed message
                        CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &geodata);
                        CFE_SB_SendMsg((CFE_SB_Msg_t *) &geodata);

                        //Re-initialize the message to be sent again
                        CFE_SB_InitMsg(&geodata, ICAROUS_GEOFENCE_MID, sizeof(geodata), TRUE);
                    }

                    //Copy the backup into fpdata
                    for(int i = 0; i < WPtoCopy; i++){
                        fpdata.waypoints[i].latitude = fpdata_backup.waypoints[i].latitude;
                        fpdata.waypoints[i].longitude = fpdata_backup.waypoints[i].longitude;
                        fpdata.waypoints[i].altitude = fpdata_backup.waypoints[i].altitude;
                        fpdata.waypoints[i].wp_metric = fpdata_backup.waypoints[i].wp_metric;
                        fpdata.waypoints[i].value_to_next_wp = fpdata_backup.waypoints[i].value_to_next_wp;
                    }
                    //Restore all other data of fpdata
                    fpdata.num_waypoints = WPtoCopy;
                    fpdata.id[0] = 'U';
                    fpdata.id[1] = 'x';
                    fpdata.id[2] = 'A';
                    fpdata.id[3] = 'S';
                    fpdata.id[4] = 'p';
                    fpdata.id[5] = 'l';
                    fpdata.id[6] = 'a';
                    fpdata.id[7] = 'n';

                    //Timestamp and send fpdata
                    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &fpdata);
                    CFE_SB_SendMsg((CFE_SB_Msg_t *) &fpdata);

                    //Reset # waypoints reached
                    wpreached = 0;

                    //Start mission
                    CFE_SB_InitMsg(&comndata, ICAROUS_STARTMISSION_MID, sizeof(comndata), TRUE);
                    comndata.param1 = 1;
                    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &comndata);
                    CFE_SB_SendMsg((CFE_SB_Msg_t *) &comndata);
                }
                else if(!strncmp(trackingHelper, "RESET_HRD", strlen("RESET_HRD"))){
                    //A hard reset is a recoverable error that renders all of our current data worthless.
                    //Thus, all data will be discarded and we'll have to start over.
                    fprintf(stdout, "CRATOUS: Hard reset requested, discarding all data...\n");

                    geoIndex = 0;
                    wpreached = 0;

                    //Send reset command to ICAROUS
                    noArgsCmd_t resetdata;
                    CFE_SB_InitMsg(&resetdata, ICAROUS_RESET_MID, sizeof(resetdata), TRUE);
                    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &resetdata);
                    CFE_SB_SendMsg((CFE_SB_Msg_t *) &resetdata);

                    fprintf(stdout, "CRATOUS: Hard reset complete. All data discarded.\n");
                }
                else{
                    fprintf(stderr, "CRATOUS: Error, unknown command type!\n");
                }

                //Cut off the processed part of tempMessageBuffer using pointer arithmetic
                fieldEnd = strchr(tempMessageBuffer, '\n');
                tempMessageBuffer = fieldEnd;
                tempMessageBuffer++;

            }else if(!strncmp(tempMessageBuffer, "WPREQ", 5)){ //Find a path between two given waypoints
                #ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: WPREQ received\n");
                #endif

                CFE_SB_InitMsg(&trajreqdata, ICAROUS_TRAJECTORY_REQUEST_MID, sizeof(trajreqdata), TRUE);

                //Type of trajectory planner to use
                trackingHelper            = strstr(tempMessageBuffer, "type");
                trackingHelper           += 4; //skip past "type"
                fieldEnd                  = strchr(trackingHelper, ',');
                fieldLength               = fieldEnd - trackingHelper;
                if(!strncmp(trackingHelper, "GRID", strlen("GRID"))){
                    trajreqdata.algorithm = _GRID;
                }
                else if(!strncmp(trackingHelper, "ASTAR", strlen("ASTAR"))){
                    trajreqdata.algorithm = _ASTAR;
                }
                else if(!strncmp(trackingHelper, "RRT", strlen("RRT"))){
                    trajreqdata.algorithm = _RRT;
                }
                else if(!strncmp(trackingHelper, "SPLINE", strlen("SPLINE"))){
                trajreqdata.algorithm = _SPLINES;
                }

                //Latitude of the initial position on the path to be found ("start latitude")
                trackingHelper  = strstr(tempMessageBuffer, "slat");
                trackingHelper += 4; //skip past "ilat"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                trajreqdata.initialPosition[0] = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Longitude of the initial position on the path to be found ("start longitude")
                trackingHelper  = strstr(tempMessageBuffer, "slong");
                trackingHelper += 5; //skip past "ilong"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                trajreqdata.initialPosition[1] = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Altitude of the initial position on the path to be found ("start altitude")
                trackingHelper  = strstr(tempMessageBuffer, "salt");
                trackingHelper += 4; //skip past "ialt"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                trajreqdata.initialPosition[2] = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Latitude of the final position on the path to be found ("end latitude")
                trackingHelper  = strstr(tempMessageBuffer, "elat");
                trackingHelper += 4; //skip past "olat"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                trajreqdata.finalPosition[0] = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Longitude of the final position on the path to be found ("end longitude")
                trackingHelper  = strstr(tempMessageBuffer, "elong");
                trackingHelper += 5; //skip past "olong"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                trajreqdata.finalPosition[1] = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Altitude of the final position on the path to be found ("end altitude")
                trackingHelper  = strstr(tempMessageBuffer, "ealt");
                trackingHelper += 4; //skip past "oalt"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                trajreqdata.finalPosition[2] = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Intial track of the vehicle in degrees
                trackingHelper  = strstr(tempMessageBuffer, "track");
                trackingHelper += 5; //skip past "track"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                trajreqdata.initialVelocity[0] = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Initial groundspeed of the vehicle in meters per second ("velocity horizontal")
                trackingHelper  = strstr(tempMessageBuffer, "vh");
                trackingHelper += 2; //skip past "vh"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                trajreqdata.initialVelocity[1] = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //Initial vertical velocity of the vehicle in meters per second ("velocity vertical")
                trackingHelper  = strstr(tempMessageBuffer, "vv");
                trackingHelper += 2; //skip past "vv"
                fieldEnd        = strchr(trackingHelper, ',');
                fieldLength     = fieldEnd - trackingHelper;
                trajreqdata.initialVelocity[2] = atof(strncpy(throwaway, trackingHelper, fieldLength));

                //#ifdef DEBUG_MODE
                fprintf(stdout, "CRATOUS: TRAJREQDATA|algorithm|%i\n", trajreqdata.algorithm);
                fprintf(stdout, "CRATOUS: TRAJREQDATA|slat|%f\n", trajreqdata.initialPosition[0]);
                fprintf(stdout, "CRATOUS: TRAJREQDATA|slong|%f\n", trajreqdata.initialPosition[1]);
                fprintf(stdout, "CRATOUS: TRAJREQDATA|salt|%f\n", trajreqdata.initialPosition[2]);
                fprintf(stdout, "CRATOUS: TRAJREQDATA|elat|%f\n", trajreqdata.finalPosition[0]);
                fprintf(stdout, "CRATOUS: TRAJREQDATA|elong|%f\n", trajreqdata.finalPosition[1]);
                fprintf(stdout, "CRATOUS: TRAJREQDATA|ealt|%f\n", trajreqdata.finalPosition[2]);
                fprintf(stdout, "CRATOUS: TRAJREQDATA|track|%f\n", trajreqdata.initialVelocity[0]);
                fprintf(stdout, "CRATOUS: TRAJREQDATA|vh|%f\n", trajreqdata.initialVelocity[1]);
                fprintf(stdout, "CRATOUS: TRAJREQDATA|vv|%f\n", trajreqdata.initialVelocity[2]);
                //#endif

                //Cut off the processed part of tempMessageBuffer using pointer arithmetic
                fieldEnd = strchr(tempMessageBuffer, '\n');
                tempMessageBuffer = fieldEnd;
                tempMessageBuffer++;

                //Send the constructed message to the rest of ICAROUS
                CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &trajreqdata);
                CFE_SB_SendMsg((CFE_SB_Msg_t *) &trajreqdata);

            }
            else{
                fprintf(stderr,"CRATOUS: Error, unknown message type!\n");

                //Cut off the processed part of tempMessageBuffer using pointer arithmetic
                fieldEnd = strchr(tempMessageBuffer, '\n');
                tempMessageBuffer = fieldEnd;
                tempMessageBuffer++;
            }
        }
    }

    //Stop Performance Log entry
    CFE_ES_PerfLogExit(CRATOUS_MAIN_TASK_PERF_ID);

    //Exit CRATOUS
    CFE_ES_ExitApp(g_CRATOUS_AppData.uiRunStatus);
}

void *ICAROUS_listener(int *var)
{
    //Begin communication protocol: send output to UxAS

    int sockfd = *var;
    //var can now be safely freed
    free(var);

    int mode = 0; //0 for PASSIVE, any other value for ACTIVE
    int sendWPtoUXAS = 0; //0 to not send flightplans to UxAS, any other value to send

    #ifdef DEBUG_MODE
    fprintf(stdout, "CRATOUS: The ICAROUS->UxAS pthread was created!\n");
    #endif

    while(true){
        #ifdef DEBUG_MODE
        printf("CRATOUS: Waiting for commands to send to sockfd %i\n", sockfd);
        #endif

        //Read for a message, and wait forever for its arrival if need be
        CFE_SB_MsgPtr_t incomingMessage_Ptr;
        int32 status = CFE_SB_RcvMsg(&incomingMessage_Ptr, messagePipe, CFE_SB_PEND_FOREVER);

        //Parse the message
        if (status == CFE_SUCCESS){

            CFE_SB_MsgId_t  MsgId;
            MsgId = CFE_SB_GetMsgId(incomingMessage_Ptr);

            switch (MsgId){
                case ICAROUS_COMMANDS_MID :{
                    argsCmd_t *cmd = (argsCmd_t*) incomingMessage_Ptr;

                    switch(cmd->name){

                        case _SETMODE_:
                            #ifdef DEBUG_MODE
                            fprintf(stdout, "CRATOUS: SETMOD received!\n");
                            #endif

                            //Alert UxAS to the fact that we're changing modes
                            if(cmd->param1 == _PASSIVE_){
                                if(mode){
                                    dprintf(sockfd, "SETMOD,type%s,\n", "_PASSIVE_");
                                    mode = 0;
                                }

                                #ifdef DEBUG_MODE
                                fprintf(stdout, "CRATOUS: PASSIVE received!\n");
                                #endif
                            }
                            else{
                                if(!mode){
                                    dprintf(sockfd, "SETMOD,type%s,\n", "_ACTIVE_");
                                    mode = 1;
                                }

                                #ifdef DEBUG_MODE
                                fprintf(stdout, "CRATOUS: ACTIVE received!\n");
                                #endif
                            }
                            break;

                        case _SETPOS_:
                            #ifdef DEBUG_MODE
                            fprintf(stdout, "CRATOUS: SETPOS received!\n");
                            #endif

                            //Send the target position message to UxAS
                            dprintf(sockfd, "SETPOS,lat%f,long%f,alt%f,\n", cmd->param1, cmd->param2, cmd->param3);
                            break;

                        case _SETVEL_:
                            #ifdef DEBUG_MODE
                            fprintf(stdout, "CRATOUS: SETVEL received!\n");
                            #endif

                            //Send the target heading message to UxAS
                            dprintf(sockfd, "SETVEL,north%f,east%f,down%f,\n", cmd->param1, cmd->param2, cmd->param3);
                            break;

                        case _GOTOWP_:
                            #ifdef DEBUG_MODE
                            fprintf(stdout, "CRATOUS: GOTOWP received!\n");
                            #endif

                            //Send the target waypoint message to UxAS
                            dprintf(sockfd, "GOTOWP,id%i,\n", cmd->param1);
                            break;

                        default:
                            break;

                    }

                    break;
                }
                case ICAROUS_TRAJECTORY_MID :{
                    //#ifdef DEBUG_MODE
                    fprintf(stdout, "CRATOUS: TRAJECTORY received!\n");
                    //#endif

                    flightplan_t *flightplan = (flightplan_t*)incomingMessage_Ptr;

                    //Tell UxAS we're sending a Route Plan ReSPonse
                    dprintf(sockfd, "RPRSP,typeST,\n");
                    for(int i = 0; i < flightplan->num_waypoints; i++){
                        float sentValue2NextWP = 0;
                        //Send waypoints to UxAS
                        if(flightplan->waypoints[i].wp_metric == WP_METRIC_SPEED){
                            sentValue2NextWP = flightplan->waypoints[i].value_to_next_wp;
                        }
                        dprintf(sockfd, "RPRSP,typeWP,lat%f,long%f,alt%f,spd%f,\n",
                            flightplan->waypoints[i].latitude,
                            flightplan->waypoints[i].longitude,
                            flightplan->waypoints[i].altitude,
                            sentValue2NextWP);
                    }
                    //End the Route Plan ReSPonse
                    dprintf(sockfd, "RPRSP,typeED,\n");

                    break;
                }
            }
        }else{
            fprintf(stderr, "CRATOUS: There was an error reading a message!\n");
            exit(EXIT_FAILURE);
        }
    }

    return NULL;
}

/*=======================================================================================
** End of file cratous_app.c
**=====================================================================================*/
