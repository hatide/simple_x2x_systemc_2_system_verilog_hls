/**
 * X2x_buffer IP
 * Created by Tien Tran
 */

#include "x2x_fifo.h"
#include "AXI_Interconnection.h"

#ifndef _X2x_buffer_H
#define _X2x_buffer_H

class X2x_buffer : public sc_module
{
private:
    x2x_fifo<C_S_AXI_ID_WIDTH> S_AXI_AWID_aw_fifo;       // AXI address Write ID.
    x2x_fifo<C_S_AXI_ADDR_WIDTH> S_AXI_AWADDR_aw_fifo;   // AXI Write address.
    x2x_fifo<PRAM_AXI_AxLEN> S_AXI_AWLEN_aw_fifo;        // AXI address Write burst length.
    x2x_fifo<PRAM_AXI_AxSIZE> S_AXI_AWSIZE_aw_fifo;      // AXI address Write burst size.
    x2x_fifo<PRAM_AXI_AxBURST> S_AXI_AWBURST_aw_fifo;    // AXI address Write burst type.
    x2x_fifo<1> S_AXI_AWLOCK_aw_fifo;                    // AXI Write address lock signal.
    x2x_fifo<PRAM_AXI_AxCACHE> S_AXI_AWCACHE_aw_fifo;    // AXI Write address cache control signal.
    x2x_fifo<PRAM_AXI_AxPROT> S_AXI_AWPROT_aw_fifo;      // AXI Write address protection signal.
    x2x_fifo<PRAM_AXI_AxREGION> S_AXI_AWREGION_aw_fifo;  // Channel address region index
    x2x_fifo<PRAM_AXI_AxQOS> S_AXI_AWQOS_aw_fifo;        // Channel Quality of Service (QoS).
    x2x_fifo<C_S_AXI_AWUSER_WIDTH> S_AXI_AWUSER_aw_fifo; // User-defined AW Channel signals.

    x2x_fifo<C_S_AXI_ID_WIDTH> S_AXI_WID_w_fifo;         // AXI3 Write ID.
    x2x_fifo<C_S_AXI_DATA_WIDTH> S_AXI_WDATA_w_fifo;     // AXI Write data.
    x2x_fifo<C_S_AXI_DATA_WIDTH / 8> S_AXI_WSTRB_w_fifo; // AXI Write data strobes.
    x2x_fifo<1> S_AXI_WLAST_w_fifo;                      // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    x2x_fifo<C_S_AXI_WUSER_WIDTH> S_AXI_WUSER_w_fifo;    // User-defined W Channel signals.

    x2x_fifo<C_S_AXI_ID_WIDTH> S_AXI_ARID_ar_fifo;       // AXI address Read ID.
    x2x_fifo<C_S_AXI_ADDR_WIDTH> S_AXI_ARADDR_ar_fifo;   // AXI Read address.
    x2x_fifo<PRAM_AXI_AxLEN> S_AXI_ARLEN_ar_fifo;        // AXI address Read burst length.
    x2x_fifo<PRAM_AXI_AxSIZE> S_AXI_ARSIZE_ar_fifo;      // AXI address Read burst size.
    x2x_fifo<PRAM_AXI_AxBURST> S_AXI_ARBURST_ar_fifo;    // AXI address Read burst type.
    x2x_fifo<PRAM_AXI_AxCACHE> S_AXI_ARCACHE_ar_fifo;    // AXI Read address cache control signal.
    x2x_fifo<PRAM_AXI_AxPROT> S_AXI_ARPROT_ar_fifo;      // AXI Read address protection signal.
    x2x_fifo<PRAM_AXI_AxREGION> S_AXI_ARREGION_ar_fifo;  // Channel address region index.
    x2x_fifo<PRAM_AXI_AxQOS> S_AXI_ARQOS_ar_fifo;        // Channel Quality of Service.
    x2x_fifo<C_S_AXI_ARUSER_WIDTH> S_AXI_ARUSER_ar_fifo; // User-defined AR Channel signals.
    x2x_fifo<1> S_AXI_ARLOCK_ar_fifo;                    // AXI Read address lock signal.

    // Method
    void handle_aw_push_method();
    void handle_w_push_method();
    void handle_ar_push_method();

    // signal
    sc_signal<bool, SC_UNCHECKED_WRITERS> aw_fifo_push_signal;
    sc_signal<bool, SC_UNCHECKED_WRITERS> ar_fifo_push_signal;
    sc_signal<bool, SC_UNCHECKED_WRITERS> w_fifo_push_signal;

public:
    X2x_buffer(sc_module_name name);
    X2x_buffer(){};
    ~X2x_buffer();
    // global port
    sc_in<bool> ACLK;    // AXI bus clock.
    sc_in<bool> ARESETN; // AXI active-Low reset
    sc_in<bool> AwPop;
    sc_in<bool> WPop;
    sc_in<bool> ArPop;
    sc_out<bool> AwFull;
    sc_in<bool> WFull;
    sc_out<bool> ARFull;
    //*****************************
    //********Slave side signal****
    //*****************************
    // AXI Write Address Channel Signals (AW)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>> S_AXI_AWID;       // AXI address Write ID.
    sc_in<sc_uint<C_S_AXI_ADDR_WIDTH>> S_AXI_AWADDR;   // AXI Write address.
    sc_in<sc_uint<PRAM_AXI_AxLEN>> S_AXI_AWLEN;        // AXI address Write burst length.
    sc_in<sc_uint<PRAM_AXI_AxSIZE>> S_AXI_AWSIZE;      // AXI address Write burst size.
    sc_in<sc_uint<PRAM_AXI_AxBURST>> S_AXI_AWBURST;    // AXI address Write burst type.
    sc_in<sc_uint<1>> S_AXI_AWLOCK;                    // AXI Write address lock signal.
    sc_in<sc_uint<PRAM_AXI_AxCACHE>> S_AXI_AWCACHE;    // AXI Write address cache control signal.
    sc_in<sc_uint<PRAM_AXI_AxPROT>> S_AXI_AWPROT;      // AXI Write address protection signal.
    sc_in<sc_uint<PRAM_AXI_AxREGION>> S_AXI_AWREGION;  // Channel address region index
    sc_in<sc_uint<PRAM_AXI_AxQOS>> S_AXI_AWQOS;        // Channel Quality of Service (QoS).
    sc_in<sc_uint<C_S_AXI_AWUSER_WIDTH>> S_AXI_AWUSER; // User-defined AW Channel signals.
    sc_in<bool> S_AXI_AWVALID;                   // AXI Write address valid.
    sc_out<bool> S_AXI_AWREADY;                  // AXI Write address ready.
    // AXI Write Data Channel Signals (W)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>> S_AXI_WID;         // AXI3 Write ID.
    sc_in<sc_uint<C_S_AXI_DATA_WIDTH>> S_AXI_WDATA;     // AXI Write data.
    sc_in<sc_uint<C_S_AXI_DATA_WIDTH / 8>> S_AXI_WSTRB; // AXI Write data strobes.
    sc_in<bool> S_AXI_WLAST;                      // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_in<sc_uint<C_S_AXI_WUSER_WIDTH>> S_AXI_WUSER;    // User-defined W Channel signals.
    sc_in<bool> S_AXI_WVALID;                     // AXI Write data valid.
    sc_out<bool> S_AXI_WREADY;                    // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>> S_AXI_BID; // AXI Write response ID.
    sc_out<sc_uint<PRAM_AXI_RRESP>> S_AXI_BRESP; // AXI Write response code.
    sc_out<bool> S_AXI_BUSER;              // User-defined B channel signals.
    sc_out<bool> S_AXI_BVALID;             // AXI Write response valid.
    sc_in<bool> S_AXI_BREADY;
    // AXI Read Address Channel Signals (AR)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>> S_AXI_ARID;       // AXI address Read ID.
    sc_in<sc_uint<C_S_AXI_ADDR_WIDTH>> S_AXI_ARADDR;   // AXI Read address.
    sc_in<sc_uint<PRAM_AXI_AxLEN>> S_AXI_ARLEN;        // AXI address Read burst length.
    sc_in<sc_uint<PRAM_AXI_AxSIZE>> S_AXI_ARSIZE;      // AXI address Read burst size.
    sc_in<sc_uint<PRAM_AXI_AxBURST>> S_AXI_ARBURST;    // AXI address Read burst type.
    sc_in<sc_uint<PRAM_AXI_AxCACHE>> S_AXI_ARCACHE;    // AXI Read address cache control signal.
    sc_in<sc_uint<PRAM_AXI_AxPROT>> S_AXI_ARPROT;      // AXI Read address protection signal.
    sc_in<sc_uint<PRAM_AXI_AxREGION>> S_AXI_ARREGION;  // Channel address region index.
    sc_in<sc_uint<PRAM_AXI_AxQOS>> S_AXI_ARQOS;        // Channel Quality of Service.
    sc_in<sc_uint<C_S_AXI_ARUSER_WIDTH>> S_AXI_ARUSER; // User-defined AR Channel signals.
    sc_in<sc_uint<1>> S_AXI_ARLOCK;                    // AXI Read address lock signal.
    sc_in<bool> S_AXI_ARVALID;                   // AXI Read address valid.
    sc_out<bool> S_AXI_ARREADY;                  // AXI Read address ready.
    // AXI Read Data Channel Signals (R)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>> S_AXI_RID;      // AXI Read data response ID.
    sc_out<sc_uint<C_S_AXI_DATA_WIDTH>> S_AXI_RDATA;  // AXI Read data.
    sc_out<sc_uint<PRAM_AXI_RRESP>> S_AXI_RRESP;      // AXI Read response code.
    sc_out<bool> S_AXI_RLAST;                   // AXI Read data last signal.
    sc_out<sc_uint<C_S_AXI_RUSER_WIDTH>> S_AXI_RUSER; // User-defined R Channel signals.
    sc_out<bool> S_AXI_RVALID;                  // AXI Read valid.
    sc_in<bool> S_AXI_RREADY;                   // Read ready.
    // output signal
    //*****************************
    //********Master side signal***
    //*****************************
    // AXI Write Address Channel Signals (AW)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>> M_AXI_AWID;       // AXI address Write ID.
    sc_out<sc_uint<C_S_AXI_ADDR_WIDTH>> M_AXI_AWADDR;   // AXI Write address.
    sc_out<sc_uint<PRAM_AXI_AxLEN>> M_AXI_AWLEN;        // AXI address Write burst length.
    sc_out<sc_uint<PRAM_AXI_AxSIZE>> M_AXI_AWSIZE;      // AXI address Write burst size.
    sc_out<sc_uint<PRAM_AXI_AxBURST>> M_AXI_AWBURST;    // AXI address Write burst type.
    sc_out<sc_uint<1>> M_AXI_AWLOCK;                    // AXI Write address lock signal.
    sc_out<sc_uint<PRAM_AXI_AxCACHE>> M_AXI_AWCACHE;    // AXI Write address cache control signal.
    sc_out<sc_uint<PRAM_AXI_AxPROT>> M_AXI_AWPROT;      // AXI Write address protection signal.
    sc_out<sc_uint<PRAM_AXI_AxREGION>> M_AXI_AWREGION;  // Channel address region index
    sc_out<sc_uint<PRAM_AXI_AxQOS>> M_AXI_AWQOS;        // Channel Quality of Service (QoS).
    sc_out<sc_uint<C_S_AXI_AWUSER_WIDTH>> M_AXI_AWUSER; // User-defined AW Channel signals.
    sc_out<bool> M_AXI_AWVALID;                   // AXI Write address valid.

    // AXI Write Data Channel Signals (W)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>> M_AXI_WID;         // AXI3 Write ID.
    sc_out<sc_uint<C_S_AXI_DATA_WIDTH>> M_AXI_WDATA;     // AXI Write data.
    sc_out<sc_uint<C_S_AXI_DATA_WIDTH / 8>> M_AXI_WSTRB; // AXI Write data strobes.
    sc_out<bool> M_AXI_WLAST;                      // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_out<sc_uint<C_S_AXI_WUSER_WIDTH>> M_AXI_WUSER;    // User-defined W Channel signals.
    sc_out<bool> M_AXI_WVALID;                     // AXI Write data valid.
    // sc_in<bool>       M_AXI_WREADY;                       // AXI Write data ready.
    //  AXI Write Response Channel Signals (B)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>> M_AXI_BID; // AXI Write response ID.
    sc_in<sc_uint<PRAM_AXI_RRESP>> M_AXI_BRESP; // AXI Write response code.
    sc_in<bool> M_AXI_BUSER;              // User-defined B channel signals.
    sc_in<bool> M_AXI_BVALID;             // AXI Write response valid.
    sc_out<bool> M_AXI_BREADY;            // Write response ready.
    // AXI Read Address Channel Signals (AR)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>> M_AXI_ARID;       // AXI address Read ID.
    sc_out<sc_uint<C_S_AXI_ADDR_WIDTH>> M_AXI_ARADDR;   // AXI Read address.
    sc_out<sc_uint<PRAM_AXI_AxLEN>> M_AXI_ARLEN;        // AXI address Read burst length.
    sc_out<sc_uint<PRAM_AXI_AxSIZE>> M_AXI_ARSIZE;      // AXI address Read burst size.
    sc_out<sc_uint<PRAM_AXI_AxBURST>> M_AXI_ARBURST;    // AXI address Read burst type.
    sc_out<sc_uint<1>> M_AXI_ARLOCK;                    // AXI Read address lock signal.
    sc_out<sc_uint<PRAM_AXI_AxCACHE>> M_AXI_ARCACHE;    // AXI Read address cache control signal.
    sc_out<sc_uint<PRAM_AXI_AxPROT>> M_AXI_ARPROT;      // AXI Read address protection signal.
    sc_out<sc_uint<PRAM_AXI_AxREGION>> M_AXI_ARREGION;  // Channel address region index.
    sc_out<sc_uint<PRAM_AXI_AxQOS>> M_AXI_ARQOS;        // Channel Quality of Service.
    sc_out<sc_uint<C_S_AXI_ARUSER_WIDTH>> M_AXI_ARUSER; // User-defined AR Channel signals.
    sc_out<bool> M_AXI_ARVALID;                   // AXI Read address valid.
    // sc_in<bool>       M_AXI_ARREADY;                      // AXI Read address ready.
    //  AXI Read Data channel Signals (R)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>> M_AXI_RID;      // AXI Read data response ID.
    sc_in<sc_uint<C_S_AXI_DATA_WIDTH>> M_AXI_RDATA;  // AXI Read data.
    sc_in<sc_uint<PRAM_AXI_RRESP>> M_AXI_RRESP;      // AXI Read response code.
    sc_in<bool> M_AXI_RLAST;                   // AXI Read data last signal.
    sc_in<sc_uint<C_S_AXI_RUSER_WIDTH>> M_AXI_RUSER; // User-defined R Channel signals.
    sc_in<bool> M_AXI_RVALID;                  // AXI Read valid.
    sc_out<bool> M_AXI_RREADY;                 // AXI Read ready.
};

#endif //_X2x_buffer_H