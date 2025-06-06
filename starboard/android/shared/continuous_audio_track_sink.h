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

#ifndef STARBOARD_ANDROID_SHARED_CONTINUOUS_AUDIO_TRACK_SINK_H_
#define STARBOARD_ANDROID_SHARED_CONTINUOUS_AUDIO_TRACK_SINK_H_

#include <pthread.h>

#include <atomic>
#include <functional>
#include <string>

#include "starboard/android/shared/audio_track_bridge.h"
#include "starboard/android/shared/jni_env_ext.h"
#include "starboard/android/shared/jni_utils.h"
#include "starboard/audio_sink.h"
#include "starboard/common/log.h"
#include "starboard/common/mutex.h"
#include "starboard/configuration.h"
#include "starboard/shared/internal_only.h"
#include "starboard/shared/starboard/audio_sink/audio_sink_internal.h"

namespace starboard::android::shared {

class ContinuousAudioTrackSink
    : public ::starboard::shared::starboard::audio_sink::SbAudioSinkImpl {
 public:
  ContinuousAudioTrackSink(
      Type* type,
      int channels,
      int sampling_frequency_hz,
      SbMediaAudioSampleType sample_type,
      SbAudioSinkFrameBuffers frame_buffers,
      int frames_per_channel,
      int preferred_buffer_size,
      SbAudioSinkUpdateSourceStatusFunc update_source_status_func,
      ConsumeFramesFunc consume_frames_func,
      SbAudioSinkPrivate::ErrorFunc error_func,
      int64_t start_media_time,
      bool is_web_audio,
      void* context);
  ~ContinuousAudioTrackSink() override;

  bool IsAudioTrackValid() const { return bridge_.is_valid(); }
  bool IsType(Type* type) override { return type_ == type; }
  void SetPlaybackRate(double playback_rate) override;

  void SetVolume(double volume) override;
  int GetUnderrunCount();
  int GetStartThresholdInFrames();

 private:
  static void* ThreadEntryPoint(void* context);
  void AudioThreadFunc();

  int WriteData(JniEnvExt* env, const void* buffer, int size);

  void ReportError(bool capability_changed, const std::string& error_message);

  int64_t GetFramesDurationUs(int frames) const;

  Type* const type_;
  const int channels_;
  const int sampling_frequency_hz_;
  const SbMediaAudioSampleType sample_type_;
  void* frame_buffer_;
  const int frames_per_channel_;
  const SbAudioSinkUpdateSourceStatusFunc update_source_status_func_;
  const ConsumeFramesFunc consume_frames_func_;
  const SbAudioSinkPrivate::ErrorFunc error_func_;
  const int64_t start_time_;  // microseconds
  void* const context_;

  AudioTrackBridge bridge_;

  volatile bool quit_ = false;
  pthread_t audio_out_thread_ = 0;

  Mutex mutex_;
  double playback_rate_ = 1.0;
};

}  // namespace starboard::android::shared

#endif  // STARBOARD_ANDROID_SHARED_CONTINUOUS_AUDIO_TRACK_SINK_H_
