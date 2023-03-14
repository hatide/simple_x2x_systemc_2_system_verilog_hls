/**
 * x2x ip
 */

#include "x2x.h"

/**
 * Constructor
 */
x2x::x2x(sc_module_name name) : sc_module(name)
{
  x2x_buffer *x2x_buffer[PRAM_MASTER_NUM];   // = {x2x_buffer("x2x_buffer")};
  X2X_DECODER *x2x_decoder[PRAM_MASTER_NUM]; //= {X2X_DECODER("x2x_decoder")};
  X2X_ARBITER *x2x_arbier[PRAM_SLAVE_NUM];   // = {X2X_ARBITER("x2x_arbier")};

  for (size_t i = 0; i < PRAM_MASTER_NUM; i++)
  {
    x2x_buffer[i] = new x2x_buffer("x2x_buffer");
    x2x_decoder[i] = new X2X_DECODER("x2x_decoder");
  }
  for (size_t i = 0; i < PRAM_SLAVE_NUM; i++)
  {
    x2x_arbier[i] = new X2X_ARBITER("x2x_arbier");
  }

  // Process registration
  SC_HAS_PROCESS(x2x);
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
    S_AXI_AWID[index](SIG_X2X_BUFF_AXI_AWID[index]);
    S_AXI_AWADDR[index](SIG_X2X_BUFF_AXI_AWADDR[index]);
    S_AXI_AWLEN[index](SIG_X2X_BUFF_AXI_AWLEN[index]);
    S_AXI_AWSIZE[index](SIG_X2X_BUFF_AXI_AWSIZE[index]);
    S_AXI_AWBURST[index](SIG_X2X_BUFF_AXI_AWBURST[index]);
    S_AXI_AWCACHE[index](SIG_X2X_BUFF_AXI_AWCACHE[index]);
    S_AXI_AWPROT[index](SIG_X2X_BUFF_AXI_AWPROT[index]);
    S_AXI_AWREGION[index](SIG_X2X_BUFF_AXI_AWREGION[index]);
    S_AXI_AWQOS[index](SIG_X2X_BUFF_AXI_AWQOS[index]);
    S_AXI_AWUSER[index](SIG_X2X_BUFF_AXI_AWUSER[index]);
    S_AXI_AWLOCK[index](SIG_X2X_BUFF_AXI_AWLOCK[index]);
    S_AXI_AWVALID[index](SIG_X2X_BUFF_AXI_AWVALID[index]);
    S_AXI_AWREADY[index](SIG_X2X_BUFF_AXI_AWREADY[index]);
    // AR
    S_AXI_ARID[index](SIG_X2X_BUFF_AXI_ARID[index]);
    S_AXI_ARADDR[index](SIG_X2X_BUFF_AXI_ARADDR[index]);
    S_AXI_ARLEN[index](SIG_X2X_BUFF_AXI_ARLEN[index]);
    S_AXI_ARSIZE[index](SIG_X2X_BUFF_AXI_ARSIZE[index]);
    S_AXI_ARBURST[index](SIG_X2X_BUFF_AXI_ARBURST[index]);
    S_AXI_ARCACHE[index](SIG_X2X_BUFF_AXI_ARCACHE[index]);
    S_AXI_ARPROT[index](SIG_X2X_BUFF_AXI_ARPROT[index]);
    S_AXI_ARREGION[index](SIG_X2X_BUFF_AXI_ARREGION[index]);
    S_AXI_ARQOS[index](SIG_X2X_BUFF_AXI_ARQOS[index]);
    S_AXI_ARUSER[index](SIG_X2X_BUFF_AXI_ARUSER[index]);
    S_AXI_ARLOCK[index](SIG_X2X_BUFF_AXI_ARLOCK[index]);
    S_AXI_ARVALID[index](SIG_X2X_BUFF_AXI_ARVALID[index]);
    S_AXI_ARREADY[index](SIG_X2X_BUFF_AXI_ARREADY[index]);
    // W
    S_AXI_WID[index](SIG_X2X_BUFF_AXI_WID[index]);
    S_AXI_WDATA[index](SIG_X2X_BUFF_AXI_WDATA[index]);
    S_AXI_WSTRB[index](SIG_X2X_BUFF_AXI_WSTRB[index]);
    S_AXI_WLAST[index](SIG_X2X_BUFF_AXI_WLAST[index]);
    S_AXI_WVALID[index](SIG_X2X_BUFF_AXI_WVALID[index]);
    S_AXI_WREADY[index](SIG_X2X_BUFF_AXI_WREADY[index]);
    // B
    S_AXI_BID[index](SIG_X2X_BUFF_AXI_BID[index]);
    S_AXI_BRESP[index](SIG_X2X_BUFF_AXI_BRESP[index]);
    S_AXI_BUSER[index](SIG_X2X_BUFF_AXI_BUSER[index]);
    S_AXI_BVALID[index](SIG_X2X_BUFF_AXI_BVALID[index]);
    S_AXI_BREADY[index](SIG_X2X_BUFF_AXI_BREADY[index]);
    // R
    S_AXI_RID[index](SIG_X2X_BUFF_AXI_RID[index]);
    S_AXI_RDATA[index](SIG_X2X_BUFF_AXI_RDATA[index]);
    S_AXI_RRESP[index](SIG_X2X_BUFF_AXI_RRESP[index]);
    S_AXI_RUSER[index](SIG_X2X_BUFF_AXI_RUSER[index]);
    S_AXI_RLAST[index](SIG_X2X_BUFF_AXI_RLAST[index]);
    S_AXI_RVALID[index](SIG_X2X_BUFF_AXI_RVALID[index]);
    S_AXI_RREADY[index](SIG_X2X_BUFF_AXI_RREADY[index]);
    // ***********************x2x_buffer to signal inputport******************
    // ***********************x2x_buffer to input port***********************
    // AW
    (x2x_buffer[index]->S_AXI_AWID)(SIG_X2X_BUFF_AXI_AWID[index]);
    (x2x_buffer[index]->S_AXI_AWADDR)(SIG_X2X_BUFF_AXI_AWADDR[index]);
    (x2x_buffer[index]->S_AXI_AWLEN)(SIG_X2X_BUFF_AXI_AWLEN[index]);
    (x2x_buffer[index]->S_AXI_AWSIZE)(SIG_X2X_BUFF_AXI_AWSIZE[index]);
    (x2x_buffer[index]->S_AXI_AWBURST)(SIG_X2X_BUFF_AXI_AWBURST[index]);
    (x2x_buffer[index]->S_AXI_AWCACHE)(SIG_X2X_BUFF_AXI_AWCACHE[index]);
    (x2x_buffer[index]->S_AXI_AWPROT)(SIG_X2X_BUFF_AXI_AWPROT[index]);
    (x2x_buffer[index]->S_AXI_AWREGION)(SIG_X2X_BUFF_AXI_AWREGION[index]);
    (x2x_buffer[index]->S_AXI_AWQOS)(SIG_X2X_BUFF_AXI_AWQOS[index]);
    (x2x_buffer[index]->S_AXI_AWUSER)(SIG_X2X_BUFF_AXI_AWUSER[index]);
    (x2x_buffer[index]->S_AXI_AWLOCK)(SIG_X2X_BUFF_AXI_AWLOCK[index]);
    (x2x_buffer[index]->S_AXI_AWVALID)(SIG_X2X_BUFF_AXI_AWVALID[index]);
    (x2x_buffer[index]->S_AXI_AWREADY)(SIG_X2X_BUFF_AXI_AWREADY[index]);
    // AR
    (x2x_buffer[index]->S_AXI_ARID)(SIG_X2X_BUFF_AXI_ARID[index]);
    (x2x_buffer[index]->S_AXI_ARADDR)(SIG_X2X_BUFF_AXI_ARADDR[index]);
    (x2x_buffer[index]->S_AXI_ARLEN)(SIG_X2X_BUFF_AXI_ARLEN[index]);
    (x2x_buffer[index]->S_AXI_ARSIZE)(SIG_X2X_BUFF_AXI_ARSIZE[index]);
    (x2x_buffer[index]->S_AXI_ARBURST)(SIG_X2X_BUFF_AXI_ARBURST[index]);
    (x2x_buffer[index]->S_AXI_ARCACHE)(SIG_X2X_BUFF_AXI_ARCACHE[index]);
    (x2x_buffer[index]->S_AXI_ARPROT)(SIG_X2X_BUFF_AXI_ARPROT[index]);
    (x2x_buffer[index]->S_AXI_ARREGION)(SIG_X2X_BUFF_AXI_ARREGION[index]);
    (x2x_buffer[index]->S_AXI_ARQOS)(SIG_X2X_BUFF_AXI_ARQOS[index]);
    (x2x_buffer[index]->S_AXI_ARUSER)(SIG_X2X_BUFF_AXI_ARUSER[index]);
    (x2x_buffer[index]->S_AXI_ARLOCK)(SIG_X2X_BUFF_AXI_ARLOCK[index]);
    (x2x_buffer[index]->S_AXI_ARVALID)(SIG_X2X_BUFF_AXI_ARVALID[index]);
    (x2x_buffer[index]->S_AXI_ARREADY)(SIG_X2X_BUFF_AXI_ARREADY[index]);
    // W
    (x2x_buffer[index]->S_AXI_WID)(SIG_X2X_BUFF_AXI_WID[index]);
    (x2x_buffer[index]->S_AXI_WDATA)(SIG_X2X_BUFF_AXI_WDATA[index]);
    (x2x_buffer[index]->S_AXI_WSTRB)(SIG_X2X_BUFF_AXI_WSTRB[index]);
    (x2x_buffer[index]->S_AXI_WLAST)(SIG_X2X_BUFF_AXI_WLAST[index]);
    (x2x_buffer[index]->S_AXI_WUSER)(SIG_X2X_BUFF_AXI_WUSER[index]);
    (x2x_buffer[index]->S_AXI_WVALID)(SIG_X2X_BUFF_AXI_WVALID[index]);
    (x2x_buffer[index]->S_AXI_WREADY)(SIG_X2X_BUFF_AXI_WREADY[index]);
    // B
    (x2x_buffer[index]->S_AXI_BID)(SIG_X2X_BUFF_AXI_BID[index]);
    (x2x_buffer[index]->S_AXI_BRESP)(SIG_X2X_BUFF_AXI_BRESP[index]);
    (x2x_buffer[index]->S_AXI_BUSER)(SIG_X2X_BUFF_AXI_BUSER[index]);
    (x2x_buffer[index]->S_AXI_BVALID)(SIG_X2X_BUFF_AXI_BVALID[index]);
    (x2x_buffer[index]->S_AXI_BREADY)(SIG_X2X_BUFF_AXI_BREADY[index]);
    // R
    (x2x_buffer[index]->S_AXI_RID)(SIG_X2X_BUFF_AXI_RID[index]);
    (x2x_buffer[index]->S_AXI_RDATA)(SIG_X2X_BUFF_AXI_RDATA[index]);
    (x2x_buffer[index]->S_AXI_RRESP)(SIG_X2X_BUFF_AXI_RRESP[index]);
    (x2x_buffer[index]->S_AXI_RUSER)(SIG_X2X_BUFF_AXI_RUSER[index]);
    (x2x_buffer[index]->S_AXI_RLAST)(SIG_X2X_BUFF_AXI_RLAST[index]);
    (x2x_buffer[index]->S_AXI_RVALID)(SIG_X2X_BUFF_AXI_RVALID[index]);
    (x2x_buffer[index]->S_AXI_RREADY)(SIG_X2X_BUFF_AXI_RREADY[index]);
    //***********************x2x_buffer to x2x_decoder signal***********************
    // ***********************x2x_buffer to x2x_decoder***********************
    // AW
    (x2x_buffer[index]->M_AXI_AWID)(SIG_BUFF_DECODER_S_AXI_AWID[index]);
    (x2x_buffer[index]->M_AXI_AWADDR)(SIG_BUFF_DECODER_S_AXI_AWADDR[index]);
    (x2x_buffer[index]->M_AXI_AWLEN)(SIG_BUFF_DECODER_S_AXI_AWLEN[index]);
    (x2x_buffer[index]->M_AXI_AWSIZE)(SIG_BUFF_DECODER_S_AXI_AWSIZE[index]);
    (x2x_buffer[index]->M_AXI_AWBURST)(SIG_BUFF_DECODER_S_AXI_AWBURST[index]);
    (x2x_buffer[index]->M_AXI_AWCACHE)(SIG_BUFF_DECODER_S_AXI_AWCACHE[index]);
    (x2x_buffer[index]->M_AXI_AWPROT)(SIG_BUFF_DECODER_S_AXI_AWPROT[index]);
    (x2x_buffer[index]->M_AXI_AWREGION)(SIG_BUFF_DECODER_S_AXI_AWREGION[index]);
    (x2x_buffer[index]->M_AXI_AWQOS)(SIG_BUFF_DECODER_S_AXI_AWQOS[index]);
    (x2x_buffer[index]->M_AXI_AWUSER)(SIG_BUFF_DECODER_S_AXI_AWUSER[index]);
    (x2x_buffer[index]->M_AXI_AWLOCK)(SIG_BUFF_DECODER_S_AXI_AWLOCK[index]);
    (x2x_buffer[index]->M_AXI_AWVALID)(SIG_BUFF_DECODER_S_AXI_AWVALID[index]);
    x2x_buffer[index]->AwPop(SIG_BUFF_DECODER_S_AXI_AWPOPOUT[index]);
    // W
    (x2x_buffer[index]->M_AXI_WID)(SIG_BUFF_DECODER_S_AXI_WID[index]);
    (x2x_buffer[index]->M_AXI_WDATA)(SIG_BUFF_DECODER_S_AXI_WDATA[index]);
    (x2x_buffer[index]->M_AXI_WSTRB)(SIG_BUFF_DECODER_S_AXI_WSTRB[index]);
    (x2x_buffer[index]->M_AXI_WUSER)(SIG_BUFF_DECODER_S_AXI_WUSER[index]);
    (x2x_buffer[index]->M_AXI_WLAST)(SIG_BUFF_DECODER_S_AXI_WLAST[index]);
    (x2x_buffer[index]->M_AXI_WVALID)(SIG_BUFF_DECODER_S_AXI_WVALID[index]);
    (x2x_buffer[index]->WPop)(SIG_BUFF_DECODER_S_AXI_WPOPOUT[index]);
    //(x2x_decoder[index][index]->S_AXI_WPOPOUT)(x2x_buffer[index]->WPop);
    // B
    x2x_buffer[index]->M_AXI_BID(SIG_BUFF_DECODER_S_AXI_BID[index]);
    x2x_buffer[index]->M_AXI_BRESP(SIG_BUFF_DECODER_S_AXI_BRESP[index]);
    x2x_buffer[index]->M_AXI_WLAST(SIG_BUFF_DECODER_S_AXI_BUSER[index]);
    x2x_buffer[index]->M_AXI_WVALID(SIG_BUFF_DECODER_S_AXI_BVALID[index]);
    (x2x_buffer[index]->M_AXI_BREADY)(SIG_BUFF_DECODER_S_AXI_BREADY[index]);
    // AR
    (x2x_buffer[index]->M_AXI_ARID)(SIG_BUFF_DECODER_S_AXI_ARID[index]);
    (x2x_buffer[index]->M_AXI_ARADDR)(SIG_BUFF_DECODER_S_AXI_ARADDR[index]);
    (x2x_buffer[index]->M_AXI_ARLEN)(SIG_BUFF_DECODER_S_AXI_ARLEN[index]);
    (x2x_buffer[index]->M_AXI_ARSIZE)(SIG_BUFF_DECODER_S_AXI_ARSIZE[index]);
    (x2x_buffer[index]->M_AXI_ARBURST)(SIG_BUFF_DECODER_S_AXI_ARBURST[index]);
    (x2x_buffer[index]->M_AXI_ARCACHE)(SIG_BUFF_DECODER_S_AXI_ARCACHE[index]);
    (x2x_buffer[index]->M_AXI_ARPROT)(SIG_BUFF_DECODER_S_AXI_ARPROT[index]);
    (x2x_buffer[index]->M_AXI_ARREGION)(SIG_BUFF_DECODER_S_AXI_ARREGION[index]);
    (x2x_buffer[index]->M_AXI_ARQOS)(SIG_BUFF_DECODER_S_AXI_ARQOS[index]);
    (x2x_buffer[index]->M_AXI_ARUSER)(SIG_BUFF_DECODER_S_AXI_ARUSER[index]);
    (x2x_buffer[index]->M_AXI_ARLOCK)(SIG_BUFF_DECODER_S_AXI_ARLOCK[index]);
    (x2x_buffer[index]->M_AXI_ARVALID)(SIG_BUFF_DECODER_S_AXI_ARVALID[index]);
    x2x_buffer[index]->ArPop(SIG_BUFF_DECODER_S_AXI_ARPOPOUT[index]);
    // R
    x2x_buffer[index]->M_AXI_RID(SIG_BUFF_DECODER_S_AXI_RID[index]);
    x2x_buffer[index]->M_AXI_RDATA(SIG_BUFF_DECODER_S_AXI_RDATA[index]);
    x2x_buffer[index]->M_AXI_RRESP(SIG_BUFF_DECODER_S_AXI_RRESP[index]);
    x2x_buffer[index]->M_AXI_RUSER(SIG_BUFF_DECODER_S_AXI_RUSER[index]);
    x2x_buffer[index]->M_AXI_RLAST(SIG_BUFF_DECODER_S_AXI_RLAST[index]);
    x2x_buffer[index]->M_AXI_RVALID(SIG_BUFF_DECODER_S_AXI_RVALID[index]);
    (x2x_buffer[index]->M_AXI_RREADY)(SIG_BUFF_DECODER_S_AXI_BREADY[index]);
    // ***********************x2x_buffer to x2x_decoder***********************
    // AW
    x2x_decoder[index]->S_AXI_AWID(x2x_buffer[index]->M_AXI_AWID);
    x2x_decoder[index]->S_AXI_AWADDR(x2x_buffer[index]->M_AXI_AWADDR);
    x2x_decoder[index]->S_AXI_AWLEN(x2x_buffer[index]->M_AXI_AWLEN);
    x2x_decoder[index]->S_AXI_AWSIZE(x2x_buffer[index]->M_AXI_AWSIZE);
    x2x_decoder[index]->S_AXI_AWBURST(x2x_buffer[index]->M_AXI_AWBURST);
    x2x_decoder[index]->S_AXI_AWCACHE(x2x_buffer[index]->M_AXI_AWCACHE);
    x2x_decoder[index]->S_AXI_AWPROT(x2x_buffer[index]->M_AXI_AWPROT);
    x2x_decoder[index]->S_AXI_AWREGION(x2x_buffer[index]->M_AXI_AWREGION);
    x2x_decoder[index]->S_AXI_AWQOS(x2x_buffer[index]->M_AXI_AWQOS);
    x2x_decoder[index]->S_AXI_AWUSER(x2x_buffer[index]->M_AXI_AWUSER);
    x2x_decoder[index]->S_AXI_AWLOCK(x2x_buffer[index]->M_AXI_AWLOCK);
    x2x_decoder[index]->S_AXI_AWVALID(x2x_buffer[index]->M_AXI_AWVALID);
    x2x_buffer[index]->AwPop(x2x_decoder[index]->S_AXI_AWPOPOUT);
    // W
    x2x_decoder[index]->S_AXI_WID(x2x_buffer[index]->M_AXI_WID);
    x2x_decoder[index]->S_AXI_WDATA(x2x_buffer[index]->M_AXI_WDATA);
    x2x_decoder[index]->S_AXI_WSTRB(x2x_buffer[index]->M_AXI_WSTRB);
    x2x_decoder[index]->S_AXI_WUSER(x2x_buffer[index]->M_AXI_WUSER);
    x2x_decoder[index]->S_AXI_WLAST(x2x_buffer[index]->M_AXI_WLAST);
    x2x_decoder[index]->S_AXI_WVALID(x2x_buffer[index]->M_AXI_WVALID);
    x2x_buffer[index]->WPop(x2x_decoder[index]->S_AXI_WPOPOUT);
    // B
    x2x_buffer[index]->M_AXI_BID(x2x_decoder[index]->S_AXI_BID);
    x2x_buffer[index]->M_AXI_BRESP(x2x_decoder[index]->S_AXI_BRESP);
    x2x_buffer[index]->M_AXI_WLAST(x2x_decoder[index]->S_AXI_BUSER);
    x2x_buffer[index]->M_AXI_WVALID(x2x_decoder[index]->S_AXI_BVALID);
    x2x_decoder[index]->S_AXI_BREADY(x2x_buffer[index]->M_AXI_BREADY);
    // AR
    x2x_decoder[index]->S_AXI_ARID(x2x_buffer[index]->M_AXI_ARID);
    x2x_decoder[index]->S_AXI_ARADDR(x2x_buffer[index]->M_AXI_ARADDR);
    x2x_decoder[index]->S_AXI_ARLEN(x2x_buffer[index]->M_AXI_ARLEN);
    x2x_decoder[index]->S_AXI_ARSIZE(x2x_buffer[index]->M_AXI_ARSIZE);
    x2x_decoder[index]->S_AXI_ARBURST(x2x_buffer[index]->M_AXI_ARBURST);
    x2x_decoder[index]->S_AXI_ARCACHE(x2x_buffer[index]->M_AXI_ARCACHE);
    x2x_decoder[index]->S_AXI_ARPROT(x2x_buffer[index]->M_AXI_ARPROT);
    x2x_decoder[index]->S_AXI_ARREGION(x2x_buffer[index]->M_AXI_ARREGION);
    x2x_decoder[index]->S_AXI_ARQOS(x2x_buffer[index]->M_AXI_ARQOS);
    x2x_decoder[index]->S_AXI_ARUSER(x2x_buffer[index]->M_AXI_ARUSER);
    x2x_decoder[index]->S_AXI_ARLOCK(x2x_buffer[index]->M_AXI_ARLOCK);
    x2x_decoder[index]->S_AXI_ARVALID(x2x_buffer[index]->M_AXI_ARVALID);
    x2x_buffer[index]->ArPop(x2x_decoder[index]->S_AXI_ARPOPOUT);
    // R
    x2x_buffer[index]->M_AXI_RID(x2x_decoder[index]->S_AXI_RID);
    x2x_buffer[index]->M_AXI_RDATA(x2x_decoder[index]->S_AXI_RDATA);
    x2x_buffer[index]->M_AXI_RRESP(x2x_decoder[index]->S_AXI_RRESP);
    x2x_buffer[index]->M_AXI_RUSER(x2x_decoder[index]->S_AXI_RUSER);
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
      x2x_arbier[index_slave]->S_AXI_AWID[index_master](x2x_decoder[index_master]->M_AXI_AWID[index_slave]);
      x2x_arbier[index_slave]->S_AXI_AWADDR[index_master](x2x_decoder[index_master]->M_AXI_AWADDR[index_slave]);
      x2x_arbier[index_slave]->S_AXI_AWLEN[index_master](x2x_decoder[index_master]->M_AXI_AWLEN[index_slave]);
      x2x_arbier[index_slave]->S_AXI_AWSIZE[index_master](x2x_decoder[index_master]->M_AXI_AWSIZE[index_slave]);
      x2x_arbier[index_slave]->S_AXI_AWBURST[index_master](x2x_decoder[index_master]->M_AXI_AWBURST[index_slave]);
      x2x_arbier[index_slave]->S_AXI_AWCACHE[index_master](x2x_decoder[index_master]->M_AXI_AWCACHE[index_slave]);
      x2x_arbier[index_slave]->S_AXI_AWPROT[index_master](x2x_decoder[index_master]->M_AXI_AWPROT[index_slave]);
      x2x_arbier[index_slave]->S_AXI_AWREGION[index_master](x2x_decoder[index_master]->M_AXI_AWREGION[index_slave]);
      x2x_arbier[index_slave]->S_AXI_AWQOS[index_master](x2x_decoder[index_master]->M_AXI_AWQOS[index_slave]);
      x2x_arbier[index_slave]->S_AXI_AWUSER[index_master](x2x_decoder[index_master]->M_AXI_AWUSER[index_slave]);
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
      x2x_arbier[index_slave]->S_AXI_WID[index_master](x2x_decoder[index_master]->M_AXI_WID[index_slave]);
      x2x_arbier[index_slave]->S_AXI_WDATA[index_master](x2x_decoder[index_master]->M_AXI_WDATA[index_slave]);
      x2x_arbier[index_slave]->S_AXI_WSTRB[index_master](x2x_decoder[index_master]->M_AXI_WSTRB[index_slave]);
      x2x_arbier[index_slave]->S_AXI_WUSER[index_master](x2x_decoder[index_master]->M_AXI_WUSER[index_slave]);
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
      x2x_decoder[index_master]->M_AXI_BID(x2x_arbier[index_slave]->S_AXI_BID);
      x2x_decoder[index_master]->M_AXI_BRESP(x2x_arbier[index_slave]->S_AXI_BRESP);
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
      x2x_arbier[index_slave]->S_AXI_ARID[index_master](x2x_decoder[index_master]->M_AXI_ARID[index_slave]);
      x2x_arbier[index_slave]->S_AXI_ARADDR[index_master](x2x_decoder[index_master]->M_AXI_ARADDR[index_slave]);
      x2x_arbier[index_slave]->S_AXI_ARLEN[index_master](x2x_decoder[index_master]->M_AXI_ARLEN[index_slave]);
      x2x_arbier[index_slave]->S_AXI_ARSIZE[index_master](x2x_decoder[index_master]->M_AXI_ARSIZE[index_slave]);
      x2x_arbier[index_slave]->S_AXI_ARBURST[index_master](x2x_decoder[index_master]->M_AXI_ARBURST[index_slave]);
      x2x_arbier[index_slave]->S_AXI_ARCACHE[index_master](x2x_decoder[index_master]->M_AXI_ARCACHE[index_slave]);
      x2x_arbier[index_slave]->S_AXI_ARPROT[index_master](x2x_decoder[index_master]->M_AXI_ARPROT[index_slave]);
      x2x_arbier[index_slave]->S_AXI_ARREGION[index_master](x2x_decoder[index_master]->M_AXI_ARREGION[index_slave]);
      x2x_arbier[index_slave]->S_AXI_ARQOS[index_master](x2x_decoder[index_master]->M_AXI_ARQOS[index_slave]);
      x2x_arbier[index_slave]->S_AXI_ARUSER[index_master](x2x_decoder[index_master]->M_AXI_ARUSER[index_slave]);
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
      x2x_decoder[index_master]->M_AXI_RID(x2x_arbier[index_slave]->S_AXI_RID);
      x2x_decoder[index_master]->M_AXI_RRESP(x2x_arbier[index_slave]->S_AXI_RRESP);
      x2x_decoder[index_master]->M_AXI_RDATA(x2x_arbier[index_slave]->S_AXI_RDATA);
      x2x_decoder[index_master]->M_AXI_RUSER(x2x_arbier[index_slave]->S_AXI_RUSER);
      x2x_arbier[index_slave]->S_AXI_RREADY(x2x_decoder[index_master]->M_AXI_RREADY);
      x2x_decoder[index_master]->M_AXI_RLAST(x2x_arbier[index_slave]->S_AXI_RLAST);
      x2x_decoder[index_master]->M_AXI_RVALID(x2x_arbier[index_slave]->S_AXI_RVALID);
    }
  }
  // *************************x2x_arbiter to output port*************************
  // AW

  for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
  {
    x2x_arbier[index]->M_AXI_AWID(SIG_ARBITER_X2X_AXI_AWID[index]);
    x2x_arbier[index]->M_AXI_AWADDR(SIG_ARBITER_X2X_AXI_AWADDR[index]);
    x2x_arbier[index]->M_AXI_AWLEN(SIG_ARBITER_X2X_AXI_AWLEN[index]);
    x2x_arbier[index]->M_AXI_AWSIZE(SIG_ARBITER_X2X_AXI_AWSIZE[index]);
    x2x_arbier[index]->M_AXI_AWBURST(SIG_ARBITER_X2X_AXI_AWBURST[index]);
    x2x_arbier[index]->M_AXI_AWCACHE(SIG_ARBITER_X2X_AXI_AWCACHE[index]);
    x2x_arbier[index]->M_AXI_AWPROT(SIG_ARBITER_X2X_AXI_AWPROT[index]);
    x2x_arbier[index]->M_AXI_AWREGION(SIG_ARBITER_X2X_AXI_AWREGION[index]);
    x2x_arbier[index]->M_AXI_AWQOS(SIG_ARBITER_X2X_AXI_AWQOS[index]);
    x2x_arbier[index]->M_AXI_AWUSER(SIG_ARBITER_X2X_AXI_AWUSER[index]);
    x2x_arbier[index]->M_AXI_AWLOCK(SIG_ARBITER_X2X_AXI_AWLOCK[index]);
    x2x_arbier[index]->M_AXI_AWVALID(SIG_ARBITER_X2X_AXI_AWVALID[index]);
    x2x_arbier[index]->M_AXI_AWREADY(SIG_ARBITER_X2X_AXI_AWREADY[index]);
    // W
    x2x_arbier[index]->M_AXI_WID(SIG_ARBITER_X2X_AXI_WID[index]);
    x2x_arbier[index]->M_AXI_WDATA(SIG_ARBITER_X2X_AXI_WDATA[index]);
    x2x_arbier[index]->M_AXI_WSTRB(SIG_ARBITER_X2X_AXI_WSTRB[index]);
    x2x_arbier[index]->M_AXI_WUSER(SIG_ARBITER_X2X_AXI_WUSER[index]);
    x2x_arbier[index]->M_AXI_WLAST(SIG_ARBITER_X2X_AXI_WLAST[index]);
    x2x_arbier[index]->M_AXI_WVALID(SIG_ARBITER_X2X_AXI_WVALID[index]);
    x2x_arbier[index]->M_AXI_WREADY(SIG_ARBITER_X2X_AXI_WREADY[index]);
    // B
    x2x_arbier[index]->M_AXI_BID(SIG_ARBITER_X2X_AXI_BID[index]);
    x2x_arbier[index]->M_AXI_BRESP(SIG_ARBITER_X2X_AXI_BRESP[index]);
    x2x_arbier[index]->M_AXI_BUSER(SIG_ARBITER_X2X_AXI_BUSER[index]);
    x2x_arbier[index]->M_AXI_BVALID(SIG_ARBITER_X2X_AXI_BVALID[index]);
    x2x_arbier[index]->M_AXI_BREADY(SIG_ARBITER_X2X_AXI_BREADY[index]);
    // AW
    x2x_arbier[index]->M_AXI_ARID(SIG_ARBITER_X2X_AXI_ARID[index]);
    x2x_arbier[index]->M_AXI_ARADDR(SIG_ARBITER_X2X_AXI_ARADDR[index]);
    x2x_arbier[index]->M_AXI_ARLEN(SIG_ARBITER_X2X_AXI_ARLEN[index]);
    x2x_arbier[index]->M_AXI_ARSIZE(SIG_ARBITER_X2X_AXI_ARSIZE[index]);
    x2x_arbier[index]->M_AXI_ARBURST(SIG_ARBITER_X2X_AXI_ARBURST[index]);
    x2x_arbier[index]->M_AXI_ARCACHE(SIG_ARBITER_X2X_AXI_ARCACHE[index]);
    x2x_arbier[index]->M_AXI_ARPROT(SIG_ARBITER_X2X_AXI_ARPROT[index]);
    x2x_arbier[index]->M_AXI_ARREGION(SIG_ARBITER_X2X_AXI_ARREGION[index]);
    x2x_arbier[index]->M_AXI_ARQOS(SIG_ARBITER_X2X_AXI_ARQOS[index]);
    x2x_arbier[index]->M_AXI_ARUSER(SIG_ARBITER_X2X_AXI_ARUSER[index]);
    x2x_arbier[index]->M_AXI_ARLOCK(SIG_ARBITER_X2X_AXI_ARLOCK[index]);
    x2x_arbier[index]->M_AXI_ARVALID(SIG_ARBITER_X2X_AXI_ARVALID[index]);
    x2x_arbier[index]->M_AXI_ARREADY(SIG_ARBITER_X2X_AXI_ARREADY[index]);
    // R
    x2x_arbier[index]->M_AXI_RID(SIG_ARBITER_X2X_AXI_RID[index]);
    x2x_arbier[index]->M_AXI_RDATA(SIG_ARBITER_X2X_AXI_RDATA[index]);
    x2x_arbier[index]->M_AXI_RRESP(SIG_ARBITER_X2X_AXI_RRESP[index]);
    x2x_arbier[index]->M_AXI_RUSER(SIG_ARBITER_X2X_AXI_RUSER[index]);
    x2x_arbier[index]->M_AXI_RLAST(SIG_ARBITER_X2X_AXI_RLAST[index]);
    x2x_arbier[index]->M_AXI_RVALID(SIG_ARBITER_X2X_AXI_RVALID[index]);
    x2x_arbier[index]->M_AXI_RREADY(SIG_ARBITER_X2X_AXI_RREADY[index]);
    // *************************x2x to output port*************************
    // *************************x2x_arbiter to output port*************************
    // AW
    (M_AXI_AWID[index])(SIG_ARBITER_X2X_AXI_AWID[index]);
    (M_AXI_AWADDR[index])(SIG_ARBITER_X2X_AXI_AWADDR[index]);
    (M_AXI_AWLEN[index])(SIG_ARBITER_X2X_AXI_AWLEN[index]);
    (M_AXI_AWSIZE[index])(SIG_ARBITER_X2X_AXI_AWSIZE[index]);
    (M_AXI_AWBURST[index])(SIG_ARBITER_X2X_AXI_AWBURST[index]);
    (M_AXI_AWCACHE[index])(SIG_ARBITER_X2X_AXI_AWCACHE[index]);
    (M_AXI_AWPROT[index])(SIG_ARBITER_X2X_AXI_AWPROT[index]);
    (M_AXI_AWREGION[index])(SIG_ARBITER_X2X_AXI_AWREGION[index]);
    (M_AXI_AWQOS[index])(SIG_ARBITER_X2X_AXI_AWQOS[index]);
    (M_AXI_AWUSER[index])(SIG_ARBITER_X2X_AXI_AWUSER[index]);
    (M_AXI_AWLOCK[index])(SIG_ARBITER_X2X_AXI_AWLOCK[index]);
    (M_AXI_AWVALID[index])(SIG_ARBITER_X2X_AXI_AWVALID[index]);
    (M_AXI_AWREADY[index])(SIG_ARBITER_X2X_AXI_AWREADY[index]);
    // W
    (M_AXI_WID[index])(SIG_ARBITER_X2X_AXI_WID[index]);
    (M_AXI_WDATA[index])(SIG_ARBITER_X2X_AXI_WDATA[index]);
    (M_AXI_WSTRB[index])(SIG_ARBITER_X2X_AXI_WSTRB[index]);
    (M_AXI_WUSER[index])(SIG_ARBITER_X2X_AXI_WUSER[index]);
    (M_AXI_WLAST[index])(SIG_ARBITER_X2X_AXI_WLAST[index]);
    (M_AXI_WVALID[index])(SIG_ARBITER_X2X_AXI_WVALID[index]);
    (M_AXI_WREADY[index])(SIG_ARBITER_X2X_AXI_WREADY[index]);
    // B
    (M_AXI_BID[index])(SIG_ARBITER_X2X_AXI_BID[index]);
    (M_AXI_BRESP[index])(SIG_ARBITER_X2X_AXI_BRESP[index]);
    (M_AXI_BUSER[index])(SIG_ARBITER_X2X_AXI_BUSER[index]);
    (M_AXI_BVALID[index])(SIG_ARBITER_X2X_AXI_BVALID[index]);
    (M_AXI_BREADY[index])(SIG_ARBITER_X2X_AXI_BREADY[index]);
    // AW
    (M_AXI_ARID[index])(SIG_ARBITER_X2X_AXI_ARID[index]);
    (M_AXI_ARADDR[index])(SIG_ARBITER_X2X_AXI_ARADDR[index]);
    (M_AXI_ARLEN[index])(SIG_ARBITER_X2X_AXI_ARLEN[index]);
    (M_AXI_ARSIZE[index])(SIG_ARBITER_X2X_AXI_ARSIZE[index]);
    (M_AXI_ARBURST[index])(SIG_ARBITER_X2X_AXI_ARBURST[index]);
    (M_AXI_ARCACHE[index])(SIG_ARBITER_X2X_AXI_ARCACHE[index]);
    (M_AXI_ARPROT[index])(SIG_ARBITER_X2X_AXI_ARPROT[index]);
    (M_AXI_ARREGION[index])(SIG_ARBITER_X2X_AXI_ARREGION[index]);
    (M_AXI_ARQOS[index])(SIG_ARBITER_X2X_AXI_ARQOS[index]);
    (M_AXI_ARUSER[index])(SIG_ARBITER_X2X_AXI_ARUSER[index]);
    (M_AXI_ARLOCK[index])(SIG_ARBITER_X2X_AXI_ARLOCK[index]);
    (M_AXI_ARVALID[index])(SIG_ARBITER_X2X_AXI_ARVALID[index]);
    (M_AXI_ARREADY[index])(SIG_ARBITER_X2X_AXI_ARREADY[index]);
    // R
    (M_AXI_RID[index])(SIG_ARBITER_X2X_AXI_RID[index]);
    (M_AXI_RDATA[index])(SIG_ARBITER_X2X_AXI_RDATA[index]);
    (M_AXI_RRESP[index])(SIG_ARBITER_X2X_AXI_RRESP[index]);
    (M_AXI_RUSER[index])(SIG_ARBITER_X2X_AXI_RUSER[index]);
    (M_AXI_RLAST[index])(SIG_ARBITER_X2X_AXI_RLAST[index]);
    (M_AXI_RVALID[index])(SIG_ARBITER_X2X_AXI_RVALID[index]);
    (M_AXI_RREADY[index])(SIG_ARBITER_X2X_AXI_RREADY[index]);
  }
}

/**
 * Desctructor
 */
x2x::~x2x()
{
}
