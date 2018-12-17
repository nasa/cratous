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
** File Name:  cratous_private_ids.h
**
** Title:  ID Header File for CRATOUS Application
**
** $Author:    Jane Doe
** $Revision: 1.1 $
** $Date:      2018-06-14
**
** Purpose:  This header file contains declarations and definitions of CRATOUS's private IDs.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2018-06-14 | Jane Doe | Build #: Code Started
**
**=====================================================================================*/

#ifndef _CRATOUS_PRIVATE_IDS_H_
#define _CRATOUS_PRIVATE_IDS_H_

/*
** Pragmas
*/

/*
** Include Files
*/

/*
** Local Defines
*/

/* Event IDs */
#define CRATOUS_RESERVED_EID  0

#define CRATOUS_INF_EID        1
#define CRATOUS_INIT_INF_EID   2
#define CRATOUS_ILOAD_INF_EID  3
#define CRATOUS_CDS_INF_EID    4
#define CRATOUS_CMD_INF_EID    5

#define CRATOUS_ERR_EID         51
#define CRATOUS_INIT_ERR_EID    52
#define CRATOUS_ILOAD_ERR_EID   53
#define CRATOUS_CDS_ERR_EID     54
#define CRATOUS_CMD_ERR_EID     55
#define CRATOUS_PIPE_ERR_EID    56
#define CRATOUS_MSGID_ERR_EID   57
#define CRATOUS_MSGLEN_ERR_EID  58

#define CRATOUS_EVT_CNT  14

/*
** Local Structure Declarations
*/

/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/

#endif /* _CRATOUS_PRIVATE_IDS_H_ */

/*=======================================================================================
** End of file cratous_private_ids.h
**=====================================================================================*/
