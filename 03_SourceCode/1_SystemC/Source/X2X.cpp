/**
 * X2X ip
 */

#include "X2X.h"

/**
 * Constructor
 */
X2X::X2X(sc_module_name mName) : sc_module(mName)
{
    X2X_BUFFER *x2x_buffer[PRAM_MASTER_NUM];// = {X2X_BUFFER("x2x_buffer")};
    X2X_DECODER *x2x_decoder[PRAM_MASTER_NUM];//= {X2X_DECODER("x2x_decoder")};
    X2X_ARBITER *x2x_arbier[PRAM_SLAVE_NUM];// = {X2X_ARBITER("x2x_arbier")};
    
    for (size_t i = 0; i < PRAM_MASTER_NUM; i++)
    {
        x2x_buffer[i] =  new X2X_BUFFER("x2x_buffer");
        x2x_decoder[i] =  new X2X_DECODER("x2x_decoder");
    }
    for (size_t i = 0; i < PRAM_SLAVE_NUM; i++)
    {
        x2x_arbier[i] =  new X2X_ARBITER("x2x_arbier");
    }
    

    // Process registration
    SC_HAS_PROCESS(X2X);
    // assigne masterID
    for (unsigned int index_dec = 0; index_dec < PRAM_MASTER_NUM; index_dec++)
    {
        for (unsigned int index_add = 0; index_add < PRAM_SLAVE_NUM; index_add++)
        {
            x2x_decoder[index_dec]->start_Address[index_add] = PRAM_START_ADDRESS[index_add];
            x2x_decoder[index_dec]->end_Address[index_add] = PRAM_END_ADDRESS[index_add];
        }
    }
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        x2x_decoder[index]->masterID = index;
    }
    // connections
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        ACLK(x2x_buffer[index]->ACLK);
        ACLK(x2x_arbier[index]->ACLK);
        ARESETN(x2x_buffer[index]->ARESETN);
        ARESETN(x2x_arbier[index]->ARESETN);
    }

    // ***********************x2x_buffer to input port***********************
    //  AW
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            S_AXI_AWID[index][index_port](SIG_X2X_BUFF_AXI_AWID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            S_AXI_AWADDR[index][index_port](SIG_X2X_BUFF_AXI_AWADDR[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            S_AXI_AWLEN[index][index_port](SIG_X2X_BUFF_AXI_AWLEN[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            S_AXI_AWSIZE[index][index_port](SIG_X2X_BUFF_AXI_AWSIZE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            S_AXI_AWBURST[index][index_port](SIG_X2X_BUFF_AXI_AWBURST[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            S_AXI_AWCACHE[index][index_port](SIG_X2X_BUFF_AXI_AWCACHE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            S_AXI_AWPROT[index][index_port](SIG_X2X_BUFF_AXI_AWPROT[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            S_AXI_AWREGION[index][index_port](SIG_X2X_BUFF_AXI_AWREGION[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            S_AXI_AWQOS[index][index_port](SIG_X2X_BUFF_AXI_AWQOS[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
        {
            S_AXI_AWUSER[index][index_port](SIG_X2X_BUFF_AXI_AWUSER[index][index_port]);
        }
        S_AXI_AWLOCK[index](SIG_X2X_BUFF_AXI_AWLOCK[index]);
        S_AXI_AWVALID[index](SIG_X2X_BUFF_AXI_AWVALID[index]);
        S_AXI_AWREADY[index](SIG_X2X_BUFF_AXI_AWREADY[index]);
    }
    // AR
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            S_AXI_ARID[index][index_port](SIG_X2X_BUFF_AXI_ARID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            S_AXI_ARADDR[index][index_port](SIG_X2X_BUFF_AXI_ARADDR[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            S_AXI_ARLEN[index][index_port](SIG_X2X_BUFF_AXI_ARLEN[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            S_AXI_ARSIZE[index][index_port](SIG_X2X_BUFF_AXI_ARSIZE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            S_AXI_ARBURST[index][index_port](SIG_X2X_BUFF_AXI_ARBURST[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            S_AXI_ARCACHE[index][index_port](SIG_X2X_BUFF_AXI_ARCACHE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            S_AXI_ARPROT[index][index_port](SIG_X2X_BUFF_AXI_ARPROT[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            S_AXI_ARREGION[index][index_port](SIG_X2X_BUFF_AXI_ARREGION[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            S_AXI_ARQOS[index][index_port](SIG_X2X_BUFF_AXI_ARQOS[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
        {
            S_AXI_ARUSER[index][index_port](SIG_X2X_BUFF_AXI_ARUSER[index][index_port]);
        }
        S_AXI_ARLOCK[index](SIG_X2X_BUFF_AXI_ARLOCK[index]);
        S_AXI_ARVALID[index](SIG_X2X_BUFF_AXI_ARVALID[index]);
        S_AXI_ARREADY[index](SIG_X2X_BUFF_AXI_ARREADY[index]);
    }
    // W
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            S_AXI_WID[index][index_port](SIG_X2X_BUFF_AXI_WID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            S_AXI_WDATA[index][index_port](SIG_X2X_BUFF_AXI_WDATA[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH / 8; index_port++)
        {
            S_AXI_WSTRB[index][index_port](SIG_X2X_BUFF_AXI_WSTRB[index][index_port]);
        }
        S_AXI_WLAST[index](SIG_X2X_BUFF_AXI_WLAST[index]);
        for (unsigned int index_port = 0; index_port < C_S_AXI_WUSER_WIDTH; index_port++)
        {
            S_AXI_WUSER[index][index_port](SIG_X2X_BUFF_AXI_WUSER[index][index_port]);
        }
        S_AXI_WVALID[index](SIG_X2X_BUFF_AXI_WVALID[index]);
        S_AXI_WREADY[index](SIG_X2X_BUFF_AXI_WREADY[index]);
    }
    // B
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            S_AXI_BID[index][index_port](SIG_X2X_BUFF_AXI_BID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            S_AXI_BRESP[index][index_port](SIG_X2X_BUFF_AXI_BRESP[index][index_port]);
        }
        S_AXI_BUSER[index](SIG_X2X_BUFF_AXI_BUSER[index]);
        S_AXI_BVALID[index](SIG_X2X_BUFF_AXI_BVALID[index]);
        S_AXI_BREADY[index](SIG_X2X_BUFF_AXI_BREADY[index]);
    }
    // R
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            S_AXI_RID[index][index_port](SIG_X2X_BUFF_AXI_RID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            S_AXI_RDATA[index][index_port](SIG_X2X_BUFF_AXI_RDATA[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            S_AXI_RRESP[index][index_port](SIG_X2X_BUFF_AXI_RRESP[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_RUSER_WIDTH; index_port++)
        {
            S_AXI_RUSER[index][index_port](SIG_X2X_BUFF_AXI_RUSER[index][index_port]);
        }
        S_AXI_RLAST[index](SIG_X2X_BUFF_AXI_RLAST[index]);
        S_AXI_RVALID[index](SIG_X2X_BUFF_AXI_RVALID[index]);
        S_AXI_RREADY[index](SIG_X2X_BUFF_AXI_RREADY[index]);
    }
    // ***********************x2x_buffer to signal inputport******************
    // ***********************x2x_buffer to input port***********************
    // AW
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_AWID[index_port])(SIG_X2X_BUFF_AXI_AWID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_AWADDR[index_port])(SIG_X2X_BUFF_AXI_AWADDR[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            (x2x_buffer[index]->S_AXI_AWLEN[index_port])(SIG_X2X_BUFF_AXI_AWLEN[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            (x2x_buffer[index]->S_AXI_AWSIZE[index_port])(SIG_X2X_BUFF_AXI_AWSIZE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            (x2x_buffer[index]->S_AXI_AWBURST[index_port])(SIG_X2X_BUFF_AXI_AWBURST[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            (x2x_buffer[index]->S_AXI_AWCACHE[index_port])(SIG_X2X_BUFF_AXI_AWCACHE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            (x2x_buffer[index]->S_AXI_AWPROT[index_port])(SIG_X2X_BUFF_AXI_AWPROT[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            (x2x_buffer[index]->S_AXI_AWREGION[index_port])(SIG_X2X_BUFF_AXI_AWREGION[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            (x2x_buffer[index]->S_AXI_AWQOS[index_port])(SIG_X2X_BUFF_AXI_AWQOS[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_AWUSER[index_port])(SIG_X2X_BUFF_AXI_AWUSER[index][index_port]);
        }
        (x2x_buffer[index]->S_AXI_AWLOCK)(SIG_X2X_BUFF_AXI_AWLOCK[index]);
        (x2x_buffer[index]->S_AXI_AWVALID)(SIG_X2X_BUFF_AXI_AWVALID[index]);
        (x2x_buffer[index]->S_AXI_AWREADY)(SIG_X2X_BUFF_AXI_AWREADY[index]);
    }
    // AR
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_ARID[index_port])(SIG_X2X_BUFF_AXI_ARID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_ARADDR[index_port])(SIG_X2X_BUFF_AXI_ARADDR[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            (x2x_buffer[index]->S_AXI_ARLEN[index_port])(SIG_X2X_BUFF_AXI_ARLEN[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            (x2x_buffer[index]->S_AXI_ARSIZE[index_port])(SIG_X2X_BUFF_AXI_ARSIZE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            (x2x_buffer[index]->S_AXI_ARBURST[index_port])(SIG_X2X_BUFF_AXI_ARBURST[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            (x2x_buffer[index]->S_AXI_ARCACHE[index_port])(SIG_X2X_BUFF_AXI_ARCACHE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            (x2x_buffer[index]->S_AXI_ARPROT[index_port])(SIG_X2X_BUFF_AXI_ARPROT[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            (x2x_buffer[index]->S_AXI_ARREGION[index_port])(SIG_X2X_BUFF_AXI_ARREGION[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            (x2x_buffer[index]->S_AXI_ARQOS[index_port])(SIG_X2X_BUFF_AXI_ARQOS[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_ARUSER[index_port])(SIG_X2X_BUFF_AXI_ARUSER[index][index_port]);
        }
        (x2x_buffer[index]->S_AXI_ARLOCK)(SIG_X2X_BUFF_AXI_ARLOCK[index]);
        (x2x_buffer[index]->S_AXI_ARVALID)(SIG_X2X_BUFF_AXI_ARVALID[index]);
        (x2x_buffer[index]->S_AXI_ARREADY)(SIG_X2X_BUFF_AXI_ARREADY[index]);
    }
    // W
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_WID[index_port])(SIG_X2X_BUFF_AXI_WID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_WDATA[index_port])(SIG_X2X_BUFF_AXI_WDATA[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH / 8; index_port++)
        {
            (x2x_buffer[index]->S_AXI_WSTRB[index_port])(SIG_X2X_BUFF_AXI_WSTRB[index][index_port]);
        }
        (x2x_buffer[index]->S_AXI_WLAST)(SIG_X2X_BUFF_AXI_WLAST[index]);
        for (unsigned int index_port = 0; index_port < C_S_AXI_WUSER_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_WUSER[index_port])(SIG_X2X_BUFF_AXI_WUSER[index][index_port]);
        }
        (x2x_buffer[index]->S_AXI_WVALID)(SIG_X2X_BUFF_AXI_WVALID[index]);
        (x2x_buffer[index]->S_AXI_WREADY)(SIG_X2X_BUFF_AXI_WREADY[index]);
    }
    // B
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_BID[index_port])(SIG_X2X_BUFF_AXI_BID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            (x2x_buffer[index]->S_AXI_BRESP[index_port])(SIG_X2X_BUFF_AXI_BRESP[index][index_port]);
        }
        (x2x_buffer[index]->S_AXI_BUSER)(SIG_X2X_BUFF_AXI_BUSER[index]);
        (x2x_buffer[index]->S_AXI_BVALID)(SIG_X2X_BUFF_AXI_BVALID[index]);
        (x2x_buffer[index]->S_AXI_BREADY)(SIG_X2X_BUFF_AXI_BREADY[index]);
    }
    // R
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_RID[index_port])(SIG_X2X_BUFF_AXI_RID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_RDATA[index_port])(SIG_X2X_BUFF_AXI_RDATA[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            (x2x_buffer[index]->S_AXI_RRESP[index_port])(SIG_X2X_BUFF_AXI_RRESP[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_RUSER_WIDTH; index_port++)
        {
            (x2x_buffer[index]->S_AXI_RUSER[index_port])(SIG_X2X_BUFF_AXI_RUSER[index][index_port]);
        }
        (x2x_buffer[index]->S_AXI_RLAST)(SIG_X2X_BUFF_AXI_RLAST[index]);
        (x2x_buffer[index]->S_AXI_RVALID)(SIG_X2X_BUFF_AXI_RVALID[index]);
        (x2x_buffer[index]->S_AXI_RREADY)(SIG_X2X_BUFF_AXI_RREADY[index]);
    }
    //***********************x2x_buffer to x2x_decoder signal***********************
    // ***********************x2x_buffer to x2x_decoder***********************
    // AW
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (x2x_buffer[index]->M_AXI_AWID[index_port])(SIG_BUFF_DECODER_S_AXI_AWID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            (x2x_buffer[index]->M_AXI_AWADDR[index_port])(SIG_BUFF_DECODER_S_AXI_AWADDR[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            (x2x_buffer[index]->M_AXI_AWLEN[index_port])(SIG_BUFF_DECODER_S_AXI_AWLEN[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            (x2x_buffer[index]->M_AXI_AWSIZE[index_port])(SIG_BUFF_DECODER_S_AXI_AWSIZE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            (x2x_buffer[index]->M_AXI_AWBURST[index_port])(SIG_BUFF_DECODER_S_AXI_AWBURST[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            (x2x_buffer[index]->M_AXI_AWCACHE[index_port])(SIG_BUFF_DECODER_S_AXI_AWCACHE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            (x2x_buffer[index]->M_AXI_AWPROT[index_port])(SIG_BUFF_DECODER_S_AXI_AWPROT[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            (x2x_buffer[index]->M_AXI_AWREGION[index_port])(SIG_BUFF_DECODER_S_AXI_AWREGION[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            (x2x_buffer[index]->M_AXI_AWQOS[index_port])(SIG_BUFF_DECODER_S_AXI_AWQOS[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
        {
            (x2x_buffer[index]->M_AXI_AWUSER[index_port])(SIG_BUFF_DECODER_S_AXI_AWUSER[index][index_port]);
        }
        (x2x_buffer[index]->M_AXI_AWLOCK)(SIG_BUFF_DECODER_S_AXI_AWLOCK[index]);
        (x2x_buffer[index]->M_AXI_AWVALID)(SIG_BUFF_DECODER_S_AXI_AWVALID[index]);
        x2x_buffer[index]->AwPop(SIG_BUFF_DECODER_S_AXI_AWPOPOUT[index]);
    }
    // W
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (x2x_buffer[index]->M_AXI_WID[index_port])(SIG_BUFF_DECODER_S_AXI_WID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            (x2x_buffer[index]->M_AXI_WDATA[index_port])(SIG_BUFF_DECODER_S_AXI_WDATA[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH / 8; index_port++)
        {
            (x2x_buffer[index]->M_AXI_WSTRB[index_port])(SIG_BUFF_DECODER_S_AXI_WSTRB[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_WUSER_WIDTH; index_port++)
        {
            (x2x_buffer[index]->M_AXI_WUSER[index_port])(SIG_BUFF_DECODER_S_AXI_WUSER[index][index_port]);
        }
        (x2x_buffer[index]->M_AXI_WLAST)(SIG_BUFF_DECODER_S_AXI_WLAST[index]);
        (x2x_buffer[index]->M_AXI_WVALID)(SIG_BUFF_DECODER_S_AXI_WVALID[index]);
        (x2x_buffer[index]->WPop)(SIG_BUFF_DECODER_S_AXI_WPOPOUT[index]);
        //(x2x_decoder[index][index]->S_AXI_WPOPOUT)(x2x_buffer[index]->WPop);
    }
    // B
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_buffer[index]->M_AXI_BID[index_port](SIG_BUFF_DECODER_S_AXI_BID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            x2x_buffer[index]->M_AXI_BRESP[index_port](SIG_BUFF_DECODER_S_AXI_BRESP[index][index_port]);
        }
        x2x_buffer[index]->M_AXI_WLAST(SIG_BUFF_DECODER_S_AXI_BUSER[index]);
        x2x_buffer[index]->M_AXI_WVALID(SIG_BUFF_DECODER_S_AXI_BVALID[index]);
        (x2x_buffer[index]->M_AXI_BREADY)(SIG_BUFF_DECODER_S_AXI_BREADY[index]);
    }
    // AR
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (x2x_buffer[index]->M_AXI_ARID[index_port])(SIG_BUFF_DECODER_S_AXI_ARID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            (x2x_buffer[index]->M_AXI_ARADDR[index_port])(SIG_BUFF_DECODER_S_AXI_ARADDR[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            (x2x_buffer[index]->M_AXI_ARLEN[index_port])(SIG_BUFF_DECODER_S_AXI_ARLEN[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            (x2x_buffer[index]->M_AXI_ARSIZE[index_port])(SIG_BUFF_DECODER_S_AXI_ARSIZE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            (x2x_buffer[index]->M_AXI_ARBURST[index_port])(SIG_BUFF_DECODER_S_AXI_ARBURST[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            (x2x_buffer[index]->M_AXI_ARCACHE[index_port])(SIG_BUFF_DECODER_S_AXI_ARCACHE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            (x2x_buffer[index]->M_AXI_ARPROT[index_port])(SIG_BUFF_DECODER_S_AXI_ARPROT[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            (x2x_buffer[index]->M_AXI_ARREGION[index_port])(SIG_BUFF_DECODER_S_AXI_ARREGION[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            (x2x_buffer[index]->M_AXI_ARQOS[index_port])(SIG_BUFF_DECODER_S_AXI_ARQOS[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
        {
            (x2x_buffer[index]->M_AXI_ARUSER[index_port])(SIG_BUFF_DECODER_S_AXI_ARUSER[index][index_port]);
        }
        (x2x_buffer[index]->M_AXI_ARLOCK)(SIG_BUFF_DECODER_S_AXI_ARLOCK[index]);
        (x2x_buffer[index]->M_AXI_ARVALID)(SIG_BUFF_DECODER_S_AXI_ARVALID[index]);
        x2x_buffer[index]->ArPop(SIG_BUFF_DECODER_S_AXI_ARPOPOUT[index]);
    }
    // R
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_buffer[index]->M_AXI_RID[index_port](SIG_BUFF_DECODER_S_AXI_RID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            x2x_buffer[index]->M_AXI_RDATA[index_port](SIG_BUFF_DECODER_S_AXI_RDATA[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            x2x_buffer[index]->M_AXI_RRESP[index_port](SIG_BUFF_DECODER_S_AXI_RRESP[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_RUSER_WIDTH; index_port++)
        {
            x2x_buffer[index]->M_AXI_RUSER[index_port](SIG_BUFF_DECODER_S_AXI_RUSER[index][index_port]);
        }
        x2x_buffer[index]->M_AXI_RLAST(SIG_BUFF_DECODER_S_AXI_RLAST[index]);
        x2x_buffer[index]->M_AXI_RVALID(SIG_BUFF_DECODER_S_AXI_RVALID[index]);
        (x2x_buffer[index]->M_AXI_RREADY)(SIG_BUFF_DECODER_S_AXI_BREADY[index]);
    }

    // ***********************x2x_buffer to x2x_decoder***********************
    // AW
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_decoder[index]->S_AXI_AWID[index_port](x2x_buffer[index]->M_AXI_AWID[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            x2x_decoder[index]->S_AXI_AWADDR[index_port](x2x_buffer[index]->M_AXI_AWADDR[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            x2x_decoder[index]->S_AXI_AWLEN[index_port](x2x_buffer[index]->M_AXI_AWLEN[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            x2x_decoder[index]->S_AXI_AWSIZE[index_port](x2x_buffer[index]->M_AXI_AWSIZE[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            x2x_decoder[index]->S_AXI_AWBURST[index_port](x2x_buffer[index]->M_AXI_AWBURST[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            x2x_decoder[index]->S_AXI_AWCACHE[index_port](x2x_buffer[index]->M_AXI_AWCACHE[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            x2x_decoder[index]->S_AXI_AWPROT[index_port](x2x_buffer[index]->M_AXI_AWPROT[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            x2x_decoder[index]->S_AXI_AWREGION[index_port](x2x_buffer[index]->M_AXI_AWREGION[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            x2x_decoder[index]->S_AXI_AWQOS[index_port](x2x_buffer[index]->M_AXI_AWQOS[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
        {
            x2x_decoder[index]->S_AXI_AWUSER[index_port](x2x_buffer[index]->M_AXI_AWUSER[index_port]);
        }
        x2x_decoder[index]->S_AXI_AWLOCK(x2x_buffer[index]->M_AXI_AWLOCK);
        x2x_decoder[index]->S_AXI_AWVALID(x2x_buffer[index]->M_AXI_AWVALID);
        x2x_buffer[index]->AwPop(x2x_decoder[index]->S_AXI_AWPOPOUT);
    }
    // W
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_decoder[index]->S_AXI_WID[index_port](x2x_buffer[index]->M_AXI_WID[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            x2x_decoder[index]->S_AXI_WDATA[index_port](x2x_buffer[index]->M_AXI_WDATA[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH / 8; index_port++)
        {
            x2x_decoder[index]->S_AXI_WSTRB[index_port](x2x_buffer[index]->M_AXI_WSTRB[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_WUSER_WIDTH; index_port++)
        {
            x2x_decoder[index]->S_AXI_WUSER[index_port](x2x_buffer[index]->M_AXI_WUSER[index_port]);
        }
        x2x_decoder[index]->S_AXI_WLAST(x2x_buffer[index]->M_AXI_WLAST);
        x2x_decoder[index]->S_AXI_WVALID(x2x_buffer[index]->M_AXI_WVALID);
        x2x_buffer[index]->WPop(x2x_decoder[index]->S_AXI_WPOPOUT);
    }
    // B
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_buffer[index]->M_AXI_BID[index_port](x2x_decoder[index]->S_AXI_BID[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            x2x_buffer[index]->M_AXI_BRESP[index_port](x2x_decoder[index]->S_AXI_BRESP[index_port]);
        }
        x2x_buffer[index]->M_AXI_WLAST(x2x_decoder[index]->S_AXI_BUSER);
        x2x_buffer[index]->M_AXI_WVALID(x2x_decoder[index]->S_AXI_BVALID);
        x2x_decoder[index]->S_AXI_BREADY(x2x_buffer[index]->M_AXI_BREADY);
    }
    // AR
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_decoder[index]->S_AXI_ARID[index_port](x2x_buffer[index]->M_AXI_ARID[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            x2x_decoder[index]->S_AXI_ARADDR[index_port](x2x_buffer[index]->M_AXI_ARADDR[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            x2x_decoder[index]->S_AXI_ARLEN[index_port](x2x_buffer[index]->M_AXI_ARLEN[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            x2x_decoder[index]->S_AXI_ARSIZE[index_port](x2x_buffer[index]->M_AXI_ARSIZE[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            x2x_decoder[index]->S_AXI_ARBURST[index_port](x2x_buffer[index]->M_AXI_ARBURST[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            x2x_decoder[index]->S_AXI_ARCACHE[index_port](x2x_buffer[index]->M_AXI_ARCACHE[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            x2x_decoder[index]->S_AXI_ARPROT[index_port](x2x_buffer[index]->M_AXI_ARPROT[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            x2x_decoder[index]->S_AXI_ARREGION[index_port](x2x_buffer[index]->M_AXI_ARREGION[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            x2x_decoder[index]->S_AXI_ARQOS[index_port](x2x_buffer[index]->M_AXI_ARQOS[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
        {
            x2x_decoder[index]->S_AXI_ARUSER[index_port](x2x_buffer[index]->M_AXI_ARUSER[index_port]);
        }
        x2x_decoder[index]->S_AXI_ARLOCK(x2x_buffer[index]->M_AXI_ARLOCK);
        x2x_decoder[index]->S_AXI_ARVALID(x2x_buffer[index]->M_AXI_ARVALID);
        x2x_buffer[index]->ArPop(x2x_decoder[index]->S_AXI_ARPOPOUT);
    }
    // R
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_buffer[index]->M_AXI_RID[index_port](x2x_decoder[index]->S_AXI_RID[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            x2x_buffer[index]->M_AXI_RDATA[index_port](x2x_decoder[index]->S_AXI_RDATA[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            x2x_buffer[index]->M_AXI_RRESP[index_port](x2x_decoder[index]->S_AXI_RRESP[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_RUSER_WIDTH; index_port++)
        {
            x2x_buffer[index]->M_AXI_RUSER[index_port](x2x_decoder[index]->S_AXI_RUSER[index_port]);
        }
        x2x_buffer[index]->M_AXI_RLAST(x2x_decoder[index]->S_AXI_RLAST);
        x2x_buffer[index]->M_AXI_RVALID(x2x_decoder[index]->S_AXI_RVALID);
        x2x_decoder[index]->S_AXI_BREADY(x2x_buffer[index]->M_AXI_RREADY);
    }
    // *************x2x_decoder to x2x_arbiter*************************
    // AW
    for (unsigned int index_slave = 0; index_slave < PRAM_SLAVE_NUM; index_slave++)
    {
        for (unsigned int index_master = 0; index_master < PRAM_MASTER_NUM; index_master++)
        {
            for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_AWID[index_master][index_port](x2x_decoder[index_master]->M_AXI_AWID[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_AWADDR[index_master][index_port](x2x_decoder[index_master]->M_AXI_AWADDR[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_AWLEN[index_master][index_port](x2x_decoder[index_master]->M_AXI_AWLEN[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_AWSIZE[index_master][index_port](x2x_decoder[index_master]->M_AXI_AWSIZE[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_AWBURST[index_master][index_port](x2x_decoder[index_master]->M_AXI_AWBURST[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_AWCACHE[index_master][index_port](x2x_decoder[index_master]->M_AXI_AWCACHE[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_AWPROT[index_master][index_port](x2x_decoder[index_master]->M_AXI_AWPROT[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_AWREGION[index_master][index_port](x2x_decoder[index_master]->M_AXI_AWREGION[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_AWQOS[index_master][index_port](x2x_decoder[index_master]->M_AXI_AWQOS[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_AWUSER[index_master][index_port](x2x_decoder[index_master]->M_AXI_AWUSER[index_slave][index_port]);
            }
            x2x_arbier[index_slave]->S_AXI_AWLOCK[index_master](x2x_decoder[index_master]->M_AXI_AWLOCK[index_slave]);
            x2x_arbier[index_slave]->S_AXI_AWVALID[index_master](x2x_decoder[index_master]->M_AXI_AWVALID[index_slave]);
            x2x_decoder[index_master]->M_AXI_AWREADY[index_master](x2x_arbier[index_slave]->S_AXI_AWREADY[index_master]);
        }
    }
    // W
    for (unsigned int index_slave = 0; index_slave < PRAM_SLAVE_NUM; index_slave++)
    {
        for (unsigned int index_master = 0; index_master < PRAM_MASTER_NUM; index_master++)
        {
            for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_WID[index_master][index_port](x2x_decoder[index_master]->M_AXI_WID[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_WDATA[index_master][index_port](x2x_decoder[index_master]->M_AXI_WDATA[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH / 8; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_WSTRB[index_master][index_port](x2x_decoder[index_master]->M_AXI_WSTRB[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < C_S_AXI_WUSER_WIDTH; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_WUSER[index_master][index_port](x2x_decoder[index_master]->M_AXI_WUSER[index_slave][index_port]);
            }
            x2x_arbier[index_slave]->S_AXI_WLAST[index_master](x2x_decoder[index_master]->M_AXI_WLAST[index_slave]);
            x2x_arbier[index_slave]->S_AXI_WVALID[index_master](x2x_decoder[index_master]->M_AXI_WVALID[index_slave]);
            x2x_decoder[index_master]->M_AXI_WREADY[index_master](x2x_arbier[index_slave]->S_AXI_WREADY[index_master]);
        }
    }
    // B
    for (unsigned int index_slave = 0; index_slave < PRAM_SLAVE_NUM; index_slave++)
    {
        for (unsigned int index_master = 0; index_master < PRAM_MASTER_NUM; index_master++)
        {
            for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
            {
                x2x_decoder[index_master]->M_AXI_BID[index_port](x2x_arbier[index_slave]->S_AXI_BID[index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
            {
                x2x_decoder[index_master]->M_AXI_BRESP[index_port](x2x_arbier[index_slave]->S_AXI_BRESP[index_port]);
            }
            x2x_arbier[index_slave]->S_AXI_BREADY(x2x_decoder[index_master]->M_AXI_BREADY);
            x2x_decoder[index_master]->M_AXI_BUSER(x2x_arbier[index_slave]->S_AXI_BUSER);
            x2x_decoder[index_master]->M_AXI_BVALID(x2x_arbier[index_slave]->S_AXI_BVALID);
        }
    }
    // AR
    for (unsigned int index_slave = 0; index_slave < PRAM_SLAVE_NUM; index_slave++)
    {
        for (unsigned int index_master = 0; index_master < PRAM_MASTER_NUM; index_master++)
        {
            for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_ARID[index_master][index_port](x2x_decoder[index_master]->M_AXI_ARID[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_ARADDR[index_master][index_port](x2x_decoder[index_master]->M_AXI_ARADDR[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_ARLEN[index_master][index_port](x2x_decoder[index_master]->M_AXI_ARLEN[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_ARSIZE[index_master][index_port](x2x_decoder[index_master]->M_AXI_ARSIZE[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_ARBURST[index_master][index_port](x2x_decoder[index_master]->M_AXI_ARBURST[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_ARCACHE[index_master][index_port](x2x_decoder[index_master]->M_AXI_ARCACHE[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_ARPROT[index_master][index_port](x2x_decoder[index_master]->M_AXI_ARPROT[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_ARREGION[index_master][index_port](x2x_decoder[index_master]->M_AXI_ARREGION[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_ARQOS[index_master][index_port](x2x_decoder[index_master]->M_AXI_ARQOS[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
            {
                x2x_arbier[index_slave]->S_AXI_ARUSER[index_master][index_port](x2x_decoder[index_master]->M_AXI_ARUSER[index_slave][index_port]);
            }
            x2x_arbier[index_slave]->S_AXI_ARLOCK[index_master](x2x_decoder[index_master]->M_AXI_AWLOCK[index_slave]);
            x2x_arbier[index_slave]->S_AXI_ARVALID[index_master](x2x_decoder[index_master]->M_AXI_ARVALID[index_slave]);
            x2x_decoder[index_master]->M_AXI_ARREADY[index_master](x2x_arbier[index_slave]->S_AXI_AWREADY[index_master]);
        }
    }
    // R
    for (unsigned int index_slave = 0; index_slave < PRAM_SLAVE_NUM; index_slave++)
    {
        for (unsigned int index_master = 0; index_master < PRAM_MASTER_NUM; index_master++)
        {
            for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
            {
                x2x_decoder[index_master]->M_AXI_RID[index_port](x2x_arbier[index_slave]->S_AXI_RID[index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
            {
                x2x_decoder[index_master]->M_AXI_RRESP[index_port](x2x_arbier[index_slave]->S_AXI_RRESP[index_port]);
            }
            for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
            {
                x2x_decoder[index_master]->M_AXI_RDATA[index_port](x2x_arbier[index_slave]->S_AXI_RDATA[index_port]);
            }
            for (unsigned int index_port = 0; index_port < C_S_AXI_RUSER_WIDTH; index_port++)
            {
                x2x_decoder[index_master]->M_AXI_RUSER[index_port](x2x_arbier[index_slave]->S_AXI_RUSER[index_port]);
            }
            x2x_arbier[index_slave]->S_AXI_RREADY(x2x_decoder[index_master]->M_AXI_RREADY);
            x2x_decoder[index_master]->M_AXI_RLAST(x2x_arbier[index_slave]->S_AXI_RLAST);
            x2x_decoder[index_master]->M_AXI_RVALID(x2x_arbier[index_slave]->S_AXI_RVALID);
        }
    }
    // *************************x2x_arbiter to output port*************************
    // AW

    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_AWID[index_port](SIG_ARBITER_X2X_AXI_AWID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_AWADDR[index_port](SIG_ARBITER_X2X_AXI_AWADDR[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            x2x_arbier[index]->M_AXI_AWLEN[index_port](SIG_ARBITER_X2X_AXI_AWLEN[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            x2x_arbier[index]->M_AXI_AWSIZE[index_port](SIG_ARBITER_X2X_AXI_AWSIZE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            x2x_arbier[index]->M_AXI_AWBURST[index_port](SIG_ARBITER_X2X_AXI_AWBURST[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            x2x_arbier[index]->M_AXI_AWCACHE[index_port](SIG_ARBITER_X2X_AXI_AWCACHE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            x2x_arbier[index]->M_AXI_AWPROT[index_port](SIG_ARBITER_X2X_AXI_AWPROT[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            x2x_arbier[index]->M_AXI_AWREGION[index_port](SIG_ARBITER_X2X_AXI_AWREGION[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            x2x_arbier[index]->M_AXI_AWQOS[index_port](SIG_ARBITER_X2X_AXI_AWQOS[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_AWUSER[index_port](SIG_ARBITER_X2X_AXI_AWUSER[index][index_port]);
        }
        x2x_arbier[index]->M_AXI_AWLOCK(SIG_ARBITER_X2X_AXI_AWLOCK[index]);
        x2x_arbier[index]->M_AXI_AWVALID(SIG_ARBITER_X2X_AXI_AWVALID[index]);
        x2x_arbier[index]->M_AXI_AWREADY(SIG_ARBITER_X2X_AXI_AWREADY[index]);
    }
    // W
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_WID[index_port](SIG_ARBITER_X2X_AXI_WID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_WDATA[index_port](SIG_ARBITER_X2X_AXI_WDATA[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH / 8; index_port++)
        {
            x2x_arbier[index]->M_AXI_WSTRB[index_port](SIG_ARBITER_X2X_AXI_WSTRB[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_WUSER_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_WUSER[index_port](SIG_ARBITER_X2X_AXI_WUSER[index][index_port]);
        }
        x2x_arbier[index]->M_AXI_WLAST(SIG_ARBITER_X2X_AXI_WLAST[index]);
        x2x_arbier[index]->M_AXI_WVALID(SIG_ARBITER_X2X_AXI_WVALID[index]);
        x2x_arbier[index]->M_AXI_WREADY(SIG_ARBITER_X2X_AXI_WREADY[index]);
    }
    // B
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_BID[index_port](SIG_ARBITER_X2X_AXI_BID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            x2x_arbier[index]->M_AXI_BRESP[index_port](SIG_ARBITER_X2X_AXI_BRESP[index][index_port]);
        }
        x2x_arbier[index]->M_AXI_BUSER(SIG_ARBITER_X2X_AXI_BUSER[index]);
        x2x_arbier[index]->M_AXI_BVALID(SIG_ARBITER_X2X_AXI_BVALID[index]);
        x2x_arbier[index]->M_AXI_BREADY(SIG_ARBITER_X2X_AXI_BREADY[index]);
    }
    // AW
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_ARID[index_port](SIG_ARBITER_X2X_AXI_ARID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_ARADDR[index_port](SIG_ARBITER_X2X_AXI_ARADDR[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            x2x_arbier[index]->M_AXI_ARLEN[index_port](SIG_ARBITER_X2X_AXI_ARLEN[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            x2x_arbier[index]->M_AXI_ARSIZE[index_port](SIG_ARBITER_X2X_AXI_ARSIZE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            x2x_arbier[index]->M_AXI_ARBURST[index_port](SIG_ARBITER_X2X_AXI_ARBURST[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            x2x_arbier[index]->M_AXI_ARCACHE[index_port](SIG_ARBITER_X2X_AXI_ARCACHE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            x2x_arbier[index]->M_AXI_ARPROT[index_port](SIG_ARBITER_X2X_AXI_ARPROT[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            x2x_arbier[index]->M_AXI_ARREGION[index_port](SIG_ARBITER_X2X_AXI_ARREGION[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            x2x_arbier[index]->M_AXI_ARQOS[index_port](SIG_ARBITER_X2X_AXI_ARQOS[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ARUSER_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_ARUSER[index_port](SIG_ARBITER_X2X_AXI_ARUSER[index][index_port]);
        }
        x2x_arbier[index]->M_AXI_ARLOCK(SIG_ARBITER_X2X_AXI_ARLOCK[index]);
        x2x_arbier[index]->M_AXI_ARVALID(SIG_ARBITER_X2X_AXI_ARVALID[index]);
        x2x_arbier[index]->M_AXI_ARREADY(SIG_ARBITER_X2X_AXI_ARREADY[index]);
    }
    // R
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_RID[index_port](SIG_ARBITER_X2X_AXI_RID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_RDATA[index_port](SIG_ARBITER_X2X_AXI_RDATA[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            x2x_arbier[index]->M_AXI_RRESP[index_port](SIG_ARBITER_X2X_AXI_RRESP[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_RUSER_WIDTH; index_port++)
        {
            x2x_arbier[index]->M_AXI_RUSER[index_port](SIG_ARBITER_X2X_AXI_RUSER[index][index_port]);
        }
        x2x_arbier[index]->M_AXI_RLAST(SIG_ARBITER_X2X_AXI_RLAST[index]);
        x2x_arbier[index]->M_AXI_RVALID(SIG_ARBITER_X2X_AXI_RVALID[index]);
        x2x_arbier[index]->M_AXI_RREADY(SIG_ARBITER_X2X_AXI_RREADY[index]);
    }
    // *************************x2x to output port*************************
    // *************************x2x_arbiter to output port*************************
    // AW
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (M_AXI_AWID[index][index_port])(SIG_ARBITER_X2X_AXI_AWID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            (M_AXI_AWADDR[index][index_port])(SIG_ARBITER_X2X_AXI_AWADDR[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            (M_AXI_AWLEN[index][index_port])(SIG_ARBITER_X2X_AXI_AWLEN[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            (M_AXI_AWSIZE[index][index_port])(SIG_ARBITER_X2X_AXI_AWSIZE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            (M_AXI_AWBURST[index][index_port])(SIG_ARBITER_X2X_AXI_AWBURST[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            (M_AXI_AWCACHE[index][index_port])(SIG_ARBITER_X2X_AXI_AWCACHE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            (M_AXI_AWPROT[index][index_port])(SIG_ARBITER_X2X_AXI_AWPROT[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            (M_AXI_AWREGION[index][index_port])(SIG_ARBITER_X2X_AXI_AWREGION[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            (M_AXI_AWQOS[index][index_port])(SIG_ARBITER_X2X_AXI_AWQOS[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++)
        {
            (M_AXI_AWUSER[index][index_port])(SIG_ARBITER_X2X_AXI_AWUSER[index][index_port]);
        }
        (M_AXI_AWLOCK[index])(SIG_ARBITER_X2X_AXI_AWLOCK[index]);
        (M_AXI_AWVALID[index])(SIG_ARBITER_X2X_AXI_AWVALID[index]);
        (M_AXI_AWREADY[index])(SIG_ARBITER_X2X_AXI_AWREADY[index]);
    }
    // W
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (M_AXI_WID[index][index_port])(SIG_ARBITER_X2X_AXI_WID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            (M_AXI_WDATA[index][index_port])(SIG_ARBITER_X2X_AXI_WDATA[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH / 8; index_port++)
        {
            (M_AXI_WSTRB[index][index_port])(SIG_ARBITER_X2X_AXI_WSTRB[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_WUSER_WIDTH; index_port++)
        {
            (M_AXI_WUSER[index][index_port])(SIG_ARBITER_X2X_AXI_WUSER[index][index_port]);
        }
        (M_AXI_WLAST[index])(SIG_ARBITER_X2X_AXI_WLAST[index]);
        (M_AXI_WVALID[index])(SIG_ARBITER_X2X_AXI_WVALID[index]);
        (M_AXI_WREADY[index])(SIG_ARBITER_X2X_AXI_WREADY[index]);
    }
    // B
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (M_AXI_BID[index][index_port])(SIG_ARBITER_X2X_AXI_BID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            (M_AXI_BRESP[index][index_port])(SIG_ARBITER_X2X_AXI_BRESP[index][index_port]);
        }
        (M_AXI_BUSER[index])(SIG_ARBITER_X2X_AXI_BUSER[index]);
        (M_AXI_BVALID[index])(SIG_ARBITER_X2X_AXI_BVALID[index]);
        (M_AXI_BREADY[index])(SIG_ARBITER_X2X_AXI_BREADY[index]);
    }
    // AW
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (M_AXI_ARID[index][index_port])(SIG_ARBITER_X2X_AXI_ARID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++)
        {
            (M_AXI_ARADDR[index][index_port])(SIG_ARBITER_X2X_AXI_ARADDR[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++)
        {
            (M_AXI_ARLEN[index][index_port])(SIG_ARBITER_X2X_AXI_ARLEN[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++)
        {
            (M_AXI_ARSIZE[index][index_port])(SIG_ARBITER_X2X_AXI_ARSIZE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++)
        {
            (M_AXI_ARBURST[index][index_port])(SIG_ARBITER_X2X_AXI_ARBURST[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++)
        {
            (M_AXI_ARCACHE[index][index_port])(SIG_ARBITER_X2X_AXI_ARCACHE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++)
        {
            (M_AXI_ARPROT[index][index_port])(SIG_ARBITER_X2X_AXI_ARPROT[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++)
        {
            (M_AXI_ARREGION[index][index_port])(SIG_ARBITER_X2X_AXI_ARREGION[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++)
        {
            (M_AXI_ARQOS[index][index_port])(SIG_ARBITER_X2X_AXI_ARQOS[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ARUSER_WIDTH; index_port++)
        {
            (M_AXI_ARUSER[index][index_port])(SIG_ARBITER_X2X_AXI_ARUSER[index][index_port]);
        }
        (M_AXI_ARLOCK[index])(SIG_ARBITER_X2X_AXI_ARLOCK[index]);
        (M_AXI_ARVALID[index])(SIG_ARBITER_X2X_AXI_ARVALID[index]);
        (M_AXI_ARREADY[index])(SIG_ARBITER_X2X_AXI_ARREADY[index]);
    }
    // R
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++)
        {
            (M_AXI_RID[index][index_port])(SIG_ARBITER_X2X_AXI_RID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++)
        {
            (M_AXI_RDATA[index][index_port])(SIG_ARBITER_X2X_AXI_RDATA[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_RRESP; index_port++)
        {
            (M_AXI_RRESP[index][index_port])(SIG_ARBITER_X2X_AXI_RRESP[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_RUSER_WIDTH; index_port++)
        {
            (M_AXI_RUSER[index][index_port])(SIG_ARBITER_X2X_AXI_RUSER[index][index_port]);
        }
        (M_AXI_RLAST[index])(SIG_ARBITER_X2X_AXI_RLAST[index]);
        (M_AXI_RVALID[index])(SIG_ARBITER_X2X_AXI_RVALID[index]);
        (M_AXI_RREADY[index])(SIG_ARBITER_X2X_AXI_RREADY[index]);
    }
}

/**
 * Desctructor
 */
X2X::~X2X()
{
}
