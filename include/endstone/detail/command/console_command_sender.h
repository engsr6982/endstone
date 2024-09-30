// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
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

#pragma once

#include "endstone/command/console_command_sender.h"
#include "endstone/detail/command/server_command_sender.h"

namespace endstone::detail {

class EndstoneConsoleCommandSender : public ServerCommandSender, public ConsoleCommandSender {
public:
    [[nodiscard]] ConsoleCommandSender *asConsole() const override;
    void sendMessage(const Message &message) const override;
    void sendErrorMessage(const Message &message) const override;
    [[nodiscard]] Server &getServer() const override;
    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] bool isOp() const override;
    void setOp(bool value) override;
    [[nodiscard]] bool isPermissionSet(std::string name) const override;
    [[nodiscard]] bool isPermissionSet(const Permission &perm) const override;
    [[nodiscard]] bool hasPermission(std::string name) const override;
    [[nodiscard]] bool hasPermission(const Permission &perm) const override;
    Result<PermissionAttachment *> addAttachment(Plugin &plugin, const std::string &name, bool value) override;
    Result<PermissionAttachment *> addAttachment(Plugin &plugin) override;
    Result<void> removeAttachment(PermissionAttachment &attachment) override;
    void recalculatePermissions() override;
    [[nodiscard]] std::unordered_set<PermissionAttachmentInfo *> getEffectivePermissions() const override;

    static std::shared_ptr<EndstoneConsoleCommandSender> create();
};

}  // namespace endstone::detail
