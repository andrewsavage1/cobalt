// Copyright 2025 The Cobalt Authors. All Rights Reserved.
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

#include "third_party/blink/renderer/core/cobalt/memory_info/memory_info_extensions.h"

#include "media/base/decoder_buffer.h"
#include "third_party/blink/public/platform/platform.h"

#if !BUILDFLAG(USE_STARBOARD_MEDIA)
#error "This file only works with Starboard media"
#endif  // !BUILDFLAG(USE_STARBOARD_MEDIA)

namespace blink {

uint64_t MemoryInfoExtensions::getMediaSourceMaximumMemoryCapacity(
    MemoryInfo&) {
  return Platform::Current()->GetMediaSourceMaximumMemoryCapacity();
}

uint64_t MemoryInfoExtensions::getMediaSourceCurrentMemoryCapacity(
    MemoryInfo&) {
  return Platform::Current()->GetMediaSourceCurrentMemoryCapacity();
}

uint64_t MemoryInfoExtensions::getMediaSourceTotalAllocatedMemory(MemoryInfo&) {
  return Platform::Current()->GetMediaSourceTotalAllocatedMemory();
}

}  //  namespace blink
