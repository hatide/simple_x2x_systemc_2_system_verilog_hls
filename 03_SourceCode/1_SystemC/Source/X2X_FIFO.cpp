/**
 * @file x2x_fifo.cpp
 * @author Hatide (tientran26794@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "x2x_fifo.h"

/**
 * @brief Construct a new x2x fifo<DATA WIDTH>::x2x fifo object
 *
 * @tparam DATA_WIDTH
 * @param name
 */
template <unsigned int DATA_WIDTH>
x2x_fifo<DATA_WIDTH>::x2x_fifo(sc_module_name name) : sc_module(name)
{
  Empty.initialize(true);
  Full.initialize(false);
  is_push = !PUSH_TYPE;
  is_pop = !POP_TYPE;
  SC_HAS_PROCESS(x2x_fifo);

  SC_METHOD(handle_push_method);
  dont_initialize();
  sensitive << Push.pos();

  SC_METHOD(handle_pop_method);
  dont_initialize();
  sensitive << Pop.pos();

  SC_METHOD(handle_buffer_method);
  dont_initialize();
  sensitive << Clock.pos();
  sensitive << Reset.neg();
}

/**
 * @brief Destroy the x2x fifo<DATA WIDTH>::x2x fifo object
 *
 * @tparam DATA_WIDTH
 */
template <unsigned int DATA_WIDTH>
x2x_fifo<DATA_WIDTH>::~x2x_fifo()
{
}
/**
 * @brief
 *
 * @tparam DATA_WIDTH
 */
template <unsigned int DATA_WIDTH>
void x2x_fifo<DATA_WIDTH>::handle_push_method()
{
  is_push = PUSH_TYPE;
}

/**
 * @brief
 *
 * @tparam DATA_WIDTH
 */
template <unsigned int DATA_WIDTH>
void x2x_fifo<DATA_WIDTH>::handle_pop_method()
{
  is_pop = PUSH_TYPE;
}
/**
 * @brief
 *
 * @tparam DATA_WIDTH
 * @return true
 * @return false
 */
template <unsigned int DATA_WIDTH>
bool x2x_fifo<DATA_WIDTH>::is_empty()
{
  for (unsigned int index = 0; index < NUMBER_ELEMENTS_OF_FIFO; index++)
  {
    if (data_buffer[index].is_empty == false)
    {
      return false;
    }
  }
  return true;
}
/**
 * @brief
 *
 * @tparam DATA_WIDTH
 * @return true
 * @return false
 */
template <unsigned int DATA_WIDTH>
bool x2x_fifo<DATA_WIDTH>::is_full()
{
  bool result = false;
  for (unsigned int index = 0; index < NUMBER_ELEMENTS_OF_FIFO; index++)
  {
    result |= data_buffer[index].is_empty;
  }
  return !result;
}
/**
 * @brief
 *
 * @tparam DATA_WIDTH
 * @param numElement
 */
template <unsigned int DATA_WIDTH>
void x2x_fifo<DATA_WIDTH>::set_data(unsigned int numElement)
{
  data_buffer[numElement].data = In.read();
  data_buffer[numElement].is_written = true;
  data_buffer[numElement].is_empty = false;
  is_push = !PUSH_TYPE;
}
/**
 * @brief
 *
 * @tparam DATA_WIDTH
 * @param numElement
 */
template <unsigned int DATA_WIDTH>
void x2x_fifo<DATA_WIDTH>::get_data(unsigned int numElement)
{
    Out.write(data_buffer[numElement].data);
}
/**
 * @brief
 *
 * @tparam DATA_WIDTH
 */
template <unsigned int DATA_WIDTH>
void x2x_fifo<DATA_WIDTH>::reset_written()
{
    for (unsigned int index = 0; index < NUMBER_ELEMENTS_OF_FIFO; index++)
    {
      data_buffer[index].reset_write();
    }
}
/**
 * @brief
 *
 * @tparam DATA_WIDTH
 */
template <unsigned int DATA_WIDTH>
void x2x_fifo<DATA_WIDTH>::reset_read_enable()
{
    for (unsigned int index = 0; index < NUMBER_ELEMENTS_OF_FIFO; index++)
    {
      data_buffer[index].reset_read();
    }
}
/**
 * @brief
 *
 * @tparam DATA_WIDTH
 */
template <unsigned int DATA_WIDTH>
void x2x_fifo<DATA_WIDTH>::handle_buffer_method()
{
    if (Reset.read() == RESET_TYPE)
    { // Reset Handler
      for (unsigned int index = 0; index < NUMBER_ELEMENTS_OF_FIFO; index++)
      {
        data_buffer[index].remove_data();
        data_buffer[index].reset_read();
        data_buffer[index].reset_write();
      }
      Out.write(0x0);
    }
    else
    { // Clock Handler
      if ((Empty.read() == true) && (is_push == true))
      {
        Out.write(In.read());
        set_data(0);
      }
      else
      {
        if (is_push == true)
        {
          for (unsigned int index = 0; index < NUMBER_ELEMENTS_OF_FIFO; index++)
          {
            if ((data_buffer[index].is_written == false) && (data_buffer[index].is_empty == true))
            {
              set_data(index);
              // re-set when fifo was write all
              if (index == NUMBER_ELEMENTS_OF_FIFO - 1)
              {
                reset_written();
              }
              break;
            }
          }
        }
        if (is_pop == true)
        {
          for (unsigned int index = 0; index < NUMBER_ELEMENTS_OF_FIFO; index++)
          {
            if ((data_buffer[index].is_read_en == false) && (data_buffer[index].is_empty == false))
            {
              data_buffer[index].remove_data();
              is_pop = !POP_TYPE;
              // re-set when fifo was write all
              if (index == NUMBER_ELEMENTS_OF_FIFO - 1)
              {
                reset_read_enable();
                if (data_buffer[0].is_empty != PUSH_TYPE)
                {
                  get_data(0);
                }
              }
              else if (data_buffer[index + 1].is_empty != PUSH_TYPE)
              {
                get_data(index + 1);
              }
              break;
            }
          }
        }
      }
      Empty.write(is_empty());
      Full.write(is_full());
    }
}
