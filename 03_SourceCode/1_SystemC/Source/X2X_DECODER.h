/**
 * X2X Decoder IP
 */

#include "AXI_Interconnection.h"
#ifndef _X2x_decoder_H
#define _X2x_decoder_H

class X2x_decoder: public sc_module {
private: 
    void InsertAWMasterIDMethod();
    void InsertWMasterIDMethod();
    void InsertARMasterIDMethod();
    void JudgmentARAddressMethod();
    void JudgmentAWAddressMethod();
    void BChannelHandlerMethod();
    void RChannelHandlerMethod();
    void AwPopOutMethod();
    void WPopOutMethod();
    void ArPopOutMethod();
    void AWSelectorMethod();
    void WSelectorMethod();
    void ARSelectorMethod();
    bool        is_aw_address_match[PRAM_SLAVE_NUM];
    bool        is_ar_address_match[PRAM_SLAVE_NUM];
    sc_uint<C_S_AXI_ID_WIDTH>        m_AXI_AWID;
    sc_uint<C_S_AXI_ID_WIDTH>        m_AXI_ARID;
    sc_uint<C_S_AXI_ID_WIDTH>        m_AXI_WID;
    sc_dt::sc_uint<C_S_AXI_ADDR_WIDTH> m_AXI_ARADDR;
    sc_dt::sc_uint<C_S_AXI_ADDR_WIDTH> m_AXI_AWADDR;
public:
    sc_dt::sc_uint<C_S_AXI_ADDR_WIDTH> start_Address[PRAM_SLAVE_NUM];
    sc_dt::sc_uint<C_S_AXI_ADDR_WIDTH> end_Address[PRAM_SLAVE_NUM];
    unsigned int masterID;
    X2x_decoder(sc_module_name name);
    ~X2x_decoder( );
    // port declare
    //*****************************
    //********Slave side signal***
    //*****************************
    // AXI Write Address Channel Signals (AW)
    sc_in<sc_uint<C_S_AXI_ADDR_WIDTH>>     S_AXI_AWADDR;   // AXI Write address.
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>>     S_AXI_AWID;       // AXI address Write ID.
    sc_in<sc_uint<PRAM_AXI_AxLEN>>     S_AXI_AWLEN;        // AXI address Write burst length.
    sc_in<sc_uint<PRAM_AXI_AxSIZE>>     S_AXI_AWSIZE;      // AXI address Write burst size.
    sc_in<sc_uint<PRAM_AXI_AxBURST>>     S_AXI_AWBURST;    // AXI address Write burst type.
    sc_in<sc_uint<1>>     S_AXI_AWLOCK;                       // AXI Write address lock signal.
    sc_in<sc_uint<PRAM_AXI_AxCACHE>>     S_AXI_AWCACHE;    // AXI Write address cache control signal.
    sc_in<sc_uint<PRAM_AXI_AxPROT>>     S_AXI_AWPROT;      // AXI Write address protection signal.
    sc_in<sc_uint<PRAM_AXI_AxREGION>>     S_AXI_AWREGION;  // Channel address region index
    sc_in<sc_uint<PRAM_AXI_AxQOS>>     S_AXI_AWQOS;        // Channel Quality of Service (QoS).
    sc_in<sc_uint<C_S_AXI_AWUSER_WIDTH>>     S_AXI_AWUSER; // User-defined AW Channel signals.
    sc_in<bool>     S_AXI_AWVALID;                      // AXI Write address valid.
    sc_out<bool>    S_AXI_AWPOPOUT;                     // AXI Write data ready.    
    // AXI Write Data Channel Signals (W)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>>     S_AXI_WID;        // AXI3 Write ID.
    sc_in<sc_uint<C_S_AXI_DATA_WIDTH>>     S_AXI_WDATA;    // AXI Write data.
    sc_in<sc_uint<C_S_AXI_DATA_WIDTH / 8>>     S_AXI_WSTRB;// AXI Write data strobes.
    sc_in<bool>     S_AXI_WLAST;                        // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_in<sc_uint<C_S_AXI_WUSER_WIDTH>>     S_AXI_WUSER;   // User-defined W Channel signals.
    sc_in<bool>     S_AXI_WVALID;                       // AXI Write data valid.
    sc_out<bool>    S_AXI_WPOPOUT;                       // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>>    S_AXI_BID;        // AXI Write response ID.
    sc_out<sc_uint<PRAM_AXI_RRESP>>    S_AXI_BRESP;        // AXI Write response code.
    sc_out<bool>    S_AXI_BUSER;                        // User-defined B channel signals.
    sc_out<bool>    S_AXI_BVALID;                       // AXI Write response valid.
    sc_in<bool>     S_AXI_BREADY;                       // Write response ready.
    // AXI Read Address Channel Signals (AR)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>>     S_AXI_ARID;       // AXI address Read ID.
    sc_in<sc_uint<C_S_AXI_ADDR_WIDTH>>     S_AXI_ARADDR;   // AXI Read address.
    sc_in<sc_uint<PRAM_AXI_AxLEN>>     S_AXI_ARLEN;        // AXI address Read burst length.
    sc_in<sc_uint<PRAM_AXI_AxSIZE>>     S_AXI_ARSIZE;      // AXI address Read burst size.
    sc_in<sc_uint<PRAM_AXI_AxBURST>>     S_AXI_ARBURST;    // AXI address Read burst type.
    sc_in<sc_uint<1>>     S_AXI_ARLOCK;                       // AXI Read address lock signal.
    sc_in<sc_uint<PRAM_AXI_AxCACHE>>     S_AXI_ARCACHE;    // AXI Read address cache control signal.
    sc_in<sc_uint<PRAM_AXI_AxPROT>>     S_AXI_ARPROT;      // AXI Read address protection signal.
    sc_in<sc_uint<PRAM_AXI_AxREGION>>     S_AXI_ARREGION;  // Channel address region index.
    sc_in<sc_uint<PRAM_AXI_AxQOS>>     S_AXI_ARQOS;        // Channel Quality of Service.
    sc_in<sc_uint<C_S_AXI_ARUSER_WIDTH>>     S_AXI_ARUSER; // User-defined AR Channel signals.
    sc_in<bool>     S_AXI_ARVALID;                      // AXI Read address valid.
    sc_out<bool>    S_AXI_ARPOPOUT;                     // AXI Read address ready.
    // AXI Read Data channel Signals (R)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>>    S_AXI_RID;        // AXI Read data response ID.
    sc_out<sc_uint<C_S_AXI_DATA_WIDTH>>    S_AXI_RDATA;    // AXI Read data.
    sc_out<sc_uint<PRAM_AXI_RRESP>>    S_AXI_RRESP;        // AXI Read response code.
    sc_out<bool>    S_AXI_RLAST;                        // AXI Read data last signal.
    sc_out<sc_uint<C_S_AXI_RUSER_WIDTH>>    S_AXI_RUSER;   // User-defined R Channel signals.
    sc_out<bool>    S_AXI_RVALID;                       // AXI Read valid.
    sc_in<bool>     S_AXI_RREADY;                       // AXI Read valid.
    //*****************************
    //********Master side signal***
    //*****************************
    // AXI Write Address Channel Signals (AW)
    sc_in<bool>      M_AXI_AWREADY[PRAM_SLAVE_NUM];                      // aw arbiter output ready out.
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>>     M_AXI_AWID[PRAM_SLAVE_NUM];       // AXI address Write ID.
    sc_out<sc_uint<C_S_AXI_ADDR_WIDTH>>     M_AXI_AWADDR[PRAM_SLAVE_NUM];   // AXI Write address.
    sc_out<sc_uint<PRAM_AXI_AxLEN>>     M_AXI_AWLEN[PRAM_SLAVE_NUM];        // AXI address Write burst length.
    sc_out<sc_uint<PRAM_AXI_AxSIZE>>     M_AXI_AWSIZE[PRAM_SLAVE_NUM];      // AXI address Write burst size.
    sc_out<sc_uint<PRAM_AXI_AxBURST>>     M_AXI_AWBURST[PRAM_SLAVE_NUM];    // AXI address Write burst type.
    sc_out<sc_uint<1>>     M_AXI_AWLOCK[PRAM_SLAVE_NUM];                       // AXI Write address lock signal.
    sc_out<sc_uint<PRAM_AXI_AxCACHE>>     M_AXI_AWCACHE[PRAM_SLAVE_NUM];    // AXI Write address cache control signal.
    sc_out<sc_uint<PRAM_AXI_AxPROT>>     M_AXI_AWPROT[PRAM_SLAVE_NUM];      // AXI Write address protection signal.
    sc_out<sc_uint<PRAM_AXI_AxREGION>>     M_AXI_AWREGION[PRAM_SLAVE_NUM];  // Channel address region index
    sc_out<sc_uint<PRAM_AXI_AxQOS>>     M_AXI_AWQOS[PRAM_SLAVE_NUM];        // Channel Quality of Service (QoS).
    sc_out<sc_uint<C_S_AXI_AWUSER_WIDTH>>     M_AXI_AWUSER[PRAM_SLAVE_NUM]; // User-defined AW Channel signals.
    sc_out<bool>     M_AXI_AWVALID[PRAM_SLAVE_NUM];                      // AXI Write address valid.
    // AXI Write Data Channel Signals (W)
    sc_in<bool>      M_AXI_WREADY[PRAM_SLAVE_NUM];                       // aw arbiter output ready out.
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>>     M_AXI_WID[PRAM_SLAVE_NUM];        // AXI3 Write ID.
    sc_out<sc_uint<C_S_AXI_DATA_WIDTH>>     M_AXI_WDATA[PRAM_SLAVE_NUM];    // AXI Write data.
    sc_out<sc_uint<C_S_AXI_DATA_WIDTH / 8>>     M_AXI_WSTRB[PRAM_SLAVE_NUM];// AXI Write data strobes.
    sc_out<bool>     M_AXI_WLAST[PRAM_SLAVE_NUM];                        // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_out<sc_uint<C_S_AXI_WUSER_WIDTH>>     M_AXI_WUSER[PRAM_SLAVE_NUM];   // User-defined W Channel signals.
    sc_out<bool>     M_AXI_WVALID[PRAM_SLAVE_NUM];                       // AXI Write data valid.
    //sc_in<bool>      M_AXI_WREADY;                       // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH> >      M_AXI_BID;        // AXI Write response ID.
    sc_in<sc_uint<PRAM_AXI_RRESP>>      M_AXI_BRESP;        // AXI Write response code.
    sc_in<bool>      M_AXI_BUSER;                        // User-defined B channel signals.
    sc_in<bool>      M_AXI_BVALID;                       // AXI Write response valid.
    sc_out<bool>     M_AXI_BREADY;                       // Write response ready.
    // AXI Read Address Channel Signals (AR)
    sc_out<sc_uint<C_S_AXI_ID_WIDTH>>     M_AXI_ARID[PRAM_SLAVE_NUM];       // AXI address Read ID.
    sc_out<sc_uint<C_S_AXI_ADDR_WIDTH>>     M_AXI_ARADDR[PRAM_SLAVE_NUM];   // AXI Read address.
    sc_out<sc_uint<PRAM_AXI_AxLEN>>     M_AXI_ARLEN[PRAM_SLAVE_NUM];        // AXI address Read burst length.
    sc_out<sc_uint<PRAM_AXI_AxSIZE>>     M_AXI_ARSIZE[PRAM_SLAVE_NUM];      // AXI address Read burst size.
    sc_out<sc_uint<PRAM_AXI_AxBURST>>     M_AXI_ARBURST[PRAM_SLAVE_NUM];    // AXI address Read burst type.
    sc_out<sc_uint<1>>     M_AXI_ARLOCK[PRAM_SLAVE_NUM];                       // AXI Read address lock signal.
    sc_out<sc_uint<PRAM_AXI_AxCACHE>>     M_AXI_ARCACHE[PRAM_SLAVE_NUM];    // AXI Read address cache control signal.
    sc_out<sc_uint<PRAM_AXI_AxPROT>>     M_AXI_ARPROT[PRAM_SLAVE_NUM];      // AXI Read address protection signal.
    sc_out<sc_uint<PRAM_AXI_AxREGION>>     M_AXI_ARREGION[PRAM_SLAVE_NUM];  // Channel address region index.
    sc_out<sc_uint<PRAM_AXI_AxQOS>>     M_AXI_ARQOS[PRAM_SLAVE_NUM];        // Channel Quality of Service.
    sc_out<sc_uint<C_S_AXI_ARUSER_WIDTH>>     M_AXI_ARUSER[PRAM_SLAVE_NUM]; // User-defined AR Channel signals.
    sc_out<bool>     M_AXI_ARVALID[PRAM_SLAVE_NUM];                      // AXI Read address valid.
    sc_in<bool>      M_AXI_ARREADY[PRAM_SLAVE_NUM];                                      // axi arbiter AR ready out.
    // AXI Read Data channel Signals (R)
    sc_in<sc_uint<C_S_AXI_ID_WIDTH>>      M_AXI_RID;        // AXI Read data response ID.
    sc_in<sc_uint<C_S_AXI_DATA_WIDTH>>      M_AXI_RDATA;    // AXI Read data.
    sc_in<sc_uint<PRAM_AXI_RRESP>>      M_AXI_RRESP;        // AXI Read response code.
    sc_in<bool>      M_AXI_RLAST;                        // AXI Read data last signal.
    sc_in<sc_uint<C_S_AXI_RUSER_WIDTH>>      M_AXI_RUSER;   // User-defined R Channel signals.
    sc_in<bool>      M_AXI_RVALID;                       // AXI Read valid.
    sc_out<bool>     M_AXI_RREADY;                       // AXI Read ready.
};

#endif //_X2x_decoder_H