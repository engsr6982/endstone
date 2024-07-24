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

#include <optional>
#include <string>
#include <utility>

#include "endstone/message.h"

namespace endstone {

/**
 * @brief Represents a button with text and an optional icon.
 */
class Button {
public:
    Button() = default;
    explicit Button(Message text, std::optional<std::string> icon = std::nullopt)
        : text_(std::move(text)), icon_(std::move(icon))
    {
    }

    /**
     * @brief Gets the text of the button.
     *
     * @return The text.
     */
    [[nodiscard]] Message getText() const
    {
        return text_;
    }

    /**
     * @brief Sets the text of the button.
     *
     * @param text The new text for the button.
     */
    void setText(Message text)
    {
        text_ = std::move(text);
    }

    /**
     * @brief Get the icon of the button.
     *
     * @return The path or URL to the icon file
     */
    [[nodiscard]] std::optional<std::string> getIcon() const
    {
        return icon_;
    }

    /**
     * @brief Sets the icon for the button.
     *
     * @param icon The path or URL to the icon file.
     */
    void setIcon(std::string icon)
    {
        icon_ = std::move(icon);
    }

private:
    Message text_;
    std::optional<std::string> icon_;
};

}  // namespace endstone