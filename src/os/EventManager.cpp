// Kenton's Code Playground -- http://code.google.com/p/kentons-code
// Author: Kenton Varda (temporal@gmail.com)
// Copyright (c) 2010 Google, Inc. and contributors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "EventManager.h"

#include <stdexcept>

#include "OsHandle.h"  // temporary, for toString()

namespace ekam {

EventManager::~EventManager() {}
EventManager::IoWatcher::~IoWatcher() {}
EventManager::FileWatcher::~FileWatcher() {}
RunnableEventManager::~RunnableEventManager() {}

void ProcessExitCode::throwError() {
  if (signaled) {
    throw std::logic_error("Process was signaled: " + toString(exitCodeOrSignal));
  } else {
    throw std::logic_error("Process was not signaled.  Exit code: " + toString(exitCodeOrSignal));
  }
}

}  // namespace ekam
