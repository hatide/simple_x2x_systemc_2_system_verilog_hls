// Unit Test Code for Class x2x:
#include <iostream>
#include "systemc.h"
#include "x2x.h" // Include the header file for class x2x.
#include "sstream"
#include <cstdlib>
#include <stdio.h>
using namespace std;

sc_signal<bool, SC_UNCHECKED_WRITERS> in_sig[2];
sc_signal<bool, SC_UNCHECKED_WRITERS> push_sig;
sc_signal<bool, SC_UNCHECKED_WRITERS> pop_sig;
sc_signal<bool, SC_UNCHECKED_WRITERS> reset_sig;
// sc_signal<bool, SC_UNCHECKED_WRITERS> clock_sig;
sc_clock clock_sig("clock_sig", 10, SC_NS);
// input signal
sc_signal<bool, SC_UNCHECKED_WRITERS> out_sig[2];
sc_signal<bool, SC_UNCHECKED_WRITERS> empty_sig;
sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>, SC_UNCHECKED_WRITERS> sig_address;
sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>, SC_UNCHECKED_WRITERS> sig_Data;
sc_signal<bool, SC_UNCHECKED_WRITERS> sig_valid;
// output signal
sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>, SC_UNCHECKED_WRITERS> sig_OUTaddress;
sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>, SC_UNCHECKED_WRITERS> sig_OUTData;
sc_signal<bool, SC_UNCHECKED_WRITERS> sig_OUTValid;

// AXI Write Address Channel Signals (AW)
sc_signal<sc_uint<C_S_AXI_ID_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWID[PRAM_MASTER_NUM];       // AXI address Write ID.
sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWADDR[PRAM_MASTER_NUM];   // AXI Write address.
sc_signal<sc_uint<PRAM_AXI_AxLEN>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWLEN[PRAM_MASTER_NUM];        // AXI address Write burst length.
sc_signal<sc_uint<PRAM_AXI_AxSIZE>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWSIZE[PRAM_MASTER_NUM];      // AXI address Write burst size.
sc_signal<sc_uint<PRAM_AXI_AxBURST>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWBURST[PRAM_MASTER_NUM];    // AXI address Write burst type.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWLOCK[PRAM_MASTER_NUM];                    // AXI Write address lock signal.
sc_signal<sc_uint<PRAM_AXI_AxCACHE>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWCACHE[PRAM_MASTER_NUM];    // AXI Write address cache control signal.
sc_signal<sc_uint<PRAM_AXI_AxPROT>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWPROT[PRAM_MASTER_NUM];      // AXI Write address protection signal.
sc_signal<sc_uint<PRAM_AXI_AxREGION>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWREGION[PRAM_MASTER_NUM];  // Channel address region index
sc_signal<sc_uint<PRAM_AXI_AxQOS>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWQOS[PRAM_MASTER_NUM];        // Channel Quality of Service (QoS).
sc_signal<sc_uint<C_S_AXI_AWUSER_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWUSER[PRAM_MASTER_NUM]; // User-defined AW Channel signals.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWVALID[PRAM_MASTER_NUM];                   // AXI Write address valid.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_AWREADY[PRAM_MASTER_NUM];                   // AXI Write address ready.
// AXI Write Data Channel Signals (W)
sc_signal<sc_uint<C_S_AXI_ID_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_WID[PRAM_MASTER_NUM];         // AXI3 Write ID.
sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_WDATA[PRAM_MASTER_NUM];     // AXI Write data.
sc_signal<sc_uint<C_S_AXI_DATA_WIDTH / 8>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_WSTRB[PRAM_MASTER_NUM]; // AXI Write data strobes.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_WLAST[PRAM_MASTER_NUM];                      // AXI Write data last signal. Indicates the last transfer in a Writeburst.
sc_signal<sc_uint<C_S_AXI_WUSER_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_WUSER[PRAM_MASTER_NUM];    // User-defined W Channel signals.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_WVALID[PRAM_MASTER_NUM];                     // AXI Write data valid.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_WREADY[PRAM_MASTER_NUM];                     // AXI Write data ready.
// AXI Write Response Channel Signals (B)
sc_signal<sc_uint<C_S_AXI_ID_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_BID[PRAM_MASTER_NUM]; // AXI Write response ID.
sc_signal<sc_uint<PRAM_AXI_RRESP>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_BRESP[PRAM_MASTER_NUM]; // AXI Write response code.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_BUSER[PRAM_MASTER_NUM];              // User-defined B channel signals.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_BVALID[PRAM_MASTER_NUM];             // AXI Write response valid.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_BREADY[PRAM_MASTER_NUM];
// AXI Read Address Channel Signals (AR)
sc_signal<sc_uint<C_S_AXI_ID_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARID[PRAM_MASTER_NUM];       // AXI address Read ID.
sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARADDR[PRAM_MASTER_NUM];   // AXI Read address.
sc_signal<sc_uint<PRAM_AXI_AxLEN>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARLEN[PRAM_MASTER_NUM];        // AXI address Read burst length.
sc_signal<sc_uint<PRAM_AXI_AxSIZE>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARSIZE[PRAM_MASTER_NUM];      // AXI address Read burst size.
sc_signal<sc_uint<PRAM_AXI_AxBURST>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARBURST[PRAM_MASTER_NUM];    // AXI address Read burst type.
sc_signal<sc_uint<PRAM_AXI_AxCACHE>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARCACHE[PRAM_MASTER_NUM];    // AXI Read address cache control signal.
sc_signal<sc_uint<PRAM_AXI_AxPROT>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARPROT[PRAM_MASTER_NUM];      // AXI Read address protection signal.
sc_signal<sc_uint<PRAM_AXI_AxREGION>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARREGION[PRAM_MASTER_NUM];  // Channel address region index.
sc_signal<sc_uint<PRAM_AXI_AxQOS>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARQOS[PRAM_MASTER_NUM];        // Channel Quality of Service.
sc_signal<sc_uint<C_S_AXI_ARUSER_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARUSER[PRAM_MASTER_NUM]; // User-defined AR Channel signals.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARLOCK[PRAM_MASTER_NUM];                    // AXI Read address lock signal.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARVALID[PRAM_MASTER_NUM];                   // AXI Read address valid.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_ARREADY[PRAM_MASTER_NUM];                   // AXI Read address ready.
// AXI Read Data Channel Signals (R)
sc_signal<sc_uint<C_S_AXI_ID_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_RID[PRAM_MASTER_NUM];      // AXI Read data response ID.
sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_RDATA[PRAM_MASTER_NUM];  // AXI Read data.
sc_signal<sc_uint<PRAM_AXI_RRESP>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_RRESP[PRAM_MASTER_NUM];      // AXI Read response code.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_RLAST[PRAM_MASTER_NUM];                   // AXI Read data last signal.
sc_signal<sc_uint<C_S_AXI_RUSER_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_RUSER[PRAM_MASTER_NUM]; // User-defined R Channel signals.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_RVALID[PRAM_MASTER_NUM];                  // AXI Read valid.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_S_AXI_RREADY[PRAM_MASTER_NUM];                  // Read ready.
// output signal
//*****************************
//********Master side signal***
//*****************************
// AXI Write Address Channel Signals (AW)

sc_signal<sc_uint<C_S_AXI_ID_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWID[PRAM_SLAVE_NUM];       // AXI address Write ID.
sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWADDR[PRAM_SLAVE_NUM];   // AXI Write address.
sc_signal<sc_uint<PRAM_AXI_AxLEN>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWLEN[PRAM_SLAVE_NUM];        // AXI address Write burst length.
sc_signal<sc_uint<PRAM_AXI_AxSIZE>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWSIZE[PRAM_SLAVE_NUM];      // AXI address Write burst size.
sc_signal<sc_uint<PRAM_AXI_AxBURST>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWBURST[PRAM_SLAVE_NUM];    // AXI address Write burst type.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWLOCK[PRAM_SLAVE_NUM];                    // AXI Write address lock signal.
sc_signal<sc_uint<PRAM_AXI_AxCACHE>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWCACHE[PRAM_SLAVE_NUM];    // AXI Write address cache control signal.
sc_signal<sc_uint<PRAM_AXI_AxPROT>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWPROT[PRAM_SLAVE_NUM];      // AXI Write address protection signal.
sc_signal<sc_uint<PRAM_AXI_AxREGION>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWREGION[PRAM_SLAVE_NUM];  // Channel address region index
sc_signal<sc_uint<PRAM_AXI_AxQOS>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWQOS[PRAM_SLAVE_NUM];        // Channel Quality of Service (QoS).
sc_signal<sc_uint<C_S_AXI_AWUSER_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWUSER[PRAM_SLAVE_NUM]; // User-defined AW Channel signals.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWVALID[PRAM_SLAVE_NUM];                   // AXI Write address valid.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_AWREADY[PRAM_SLAVE_NUM];                   // AXI Write data ready.

// AXI Write Data Channel Signals (W)
sc_signal<sc_uint<C_S_AXI_ID_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_WID[PRAM_SLAVE_NUM];         // AXI3 Write ID.
sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_WDATA[PRAM_SLAVE_NUM];     // AXI Write data.
sc_signal<sc_uint<C_S_AXI_DATA_WIDTH / 8>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_WSTRB[PRAM_SLAVE_NUM]; // AXI Write data strobes.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_WLAST[PRAM_SLAVE_NUM];                      // AXI Write data last signal. Indicates the last transfer in a Writeburst.
sc_signal<sc_uint<C_S_AXI_WUSER_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_WUSER[PRAM_SLAVE_NUM];    // User-defined W Channel signals.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_WVALID[PRAM_SLAVE_NUM];                     // AXI Write data valid.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_WREADY[PRAM_SLAVE_NUM];                     // AXI Write data ready.
// AXI Write Response Channel Signals (B)
sc_signal<sc_uint<C_S_AXI_ID_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_BID[PRAM_SLAVE_NUM]; // AXI Write response ID.
sc_signal<sc_uint<PRAM_AXI_RRESP>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_BRESP[PRAM_SLAVE_NUM]; // AXI Write response code.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_BUSER[PRAM_SLAVE_NUM];              // User-defined B channel signals.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_BVALID[PRAM_SLAVE_NUM];             // AXI Write response valid.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_BREADY[PRAM_SLAVE_NUM];             // Write response ready.
// AXI Read Address Channel Signals (AR)
sc_signal<sc_uint<C_S_AXI_ID_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARID[PRAM_SLAVE_NUM];       // AXI address Read ID.
sc_signal<sc_uint<C_S_AXI_ADDR_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARADDR[PRAM_SLAVE_NUM];   // AXI Read address.
sc_signal<sc_uint<PRAM_AXI_AxLEN>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARLEN[PRAM_SLAVE_NUM];        // AXI address Read burst length.
sc_signal<sc_uint<PRAM_AXI_AxSIZE>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARSIZE[PRAM_SLAVE_NUM];      // AXI address Read burst size.
sc_signal<sc_uint<PRAM_AXI_AxBURST>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARBURST[PRAM_SLAVE_NUM];    // AXI address Read burst type.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARLOCK[PRAM_SLAVE_NUM];                    // AXI Read address lock signal.
sc_signal<sc_uint<PRAM_AXI_AxCACHE>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARCACHE[PRAM_SLAVE_NUM];    // AXI Read address cache control signal.
sc_signal<sc_uint<PRAM_AXI_AxPROT>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARPROT[PRAM_SLAVE_NUM];      // AXI Read address protection signal.
sc_signal<sc_uint<PRAM_AXI_AxREGION>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARREGION[PRAM_SLAVE_NUM];  // Channel address region index.
sc_signal<sc_uint<PRAM_AXI_AxQOS>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARQOS[PRAM_SLAVE_NUM];        // Channel Quality of Service.
sc_signal<sc_uint<C_S_AXI_ARUSER_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARUSER[PRAM_SLAVE_NUM]; // User-defined AR Channel signals.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARVALID[PRAM_SLAVE_NUM];                   // AXI Read address valid.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_ARREADY[PRAM_SLAVE_NUM];                   // AXI Read address ready.
// AXI Read Data channel Signals (R)
sc_signal<sc_uint<C_S_AXI_ID_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_RID[PRAM_SLAVE_NUM];      // AXI Read data response ID.
sc_signal<sc_uint<C_S_AXI_DATA_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_RDATA[PRAM_SLAVE_NUM];  // AXI Read data.
sc_signal<sc_uint<PRAM_AXI_RRESP>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_RRESP[PRAM_SLAVE_NUM];      // AXI Read response code.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_RLAST[PRAM_SLAVE_NUM];                   // AXI Read data last signal.
sc_signal<sc_uint<C_S_AXI_RUSER_WIDTH>, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_RUSER[PRAM_SLAVE_NUM]; // User-defined R Channel signals.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_RVALID[PRAM_SLAVE_NUM];                  // AXI Read valid.
sc_signal<bool, SC_UNCHECKED_WRITERS> SIGNAL_M_AXI_RREADY[PRAM_SLAVE_NUM];                  // AXI Read ready.
// ------------------------------------------------------------------
// module
// x2x *pX2X = NULL;

sc_trace_file *tracefile = sc_create_vcd_trace_file("tracefile");

void SetAddress(unsigned long long Address)
{

    SIGNAL_S_AXI_AWADDR[0].write((Address)&0x1);
    sig_valid.write(true);
}

void set_data(unsigned long long Data)
{

    SIGNAL_S_AXI_WDATA[0].write((Data)&0x1);
}

void X2XTest_Init(x2x *x2x_module)
{

    x2x_module->ACLK(clock_sig);
    x2x_module->ARESETN(reset_sig);
    tracefile = sc_create_vcd_trace_file("x2x_simple");
    sc_trace(tracefile, clock_sig, "clock_sig");
    sc_trace(tracefile, reset_sig, "reset_sig");
    ostringstream nameSigaddress;
    nameSigaddress << "sig_address";
    ostringstream nameSigdata;
    nameSigdata << "sig_Data";
    // coonec
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {

        x2x_module->S_AXI_AWID[index](SIGNAL_S_AXI_AWID[index]);

        x2x_module->S_AXI_AWADDR[index](SIGNAL_S_AXI_AWADDR[index]);

        x2x_module->S_AXI_AWLEN[index](SIGNAL_S_AXI_AWLEN[index]);

        x2x_module->S_AXI_AWSIZE[index](SIGNAL_S_AXI_AWSIZE[index]);

        x2x_module->S_AXI_AWBURST[index](SIGNAL_S_AXI_AWBURST[index]);

        x2x_module->S_AXI_AWCACHE[index](SIGNAL_S_AXI_AWCACHE[index]);

        x2x_module->S_AXI_AWPROT[index](SIGNAL_S_AXI_AWPROT[index]);

        x2x_module->S_AXI_AWREGION[index](SIGNAL_S_AXI_AWREGION[index]);

        x2x_module->S_AXI_AWQOS[index](SIGNAL_S_AXI_AWQOS[index]);

        x2x_module->S_AXI_AWUSER[index](SIGNAL_S_AXI_AWUSER[index]);

        x2x_module->S_AXI_AWLOCK[index](SIGNAL_S_AXI_AWLOCK[index]);
        x2x_module->S_AXI_AWVALID[index](SIGNAL_S_AXI_AWVALID[index]);
        x2x_module->S_AXI_AWREADY[index](SIGNAL_S_AXI_AWREADY[index]);
    }
    // AR
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {

        x2x_module->S_AXI_ARID[index](SIGNAL_S_AXI_ARID[index]);

        x2x_module->S_AXI_ARADDR[index](SIGNAL_S_AXI_ARADDR[index]);

        x2x_module->S_AXI_ARLEN[index](SIGNAL_S_AXI_ARLEN[index]);

        x2x_module->S_AXI_ARSIZE[index](SIGNAL_S_AXI_ARSIZE[index]);

        x2x_module->S_AXI_ARBURST[index](SIGNAL_S_AXI_ARBURST[index]);

        x2x_module->S_AXI_ARCACHE[index](SIGNAL_S_AXI_ARCACHE[index]);

        x2x_module->S_AXI_ARPROT[index](SIGNAL_S_AXI_ARPROT[index]);

        x2x_module->S_AXI_ARREGION[index](SIGNAL_S_AXI_ARREGION[index]);

        x2x_module->S_AXI_ARQOS[index](SIGNAL_S_AXI_ARQOS[index]);

        x2x_module->S_AXI_ARUSER[index](SIGNAL_S_AXI_ARUSER[index]);

        x2x_module->S_AXI_ARLOCK[index](SIGNAL_S_AXI_ARLOCK[index]);
        x2x_module->S_AXI_ARVALID[index](SIGNAL_S_AXI_ARVALID[index]);
        x2x_module->S_AXI_ARREADY[index](SIGNAL_S_AXI_ARREADY[index]);
    }
    // W
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {

        x2x_module->S_AXI_WID[index](SIGNAL_S_AXI_WID[index]);

        x2x_module->S_AXI_WDATA[index](SIGNAL_S_AXI_WDATA[index]);
        x2x_module->S_AXI_WSTRB[index](SIGNAL_S_AXI_WSTRB[index]);

        x2x_module->S_AXI_WLAST[index](SIGNAL_S_AXI_WLAST[index]);

        x2x_module->S_AXI_WUSER[index](SIGNAL_S_AXI_WUSER[index]);

        x2x_module->S_AXI_WVALID[index](SIGNAL_S_AXI_WVALID[index]);
        x2x_module->S_AXI_WREADY[index](SIGNAL_S_AXI_WREADY[index]);
    }
    // B
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {

        x2x_module->S_AXI_BID[index](SIGNAL_S_AXI_BID[index]);

        x2x_module->S_AXI_BRESP[index](SIGNAL_S_AXI_BRESP[index]);

        x2x_module->S_AXI_BUSER[index](SIGNAL_S_AXI_BUSER[index]);
        x2x_module->S_AXI_BVALID[index](SIGNAL_S_AXI_BVALID[index]);
        x2x_module->S_AXI_BREADY[index](SIGNAL_S_AXI_BREADY[index]);
    }
    // R
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {

        x2x_module->S_AXI_RID[index](SIGNAL_S_AXI_RID[index]);

        x2x_module->S_AXI_RDATA[index](SIGNAL_S_AXI_RDATA[index]);

        x2x_module->S_AXI_RRESP[index](SIGNAL_S_AXI_RRESP[index]);

        x2x_module->S_AXI_RUSER[index](SIGNAL_S_AXI_RUSER[index]);
        x2x_module->S_AXI_RLAST[index](SIGNAL_S_AXI_RLAST[index]);
        x2x_module->S_AXI_RVALID[index](SIGNAL_S_AXI_RVALID[index]);
        x2x_module->S_AXI_RREADY[index](SIGNAL_S_AXI_RREADY[index]);
    }

    //// *************************x2x_arbiter to output port*************************
    // for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
    //         x2x_module->M_AXI_AWID[index](SIGNAL_M_AXI_AWID[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++) {
    //         x2x_module->M_AXI_AWADDR[index](SIGNAL_M_AXI_AWADDR[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++) {
    //         x2x_module->M_AXI_AWLEN[index](SIGNAL_M_AXI_AWLEN[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++) {
    //         x2x_module->M_AXI_AWSIZE[index](SIGNAL_M_AXI_AWSIZE[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++) {
    //         x2x_module->M_AXI_AWBURST[index](SIGNAL_M_AXI_AWBURST[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++) {
    //         x2x_module->M_AXI_AWCACHE[index](SIGNAL_M_AXI_AWCACHE[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++) {
    //         x2x_module->M_AXI_AWPROT[index](SIGNAL_M_AXI_AWPROT[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++) {
    //         x2x_module->M_AXI_AWREGION[index](SIGNAL_M_AXI_AWREGION[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++) {
    //         x2x_module->M_AXI_AWQOS[index](SIGNAL_M_AXI_AWQOS[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++) {
    //         x2x_module->M_AXI_AWUSER[index](SIGNAL_M_AXI_AWUSER[index]);
    //     }
    //     x2x_module->M_AXI_AWLOCK[index](SIGNAL_M_AXI_AWLOCK[index]);
    //     x2x_module->M_AXI_AWVALID[index](SIGNAL_M_AXI_AWVALID[index]);
    //     x2x_module->M_AXI_AWREADY[index](SIGNAL_M_AXI_AWREADY[index]);
    // }
    //// AR
    // for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
    //         x2x_module->M_AXI_ARID[index](SIGNAL_M_AXI_ARID[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++) {
    //         x2x_module->M_AXI_ARADDR[index](SIGNAL_M_AXI_ARADDR[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++) {
    //         x2x_module->M_AXI_ARLEN[index](SIGNAL_M_AXI_ARLEN[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++) {
    //         x2x_module->M_AXI_ARSIZE[index](SIGNAL_M_AXI_ARSIZE[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++) {
    //         x2x_module->M_AXI_ARBURST[index](SIGNAL_M_AXI_ARBURST[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++) {
    //         x2x_module->M_AXI_ARCACHE[index](SIGNAL_M_AXI_ARCACHE[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++) {
    //         x2x_module->M_AXI_ARPROT[index](SIGNAL_M_AXI_ARPROT[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++) {
    //         x2x_module->M_AXI_ARREGION[index](SIGNAL_M_AXI_ARREGION[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++) {
    //         x2x_module->M_AXI_ARQOS[index](SIGNAL_M_AXI_ARQOS[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++) {
    //         x2x_module->M_AXI_ARUSER[index](SIGNAL_M_AXI_ARUSER[index]);
    //     }
    //     x2x_module->M_AXI_ARLOCK[index](SIGNAL_M_AXI_ARLOCK[index]);
    //     x2x_module->M_AXI_ARVALID[index](SIGNAL_M_AXI_ARVALID[index]);
    //     x2x_module->M_AXI_ARREADY[index](SIGNAL_M_AXI_ARREADY[index]);
    // }
    //// W
    // for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
    //         x2x_module->M_AXI_WID[index](SIGNAL_M_AXI_WID[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++) {
    //         x2x_module->M_AXI_WDATA[index](SIGNAL_M_AXI_WDATA[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH / 8; index_port++) {
    //         x2x_module->M_AXI_WSTRB[index](SIGNAL_M_AXI_WSTRB[index]);
    //     }
    //     x2x_module->M_AXI_WLAST[index](SIGNAL_M_AXI_WLAST[index]);
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_WUSER_WIDTH; index_port++) {
    //         x2x_module->M_AXI_WUSER[index](SIGNAL_M_AXI_WUSER[index]);
    //     }
    //     x2x_module->M_AXI_WVALID[index](SIGNAL_M_AXI_WVALID[index]);
    //     x2x_module->M_AXI_WREADY[index](SIGNAL_M_AXI_WREADY[index]);
    // }
    //// B
    // for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
    //         x2x_module->M_AXI_BID[index](SIGNAL_M_AXI_BID[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++) {
    //         x2x_module->M_AXI_BRESP[index](SIGNAL_M_AXI_BRESP[index]);
    //     }
    //     x2x_module->M_AXI_BUSER[index](SIGNAL_M_AXI_BUSER[index]);
    //     x2x_module->M_AXI_BVALID[index](SIGNAL_M_AXI_BVALID[index]);
    //     x2x_module->M_AXI_BREADY[index](SIGNAL_M_AXI_BREADY[index]);
    // }
    //// R
    // for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
    //         x2x_module->M_AXI_RID[index](SIGNAL_M_AXI_RID[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++) {
    //         x2x_module->M_AXI_RDATA[index](SIGNAL_M_AXI_RDATA[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++) {
    //         x2x_module->M_AXI_RRESP[index](SIGNAL_M_AXI_RRESP[index]);
    //     }
    //     for (unsigned int index_port = 0; index_port < C_S_AXI_RUSER_WIDTH; index_port++) {
    //         x2x_module->M_AXI_RUSER[index](SIGNAL_M_AXI_RUSER[index]);
    //     }
    //     x2x_module->M_AXI_RLAST[index](SIGNAL_M_AXI_RLAST[index]);
    //     x2x_module->M_AXI_RVALID[index](SIGNAL_M_AXI_RVALID[index]);
    //     x2x_module->M_AXI_RREADY[index](SIGNAL_M_AXI_RREADY[index]);
    // }

    sc_trace(tracefile, sig_address, nameSigaddress.str());
    sc_trace(tracefile, sig_Data, nameSigdata.str());

    x2x_module->S_AXI_AWADDR[0](sig_address);
    x2x_module->S_AXI_WDATA[0](sig_Data);

    // for (unsigned int i = 0, j = 0; i < C_S_AXI_ADDR_WIDTH, j < C_S_AXI_DATA_WIDTH; i++, j++)
    // {
    //     x2x_module->S_AXI_AWADDR[0][i](sig_address[i]);
    //     x2x_module->S_AXI_WDATA[0][j](sig_Data[j]);
    // }
    x2x_module->S_AXI_AWVALID[0](sig_valid);
    x2x_module->M_AXI_AWVALID[0](sig_OUTValid);
}

void X2XTest_DeInit(void)
{
    //  delete pX2X;
}

int sc_main(int argc, char *argv[])
{
    // Create a clock signal and set its period to 10 ns.
    sc_clock clk("clk", 10, SC_NS);
    sc_signal<bool> ARESETN_signal;
    // Create an instance of the x2x module and name it 'x2x'.
    x2x *x2x_module = new x2x("simpleX2X");
    X2XTest_Init(x2x_module);
    // Connect the input signals to the x2x instance.
    //  x2x.ACLK(clk);
    //  x2x.ARESETN(ARESETN_signal);
    // Create a reset signal and set it to false initially.      bool reset = false;      bool enable = true;

    // Initialize the output signal with some value before running the testbench.       sc_uint<4> initData = 5;       x2x->data = initData;       cout << "Initial Data Value: " << initData
    sc_start(10, SC_NS);
    SetAddress(0x1000);
    set_data(0xFAFAFAFA);
    sc_start(10, SC_NS);
    // Close tracefile
    sc_close_vcd_trace_file(tracefile);
    return 0;
}