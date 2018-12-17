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
# File:    CFS Application Makefile
# Author:  GSFC/Flight Software Branch/Code 582
# Date:    2008-2010
#
#######################################################################################

#
# Subsystem produced by this makefile
#
APPTARGET = cratous

#
# Entry Point for task
#
ENTRY_PT = CRATOUS_AppMain

#
# Object files required to build subsystem.
#
OBJS = cratous_app.o cratous_iload_utils.o

#
# Source files required to build subsystem; used to generate dependencies.
# As long as there are no assembly files this can be automated.
#
SOURCES = $(OBJS:.o=.c)

#
# Specify extra C Flags needed to build this subsystem
#
LOCAL_COPTS =

#
# EXEDIR is defined here, just in case it needs to be different for a custom build
#
EXEDIR=../exe

#
# Certain OSs and Application Loaders require the following option for shared libraries.
# Currently only needed for vxWorks 5.5 and RTEMS.
# For each shared library that this app depends on, you need to have an entry like the
# following:
#    -R../tst_lib/tst_lib.elf
#
SHARED_LIB_LINK =

#======================================================================================
# Should not have to change below this line, except for customized mission and cFE
# directory structures
#======================================================================================
#
# Set build type to CFE_APP. This allows us to
# define different compiler flags for the cFE Core and Apps.
#
BUILD_TYPE = CFE_APP

#
# Include all necessary cFE make rules
# Any of these can be copied to a local file and changed if needed.
#
#       cfe-config.mak contains PSP and OS selection
#
include ../cfe/cfe-config.mak
#
#       debug-opts.mak contains debug switches
#
include ../cfe/debug-opts.mak
#
#       compiler-opts.mak contains compiler definitions and switches/defines
#
include $(CFE_PSP_SRC)/$(PSP)/make/compiler-opts.mak

#
# Setup the include path for this subsystem
# The OS specific includes are in the build-rules.make file
#
# If this subsystem needs include files from another app, add the path here.
#
INCLUDE_PATH = -I$(OSAL_SRC)/inc \
							 -I$(CFE_CORE_SRC)/inc \
							 -I$(CFE_PSP_SRC)/inc \
							 -I$(CFE_PSP_SRC)/$(PSP)/inc \
							 -I$(CFS_APP_SRC)/inc \
							 -I$(CFS_APP_SRC)/$(APPTARGET)/fsw/src \
							 -I$(CFS_APP_SRC)/$(APPTARGET)/fsw/tables \
							 -I$(CFS_MISSION_INC) \
							 -I../cfe/inc \
							 -I../inc

#
# Define the VPATH make variable.
# This can be modified to include source from another directory.
# If there is no corresponding app in the cfs-apps directory, then this can be discarded,
# or if the mission chooses to put the src in another directory such as "src", then that
# can be added here as well.
#
VPATH = $(CFS_APP_SRC)/$(APPTARGET)/fsw/src \
				$(CFS_APP_SRC)/$(APPTARGET)/fsw/tables

#
# Include the common make rules for building a cFE Application
#
include $(CFE_CORE_SRC)/make/app-rules.mak

#######################################################################################
