/**
 * X2x_buffer ip
 * Created by Tien Tran
 */

#include "X2x_buffer.h"

/**
 * Constructor
 */

X2x_buffer::X2x_buffer(sc_module_name name) : sc_module(name)
, S_AXI_AWID_aw_fifo("S_AXI_AWID_aw_fifo")
, S_AXI_AWADDR_aw_fifo("S_AXI_AWADDR_aw_fifo")
, S_AXI_AWLEN_aw_fifo("S_AXI_AWLEN_aw_fifo")
, S_AXI_AWSIZE_aw_fifo("S_AXI_AWSIZE_aw_fifo")
, S_AXI_AWBURST_aw_fifo("S_AXI_AWBURST_aw_fifo")
, S_AXI_AWLOCK_aw_fifo("S_AXI_AWLOCK_aw_fifo")
, S_AXI_AWCACHE_aw_fifo("S_AXI_AWCACHE_aw_fifo")
, S_AXI_AWPROT_aw_fifo("S_AXI_AWPROT_aw_fifo")
, S_AXI_AWREGION_aw_fifo("S_AXI_AWREGION_aw_fifo")
, S_AXI_AWQOS_aw_fifo("S_AXI_AWQOS_aw_fifo")
, S_AXI_AWUSER_aw_fifo("S_AXI_AWUSER_aw_fifo")
,S_AXI_WID_w_fifo("S_AXI_WID_w_fifo")
, S_AXI_WDATA_w_fifo("S_AXI_WDATA_w_fifo")
, S_AXI_WSTRB_w_fifo("S_AXI_WSTRB_w_fifo")
, S_AXI_WUSER_w_fifo("S_AXI_WUSER_w_fifo")
,S_AXI_ARID_ar_fifo("S_AXI_ARID_ar_fifo")
, S_AXI_ARADDR_ar_fifo("S_AXI_ARADDR_ar_fifo")
, S_AXI_ARLEN_ar_fifo("S_AXI_ARLEN_ar_fifo")
, S_AXI_ARSIZE_ar_fifo("S_AXI_ARSIZE_ar_fifo")
, S_AXI_ARBURST_ar_fifo("S_AXI_ARBURST_ar_fifo")
, S_AXI_ARCACHE_ar_fifo("S_AXI_ARCACHE_ar_fifo")
, S_AXI_ARPROT_ar_fifo("S_AXI_ARPROT_ar_fifo")
, S_AXI_ARREGION_ar_fifo("S_AXI_ARREGION_ar_fifo")
, S_AXI_ARQOS_ar_fifo("S_AXI_ARQOS_ar_fifo")
, S_AXI_ARUSER_ar_fifo("S_AXI_ARUSER_ar_fifo")
, S_AXI_ARLOCK_ar_fifo("S_AXI_ARLOCK_ar_fifo")
{
  // Process registration
  SC_HAS_PROCESS(X2x_buffer);
  // connect clock and reset
  S_AXI_AWID_aw_fifo.Clock(ACLK);
  S_AXI_AWADDR_aw_fifo.Clock(ACLK);
  S_AXI_AWLEN_aw_fifo.Clock(ACLK);
  S_AXI_AWSIZE_aw_fifo.Clock(ACLK);
  S_AXI_AWBURST_aw_fifo.Clock(ACLK);
  S_AXI_AWLOCK_aw_fifo.Clock(ACLK);
  S_AXI_AWCACHE_aw_fifo.Clock(ACLK);
  S_AXI_AWPROT_aw_fifo.Clock(ACLK);
  S_AXI_AWREGION_aw_fifo.Clock(ACLK);
  S_AXI_AWQOS_aw_fifo.Clock(ACLK);
  S_AXI_AWUSER_aw_fifo.Clock(ACLK);

  S_AXI_WID_w_fifo.Clock(ACLK);
  S_AXI_WDATA_w_fifo.Clock(ACLK);
  S_AXI_WSTRB_w_fifo.Clock(ACLK);
  S_AXI_WUSER_w_fifo.Clock(ACLK);

  S_AXI_ARID_ar_fifo.Clock(ACLK);
  S_AXI_ARADDR_ar_fifo.Clock(ACLK);
  S_AXI_ARLEN_ar_fifo.Clock(ACLK);
  S_AXI_ARSIZE_ar_fifo.Clock(ACLK);
  S_AXI_ARBURST_ar_fifo.Clock(ACLK);
  S_AXI_ARCACHE_ar_fifo.Clock(ACLK);
  S_AXI_ARPROT_ar_fifo.Clock(ACLK);
  S_AXI_ARREGION_ar_fifo.Clock(ACLK);
  S_AXI_ARQOS_ar_fifo.Clock(ACLK);
  S_AXI_ARUSER_ar_fifo.Clock(ACLK);
  S_AXI_ARLOCK_ar_fifo.Clock(ACLK);

  S_AXI_AWID_aw_fifo.Reset(ARESETN);
  S_AXI_AWADDR_aw_fifo.Reset(ARESETN);
  S_AXI_AWLEN_aw_fifo.Reset(ARESETN);
  S_AXI_AWSIZE_aw_fifo.Reset(ARESETN);
  S_AXI_AWBURST_aw_fifo.Reset(ARESETN);
  S_AXI_AWLOCK_aw_fifo.Reset(ARESETN);
  S_AXI_AWCACHE_aw_fifo.Reset(ARESETN);
  S_AXI_AWPROT_aw_fifo.Reset(ARESETN);
  S_AXI_AWREGION_aw_fifo.Reset(ARESETN);
  S_AXI_AWQOS_aw_fifo.Reset(ARESETN);
  S_AXI_AWUSER_aw_fifo.Reset(ARESETN);

  S_AXI_WID_w_fifo.Reset(ARESETN);
  S_AXI_WDATA_w_fifo.Reset(ARESETN);
  S_AXI_WSTRB_w_fifo.Reset(ARESETN);
  S_AXI_WUSER_w_fifo.Reset(ARESETN);

  S_AXI_ARID_ar_fifo.Reset(ARESETN);
  S_AXI_ARADDR_ar_fifo.Reset(ARESETN);
  S_AXI_ARLEN_ar_fifo.Reset(ARESETN);
  S_AXI_ARSIZE_ar_fifo.Reset(ARESETN);
  S_AXI_ARBURST_ar_fifo.Reset(ARESETN);
  S_AXI_ARCACHE_ar_fifo.Reset(ARESETN);
  S_AXI_ARPROT_ar_fifo.Reset(ARESETN);
  S_AXI_ARREGION_ar_fifo.Reset(ARESETN);
  S_AXI_ARQOS_ar_fifo.Reset(ARESETN);
  S_AXI_ARUSER_ar_fifo.Reset(ARESETN);
  S_AXI_ARLOCK_ar_fifo.Reset(ARESETN);

  S_AXI_WID_w_fifo.Pop(WPop);
  S_AXI_WDATA_w_fifo.Pop(WPop);
  S_AXI_WSTRB_w_fifo.Pop(WPop);
  S_AXI_WUSER_w_fifo.Pop(WPop);

  S_AXI_AWID_aw_fifo.Pop(AwPop);
  S_AXI_AWADDR_aw_fifo.Pop(AwPop);
  S_AXI_AWLEN_aw_fifo.Pop(AwPop);
  S_AXI_AWSIZE_aw_fifo.Pop(AwPop);
  S_AXI_AWBURST_aw_fifo.Pop(AwPop);
  S_AXI_AWLOCK_aw_fifo.Pop(AwPop);
  S_AXI_AWCACHE_aw_fifo.Pop(AwPop);
  S_AXI_AWPROT_aw_fifo.Pop(AwPop);
  S_AXI_AWREGION_aw_fifo.Pop(AwPop);
  S_AXI_AWQOS_aw_fifo.Pop(AwPop);
  S_AXI_AWUSER_aw_fifo.Pop(AwPop);

  S_AXI_ARID_ar_fifo.Pop(ArPop);
  S_AXI_ARADDR_ar_fifo.Pop(ArPop);
  S_AXI_ARLEN_ar_fifo.Pop(ArPop);
  S_AXI_ARSIZE_ar_fifo.Pop(ArPop);
  S_AXI_ARBURST_ar_fifo.Pop(ArPop);
  S_AXI_ARCACHE_ar_fifo.Pop(ArPop);
  S_AXI_ARPROT_ar_fifo.Pop(ArPop);
  S_AXI_ARREGION_ar_fifo.Pop(ArPop);
  S_AXI_ARQOS_ar_fifo.Pop(ArPop);
  S_AXI_ARUSER_ar_fifo.Pop(ArPop);
  S_AXI_ARLOCK_ar_fifo.Pop(ArPop);

  AwFull(S_AXI_WDATA_w_fifo.Full);
  WFull(S_AXI_AWADDR_aw_fifo.Full);
  ARFull(S_AXI_ARADDR_ar_fifo.Full);
  // R channel
  M_AXI_RID(S_AXI_RID);
  M_AXI_RDATA(S_AXI_RDATA);
  M_AXI_RRESP(S_AXI_RRESP);
  M_AXI_RUSER(S_AXI_RUSER);
  M_AXI_RLAST(S_AXI_RLAST);
  M_AXI_RVALID(S_AXI_RVALID);
  S_AXI_RREADY(M_AXI_RREADY);
  // B channel
  M_AXI_BID(S_AXI_BID);
  M_AXI_BRESP(S_AXI_BRESP);
  M_AXI_BUSER(S_AXI_BUSER);
  M_AXI_BVALID(S_AXI_BVALID);
  S_AXI_BREADY(M_AXI_BREADY);

  S_AXI_WID_w_fifo.In(S_AXI_WID);
  S_AXI_WDATA_w_fifo.In(S_AXI_WDATA);
  S_AXI_WSTRB_w_fifo.In(S_AXI_WSTRB);
  S_AXI_WUSER_w_fifo.In(S_AXI_WUSER);

  S_AXI_AWID_aw_fifo.In(S_AXI_AWID);
  S_AXI_AWADDR_aw_fifo.In(S_AXI_AWADDR);
  S_AXI_AWLEN_aw_fifo.In(S_AXI_AWLEN);
  S_AXI_AWSIZE_aw_fifo.In(S_AXI_AWSIZE);
  S_AXI_AWBURST_aw_fifo.In(S_AXI_AWBURST);
  S_AXI_AWLOCK_aw_fifo.In(S_AXI_AWLOCK);
  S_AXI_AWCACHE_aw_fifo.In(S_AXI_AWCACHE);
  S_AXI_AWPROT_aw_fifo.In(S_AXI_AWPROT);
  S_AXI_AWREGION_aw_fifo.In(S_AXI_AWREGION);
  S_AXI_AWQOS_aw_fifo.In(S_AXI_AWQOS);
  S_AXI_AWUSER_aw_fifo.In(S_AXI_AWUSER);

  S_AXI_ARID_ar_fifo.In(S_AXI_ARID);
  S_AXI_ARADDR_ar_fifo.In(S_AXI_ARADDR);
  S_AXI_ARLEN_ar_fifo.In(S_AXI_ARLEN);
  S_AXI_ARSIZE_ar_fifo.In(S_AXI_ARSIZE);
  S_AXI_ARBURST_ar_fifo.In(S_AXI_ARBURST);
  S_AXI_ARCACHE_ar_fifo.In(S_AXI_ARCACHE);
  S_AXI_ARPROT_ar_fifo.In(S_AXI_ARPROT);
  S_AXI_ARREGION_ar_fifo.In(S_AXI_ARREGION);
  S_AXI_ARQOS_ar_fifo.In(S_AXI_ARQOS);
  S_AXI_ARUSER_ar_fifo.In(S_AXI_ARUSER);
  S_AXI_ARLOCK_ar_fifo.In(S_AXI_ARLOCK);

  S_AXI_WID_w_fifo.Out(M_AXI_WID);
  S_AXI_WDATA_w_fifo.Out(M_AXI_WDATA);
  S_AXI_WSTRB_w_fifo.Out(M_AXI_WSTRB);
  S_AXI_WUSER_w_fifo.Out(M_AXI_WUSER);

  S_AXI_AWID_aw_fifo.Out(M_AXI_AWID);
  S_AXI_AWADDR_aw_fifo.Out(M_AXI_AWADDR);
  S_AXI_AWLEN_aw_fifo.Out(M_AXI_AWLEN);
  S_AXI_AWSIZE_aw_fifo.Out(M_AXI_AWSIZE);
  S_AXI_AWBURST_aw_fifo.Out(M_AXI_AWBURST);
  S_AXI_AWLOCK_aw_fifo.Out(M_AXI_AWLOCK);
  S_AXI_AWCACHE_aw_fifo.Out(M_AXI_AWCACHE);
  S_AXI_AWPROT_aw_fifo.Out(M_AXI_AWPROT);
  S_AXI_AWREGION_aw_fifo.Out(M_AXI_AWREGION);
  S_AXI_AWQOS_aw_fifo.Out(M_AXI_AWQOS);
  S_AXI_AWUSER_aw_fifo.Out(M_AXI_AWUSER);

  S_AXI_ARID_ar_fifo.Out(M_AXI_ARID);
  S_AXI_ARADDR_ar_fifo.Out(M_AXI_ARADDR);
  S_AXI_ARLEN_ar_fifo.Out(M_AXI_ARLEN);
  S_AXI_ARSIZE_ar_fifo.Out(M_AXI_ARSIZE);
  S_AXI_ARBURST_ar_fifo.Out(M_AXI_ARBURST);
  S_AXI_ARCACHE_ar_fifo.Out(M_AXI_ARCACHE);
  S_AXI_ARPROT_ar_fifo.Out(M_AXI_ARPROT);
  S_AXI_ARREGION_ar_fifo.Out(M_AXI_ARREGION);
  S_AXI_ARQOS_ar_fifo.Out(M_AXI_ARQOS);
  S_AXI_ARUSER_ar_fifo.Out(M_AXI_ARUSER);
  S_AXI_ARLOCK_ar_fifo.Out(M_AXI_ARLOCK);

  SC_METHOD(handle_aw_push_method)
  dont_initialize();
  sensitive << S_AXI_AWVALID;
  sensitive << S_AXI_AWADDR_aw_fifo.Full;

  SC_METHOD(handle_w_push_method)
  dont_initialize();
  sensitive << S_AXI_WVALID;
  sensitive << S_AXI_WDATA_w_fifo.Full;

  SC_METHOD(handle_ar_push_method)
  dont_initialize();
  sensitive << S_AXI_ARVALID;
  sensitive << S_AXI_ARADDR_ar_fifo.Full;
}

/**
 * Desctructor
 */
X2x_buffer::~X2x_buffer()
{
}
/**
 * handle_aw_push_method
 */
void X2x_buffer::handle_aw_push_method()
{
  aw_fifo_push_signal.write((!S_AXI_AWADDR_aw_fifo.Full.read()) & S_AXI_AWVALID.read());

  S_AXI_AWID_aw_fifo.Push(aw_fifo_push_signal);
  S_AXI_AWADDR_aw_fifo.Push(aw_fifo_push_signal);
  S_AXI_AWLEN_aw_fifo.Push(aw_fifo_push_signal);
  S_AXI_AWSIZE_aw_fifo.Push(aw_fifo_push_signal);
  S_AXI_AWBURST_aw_fifo.Push(aw_fifo_push_signal);
  S_AXI_AWLOCK_aw_fifo.Push(aw_fifo_push_signal);
  S_AXI_AWCACHE_aw_fifo.Push(aw_fifo_push_signal);
  S_AXI_AWPROT_aw_fifo.Push(aw_fifo_push_signal);
  S_AXI_AWREGION_aw_fifo.Push(aw_fifo_push_signal);
  S_AXI_AWQOS_aw_fifo.Push(aw_fifo_push_signal);
  S_AXI_AWUSER_aw_fifo.Push(aw_fifo_push_signal);

  S_AXI_AWREADY.write(!S_AXI_AWADDR_aw_fifo.Full.read());
}
/**
 * handle_w_push_method
 */
void X2x_buffer::handle_w_push_method()
{
  w_fifo_push_signal.write((!S_AXI_WDATA_w_fifo.Full.read()) & S_AXI_WVALID.read());
  S_AXI_WID_w_fifo.Push(w_fifo_push_signal);
  S_AXI_WDATA_w_fifo.Push(w_fifo_push_signal);
  S_AXI_WSTRB_w_fifo.Push(w_fifo_push_signal);
  S_AXI_WUSER_w_fifo.Push(w_fifo_push_signal);

  S_AXI_WREADY.write(!S_AXI_WDATA_w_fifo.Full.read());
}
/**
 * handle_ar_push_method
 */
void X2x_buffer::handle_ar_push_method()
{
  ar_fifo_push_signal.write((!S_AXI_ARADDR_ar_fifo.Full.read()) & S_AXI_ARVALID.read());

  S_AXI_ARID_ar_fifo.Push(ar_fifo_push_signal);
  S_AXI_ARADDR_ar_fifo.Push(ar_fifo_push_signal);
  S_AXI_ARLEN_ar_fifo.Push(ar_fifo_push_signal);
  S_AXI_ARSIZE_ar_fifo.Push(ar_fifo_push_signal);
  S_AXI_ARBURST_ar_fifo.Push(ar_fifo_push_signal);
  S_AXI_ARCACHE_ar_fifo.Push(ar_fifo_push_signal);
  S_AXI_ARPROT_ar_fifo.Push(ar_fifo_push_signal);
  S_AXI_ARREGION_ar_fifo.Push(ar_fifo_push_signal);
  S_AXI_ARQOS_ar_fifo.Push(ar_fifo_push_signal);
  S_AXI_ARUSER_ar_fifo.Push(ar_fifo_push_signal);
  S_AXI_ARLOCK_ar_fifo.Push(ar_fifo_push_signal);

  S_AXI_ARREADY.write(!S_AXI_ARADDR_ar_fifo.Full.read());
}
