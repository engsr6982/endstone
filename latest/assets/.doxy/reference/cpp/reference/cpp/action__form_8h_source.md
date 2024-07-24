

# File action\_form.h

[**File List**](files.md) **>** [**endstone**](dir_6cf277b678674f97c7a2b6b3b2447b33.md) **>** [**form**](dir_0fd3b458603af3963ebb9c312a9238ec.md) **>** [**action\_form.h**](action__form_8h.md)

[Go to the documentation of this file](action__form_8h.md)


```C++
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

#include <utility>

#include "endstone/form/controls/button.h"
#include "endstone/form/form.h"

namespace endstone {

class ActionForm : public Form<ActionForm> {
public:
    [[nodiscard]] Message getContent() const
    {
        return content_;
    }

    ActionForm &setContent(Message text)
    {
        content_ = std::move(text);
        return *this;
    }

    ActionForm &addButton(const Message &text, const std::optional<std::string> &icon = std::nullopt)
    {
        buttons_.emplace_back(text, icon);
        return *this;
    }

    [[nodiscard]] const std::vector<Button> &getButtons() const
    {
        return buttons_;
    }

    ActionForm &setButtons(const std::vector<Button> &buttons)
    {
        buttons_ = buttons;
        return *this;
    }

private:
    Message content_;
    std::vector<Button> buttons_;
};

}  // namespace endstone
```

