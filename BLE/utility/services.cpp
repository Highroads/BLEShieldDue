/* Copyright (c) 2010 Nordic Semiconductor. All Rights Reserved.
*
* The information contained herein is property of Nordic Semiconductor ASA.
* Terms and conditions of usage are described in detail in NORDIC
* SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
*
* Licensees are granted free, non-transferable use of the information. NO
* WARRANTY of ANY KIND is provided. This heading must NOT be removed from
* the file.
*/

/**
* This file is autogenerated by 1.12.2.2126 
*/

#include "services.h"
#include "lib_aci.h"

static bool is_bleshield_vendor_name_set_requested = false;
static bool is_bleshield_rx_data_send_requested = false;
static bool is_bleshield_lib_ver_set_requested = false;

static void *bleshield_vendor_name_set;
static uint8_t bleshield_vendor_name_set_size;
static void *bleshield_rx_data_tx;
static uint8_t bleshield_rx_data_tx_size;
static void *bleshield_lib_ver_set;
static uint8_t bleshield_lib_ver_set_size;

static bool bleshield_vendor_name_update_set(void)
{
  return(lib_aci_set_local_data(PIPE_BLESHIELD_VENDOR_NAME_SET, (uint8_t*)bleshield_vendor_name_set, bleshield_vendor_name_set_size));
}

void services_set_bleshield_vendor_name(void *src, int size)
{
  bleshield_vendor_name_set_size = size;
  bleshield_vendor_name_set = src;
  is_bleshield_vendor_name_set_requested = true;
  services_update_pipes();
}
static bool bleshield_rx_data_update_send(void)
{
  if (lib_aci_is_pipe_available(PIPE_BLESHIELD_RX_DATA_TX))
  {
    return(lib_aci_send_data(PIPE_BLESHIELD_RX_DATA_TX, (uint8_t*)bleshield_rx_data_tx, bleshield_rx_data_tx_size));
  }
  return(false);
}

bool services_send_bleshield_rx_data(void *src, int size, bool is_freshest_sample)
{
  if (false == is_freshest_sample)
  {
    if (true == is_bleshield_rx_data_send_requested)
    {
      services_update_pipes();
    }
    if (false == is_bleshield_rx_data_send_requested)
    {
      bleshield_rx_data_tx_size = size;
      bleshield_rx_data_tx = src;
      is_bleshield_rx_data_send_requested = true;
      services_update_pipes();
      return(true);
    }
    return(false);
  }
  else
  {
    bleshield_rx_data_tx_size = size;
    bleshield_rx_data_tx = src;
    is_bleshield_rx_data_send_requested = true;
    services_update_pipes();
    return(true);
  }
}
static bool bleshield_lib_ver_update_set(void)
{
  return(lib_aci_set_local_data(PIPE_BLESHIELD_LIB_VER_SET, (uint8_t*)bleshield_lib_ver_set, bleshield_lib_ver_set_size));
}

void services_set_bleshield_lib_ver(void *src, int size)
{
  bleshield_lib_ver_set_size = size;
  bleshield_lib_ver_set = src;
  is_bleshield_lib_ver_set_requested = true;
  services_update_pipes();
}

void services_update_pipes(void)
{
  if(is_bleshield_vendor_name_set_requested)
  {
    is_bleshield_vendor_name_set_requested = !(bleshield_vendor_name_update_set());
  }
  if(is_bleshield_rx_data_send_requested)
  {
    is_bleshield_rx_data_send_requested = !(bleshield_rx_data_update_send());
  }
  if(is_bleshield_lib_ver_set_requested)
  {
    is_bleshield_lib_ver_set_requested = !(bleshield_lib_ver_update_set());
  }
}
