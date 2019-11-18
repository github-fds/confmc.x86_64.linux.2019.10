//------------------------------------------------------------------------------
// Copyright (c) 2018-2019 Future Design Systems
// http://www.future-ds.com
//------------------------------------------------------------------------------
// trx_ahb_api.c
//------------------------------------------------------------------------------
// VERSION = 2019.04.15.
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <assert.h>
#include <sys/types.h>
#if defined(_WIN32)
#	include <windows.h>
#endif
#include "conapi.h"
#include "trx_ahb_api.h"

#define GET_CMD(CMD,EI,WR,LK,SZ,BT,PR,BL)\
        CMD = ((EI)&0x1)  <<31\
            | ((WR)&0x1)  <<30\
            | ((LK)&0x3)  <<28\
            | ((SZ)&0x3)  <<26\
            | ((BT)&0xF)  <<23\
            | ((PR)&0xF)  <<19\
            | ((BL)&0xFFF)

//------------------------------------------------------------------------------
// It generates 'length' incremental write transactions
// from the address in 'addr' with data in 'data[]'.
CONFMC_BFM_API
int  BfmWrite( con_Handle_t  handle
             , unsigned int  addr
             , unsigned int *data // pointer to the array of justified data
             , unsigned int  size // num of bytes in an item
             , unsigned int  length)
{
#ifdef RIGOR
   if (data==NULL) {
       printf("%s() invalid buffer\n", __FUNCTION__);
       return -1;
   }
   switch (size) {
   case 1: case 2: case 4: break;
   default: printf("%s() cannot support %d-byte transfer\n", __FUNCTION__, size);
            return -2;
   }
   if ((length>0x1000)&&(length<0)) {
       printf("%s() can support up to 4096 for length\n", __FUNCTION__);
       return -3;
   }
   if (addr%size) {
       printf("%s() cannot support mis-aligned access\n", __FUNCTION__);
       return -4;
   }
#endif
   // to push BFM command for write
   // - control-flit for command
   // - command-flit for bfm write
   // - address-flit for bfm write
   unsigned int cbuf[4];
   cbuf[0] = (2<<16) // command+address
           | ((0b0010&0xF)<<12) // control packet
           | ((0x0&0xF)<<4); // transactor
   GET_CMD(cbuf[1], 0, 1, 0, size>>1, 1, 0,length-1);
          //       EI,WR,LK, SZ     ,BT,PR
   cbuf[2] = addr;
   // to push BFM data for write
   // - control-flit for data
   cbuf[3] = (length<<16) //  command+data
           | ((0b0100&0xF)<<12) // control packet
           | ((0x0&0xF)<<4); // transactor

   unsigned int done=0;
   if (conStreamWrite(handle, cbuf, 4, &done, 0) || (done!=4)) {
       printf("%s() something went wrong: %d\n", __FUNCTION__, done);
       return -5;
   }

   // to push BFM data for write
   unsigned int num;
   unsigned int *pbuf=data;
   for (num=length, done=0; num>0; num -= done, pbuf += done) {
        unsigned int zlp = ((num*4)%handle->usb.bulk_max_pkt_size_out) ? 0 : 1;
        if (conStreamWrite(handle, (void *)pbuf, num, &done, zlp)) {
            printf("%s() something went wrong: %d\n", __FUNCTION__, done);
            return -6;
        }
   }
   return 0;
}

//-------------------------------------------------------------
// It generates 'length' incremental read transactions
// from the address in 'addr' with data in 'data[]'.
CONFMC_BFM_API
int  BfmRead( con_Handle_t  handle
            , unsigned int  addr
            , unsigned int *data // pointer to the array of justified data
            , unsigned int  size
            , unsigned int  length)
{
#ifdef RIGOR
   if (data==NULL) {
       printf("%s() invalid buffer\n", __FUNCTION__);
       return -1;
   }
   switch (size) {
   case 1: case 2: case 4: break;
   default: printf("%s() cannot support %d-byte transfer\n", __FUNCTION__, size);
            return -2;
   }
   if ((length>0x1000)&&(length<0)) {
       printf("%s() can support up to 4096 for length\n", __FUNCTION__);
       return -3;
   }
   if (addr%size) {
       printf("%s() cannot support mis-aligned access\n", __FUNCTION__);
       return -4;
   }
#endif
   // to push BFM command for write
   // - control-flit for command
   // - command-flit for bfm write
   // - address-flit for bfm write
   unsigned int cbuf[4];
   cbuf[0] = (2<<16) // command+address
           | ((0b0010&0xF)<<12) // control packet
           | ((0x0&0xF)<<4); // transactor
   GET_CMD(cbuf[1], 0, 0, 0, size>>1, 1, 0,length-1);
          //       EI,WR,LK, SZ     ,BT,PR,BL
   cbuf[2] = addr;
   // to push BFM data for write
   // - control-flit for data
   cbuf[3] = (length<<16) // command+data
           | ((0b0101&0xF)<<12) // control packet
           | ((0x0&0xF)<<4); // transactor

   unsigned int done=0;
   if (conStreamWrite(handle, cbuf, 4, &done, 0) || (done!=4)) {
       printf("%s() something went wrong CMD\n", __FUNCTION__);
       return -5;
   }

   // to pop BFM data for read
   unsigned int num;
   unsigned int *pbuf=data;
   for (num=length, done=0; num>0; num -= done, pbuf += done) {
        if (conStreamRead(handle, (void *)pbuf, num, &done)) {
            printf("%s() something went wrong DATA\n", __FUNCTION__);
            return -5;
        }
   }
   return 0;
}

//------------------------------------------------------------------------------
// It writes GPIO pins.
//
// Return <0 on failure, 0 on success.
CONFMC_BFM_API
int BfmGpout( con_Handle_t  handle
            , unsigned int value )
{
   unsigned int cbuf[1]; //pbuf[1];
   unsigned int done;
   cbuf[0] = 1<<31
           | 1<<30
           | (value&0xFFFF);
   if (conCmdWrite(handle, (void *)cbuf, 1, &done, 0)) {
       printf("%s() something went wrong\n", __FUNCTION__);
       return -1;
   }
   return 0;
}

//------------------------------------------------------------------------------
// It reads GPIO pins.
//
// Return <0 on failure, 0 on success.
CONFMC_BFM_API
int BfmGpin( con_Handle_t  handle
           , unsigned int *pValue )
{
   unsigned int cbuf[1], pbuf[1];
   unsigned int done;
   if (pValue==NULL) {
       return -1;
   }
   cbuf[0] = 1<<31;
   if (conCmdWrite(handle, (void *)cbuf, 1, &done, 0)) {
       printf("%s() something went wrong\n", __FUNCTION__);
       return -1;
   }
   if (conDataRead(handle, (void *)pbuf, 1, &done, 0)) {
       printf("%s() something went wrong\n", __FUNCTION__);
       return -1;
   }
   *pValue = pbuf[0];
   return 0;
}

//------------------------------------------------------------------------------
// [External access]
// [cmd-fifo]
//  31 30 29-28|27-26|25-23|22-19|18-16|15-12|11-0|
// |EI|WR|LK   |SZ   | BT  |PR   |res  |res  |BL  |
// |                     start address            |
// [u2f-fifo for write]
// |          justified data (when write)         |
// [f2u-fifo for read]
// |          justified data (when write)         |
//
//  EI      : Mode (0 for external, 1 for internal)
//  WR      : Read/Write(HWRITE) -- 0 for read, 1 for write
//  LK[1:0] : Locked Transfer(HLOCK) -- 00=normal or keep, 11=lock, 10=unlock
//  SZ[1:0] : Transfer Size(HSIZE) -- 00 for byte, 01 for short, 10 for word
//  BT[2:0] : Burst mode(HBURST) -- 000=1, 001=inc, 011=incr4, 101=inc8, 111=inc16
//  PR[3:0] : Protection Control(HPROT)
//  BL[9:0] : Burst Length (BL+1 beats: 0=1-beat, 3=4-beat, 1023=1024-beat)
//------------------------------------------------------------------------------
// [internal access]
//
// [u2f-fifo for write]
//  31 30  29-16   15-0
// |EI|WR| reserv |data|
//                 GPOUT[15:0]
//
// [f2u-fifo for write]
//  31 30 29-28 27-24 23-19 18-16 15-0
// |F |I |     |     |resrv|DW   |data|
//
// F       : FIQ
// I       : IRQ
// DW[3:0] : Data-bus width (1<<DW)-byte
// data    : read data from GPIN[15:0]
//------------------------------------------------------------------------------
// Revision History
//
// 2019.04.15: BfmWrite()/BfmRead()/BfmWriteFix()/BfmReadFix()
//             returns negative on failure
//             returns 0 on success.
// 2019.02.07: Each API has new arguemnt 'con_Handle_t handle'.
// 2019.02.07: 'extern con_Handle_t handle' removed
// 2018.06.25: Mis-aligned case check
// 2018.04.27: Start by Ando Ki (adki@future-ds.com)
//------------------------------------------------------------------------------
