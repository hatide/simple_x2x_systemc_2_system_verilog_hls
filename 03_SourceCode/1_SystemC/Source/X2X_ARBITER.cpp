/**
 * X2X ARBITER Implementation
 */

#include "x2x_arbiter.h"

/**
 * x2x_arbiter constructor
 */
x2x_arbiter::x2x_arbiter(sc_module_name name) : sc_module(name)
{
  SC_HAS_PROCESS(x2x_arbiter);
  // R channel
  M_AXI_RID.bind(S_AXI_RID);
  M_AXI_RDATA.bind(S_AXI_RDATA);
  M_AXI_RRESP.bind(S_AXI_RRESP);
  M_AXI_RUSER.bind(S_AXI_RUSER);
  M_AXI_RLAST.bind(S_AXI_RLAST);
  M_AXI_RVALID.bind(S_AXI_RVALID);
  S_AXI_RREADY.bind(M_AXI_RREADY);
  // B channel
  M_AXI_BID.bind(S_AXI_BID);
  M_AXI_BRESP.bind(S_AXI_BRESP);
  M_AXI_BUSER.bind(S_AXI_BUSER);
  M_AXI_BVALID.bind(S_AXI_BVALID);
  S_AXI_BREADY.bind(M_AXI_BREADY);
  // internal variable
  for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
  {
    // Aw channel
    AwCounterValue[index] = PRAM_MASTER_NUM - 1;
    isAwValid[index] = false;
    isAwSelector[index] = false;
    // Ar channel
    ArCounterValue[index] = PRAM_MASTER_NUM - 1;
    isArValid[index] = false;
    isArSelector[index] = false;
    // W channel
    WCounterValue[index] = PRAM_MASTER_NUM - 1;
    isWValid[index] = false;
    isWSelector[index] = false;
  }
  // Aw
  isAwInprocess = false;
  AWPriorityValid = PRAM_MASTER_NUM - 1;
  // Ar
  isArInprocess = false;
  ARPriorityValid = PRAM_MASTER_NUM - 1;
  // W
  isWInprocess = false;
  WPriorityValid = PRAM_MASTER_NUM - 1;
  // AW Method
  SC_METHOD(AWRoundRobinMethod)
  for (size_t i = 0; i < PRAM_MASTER_NUM; i++)
  {
    sensitive << S_AXI_AWVALID[i];
  }
  dont_initialize();

  SC_METHOD(AWHandShackSlaveMethod)
  sensitive << M_AXI_AWREADY;
  dont_initialize();

  // AR Method
  SC_METHOD(ARRoundRobinMethod)
  for (size_t i = 0; i < PRAM_MASTER_NUM; i++)
  {
    sensitive << S_AXI_ARVALID[i];
  }

  dont_initialize();

  SC_METHOD(ARHandShackSlaveMethod)
  sensitive << M_AXI_ARREADY;
  dont_initialize();

  // W Method
  SC_METHOD(WRoundRobinMethod)
  for (size_t i = 0; i < PRAM_MASTER_NUM; i++)
  {
    sensitive << S_AXI_WVALID[i];
  }

  dont_initialize();

  SC_METHOD(WHandShackSlaveMethod)
  sensitive << M_AXI_WREADY;
  dont_initialize();
  // Method core
  SC_METHOD(ArbiterCoreMethod)
  sensitive << ACLK.pos();
  sensitive << ARESETN.neg();
  dont_initialize();
}
/**
 * x2x_arbiter constructor
 */
x2x_arbiter::~x2x_arbiter()
{
}

void x2x_arbiter::AWRoundRobinMethod()
{
  for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
  {
    if (S_AXI_AWVALID[index].posedge() && (!isAwValid[index]))
    {
      AwCounterValue[index] -= AWPriorityValid;
      isAwValid[index] = true;
      if (AWPriorityValid > 0)
      { // last valid
        --AWPriorityValid;
      }
    }
    else if (S_AXI_AWVALID[index].negedge() && (isAwValid[index]))
    {
      AwCounterValue[index] = (PRAM_MASTER_NUM - 1);
      isAwValid[index] = false;
      AWPriorityValid++;
      for (unsigned int dec = 0; dec < PRAM_MASTER_NUM; dec++)
      {
        if (dec != index && isAwValid[dec])
        {
          AwCounterValue[index] -= 1;
        }
      }
    }
  }
}

void x2x_arbiter::AWHandShackSlaveMethod()
{
  if (M_AXI_AWREADY.negedge())
  {
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
      if (S_AXI_AWVALID[index].read() == true && AwCounterValue[index] == 0 && isAwValid[index] && isAwSelector[index])
      {
        S_AXI_AWREADY[index].write(true); // need have a internal variable to store it,
        isAwSelector[index] = false;
      }
      else if (S_AXI_AWVALID[index].read() == true && isAwValid[index] && AwCounterValue[index] > 0)
      {
        AwCounterValue[index]--;
      }
    }
  }
  else
  {
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
      if (S_AXI_AWVALID[index].read() == true && AwCounterValue[index] == 0 && isAwValid[index] && isAwSelector[index] != true)
      {
        isAwSelector[index] = true;
      }
    }
  }
}

void x2x_arbiter::ArbiterCoreMethod()
{
  if (ARESETN.negedge())
  {
    // reset internal value
    // internal variable
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
      // Aw channel
      AwCounterValue[index] = PRAM_MASTER_NUM - 1;
      isAwValid[index] = false;
      isAwSelector[index] = false;
      // Ar channel
      ArCounterValue[index] = PRAM_MASTER_NUM - 1;
      isArValid[index] = false;
      isArSelector[index] = false;
      // W channel
      WCounterValue[index] = PRAM_MASTER_NUM - 1;
      isWValid[index] = false;
      isWSelector[index] = false;
    }
    // Aw
    isAwInprocess = false;
    AWPriorityValid = PRAM_MASTER_NUM - 1;
    // Ar
    isArInprocess = false;
    ARPriorityValid = PRAM_MASTER_NUM - 1;
    // W
    isWInprocess = false;
    WPriorityValid = PRAM_MASTER_NUM - 1;
    // AW Method
  }
  else
  {
    // AW varaiable
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
      if (isAwValid[index] && isAwInprocess != true)
      {
        M_AXI_AWVALID.write(isAwValid[index]);
        isAwInprocess = true;
      }
      else if (isAwSelector[index])
      {
        M_AXI_AWID.write(S_AXI_AWID[index]);
        M_AXI_AWADDR.write(S_AXI_AWADDR[index].read());
        M_AXI_AWLEN.write(S_AXI_AWLEN[index].read());
        M_AXI_AWSIZE.write(S_AXI_AWSIZE[index].read());
        M_AXI_AWBURST.write(S_AXI_AWBURST[index].read());
        M_AXI_AWLOCK.write(S_AXI_AWLOCK[index].read());
        M_AXI_AWCACHE.write(S_AXI_AWCACHE[index].read());
        M_AXI_AWPROT.write(S_AXI_AWPROT[index].read());
        M_AXI_AWREGION.write(S_AXI_AWREGION[index].read());
        M_AXI_AWQOS.write(S_AXI_AWQOS[index].read());
        M_AXI_AWUSER.write(S_AXI_AWUSER[index].read());
      }
    }
    // AR varaiable
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
      if (isArValid[index] && isArInprocess != true)
      {
        M_AXI_ARVALID.write(isArValid[index]);
        isArInprocess = true;
      }
      else if (isArSelector[index])
      {

        M_AXI_ARID.write(S_AXI_ARID[index]);
        M_AXI_ARADDR.write(S_AXI_ARADDR[index].read());
        M_AXI_ARLEN.write(S_AXI_ARLEN[index].read());
        M_AXI_ARSIZE.write(S_AXI_ARSIZE[index].read());
        M_AXI_ARBURST.write(S_AXI_ARBURST[index].read());
        M_AXI_ARLOCK.write(S_AXI_ARLOCK[index].read());
        M_AXI_ARCACHE.write(S_AXI_ARCACHE[index].read());
        M_AXI_ARPROT.write(S_AXI_ARPROT[index].read());
        M_AXI_ARREGION.write(S_AXI_ARREGION[index].read());
        M_AXI_ARQOS.write(S_AXI_ARQOS[index].read());
        M_AXI_ARUSER.write(S_AXI_ARUSER[index].read());
      }
    }
    // W varaiable
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
      if (isArValid[index] && isArInprocess != true)
      {
        M_AXI_WVALID.write(isArValid[index]);
        isArInprocess = true;
      }
      else if (isArSelector[index])
      {
        M_AXI_WID.write(S_AXI_WID[index]);
        M_AXI_WDATA.write(S_AXI_WDATA[index].read());
        M_AXI_WSTRB.write(S_AXI_WSTRB[index].read());
        M_AXI_WUSER.write(S_AXI_WUSER[index].read());
        M_AXI_WLAST.write(S_AXI_WLAST[index].read());
      }
    }
  }
}

void x2x_arbiter::ARRoundRobinMethod()
{
  for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
  {
    if (S_AXI_ARVALID[index].posedge() && (!isArValid[index]))
    {
      ArCounterValue[index] -= ARPriorityValid;
      isArValid[index] = true;
      if (ARPriorityValid > 0)
      { // last valid
        --ARPriorityValid;
      }
    }
    else if (S_AXI_ARVALID[index].negedge() && (isArValid[index]))
    {
      ArCounterValue[index] = (PRAM_MASTER_NUM - 1);
      isArValid[index] = false;
      ARPriorityValid++;
      for (unsigned int dec = 0; dec < PRAM_MASTER_NUM; dec++)
      {
        if (dec != index && isArValid[dec])
        {
          ArCounterValue[index] = -1;
        }
      }
    }
  }
}

void x2x_arbiter::ARHandShackSlaveMethod()
{
  if (M_AXI_ARREADY.negedge())
  {
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
      if (S_AXI_ARVALID[index].read() == true && ArCounterValue[index] == 0 && isArValid[index] && isArSelector[index])
      {
        S_AXI_ARREADY[index].write(true); // need have a internal variable to store it,
        isArSelector[index] = false;
      }
      else if (S_AXI_ARVALID[index].read() == true && isArValid[index] && ArCounterValue[index] > 0)
      {
        ArCounterValue[index]--;
      }
    }
  }
  else
  {
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
      if (S_AXI_ARVALID[index].read() == true && ArCounterValue[index] == 0 && isArValid[index] && isArSelector[index] != true)
      {
        isArSelector[index] = true;
      }
    }
  }
}

void x2x_arbiter::WRoundRobinMethod()
{
  for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
  {
    if (S_AXI_WVALID[index].posedge() && (!isArValid[index]))
    {
      ArCounterValue[index] -= WPriorityValid;
      isArValid[index] = true;
      if (WPriorityValid > 0)
      { // last valid
        --WPriorityValid;
      }
    }
    else if (S_AXI_WVALID[index].negedge() && (isArValid[index]))
    {
      ArCounterValue[index] = (PRAM_MASTER_NUM - 1);
      isArValid[index] = false;
      WPriorityValid++;
      for (unsigned int dec = 0; dec < PRAM_MASTER_NUM; dec++)
      {
        if (dec != index && isArValid[dec])
        {
          ArCounterValue[index] = -1;
        }
      }
    }
  }
}

void x2x_arbiter::WHandShackSlaveMethod()
{
  if (M_AXI_WREADY.negedge())
  {
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
      if (S_AXI_WVALID[index].read() == true && WCounterValue[index] == 0 && isWValid[index] && isWSelector[index])
      {
        S_AXI_WREADY[index].write(true); // need have a internal variable to store it,
        isWSelector[index] = false;
      }
      else if (S_AXI_WVALID[index].read() == true && isWValid[index] && WCounterValue[index] > 0)
      {
        WCounterValue[index]--;
      }
    }
  }
  else
  {
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
    {
      if (S_AXI_WVALID[index].read() == true && WCounterValue[index] == 0 && isWValid[index] && isWSelector[index] != true)
      {
        isWSelector[index] = true;
      }
    }
  }
}