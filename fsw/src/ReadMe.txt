# Notices:
#
# Copyright 2018 United States Government as represented by the Administrator
# of the National Aeronautics and Space Administration. All Rights Reserved.
#
# Disclaimers:
#
# No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY
# OF ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT
# LIMITED TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO
# SPECIFICATIONS, ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
# PARTICULAR PURPOSE, OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE
# SUBJECT SOFTWARE WILL BE ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF
# PROVIDED, WILL CONFORM TO THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN
# ANY MANNER, CONSTITUTE AN ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR
# RECIPIENT OF ANY RESULTS, RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR
# ANY OTHER APPLICATIONS RESULTING FROM USE OF THE SUBJECT SOFTWARE. FURTHER,
# GOVERNMENT AGENCY DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING
# THIRD-PARTY SOFTWARE, IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES
# IT "AS IS."
#
# Waiver and Indemnity: RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
# THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS
# ANY PRIOR RECIPIENT. IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS IN
# ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH USE,
# INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM, RECIPIENT'S
# USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD HARMLESS THE
# UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL AS ANY
# PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW. RECIPIENT'S SOLE REMEDY FOR
# ANY SUCH MATTER SHALL BE THE IMMEDIATE, UNILATERAL TERMINATION OF THIS
# AGREEMENT.

#######################################################################################
#
# File:  ReadMe.txt
# Desc:  This file describes the data flow of a CFS application.
#
#######################################################################################

A CFS application runs as a child thread in non-realtime OS, like Linux, and as a task
in realtime OS, like VxWorks.

Once invoked (automatically done by the CFE services), the application first initializes
its data, including creations and registrations of message pipes and tables, subscriptions
to other applications' output data, etc.  Then it enters a main loop, awaiting for
messages to respond to.  (From hereon, this will be referring to as listening mode.)

When in listening mode, there are 2 specific messages the application should respond to:

1) <app-name>_WAKEUP_MID

   This message is normally sent by the CFS message scheduler.  Only upon receiving
   this message would the application start doing work.  When woken up, the application
   will first process and respond to all incoming commands.  Then, it will process
   all incoming data.  Next, it performs 1-cycle worth of data processing.  And last,
   it sends out its output data (<app-name>_OUT_DATA_MID) before going back to the
   listening mode.

   The application's output data is published at its running rate.  It should contain
   data to be recorded on-board (not downlinked) and data to be consumed by other
   applications.

2) <app-name>_SEND_HK_MID

   This message is normally sent by the CFS message scheduler.  Upon receiving this
   message, the application sends out its latest housekepping data (<app-name>_HK_TLM_MID)
   to be downlinked to the ground.  Then it goes back to the listening mode.

   The application's housekeeping data is published only upon receiving an
   <app-name>_SEND_HK_MID message.  It should contain ONLY essential data that the ground
   system needs in order to run the mission effectively.
