#ifndef _AXI_INTERCONNECTION_H
#define _AXI_INTERCONNECTION_H
#include "systemc.h"

#define C_S_AXI_ID_WIDTH 8
#define C_S_AXI_ADDR_WIDTH 40
#define C_S_AXI_AWUSER_WIDTH 10
#define C_S_AXI_WUSER_WIDTH 10
#define C_S_AXI_ARUSER_WIDTH 10
#define C_S_AXI_RUSER_WIDTH 10
// default bus_width
#define C_S_AXI_DATA_WIDTH 32
// define parameter width
#define PRAM_AXI_AxLEN 8
#define PRAM_AXI_AxSIZE  3
#define PRAM_AXI_AxBURST  2
#define PRAM_AXI_AxCACHE  4
#define PRAM_AXI_AxPROT  3
#define PRAM_AXI_AxREGION  4
#define PRAM_AXI_AxQOS  4
#define PRAM_AXI_RRESP  2
// define slave num 
#define PRAM_SLAVE_NUM 1
// define master num
#define PRAM_MASTER_NUM 1
// address range
#define PRAM_BIT_INSERTID 5
// start end

const unsigned int  PRAM_AW_WIDTH =  C_S_AXI_ID_WIDTH \
                        + C_S_AXI_ADDR_WIDTH \
                        + PRAM_AXI_AxLEN \
                        + PRAM_AXI_AxSIZE \
                        + PRAM_AXI_AxBURST \
                        + PRAM_AXI_AxCACHE \
                        + PRAM_AXI_AxPROT \
                        + PRAM_AXI_AxREGION \
                        + PRAM_AXI_AxQOS \
                        + C_S_AXI_AWUSER_WIDTH \
                        + 1;

const unsigned int PRAM_WRITE_WIDTH = C_S_AXI_ID_WIDTH \
                            + C_S_AXI_DATA_WIDTH \
                            + C_S_AXI_DATA_WIDTH \
                            + C_S_AXI_WUSER_WIDTH \
                            + 1;

const unsigned int PRAM_AREAD_WIDTH = C_S_AXI_ID_WIDTH \
                        + C_S_AXI_ADDR_WIDTH \
                        + PRAM_AXI_AxLEN \
                        + PRAM_AXI_AxSIZE \
                        + PRAM_AXI_AxBURST \
                        + PRAM_AXI_AxCACHE \
                        + PRAM_AXI_AxPROT \
                        + PRAM_AXI_AxREGION \
                        + PRAM_AXI_AxQOS \
                        + C_S_AXI_ARUSER_WIDTH \
                        + 1;

const sc_dt::sc_uint<C_S_AXI_ADDR_WIDTH> PRAM_START_ADDRESS[PRAM_SLAVE_NUM] = {0x000000000};
const sc_dt::sc_uint<C_S_AXI_ADDR_WIDTH> PRAM_END_ADDRESS[PRAM_SLAVE_NUM] = {0x00000FFFFF};      
#endif //_AXI_INTERCONNECTION_H