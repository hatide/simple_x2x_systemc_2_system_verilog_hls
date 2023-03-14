/**
 * x2x_fifo IP
 */

#include "systemc.h"

#ifndef __x2x_fifo__H__
#define __x2x_fifo__H__
template <unsigned int DATA_WIDTH>
class x2x_fifo : public sc_module
{
private:
  const bool RESET_TYPE = false;
  const bool PUSH_TYPE = true;
  const bool POP_TYPE = true;
  #define NUMBER_ELEMENTS_OF_FIFO 16

  struct DataStructure
  {
    sc_biguint<DATA_WIDTH> data;
    bool is_empty;
    bool is_read_en;
    bool is_written;
    DataStructure()
    {
      data = 0;
      is_empty = true;
      is_read_en = false;
      is_written = false;
    }
    void remove_data()
    {
      is_empty = true;
      is_read_en = true;
      data = 0;
    }
    void reset_read()
    {
      is_read_en = false;
    }
    void reset_write()
    {
      is_written = false;
    }
  };

  DataStructure data_buffer[NUMBER_ELEMENTS_OF_FIFO];
  bool is_push;
  bool is_pop;

  void handle_push_method();
  void handle_pop_method();
  void reset_written();
  void reset_read_enable();
  void set_data(unsigned int numElement);
  void get_data(unsigned int numElement);
  void handle_buffer_method();
  bool is_empty();
  bool is_full();

public:
  x2x_fifo(){};
  x2x_fifo(sc_module_name name);
  ~x2x_fifo();
  // input signal
  sc_in<sc_uint<DATA_WIDTH>> In;
  sc_in<bool> Push;
  sc_in<bool> Pop;
  sc_in<bool> Clock;
  sc_in<bool> Reset;
  // output signal
  sc_out<sc_uint<DATA_WIDTH>> Out;
  sc_out<bool> Empty;
  sc_out<bool> Full;
};

#endif //_x2x_fifo_H