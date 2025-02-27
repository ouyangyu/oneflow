/*
Copyright 2020 The OneFlow Authors. All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef ONEFLOW_CORE_COMMON_BUFFER_MANAGER_H_
#define ONEFLOW_CORE_COMMON_BUFFER_MANAGER_H_

#include "oneflow/core/common/util.h"
#include "oneflow/core/common/buffer.h"

namespace oneflow {

template<typename T>
class BufferMgr final {
 public:
  OF_DISALLOW_COPY_AND_MOVE(BufferMgr);
  ~BufferMgr() = default;

  void NewBuffer(const std::string& buffer_name, size_t buffer_size) {
    CHECK(name2buffer_.emplace(buffer_name, std::make_unique<Buffer<T>>(buffer_size)).second);
  }
  Buffer<T>* Get(const std::string& buffer_name) const {
    const auto& iter = name2buffer_.find(buffer_name);
    CHECK(iter != name2buffer_.end()) << "buffer_name: " << buffer_name;
    return iter->second.get();
  }

 private:
  friend class Singleton<BufferMgr>;
  BufferMgr() = default;

  HashMap<std::string, std::unique_ptr<Buffer<T>>> name2buffer_;
};

static const std::string kBufferNameGlobalWaitJobId = "GlobalWaitJobId";

inline std::string GetCallbackNotifierBufferName(const std::string& job_name) {
  static const std::string prefix = "CallbackNotifier-";
  return prefix + job_name;
}

inline std::string GetInputCriticalSectionWaitBufferName(const std::string& job_name) {
  static const std::string prefix = "InputCriticalSectionWait-";
  return prefix + job_name;
}

inline std::string GetInputCriticalSectionCallbackBufferName(const std::string& job_name) {
  static const std::string prefix = "InputCriticalSectionCallback-";
  return prefix + job_name;
}

inline std::string GetOutputCriticalSectionWaitBufferName(const std::string& job_name) {
  static const std::string prefix = "OutputCriticalSectionWait-";
  return prefix + job_name;
}

inline std::string GetOutputCriticalSectionCallbackBufferName(const std::string& job_name) {
  static const std::string prefix = "OutputCriticalSectionCallback-";
  return prefix + job_name;
}

inline std::string GetInputBufferName(const std::string& job_name, const std::string& op_name) {
  static const std::string prefix = "Input-";
  return prefix + job_name + "-" + op_name;
}

inline std::string GetOutputBufferName(const std::string& job_name, const std::string& op_name) {
  static const std::string prefix = "Output-";
  return prefix + job_name + "-" + op_name;
}

inline std::string GetSourceTickBufferName(const std::string& job_name) {
  static const std::string prefix = "SourceTick-";
  return prefix + job_name;
}

}  // namespace oneflow

#endif  // ONEFLOW_CORE_COMMON_BUFFER_MANAGER_H_
