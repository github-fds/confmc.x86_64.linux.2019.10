#------------------------------------------------------------------------------
# Copyright (c) 2018-2019 Future Design Systems, Inc. All rights reserved. 
#------------------------------------------------------------------------------
# FILE: setting.csh
#------------------------------------------------------------------------------
set KERN=`uname -s | tr '[:upper:]' '[:lower:]'`
set MACH=`uname -m`

setenv CONFMC_HOME CONFMC_CONFMC
if $?PATH then
  setenv PATH $CONFMC_HOME/bin:$PATH
else
  setenv PATH $CONFMC_HOME/bin
endif
if $?LD_LIBRARY_PATH then
  setenv LD_LIBRARY_PATH $CONFMC_HOME/lib/${KERN}_${MACH}:$LD_LIBRARY_PATH
else
  setenv LD_LIBRARY_PATH $CONFMC_HOME/lib/${KERN}_${MACH}
endif
if $?C_INCLUDE_PATH then
  setenv C_INCLUDE_PATH $CONFMC_HOME/include:$C_INCLUDE_PATH
else
  setenv C_INCLUDE_PATH $CONFMC_HOME/include
endif
if $?CPLUS_INCLUDE_PATH then
  setenv CPLUS_INCLUDE_PATH $CONFMC_HOME/include:$CPLUS_INCLUDE_PATH
else
  setenv CPLUS_INCLUDE_PATH $CONFMC_HOME/include
endif
if $?PYTHONPATH then
  setenv PYTHONPATH=$CONFMC_HOME/python/${KERN}_${MACH}:$PYTHONPATH
else
  setenv PYTHONPATH=$CONFMC_HOME/python/${KERN}_${MACH}
fi
