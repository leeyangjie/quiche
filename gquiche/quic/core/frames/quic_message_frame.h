// Copyright (c) 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef QUICHE_QUIC_CORE_FRAMES_QUIC_MESSAGE_FRAME_H_
#define QUICHE_QUIC_CORE_FRAMES_QUIC_MESSAGE_FRAME_H_

#include "absl/container/inlined_vector.h"
#include "absl/types/span.h"
#include "gquiche/quic/core/quic_types.h"
#include "gquiche/quic/platform/api/quic_containers.h"
#include "gquiche/quic/platform/api/quic_export.h"
#include "gquiche/quic/platform/api/quic_mem_slice.h"

namespace quic {

using QuicMessageData = absl::InlinedVector<QuicMemSlice, 1>;

struct QUIC_EXPORT_PRIVATE QuicMessageFrame {
  QuicMessageFrame() = default;
  explicit QuicMessageFrame(QuicMessageId message_id);
  QuicMessageFrame(QuicMessageId message_id, absl::Span<QuicMemSlice> span);
  QuicMessageFrame(QuicMessageId message_id, QuicMemSlice slice);
  QuicMessageFrame(const char* data, QuicPacketLength length);

  QuicMessageFrame(const QuicMessageFrame& other) = delete;
  QuicMessageFrame& operator=(const QuicMessageFrame& other) = delete;

  QuicMessageFrame(QuicMessageFrame&& other) = default;
  QuicMessageFrame& operator=(QuicMessageFrame&& other) = default;

  ~QuicMessageFrame();

  friend QUIC_EXPORT_PRIVATE std::ostream& operator<<(
      std::ostream& os,
      const QuicMessageFrame& s);

  // message_id is only used on the sender side and does not get serialized on
  // wire.
  QuicMessageId message_id = 0;
  // Not owned, only used on read path.
  const char* data = nullptr;
  // Total length of message_data, must be fit into one packet.
  QuicPacketLength message_length = 0;

  // The actual message data which is reference counted, used on write path.
  QuicMessageData message_data;
};

}  // namespace quic

#endif  // QUICHE_QUIC_CORE_FRAMES_QUIC_MESSAGE_FRAME_H_
