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
# File:    CFS Application Table Makefile
# Author:  GSFC/Flight Software Branch/Code 582
# Date:    2008-2010
#
#######################################################################################

#
# The Application needs to be specified here
#
PARENTAPP = cratous

#
# List the tables that are generated here.
# Restrictions:
# 1. The table file name must be the same as the C source file name.
# 2. There must be a single C source file for each table.
#
TABLES = cratous_iloads.tbl

#======================================================================================
# Normally, nothing has to be changed below this line.
# The following are changes that may have to be made for a custom app environment:
# 1. INCLUDE_PATH - This may be customized to tailor the include path for an app.
# 2. VPATH - This may be customized to tailor the location of the table sources.
#            For example: if the tables were stored in a "tables" subdirectory
#                         (build/cpu1/sch/tables)
#======================================================================================

#
# Object files required for tables
#
OBJS = $(TABLES:.tbl=.o)

#
# Source files required to build tables.
#
SOURCES = $(OBJS:.o=.c)

#
# Specify extra C Flags needed to build this subsystem
#
LOCAL_COPTS =

#
# EXEDIR is defined here, just in case it needs to be different for a custom build.
#
EXEDIR = ../exe

#======================================================================================
# Should not have to change below this line, except for customized mission and cFE
# directory structures.
#======================================================================================

#
# Set build type to CFE_APP. This allows us to define different compiler flags for the
# cFE Core and Apps.
#
BUILD_TYPE = CFE_TABLE

#
# Include all necessary cFE make rules
# Any of these can be copied to a local file and changed if needed.
#
#
#       cfe-config.mak contains arch, BSP, and OS selection.
#
include ../cfe/cfe-config.mak

#
#       debug-opts.mak contains debug switches.
#       -- Note that the table must be built with -g for the elf2tbl utility to work.
#
include ../cfe/debug-opts.mak

##
##       compiler-opts.mak contains compiler definitions and switches/defines.
##
include $(CFE_PSP_SRC)/$(PSP)/make/compiler-opts.mak

#
# Setup the include path for this subsystem.
# The OS specific includes are in the build-rules.make file.
#
# If this subsystem needs include files from another app, add the path here.
#
INCLUDE_PATH = -I$(OSAL_SRC)/inc \
               -I$(CFE_CORE_SRC)/inc \
               -I$(CFE_PSP_SRC)/$(PSP)/inc \
               -I$(CFE_PSP_SRC)/inc \
               -I$(CFS_APP_SRC)/inc \
               -I$(CFS_APP_SRC)/$(PARENTAPP)/fsw/src \
               -I$(CFS_APP_SRC)/$(PARENTAPP)/fsw/tables \
               -I$(CFS_MISSION_INC) \
               -I../cfe/inc \
               -I../inc

#
# Define the VPATH make variable.
# This can be modified to include source from another directory.
# If there is no corresponding app in the cfe-apps directory, then this can be discarded,
# or if the mission chooses to put the src in another directory such as "src", then that
# can be added here as well.
#
VPATH = $(CFS_APP_SRC)/$(PARENTAPP)/fsw/tables

#
# Include the common make rules for building a cFE Application
#
include $(CFE_CORE_SRC)/make/table-rules.mak

#######################################################################################
