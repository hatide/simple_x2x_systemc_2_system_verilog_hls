/**
 * X2X Decoder Implementation
 */

#include "X2x_decoder.h"

/**
 * X2x_decoder constructor
 */
X2x_decoder::X2x_decoder(sc_module_name name) : sc_module(name)
{
  for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
  {
    is_aw_address_match[index] = false;
    is_ar_address_match[index] = false;
    start_Address[index] = 0x0;
    end_Address[index] = 0x0;
  }
  m_AXI_ARADDR = 0x0;
  m_AXI_AWADDR = 0x0;
  // Process registration
  SC_HAS_PROCESS(X2x_decoder);
  SC_METHOD(InsertAWMasterIDMethod)
  sensitive << S_AXI_AWID;
  dont_initialize();
  SC_METHOD(InsertARMasterIDMethod)
  sensitive << S_AXI_ARID;
  dont_initialize();
  SC_METHOD(InsertWMasterIDMethod)
  sensitive << S_AXI_WID;
  dont_initialize();
  SC_METHOD(BChannelHandlerMethod)
  sensitive << M_AXI_BVALID;
  dont_initialize();
  SC_METHOD(RChannelHandlerMethod)
  sensitive << M_AXI_RVALID;
  dont_initialize();
  SC_METHOD(AwPopOutMethod)
  sensitive << S_AXI_AWVALID;
  for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
  {
    sensitive << M_AXI_AWREADY[index];
  }
  dont_initialize();
  SC_METHOD(WPopOutMethod)
  sensitive << S_AXI_WVALID;
  for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
  {
    sensitive << M_AXI_WREADY[index];
  }
  dont_initialize();
  SC_METHOD(ArPopOutMethod)
  sensitive << S_AXI_ARVALID;
  for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
  {
    sensitive << M_AXI_ARREADY[index];
  }
  dont_initialize();
  // blind port
  S_AXI_BREADY(M_AXI_BREADY);
  S_AXI_RREADY(M_AXI_RREADY);
  SC_METHOD(AWSelectorMethod)
  sensitive << S_AXI_AWID;
  sensitive << S_AXI_AWADDR;
  sensitive << S_AXI_AWLEN;
  sensitive << S_AXI_AWSIZE;
  sensitive << S_AXI_AWBURST;
  sensitive << S_AXI_AWCACHE;
  sensitive << S_AXI_AWLOCK;
  sensitive << S_AXI_AWPROT;
  sensitive << S_AXI_AWREGION;
  sensitive << S_AXI_AWQOS;
  sensitive << S_AXI_AWUSER;
  sensitive << S_AXI_AWVALID;
  dont_initialize();
  SC_METHOD(WSelectorMethod)
  sensitive << S_AXI_WID;
  sensitive << S_AXI_WDATA;
  sensitive << S_AXI_WSTRB;
  sensitive << S_AXI_WLAST;
  sensitive << S_AXI_WUSER;
  sensitive << S_AXI_WVALID;
  dont_initialize();
  SC_METHOD(ARSelectorMethod)
  sensitive << S_AXI_ARID;
  sensitive << S_AXI_ARADDR;
  sensitive << S_AXI_ARLEN;
  sensitive << S_AXI_ARSIZE;
  sensitive << S_AXI_ARBURST;
  sensitive << S_AXI_ARLOCK;
  sensitive << S_AXI_ARCACHE;
  sensitive << S_AXI_ARPROT;
  sensitive << S_AXI_ARREGION;
  sensitive << S_AXI_ARQOS;
  sensitive << S_AXI_ARUSER;
  sensitive << S_AXI_ARVALID;
  dont_initialize();
}
/**
 * X2x_decoder constructor
 */
X2x_decoder::~X2x_decoder()
{
}
/**
 * InsertAWMasterIDMethod
 */
void X2x_decoder::InsertAWMasterIDMethod()
{
  m_AXI_AWID.range(C_S_AXI_ID_WIDTH - 1, PRAM_BIT_INSERTID) = masterID;
}
/**
 * InsertWMasterIDMethod
 */
void X2x_decoder::InsertWMasterIDMethod()
{
  m_AXI_WID.range(C_S_AXI_ID_WIDTH - 1, PRAM_BIT_INSERTID) = masterID;
}
/**
 * InsertARMasterIDMethod
 */
void X2x_decoder::InsertARMasterIDMethod()
{
  m_AXI_ARID.range(C_S_AXI_ID_WIDTH - 1, PRAM_BIT_INSERTID) = masterID;
}
/**
 * JudgmentARAddressMethod
 */
void X2x_decoder::JudgmentARAddressMethod()
{
  m_AXI_ARADDR = S_AXI_ARADDR.read();
  for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
  {
    if ((start_Address[index] <= m_AXI_ARADDR) && (m_AXI_ARADDR <= end_Address[index]))
    {
      is_ar_address_match[index] = true;
    }
    else
    {
      is_ar_address_match[index] = false;
    }
  }
}
/**
 * JudgmentAWAddressMethod
 */
void X2x_decoder::JudgmentAWAddressMethod()
{
  m_AXI_AWADDR = S_AXI_ARADDR.read();
  // get address
  for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
  {
    if ((start_Address[index] <= m_AXI_AWADDR) && (m_AXI_AWADDR <= end_Address[index]))
    {
      is_aw_address_match[index] = true;
    }
    else
    {
      is_aw_address_match[index] = false;
    }
  }
}
/**
 * BChannelHandlerMethod
 */
void X2x_decoder::BChannelHandlerMethod()
{
  bool isMasterID = false;
  if (M_AXI_BVALID.read() != 0)
  {
    if (masterID == M_AXI_BID.read().range(C_S_AXI_ID_WIDTH - 1, PRAM_BIT_INSERTID))
    {
      isMasterID = true;
    }
    if (isMasterID != true)
    {
      S_AXI_BID.write(M_AXI_BID.read());     // AXI Read data response ID
      S_AXI_BRESP.write(M_AXI_BRESP.read()); // AXI Read response code.
      S_AXI_BUSER.write(M_AXI_BUSER.read()); // User-defined R Channel signals.
      S_AXI_RLAST.write(M_AXI_RLAST.read()); // AXI Read data last signal.
      S_AXI_BVALID.write(M_AXI_BVALID.read());
    }
  }
  else
  {
    S_AXI_BVALID.write(M_AXI_BVALID.read());
    // not thing
  }
}
/**
 * RChannelHandlerMethod
 */
void X2x_decoder::RChannelHandlerMethod()
{
  bool isMasterID = false;
  if (M_AXI_RVALID.read() != false)
  {
    if (masterID == M_AXI_RID.read().range(C_S_AXI_ID_WIDTH - 1, PRAM_BIT_INSERTID))
    {
      isMasterID = true;
    }
    if (isMasterID != true)
    {
      S_AXI_RID.write(M_AXI_RID.read());     // AXI Read data response ID
      S_AXI_RDATA.write(M_AXI_RDATA.read()); // AXI Read data.
      S_AXI_RRESP.write(M_AXI_RRESP.read()); // AXI Read response code.
      S_AXI_RUSER.write(M_AXI_RUSER.read()); // User-defined R Channel signals.
      S_AXI_RLAST.write(M_AXI_RLAST.read()); // AXI Read data last signal.
      S_AXI_RVALID.write(M_AXI_RVALID.read());
    }
  }
  else
  {
    S_AXI_RVALID.write(M_AXI_RVALID.read());
  }
}
/**
 * AwPopOutMethod
 */
void X2x_decoder::AwPopOutMethod()
{
  bool mAwPopOut = false;
  for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
  {
    bool mValid = (M_AXI_AWREADY[index].read() & is_aw_address_match[index] & S_AXI_AWVALID.read());
    mAwPopOut |= mValid;
  }
  S_AXI_AWPOPOUT.write(mAwPopOut);
}
/**
 * WPopOutMethod
 */
void X2x_decoder::WPopOutMethod()
{
  bool mWPopOut = false;
  for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
  {
    bool mValid = (M_AXI_WREADY[index].read() & S_AXI_WVALID.read());
    mWPopOut |= mValid;
  }
  S_AXI_WPOPOUT.write(mWPopOut);
}
/**
 * ArPopOutMethod
 */
void X2x_decoder::ArPopOutMethod()
{
  bool mArPopOut = false;
  for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
  {
    bool mValid = (M_AXI_ARREADY[index].read() & is_ar_address_match[index] & S_AXI_ARVALID.read());
    mArPopOut |= mValid;
  }
  S_AXI_ARPOPOUT.write(mArPopOut);
}
/**
 * AWSelectorMethod
 */
void X2x_decoder::AWSelectorMethod()
{
  if (S_AXI_AWVALID.read() != false)
  { // valid
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
      if (is_aw_address_match[index])
      { // correct address

        M_AXI_AWID[index].write(m_AXI_AWID);
        M_AXI_AWADDR[index].write(S_AXI_AWADDR.read());
        M_AXI_AWLEN[index].write(S_AXI_AWLEN.read());
        M_AXI_AWSIZE[index].write(S_AXI_AWSIZE.read());
        M_AXI_AWBURST[index].write(S_AXI_AWBURST.read());
        M_AXI_AWLOCK[index].write(S_AXI_AWLOCK.read());
        M_AXI_AWCACHE[index].write(S_AXI_AWCACHE.read());
        M_AXI_AWPROT[index].write(S_AXI_AWPROT.read());
        M_AXI_AWREGION[index].write(S_AXI_AWREGION.read());
        M_AXI_AWQOS[index].write(S_AXI_AWQOS.read());
        M_AXI_AWUSER[index].write(S_AXI_AWUSER.read());
        M_AXI_AWVALID[index].write(S_AXI_AWVALID.read());
      }
      else
      {
        M_AXI_AWVALID[index].write(0x0);
      }
    }
  }
  else
  { // not valid
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
      M_AXI_AWVALID[index].write(0x0);
    }
  }
}
/**
 * WSelectorMethod
 */
void X2x_decoder::WSelectorMethod()
{
  if (S_AXI_WVALID.read() != false)
  { // valid
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
      if (is_aw_address_match[index])
      { // correct address
        M_AXI_WID[index].write(S_AXI_WID.read());
        M_AXI_WDATA[index].write(S_AXI_WDATA.read());
        M_AXI_WSTRB[index].write(S_AXI_WSTRB.read());
        M_AXI_WLAST[index].write(S_AXI_WLAST.read());
        M_AXI_WUSER[index].write(S_AXI_WUSER.read());
        M_AXI_WVALID[index].write(S_AXI_WVALID.read());
      }
      else
      {
        M_AXI_WVALID[index].write(0x0);
      }
    }
  }
  else
  { // not valid
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
      M_AXI_WVALID[index].write(0x0);
    }
  }
}
/**
 * ARSelectorMethod
 */
void X2x_decoder::ARSelectorMethod()
{
  if (S_AXI_ARVALID.read() != false)
  { // valid
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
      if (is_ar_address_match[index])
      { // correct address
        M_AXI_ARID[index].write(m_AXI_ARID);
        M_AXI_ARADDR[index].write(S_AXI_ARADDR.read());
        M_AXI_ARLEN[index].write(S_AXI_ARLEN.read());
        M_AXI_ARSIZE[index].write(S_AXI_ARSIZE.read());
        M_AXI_ARBURST[index].write(S_AXI_ARBURST.read());
        M_AXI_ARLOCK[index].write(S_AXI_ARLOCK.read());
        M_AXI_ARCACHE[index].write(S_AXI_ARCACHE.read());
        M_AXI_ARPROT[index].write(S_AXI_ARPROT.read());
        M_AXI_ARREGION[index].write(S_AXI_ARREGION.read());
        M_AXI_ARQOS[index].write(S_AXI_ARQOS.read());
        M_AXI_ARUSER[index].write(S_AXI_ARUSER.read());
        M_AXI_ARVALID[index].write(S_AXI_ARVALID.read());
      }
      else
      {
        for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
        {
          M_AXI_ARVALID[index].write(0x0);
        }
      }
    }
  }
  else
  { // not valid
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
    {
      M_AXI_ARVALID[index].write(0x0);
    }
  }
}