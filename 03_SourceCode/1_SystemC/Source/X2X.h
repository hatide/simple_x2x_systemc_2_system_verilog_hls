/**
 * x2x top module
 * Author: Tien Tran
 * Email: tientran26794@gmail.com
 * Date: Mar/26
 */


#ifndef _X2X_H
#define _X2X_H
#include "x2x_buffer.h"
#include "X2X_DECODER.h"
#include "X2X_ARBITER.h"
#include "AXI_Interconnection.h"

class x2x : public sc_module {
private:
    // x2x_buffer x2x_buffer[PRAM_MASTER_NUM] = {x2x_buffer("x2x_buffer")};
    // X2X_DECODER x2x_decoder[PRAM_MASTER_NUM] = {X2X_DECODER("x2x_decoder")};
    // X2X_ARBITER x2x_arbiter[PRAM_SLAVE_NUM] = {X2X_ARBITER("x2x_arbiter")};
    X2x_buffer *x2x_buffer[PRAM_MASTER_NUM];// = {x2x_buffer("x2x_buffer")};
    X2x_decoder *x2x_decoder[PRAM_MASTER_NUM];//= {X2X_DECODER("x2x_decoder")};
    X2x_arbiter *x2x_arbiter[PRAM_SLAVE_NUM];// = {X2X_ARBITER("x2x_arbiter")};
public: 
    x2x(sc_module_name name);
    ~x2x( );
    // global port 
    sc_in<bool>      ACLK;                                // AXI bus clock.
    sc_in<bool>      ARESETN;                             // AXI active-Low reset
    //*****************************
    //********Slave side signal****
    //*****************************
    // AXI Write Address Channel Signals (AW)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>>      S_AXI_AWID[PRAM_MASTER_NUM];        // AXI address Write ID.
    sc_in<sc_uint<C_S_AXI_ADDR_WIDTH>>      S_AXI_AWADDR[PRAM_MASTER_NUM];    // AXI Write address.
    sc_in<sc_uint<PRAM_AXI_AxLEN>>      S_AXI_AWLEN[PRAM_MASTER_NUM];         // AXI address Write burst length.
    sc_in<sc_uint<PRAM_AXI_AxSIZE>>      S_AXI_AWSIZE[PRAM_MASTER_NUM];       // AXI address Write burst size.
    sc_in<sc_uint<PRAM_AXI_AxBURST>>      S_AXI_AWBURST[PRAM_MASTER_NUM];     // AXI address Write burst type.
    sc_in<sc_uint<1>>      S_AXI_AWLOCK[PRAM_MASTER_NUM];                        // AXI Write address lock signal.
    sc_in<sc_uint<PRAM_AXI_AxCACHE>>      S_AXI_AWCACHE[PRAM_MASTER_NUM];     // AXI Write address cache control signal.
    sc_in<sc_uint<PRAM_AXI_AxPROT>>      S_AXI_AWPROT[PRAM_MASTER_NUM];       // AXI Write address protection signal.
    sc_in<sc_uint<PRAM_AXI_AxREGION>>      S_AXI_AWREGION[PRAM_MASTER_NUM];   // Channel address region index
    sc_in<sc_uint<PRAM_AXI_AxQOS>>      S_AXI_AWQOS[PRAM_MASTER_NUM];         // Channel Quality of Service (QoS).
    sc_in<sc_uint<C_S_AXI_AWUSER_WIDTH>>      S_AXI_AWUSER[PRAM_MASTER_NUM];  // User-defined AW Channel signals.
    sc_in<bool>      S_AXI_AWVALID[PRAM_MASTER_NUM];                       // AXI Write address valid.
    sc_out<bool>     S_AXI_AWREADY[PRAM_MASTER_NUM];                     // AXI Write address ready.
    // AXI Write Data Channel Signals (W)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>>      S_AXI_WID[PRAM_MASTER_NUM];         // AXI3 Write ID.
    sc_in<sc_uint<C_S_AXI_DATA_WIDTH>>      S_AXI_WDATA[PRAM_MASTER_NUM];     // AXI Write data.
    sc_in<sc_uint<C_S_AXI_DATA_WIDTH / 8>>      S_AXI_WSTRB[PRAM_MASTER_NUM]; // AXI Write data strobes.
    sc_in<bool>      S_AXI_WLAST[PRAM_MASTER_NUM];                         // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_in<sc_uint<C_S_AXI_WUSER_WIDTH>>      S_AXI_WUSER[PRAM_MASTER_NUM];    // User-defined W Channel signals.
    sc_in<bool>      S_AXI_WVALID[PRAM_MASTER_NUM];                        // AXI Write data valid.
    sc_out<bool>     S_AXI_WREADY[PRAM_MASTER_NUM];                        // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>>     S_AXI_BID[PRAM_MASTER_NUM];         // AXI Write response ID.
    sc_out<sc_uint<PRAM_AXI_RRESP>>     S_AXI_BRESP[PRAM_MASTER_NUM];         // AXI Write response code.
    sc_out<bool>     S_AXI_BUSER[PRAM_MASTER_NUM];                         // User-defined B channel signals.
    sc_out<bool>     S_AXI_BVALID[PRAM_MASTER_NUM];                        // AXI Write response valid.
    sc_in<bool>      S_AXI_BREADY[PRAM_MASTER_NUM];
    // AXI Read Address Channel Signals (AR)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>>      S_AXI_ARID[PRAM_MASTER_NUM];        // AXI address Read ID.
    sc_in<sc_uint<C_S_AXI_ADDR_WIDTH>>      S_AXI_ARADDR[PRAM_MASTER_NUM];    // AXI Read address.
    sc_in<sc_uint<PRAM_AXI_AxLEN>>      S_AXI_ARLEN[PRAM_MASTER_NUM];         // AXI address Read burst length.
    sc_in<sc_uint<PRAM_AXI_AxSIZE>>      S_AXI_ARSIZE[PRAM_MASTER_NUM];       // AXI address Read burst size.
    sc_in<sc_uint<PRAM_AXI_AxBURST>>      S_AXI_ARBURST[PRAM_MASTER_NUM];     // AXI address Read burst type.
    sc_in<sc_uint<PRAM_AXI_AxCACHE>>      S_AXI_ARCACHE[PRAM_MASTER_NUM];     // AXI Read address cache control signal.
    sc_in<sc_uint<PRAM_AXI_AxPROT>>      S_AXI_ARPROT[PRAM_MASTER_NUM];       // AXI Read address protection signal.
    sc_in<sc_uint<PRAM_AXI_AxREGION>>      S_AXI_ARREGION[PRAM_MASTER_NUM];   // Channel address region index.
    sc_in<sc_uint<PRAM_AXI_AxQOS>>      S_AXI_ARQOS[PRAM_MASTER_NUM];         // Channel Quality of Service.
    sc_in<sc_uint<C_S_AXI_ARUSER_WIDTH>>      S_AXI_ARUSER[PRAM_MASTER_NUM];  // User-defined AR Channel signals.
    sc_in<sc_uint<1>>      S_AXI_ARLOCK[PRAM_MASTER_NUM];                        // AXI Read address lock signal.
    sc_in<bool>      S_AXI_ARVALID[PRAM_MASTER_NUM];                       // AXI Read address valid.
    sc_out<bool>     S_AXI_ARREADY[PRAM_MASTER_NUM];                       // AXI Read address ready.               
    // AXI Read Data Channel Signals (R)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>>     S_AXI_RID[PRAM_MASTER_NUM];         // AXI Read data response ID.
    sc_out<sc_uint<C_S_AXI_DATA_WIDTH>>     S_AXI_RDATA[PRAM_MASTER_NUM];     // AXI Read data.
    sc_out<sc_uint<PRAM_AXI_RRESP>>     S_AXI_RRESP[PRAM_MASTER_NUM];         // AXI Read response code.
    sc_out<bool>     S_AXI_RLAST[PRAM_MASTER_NUM];                         // AXI Read data last signal.
    sc_out<sc_uint<C_S_AXI_RUSER_WIDTH>>     S_AXI_RUSER[PRAM_MASTER_NUM];    // User-defined R Channel signals.
    sc_out<bool>     S_AXI_RVALID[PRAM_MASTER_NUM];                        // AXI Read valid.
    sc_in<bool>      S_AXI_RREADY[PRAM_MASTER_NUM];                        // Read ready.
    // output signal
    //*****************************
    //********Master side signal***
    //*****************************
    // AXI Write Address Channel Signals (AW)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>>      M_AXI_AWID[PRAM_SLAVE_NUM];       // AXI address Write ID.
    sc_out<sc_uint<C_S_AXI_ADDR_WIDTH>>      M_AXI_AWADDR[PRAM_SLAVE_NUM];   // AXI Write address.
    sc_out<sc_uint<PRAM_AXI_AxLEN>>      M_AXI_AWLEN[PRAM_SLAVE_NUM];        // AXI address Write burst length.
    sc_out<sc_uint<PRAM_AXI_AxSIZE>>      M_AXI_AWSIZE[PRAM_SLAVE_NUM];      // AXI address Write burst size.
    sc_out<sc_uint<PRAM_AXI_AxBURST>>      M_AXI_AWBURST[PRAM_SLAVE_NUM];    // AXI address Write burst type.
    sc_out<sc_uint<1>>      M_AXI_AWLOCK[PRAM_SLAVE_NUM];                       // AXI Write address lock signal.
    sc_out<sc_uint<PRAM_AXI_AxCACHE>>      M_AXI_AWCACHE[PRAM_SLAVE_NUM];    // AXI Write address cache control signal.
    sc_out<sc_uint<PRAM_AXI_AxPROT>>      M_AXI_AWPROT[PRAM_SLAVE_NUM];      // AXI Write address protection signal.
    sc_out<sc_uint<PRAM_AXI_AxREGION>>      M_AXI_AWREGION[PRAM_SLAVE_NUM];  // Channel address region index
    sc_out<sc_uint<PRAM_AXI_AxQOS>>      M_AXI_AWQOS[PRAM_SLAVE_NUM];        // Channel Quality of Service (QoS).
    sc_out<sc_uint<C_S_AXI_AWUSER_WIDTH>>      M_AXI_AWUSER[PRAM_SLAVE_NUM]; // User-defined AW Channel signals.
    sc_out<bool>      M_AXI_AWVALID[PRAM_SLAVE_NUM];                      // AXI Write address valid.
    sc_in<bool>       M_AXI_AWREADY[PRAM_SLAVE_NUM];                      // AXI Write data ready.

    // AXI Write Data Channel Signals (W)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>>      M_AXI_WID[PRAM_SLAVE_NUM];        // AXI3 Write ID.
    sc_out<sc_uint<C_S_AXI_DATA_WIDTH>>      M_AXI_WDATA[PRAM_SLAVE_NUM];    // AXI Write data.
    sc_out<sc_uint<C_S_AXI_DATA_WIDTH / 8>>      M_AXI_WSTRB[PRAM_SLAVE_NUM];// AXI Write data strobes.
    sc_out<bool>      M_AXI_WLAST[PRAM_SLAVE_NUM];                        // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_out<sc_uint<C_S_AXI_WUSER_WIDTH>>      M_AXI_WUSER[PRAM_SLAVE_NUM];   // User-defined W Channel signals.
    sc_out<bool>      M_AXI_WVALID[PRAM_SLAVE_NUM];                       // AXI Write data valid.
    sc_in<bool>       M_AXI_WREADY[PRAM_SLAVE_NUM];                       // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>>       M_AXI_BID[PRAM_SLAVE_NUM];        // AXI Write response ID.
    sc_in<sc_uint<PRAM_AXI_RRESP>>       M_AXI_BRESP[PRAM_SLAVE_NUM];        // AXI Write response code.
    sc_in<bool>       M_AXI_BUSER[PRAM_SLAVE_NUM];                        // User-defined B channel signals.
    sc_in<bool>       M_AXI_BVALID[PRAM_SLAVE_NUM];                       // AXI Write response valid.
    sc_out<bool>      M_AXI_BREADY[PRAM_SLAVE_NUM];                       // Write response ready.
    // AXI Read Address Channel Signals (AR)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>>      M_AXI_ARID[PRAM_SLAVE_NUM];       // AXI address Read ID.
    sc_out<sc_uint<C_S_AXI_ADDR_WIDTH>>      M_AXI_ARADDR[PRAM_SLAVE_NUM];   // AXI Read address.
    sc_out<sc_uint<PRAM_AXI_AxLEN>>      M_AXI_ARLEN[PRAM_SLAVE_NUM];        // AXI address Read burst length.
    sc_out<sc_uint<PRAM_AXI_AxSIZE>>      M_AXI_ARSIZE[PRAM_SLAVE_NUM];      // AXI address Read burst size.
    sc_out<sc_uint<PRAM_AXI_AxBURST>>      M_AXI_ARBURST[PRAM_SLAVE_NUM];    // AXI address Read burst type.
    sc_out<sc_uint<1>>      M_AXI_ARLOCK[PRAM_SLAVE_NUM];                       // AXI Read address lock signal.
    sc_out<sc_uint<PRAM_AXI_AxCACHE>>      M_AXI_ARCACHE[PRAM_SLAVE_NUM];    // AXI Read address cache control signal.
    sc_out<sc_uint<PRAM_AXI_AxPROT>>      M_AXI_ARPROT[PRAM_SLAVE_NUM];      // AXI Read address protection signal.
    sc_out<sc_uint<PRAM_AXI_AxREGION>>      M_AXI_ARREGION[PRAM_SLAVE_NUM];  // Channel address region index.
    sc_out<sc_uint<PRAM_AXI_AxQOS>>      M_AXI_ARQOS[PRAM_SLAVE_NUM];        // Channel Quality of Service.
    sc_out<sc_uint<C_S_AXI_ARUSER_WIDTH>>      M_AXI_ARUSER[PRAM_SLAVE_NUM]; // User-defined AR Channel signals.
    sc_out<bool>      M_AXI_ARVALID[PRAM_SLAVE_NUM];                      // AXI Read address valid.
    sc_in<bool>       M_AXI_ARREADY[PRAM_SLAVE_NUM];                      // AXI Read address ready.
    // AXI Read Data channel Signals (R)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>>       M_AXI_RID[PRAM_SLAVE_NUM];        // AXI Read data response ID.
    sc_in<sc_uint<C_S_AXI_DATA_WIDTH>>       M_AXI_RDATA[PRAM_SLAVE_NUM];    // AXI Read data.
    sc_in<sc_uint<PRAM_AXI_RRESP>>       M_AXI_RRESP[PRAM_SLAVE_NUM];        // AXI Read response code.
    sc_in<bool>       M_AXI_RLAST[PRAM_SLAVE_NUM];                        // AXI Read data last signal.
    sc_in<sc_uint<C_S_AXI_RUSER_WIDTH>>       M_AXI_RUSER[PRAM_SLAVE_NUM];   // User-defined R Channel signals.
    sc_in<bool>       M_AXI_RVALID[PRAM_SLAVE_NUM];                       // AXI Read valid.
    sc_out<bool>      M_AXI_RREADY[PRAM_SLAVE_NUM];                       // AXI Read ready.
    // Signal interconnect port 
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWID[PRAM_MASTER_NUM];       // AXI address Write ID.
    sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWADDR[PRAM_MASTER_NUM];   // AXI Write address.
    sc_signal<sc_uint<PRAM_AXI_AxLEN>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWLEN[PRAM_MASTER_NUM];        // AXI address Write burst length.
    sc_signal<sc_uint<PRAM_AXI_AxSIZE>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWSIZE[PRAM_MASTER_NUM];      // AXI address Write burst size.
    sc_signal<sc_uint<PRAM_AXI_AxBURST>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWBURST[PRAM_MASTER_NUM];    // AXI address Write burst type.
    sc_signal<sc_uint<1>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWLOCK[PRAM_MASTER_NUM];                        // AXI Write address lock signal.
    sc_signal<sc_uint<PRAM_AXI_AxCACHE>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWCACHE[PRAM_MASTER_NUM];    // AXI Write address cache control signal.
    sc_signal<sc_uint<PRAM_AXI_AxPROT>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWPROT[PRAM_MASTER_NUM];      // AXI Write address protection signal.
    sc_signal<sc_uint<PRAM_AXI_AxREGION>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWREGION[PRAM_MASTER_NUM];  // Channel address region index
    sc_signal<sc_uint<PRAM_AXI_AxQOS>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWQOS[PRAM_MASTER_NUM];        // Channel Quality of Service (QoS).
    sc_signal<sc_uint<C_S_AXI_AWUSER_WIDTH>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWUSER[PRAM_MASTER_NUM]; // User-defined AW Channel signals.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWVALID[PRAM_MASTER_NUM];                       // AXI Write address valid.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_AWREADY[PRAM_MASTER_NUM];                     // AXI Write address ready.
    // AXI Write Data Channel Signals (W)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_WID[PRAM_MASTER_NUM];        // AXI3 Write ID.
    sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_WDATA[PRAM_MASTER_NUM];    // AXI Write data.
    sc_signal<sc_uint<C_S_AXI_DATA_WIDTH / 8>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_WSTRB[PRAM_MASTER_NUM];// AXI Write data strobes.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_WLAST[PRAM_MASTER_NUM];                         // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_signal<sc_uint<C_S_AXI_WUSER_WIDTH>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_WUSER[PRAM_MASTER_NUM];   // User-defined W Channel signals.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_WVALID[PRAM_MASTER_NUM];                        // AXI Write data valid.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_WREADY[PRAM_MASTER_NUM];                        // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>   SIG_X2X_BUFF_AXI_BID[PRAM_MASTER_NUM];        // AXI Write response ID.
    sc_signal<sc_uint<PRAM_AXI_RRESP>,SC_MANY_WRITERS>   SIG_X2X_BUFF_AXI_BRESP[PRAM_MASTER_NUM];        // AXI Write response code.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_X2X_BUFF_AXI_BUSER[PRAM_MASTER_NUM];                         // User-defined B channel signals.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_X2X_BUFF_AXI_BVALID[PRAM_MASTER_NUM];                        // AXI Write response valid.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_BREADY[PRAM_MASTER_NUM];
    // AXI Read Address Channel Signals (AR)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARID[PRAM_MASTER_NUM];       // AXI address Read ID.
    sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARADDR[PRAM_MASTER_NUM];   // AXI Read address.
    sc_signal<sc_uint<PRAM_AXI_AxLEN>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARLEN[PRAM_MASTER_NUM];        // AXI address Read burst length.
    sc_signal<sc_uint<PRAM_AXI_AxSIZE>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARSIZE[PRAM_MASTER_NUM];      // AXI address Read burst size.
    sc_signal<sc_uint<PRAM_AXI_AxBURST>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARBURST[PRAM_MASTER_NUM];    // AXI address Read burst type.
    sc_signal<sc_uint<PRAM_AXI_AxCACHE>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARCACHE[PRAM_MASTER_NUM];    // AXI Read address cache control signal.
    sc_signal<sc_uint<PRAM_AXI_AxPROT>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARPROT[PRAM_MASTER_NUM];      // AXI Read address protection signal.
    sc_signal<sc_uint<PRAM_AXI_AxREGION>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARREGION[PRAM_MASTER_NUM];  // Channel address region index.
    sc_signal<sc_uint<PRAM_AXI_AxQOS>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARQOS[PRAM_MASTER_NUM];        // Channel Quality of Service.
    sc_signal<sc_uint<C_S_AXI_ARUSER_WIDTH>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARUSER[PRAM_MASTER_NUM]; // User-defined AR Channel signals.
    sc_signal<sc_uint<1>,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARLOCK[PRAM_MASTER_NUM];                        // AXI Read address lock signal.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_ARVALID[PRAM_MASTER_NUM];                       // AXI Read address valid.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_X2X_BUFF_AXI_ARREADY[PRAM_MASTER_NUM];                       // AXI Read address ready.               
    // AXI Read Data Channel Signals (R)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>   SIG_X2X_BUFF_AXI_RID[PRAM_MASTER_NUM];        // AXI Read data response ID.
    sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>,SC_MANY_WRITERS>   SIG_X2X_BUFF_AXI_RDATA[PRAM_MASTER_NUM];    // AXI Read data.
    sc_signal<sc_uint<PRAM_AXI_RRESP>,SC_MANY_WRITERS>   SIG_X2X_BUFF_AXI_RRESP[PRAM_MASTER_NUM];        // AXI Read response code.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_X2X_BUFF_AXI_RLAST[PRAM_MASTER_NUM];                         // AXI Read data last signal.
    sc_signal<sc_uint<C_S_AXI_RUSER_WIDTH>,SC_MANY_WRITERS>   SIG_X2X_BUFF_AXI_RUSER[PRAM_MASTER_NUM];   // User-defined R Channel signals.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_X2X_BUFF_AXI_RVALID[PRAM_MASTER_NUM];                        // AXI Read valid.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_X2X_BUFF_AXI_RREADY[PRAM_MASTER_NUM];                        // Read ready.

    // signal interconnect to output port 
    // AXI Write Address Channel Signals (AW)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWID[PRAM_SLAVE_NUM];      // AXI address Write ID.
    sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWADDR[PRAM_SLAVE_NUM];  // AXI Write address.
    sc_signal<sc_uint<PRAM_AXI_AxLEN>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWLEN[PRAM_SLAVE_NUM];       // AXI address Write burst length.
    sc_signal<sc_uint<PRAM_AXI_AxSIZE>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWSIZE[PRAM_SLAVE_NUM];     // AXI address Write burst size.
    sc_signal<sc_uint<PRAM_AXI_AxBURST>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWBURST[PRAM_SLAVE_NUM];   // AXI address Write burst type.
    sc_signal<sc_uint<1>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWLOCK[PRAM_SLAVE_NUM];                       // AXI Write address lock signal.
    sc_signal<sc_uint<PRAM_AXI_AxCACHE>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWCACHE[PRAM_SLAVE_NUM];   // AXI Write address cache control signal.
    sc_signal<sc_uint<PRAM_AXI_AxPROT>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWPROT[PRAM_SLAVE_NUM];     // AXI Write address protection signal.
    sc_signal<sc_uint<PRAM_AXI_AxREGION>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWREGION[PRAM_SLAVE_NUM]; // Channel address region index
    sc_signal<sc_uint<PRAM_AXI_AxQOS>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWQOS[PRAM_SLAVE_NUM];       // Channel Quality of Service (QoS).
    sc_signal<sc_uint<C_S_AXI_AWUSER_WIDTH>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWUSER[PRAM_SLAVE_NUM];// User-defined AW Channel signals.
    sc_signal<bool,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWVALID[PRAM_SLAVE_NUM];                      // AXI Write address valid.
    sc_signal<bool,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_AWREADY[PRAM_SLAVE_NUM];                      // AXI Write data ready.

    // AXI Write Data Channel Signals (W)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_WID[PRAM_SLAVE_NUM];       // AXI3 Write ID.
    sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_WDATA[PRAM_SLAVE_NUM];   // AXI Write data.
    sc_signal<sc_uint<C_S_AXI_DATA_WIDTH / 8>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_WSTRB[PRAM_SLAVE_NUM];// AXI Write data strobes.
    sc_signal<bool,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_WLAST[PRAM_SLAVE_NUM];                        // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_signal<sc_uint<C_S_AXI_WUSER_WIDTH>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_WUSER[PRAM_SLAVE_NUM];  // User-defined W Channel signals.
    sc_signal<bool,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_WVALID[PRAM_SLAVE_NUM];                       // AXI Write data valid.
    sc_signal<bool,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_WREADY[PRAM_SLAVE_NUM];                       // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_BID[PRAM_SLAVE_NUM];       // AXI Write response ID.
    sc_signal<sc_uint<PRAM_AXI_RRESP>,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_BRESP[PRAM_SLAVE_NUM];       // AXI Write response code.
    sc_signal<bool,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_BUSER[PRAM_SLAVE_NUM];                        // User-defined B channel signals.
    sc_signal<bool,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_BVALID[PRAM_SLAVE_NUM];                       // AXI Write response valid.
    sc_signal<bool,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_BREADY[PRAM_SLAVE_NUM];                       // Write response ready.
    // AXI Read Address Channel Signals (AR)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARID[PRAM_SLAVE_NUM];      // AXI address Read ID.
    sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARADDR[PRAM_SLAVE_NUM];  // AXI Read address.
    sc_signal<sc_uint<PRAM_AXI_AxLEN>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARLEN[PRAM_SLAVE_NUM];       // AXI address Read burst length.
    sc_signal<sc_uint<PRAM_AXI_AxSIZE>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARSIZE[PRAM_SLAVE_NUM];     // AXI address Read burst size.
    sc_signal<sc_uint<PRAM_AXI_AxBURST>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARBURST[PRAM_SLAVE_NUM];   // AXI address Read burst type.
    sc_signal<sc_uint<1>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARLOCK[PRAM_SLAVE_NUM];                       // AXI Read address lock signal.
    sc_signal<sc_uint<PRAM_AXI_AxCACHE>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARCACHE[PRAM_SLAVE_NUM];   // AXI Read address cache control signal.
    sc_signal<sc_uint<PRAM_AXI_AxPROT>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARPROT[PRAM_SLAVE_NUM];     // AXI Read address protection signal.
    sc_signal<sc_uint<PRAM_AXI_AxREGION>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARREGION[PRAM_SLAVE_NUM]; // Channel address region index.
    sc_signal<sc_uint<PRAM_AXI_AxQOS>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARQOS[PRAM_SLAVE_NUM];       // Channel Quality of Service.
    sc_signal<sc_uint<C_S_AXI_ARUSER_WIDTH>,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARUSER[PRAM_SLAVE_NUM];// User-defined AR Channel signals.
    sc_signal<bool,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARVALID[PRAM_SLAVE_NUM];                      // AXI Read address valid.
    sc_signal<bool,SC_MANY_WRITERS>       SIG_ARBITER_X2X_AXI_ARREADY[PRAM_SLAVE_NUM];                      // AXI Read address ready.
    // AXI Read Data channel Signals (R)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_RID[PRAM_SLAVE_NUM];       // AXI Read data response ID.
    sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_RDATA[PRAM_SLAVE_NUM];   // AXI Read data.
    sc_signal<sc_uint<PRAM_AXI_RRESP>,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_RRESP[PRAM_SLAVE_NUM];       // AXI Read response code.
    sc_signal<bool,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_RLAST[PRAM_SLAVE_NUM];                        // AXI Read data last signal.
    sc_signal<sc_uint<C_S_AXI_RUSER_WIDTH>,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_RUSER[PRAM_SLAVE_NUM];  // User-defined R Channel signals.
    sc_signal<bool,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_RVALID[PRAM_SLAVE_NUM];                       // AXI Read valid.
    sc_signal<bool,SC_MANY_WRITERS>        SIG_ARBITER_X2X_AXI_RREADY[PRAM_SLAVE_NUM];                       // AXI Read ready.

    // AXI Write Address Channel Signals (AW)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWID[PRAM_MASTER_NUM];      // AXI address Write ID.
    sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWADDR[PRAM_MASTER_NUM];  // AXI Write address.
    sc_signal<sc_uint<PRAM_AXI_AxLEN>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWLEN[PRAM_MASTER_NUM];       // AXI address Write burst length.
    sc_signal<sc_uint<PRAM_AXI_AxSIZE>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWSIZE[PRAM_MASTER_NUM];     // AXI address Write burst size.
    sc_signal<sc_uint<PRAM_AXI_AxBURST>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWBURST[PRAM_MASTER_NUM];   // AXI address Write burst type.
    sc_signal<sc_uint<1>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWLOCK[PRAM_MASTER_NUM];                       // AXI Write address lock signal.
    sc_signal<sc_uint<PRAM_AXI_AxCACHE>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWCACHE[PRAM_MASTER_NUM];   // AXI Write address cache control signal.
    sc_signal<sc_uint<PRAM_AXI_AxPROT>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWPROT[PRAM_MASTER_NUM];     // AXI Write address protection signal.
    sc_signal<sc_uint<PRAM_AXI_AxREGION>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWREGION[PRAM_MASTER_NUM]; // Channel address region index
    sc_signal<sc_uint<PRAM_AXI_AxQOS>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWQOS[PRAM_MASTER_NUM];       // Channel Quality of Service (QoS).
    sc_signal<sc_uint<C_S_AXI_AWUSER_WIDTH>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWUSER[PRAM_MASTER_NUM];// User-defined AW Channel signals.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_AWVALID[PRAM_MASTER_NUM];                      // AXI Write address valid.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_AWPOPOUT[PRAM_MASTER_NUM];                     // AXI Write data ready.    
    // AXI Write Data Channel Signals (W)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_WID[PRAM_MASTER_NUM];       // AXI3 Write ID.
    sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_WDATA[PRAM_MASTER_NUM];   // AXI Write data.
    sc_signal<sc_uint<C_S_AXI_DATA_WIDTH / 8>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_WSTRB[PRAM_MASTER_NUM];// AXI Write data strobes.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_WLAST[PRAM_MASTER_NUM];                        // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_signal<sc_uint<C_S_AXI_WUSER_WIDTH>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_WUSER[PRAM_MASTER_NUM];  // User-defined W Channel signals.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_WVALID[PRAM_MASTER_NUM];                       // AXI Write data valid.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_WPOPOUT[PRAM_MASTER_NUM];                       // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_BID[PRAM_MASTER_NUM];       // AXI Write response ID.
    sc_signal<sc_uint<PRAM_AXI_RRESP>,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_BRESP[PRAM_MASTER_NUM];       // AXI Write response code.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_BUSER[PRAM_MASTER_NUM];                        // User-defined B channel signals.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_BVALID[PRAM_MASTER_NUM];                       // AXI Write response valid.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_BREADY[PRAM_MASTER_NUM];                       // Write response ready.
    // AXI Read Address Channel Signals (AR)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARID[PRAM_MASTER_NUM];      // AXI address Read ID.
    sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARADDR[PRAM_MASTER_NUM];  // AXI Read address.
    sc_signal<sc_uint<PRAM_AXI_AxLEN>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARLEN[PRAM_MASTER_NUM];       // AXI address Read burst length.
    sc_signal<sc_uint<PRAM_AXI_AxSIZE>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARSIZE[PRAM_MASTER_NUM];     // AXI address Read burst size.
    sc_signal<sc_uint<PRAM_AXI_AxBURST>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARBURST[PRAM_MASTER_NUM];   // AXI address Read burst type.
    sc_signal<sc_uint<1>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARLOCK[PRAM_MASTER_NUM];                       // AXI Read address lock signal.
    sc_signal<sc_uint<PRAM_AXI_AxCACHE>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARCACHE[PRAM_MASTER_NUM];   // AXI Read address cache control signal.
    sc_signal<sc_uint<PRAM_AXI_AxPROT>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARPROT[PRAM_MASTER_NUM];     // AXI Read address protection signal.
    sc_signal<sc_uint<PRAM_AXI_AxREGION>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARREGION[PRAM_MASTER_NUM]; // Channel address region index.
    sc_signal<sc_uint<PRAM_AXI_AxQOS>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARQOS[PRAM_MASTER_NUM];       // Channel Quality of Service.
    sc_signal<sc_uint<C_S_AXI_ARUSER_WIDTH>,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARUSER[PRAM_MASTER_NUM];// User-defined AR Channel signals.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_ARVALID[PRAM_MASTER_NUM];                      // AXI Read address valid.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_ARPOPOUT[PRAM_MASTER_NUM];                     // AXI Read address ready.
    // AXI Read Data channel Signals (R)
    sc_signal<sc_uint<C_S_AXI_ID_WIDTH>,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_RID[PRAM_MASTER_NUM];       // AXI Read data response ID.
    sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_RDATA[PRAM_MASTER_NUM];   // AXI Read data.
    sc_signal<sc_uint<PRAM_AXI_RRESP>,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_RRESP[PRAM_MASTER_NUM];       // AXI Read response code.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_RLAST[PRAM_MASTER_NUM];                        // AXI Read data last signal.
    sc_signal<sc_uint<C_S_AXI_RUSER_WIDTH>,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_RUSER[PRAM_MASTER_NUM];  // User-defined R Channel signals.
    sc_signal<bool,SC_MANY_WRITERS>   SIG_BUFF_DECODER_S_AXI_RVALID[PRAM_MASTER_NUM];                       // AXI Read valid.
    sc_signal<bool,SC_MANY_WRITERS>    SIG_BUFF_DECODER_S_AXI_RREADY[PRAM_MASTER_NUM];                       // AXI Read valid.
    //
    sc_signal<bool,SC_MANY_WRITERS> Test_in;
    sc_signal<bool,SC_MANY_WRITERS> Test_Out;
};

#endif //_X2X_H
