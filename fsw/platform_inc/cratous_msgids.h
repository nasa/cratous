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
** File Name:  cratous_msgids.h
**
** Title:  Message ID Header File for CRATOUS Application
**
** $Author:    Jane Doe
** $Revision: 1.1 $
** $Date:      2018-06-14
**
** Purpose:  This header file contains declartions and definitions of all CRATOUS's
**           Message IDs.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2018-06-14 | Jane Doe | Build #: Code Started
**
**=====================================================================================*/

#ifndef _CRATOUS_MSGIDS_H_
#define _CRATOUS_MSGIDS_H_

/***** TODO:  These Message ID values are default and may need to be changed by the developer  *****/
#define CRATOUS_CMD_MID             0x1880
#define CRATOUS_SEND_HK_MID         0x1881

#define CRATOUS_WAKEUP_MID          0x1882
#define CRATOUS_OUT_DATA_MID        0x1883

#define CRATOUS_HK_TLM_MID          0x0880
#define CRATOUS_DATA_TYPES_MID      0x0881

#include "cratous_tbldefs.h"



#endif /* _CRATOUS_MSGIDS_H_ */

/*=======================================================================================
** End of file cratous_msgids.h
**=====================================================================================*/
