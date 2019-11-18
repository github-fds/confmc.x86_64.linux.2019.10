#------------------------------------------------------------------------------
# Copyright (c) 2018-2019 Future Design Systems, Inc. All rights reserved. 
#------------------------------------------------------------------------------
# FILE: setting.sh
#------------------------------------------------------------------------------
KERN=`uname -s | tr '[:upper:]' '[:lower:]'`
MACH=`uname -m`

export CONFMC_HOME=CONFMC_CONFMC
if [ -n "${PATH}" ]; then
  export PATH=$CONFMC_HOME/bin:$PATH
else
  export PATH=$CONFMC_HOME/bin
fi
if [ -n "${LD_LIBRARY_PATH}" ]; then
  export LD_LIBRARY_PATH=$CONFMC_HOME/lib/${KERN}_${MACH}:$LD_LIBRARY_PATH
else
  export LD_LIBRARY_PATH=$CONFMC_HOME/lib/${KERN}_${MACH}
fi
if [ -n "${C_INCLUDE_PATH}" ]; then
  export C_INCLUDE_PATH=$CONFMC_HOME/include:$C_INCLUDE_PATH
else
  export C_INCLUDE_PATH=$CONFMC_HOME/include
fi
if [ -n "${CPLUS_INCLUDE_PATH}" ]; then
  export CPLUS_INCLUDE_PATH=$CONFMC_HOME/include:$CPLUS_INCLUDE_PATH
else
  export CPLUS_INCLUDE_PATH=$CONFMC_HOME/include
fi
if [ -n "${PYTHONPATH}" ]; then
  export PYTHONPATH=$CONFMC_HOME/python/${KERN}_${MACH}:$PYTHONPATH
else
  export PYTHONPATH=$CONFMC_HOME/python/${KERN}_${MACH}
fi
