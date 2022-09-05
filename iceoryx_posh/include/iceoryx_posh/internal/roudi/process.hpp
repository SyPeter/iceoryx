// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
// Copyright (c) 2021 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0
#ifndef IOX_POSH_ROUDI_PROCESS_HPP
#define IOX_POSH_ROUDI_PROCESS_HPP

#include "iceoryx_hoofs/cxx/list.hpp"
#include "iceoryx_hoofs/posix_wrapper/posix_access_rights.hpp"
#include "iceoryx_posh/internal/mepoo/segment_manager.hpp"
#include "iceoryx_posh/internal/roudi/port_manager.hpp"
#include "iceoryx_posh/internal/runtime/ipc_interface_user.hpp"
#include "iceoryx_posh/mepoo/chunk_header.hpp"
#include "iceoryx_posh/version/compatibility_check_level.hpp"
#include "iceoryx_posh/version/version_info.hpp"

#include <cstdint>

namespace iox
{
namespace roudi
{
class Process
{
  public:
    /// @brief This class represents an application which has registered at RouDi and manages the communication to the
    /// application
    /// @param [in] name of the process; this is equal to the IPC channel name, which is used for communication
    /// @param [in] pid is the host system process id
    /// @param [in] user is user used in the operating system for this process
    /// @param [in] isMonitored indicates if the process should be monitored for being alive
    /// @param [in] dataSegmentId is an identifier for the shm data segment
    /// @param [in] sessionId is an ID generated by RouDi to prevent sending outdated IPC channel transmission
    Process(const RuntimeName_t& name,
            const uint32_t pid,
            const posix::PosixUser& user,
            const bool isMonitored,
            const uint64_t sessionId) noexcept;

    Process(const Process& other) = delete;
    Process& operator=(const Process& other) = delete;
    /// @note the move cTor and assignment operator are already implicitly deleted because of the atomic
    Process(Process&& other) = delete;
    Process& operator=(Process&& other) = delete;
    ~Process() noexcept = default;

    uint32_t getPid() const noexcept;

    const RuntimeName_t getName() const noexcept;

    void sendViaIpcChannel(const runtime::IpcMessage& data) noexcept;

    /// @brief The session ID which is used to check outdated IPC channel transmissions for this process
    /// @return the session ID for this process
    uint64_t getSessionId() noexcept;

    void setTimestamp(const mepoo::TimePointNs_t timestamp) noexcept;

    mepoo::TimePointNs_t getTimestamp() noexcept;

    posix::PosixUser getUser() const noexcept;

    bool isMonitored() const noexcept;

  private:
    const uint32_t m_pid{0U};
    runtime::IpcInterfaceUser m_ipcChannel;
    mepoo::TimePointNs_t m_timestamp;
    posix::PosixUser m_user;
    bool m_isMonitored{true};
    std::atomic<uint64_t> m_sessionId{0U};
};

} // namespace roudi
} // namespace iox

#endif // IOX_POSH_ROUDI_PROCESS_HPP
