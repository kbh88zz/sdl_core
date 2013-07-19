/**
 * \file device_adapter_listener.h
 * \brief interface for DeviceAdapterListener header file.
 *
 * Copyright (c) 2013, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_DEVICE_ADAPTER_LISTENER
#define SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_DEVICE_ADAPTER_LISTENER

#include "transport_manager/common.h"
#include "transport_manager/device_adapter.h"

namespace transport_manager {

class DeviceAdapterListener {
 public:
  // TODO: Kill me, please!
  class DeviceAdapterEvent {
   public:
    bool operator ==(const DeviceAdapterEvent &other);
    DeviceAdapterEvent(int type, int session_id, DeviceAdapter *adapter,
                       const DeviceHandle &device,
                       RawMessageSptr data, DeviceAdapterError *error);
    ~DeviceAdapterEvent();
    void set_event_type(int type);
    void set_session_id(int id);
    void set_device_adapter(DeviceAdapter *device_adapter);
    void set_data(RawMessageSptr data);
    void set_error(DeviceAdapterError *error);
    void set_device_handle(const DeviceHandle &handle);

    int event_type(void) const;
    int session_id(void) const;
    DeviceAdapter *device_adapter(void) const;
    RawMessageSptr data(void) const;
    DeviceAdapterError *event_error(void) const;
    const DeviceHandle &device_handle() const;

   private:
    int event_type_;
    int session_id_;
    DeviceAdapter *device_adapter_;
    DeviceHandle device_handle_;
    RawMessageSptr event_data_;
    DeviceAdapterError *event_error_;
  };

  virtual ~DeviceAdapterListener();
  virtual void onSearchDeviceDone(const DeviceAdapter* device_adapter) = 0;
  virtual void onSearchDeviceFailed(const DeviceAdapter* device_adapter,
                                    const SearchDeviceError& error) = 0;

  virtual void onConnectDone(
      const DeviceAdapter* device_adapter,
      const DeviceHandle device,
      const ConnectionId session_id) = 0;
  virtual void onConnectFailed(const DeviceAdapter* device_adapter,
                               const DeviceHandle device,
                               const ConnectionId session_id,
                               const ConnectError& error) = 0;

  virtual void onDisconnectDone(const DeviceAdapter* device_adapter,
                                const ConnectionId session_id) = 0;
  virtual void onDisconnectFailed(const DeviceAdapter* device_adapter,
                                  const ConnectionId session_id,
                                  const DisconnectError& error) = 0;

  virtual void onDisconnectDeviceDone(const DeviceAdapter* device_adapter,
                                      const ConnectionId session_id) = 0;
  virtual void onDisconnectDeviceFailed(const DeviceAdapter* device_adapter,
                                        const ConnectionId session_id,
                                        const DisconnectDeviceError& error) = 0;

  virtual void onDataSendDone(const DeviceAdapter* device_adapter,
                              const ConnectionId session_id,
                              const RawMessageSptr data_container) = 0;
  virtual void onDataSendFailed(const DeviceAdapter* device_adapter,
                                const ConnectionId session_id,
                                const RawMessageSptr data_container,
                                const DataSendError& error) = 0;

  virtual void onDataReceiveDone(const DeviceAdapter* device_adapter,
                                 const ConnectionId session_id,
                                 const RawMessageSptr data_container) = 0;
  virtual void onDataReceiveFailed(const DeviceAdapter* device_adapter,
                                   const ConnectionId session_id,
                                   const DataReceiveError& error) = 0;

  virtual void onCommunicationError(const DeviceAdapter* device_adapter,
                                    const ConnectionId session_id) = 0;
};
}  //namespace
#endif // SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_DEVICE_ADAPTER_LISTENER
