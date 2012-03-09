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

#ifndef EKAM_PROTODASHBOARD_H_
#define EKAM_PROTODASHBOARD_H_

#include <queue>
#include <string>

#include "Dashboard.h"
#include "os/ByteStream.h"
#include "os/EventManager.h"

namespace google {
  namespace protobuf {
    class MessageLite;
  }
}

namespace ekam {

class ProtoDashboard : public Dashboard {
public:
  ProtoDashboard(EventManager* eventManager, OwnedPtr<ByteStream> stream);
  ~ProtoDashboard();

  Promise<void> onDisconnect();

  // implements Dashboard ----------------------------------------------------------------
  OwnedPtr<Task> beginTask(const std::string& verb, const std::string& noun, Silence silence);

private:
  class TaskImpl;

  class WriteBuffer {
  public:
    WriteBuffer(EventManager* eventManager, OwnedPtr<ByteStream> stream);
    ~WriteBuffer();

    void write(const google::protobuf::MessageLite& data);
    Promise<void> onDisconnect();

  private:
    EventManager* eventManager;
    OwnedPtr<ByteStream> stream;
    OwnedPtr<EventManager::IoWatcher> ioWatcher;
    std::queue<std::string> messages;
    std::string::size_type offset;
    Promise<void> waitWritablePromise;

    class DisconnectFulfiller : public PromiseFulfiller<void> {
    public:
      DisconnectFulfiller(Callback* callback, WriteBuffer* writeBuffer);
      ~DisconnectFulfiller();

      void disconnected() { callback->fulfill(); }

    private:
      Callback* callback;
      WriteBuffer* writeBuffer;
    };
    DisconnectFulfiller* disconnectFulfiller;

    void ready();
  };

  int idCounter;
  WriteBuffer writeBuffer;
};

}  // namespace ekam

#endif  // EKAM_PROTODASHBOARD_H_
