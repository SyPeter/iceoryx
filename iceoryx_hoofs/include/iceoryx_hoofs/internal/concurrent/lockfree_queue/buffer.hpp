// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
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

#ifndef IOX_HOOFS_CONCURRENT_LOCKFREE_QUEUE_BUFFER_HPP
#define IOX_HOOFS_CONCURRENT_LOCKFREE_QUEUE_BUFFER_HPP

#include <cstdint>

namespace iox
{
namespace concurrent
{
// remark: we can add more functionality (policies for cache line size, redzoning)

template <typename ElementType, uint64_t Capacity, typename index_t = uint64_t>
class Buffer
{
  public:
    Buffer() noexcept = default;
    ~Buffer() noexcept = default;

    Buffer(const Buffer&) = delete;
    Buffer(Buffer&&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer& operator=(Buffer&&) = delete;

    ElementType& operator[](const index_t index) noexcept;

    const ElementType& operator[](const index_t index) const noexcept;

    ElementType* ptr(const index_t index) noexcept;

    const ElementType* ptr(const index_t index) const noexcept;

    uint64_t capacity() const noexcept;

  private:
    using byte_t = uint8_t;

    // NOLINTJUSTIFICATION required by low level buffer building block and encapsulated in abstraction
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays)
    alignas(ElementType) byte_t m_buffer[Capacity * sizeof(ElementType)];

    ElementType* toPtr(index_t index) const noexcept;
};

} // namespace concurrent
} // namespace iox

#include "iceoryx_hoofs/internal/concurrent/lockfree_queue/buffer.inl"

#endif // IOX_HOOFS_CONCURRENT_LOCKFREE_QUEUE_BUFFER_HPP
