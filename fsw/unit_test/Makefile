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
# File:    Linux Makefile for Unit Testing of cratous Application
# Author:  Jane Doe
# Date:    2018-06-14
#
#######################################################################################

#
# Compiler/linker definitions
#

#
# Search path definitions to modify
#
export CFS_MISSION=$(YOUR_PROJ_HOME)
CFS_APP_SRC=$(CFS_MISSION)/apps/
APPTARGET=ut_CRATOUS

# Set build type to CFE_APP. This allows us to
# define different compiler flags for the cFE Core and Apps.
#
BUILD_TYPE = CFE_APP

#
# Include all necessary cFE make rules
# Any of these can be copied to a local file and changed if needed.
#
#     cfe-config.mak contains PSP and OS selection
#
include $(CFS_MISSION)/build/linux/cfe/cfe-config.mak

#
# Setup the source path for this build
#
VPATH := .

#
# Setup the include path for this build
# The OS specific includes are in the build-rules.make file
#
# If this build needs include files from another app, add the path here.
#
INC_PATH := -I. \
						-I../platform_inc \
						-I$(CFS_MISSION)/osal/src/os/inc \
						-I$(CFS_MISSION)/osal/build/inc  \
						-I$(CFS_MISSION)/psp/fsw/inc \
						-I$(CFS_MISSION)/psp/fsw/$(PSP)/inc \
						-I$(CFS_MISSION)/cfe/fsw/cfe-core/src/inc

#
# The default "make" target
#
all:: ut_cratous.bin

clean::
	-rm -f *.o
	-rm -f *.bin

ut_cratous.bin: ut_cratous.c
	gcc $(LOCAL_COPTS) $(INC_PATH) $(COPTS) $(DEBUG_OPTS) \
			-DOS_DEBUG_LEVEL=$(DEBUG_LEVEL) -m32 $^ \
			-o ut_cratous.bin

#######################################################################################
