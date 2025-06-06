// Copyright 2017 The Cobalt Authors. All Rights Reserved.
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

#include "starboard/shared/starboard/media/media_support_internal.h"

#include "starboard/media.h"

namespace starboard::shared::starboard::media {

bool MediaIsVideoSupported(SbMediaVideoCodec video_codec,
                           const MimeType* mime_type,
                           int profile,
                           int level,
                           int bit_depth,
                           SbMediaPrimaryId primary_id,
                           SbMediaTransferId transfer_id,
                           SbMediaMatrixId matrix_id,
                           int frame_width,
                           int frame_height,
                           int64_t bitrate,
                           int fps,
                           bool decode_to_texture_required) {
  return false;
}

}  // namespace starboard::shared::starboard::media
