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

#include <cstdint>

#include "bedrock/common_types.h"
#include "bedrock/world/level/biome/components/biome_component_storage.h"
#include "bedrock/world/level/biome/mob_spawner_data.h"

enum class OceanTempCategory {
    COLD = 0,
    WARM = 1,
};

struct OceanRuinConfiguration {
    OceanTempCategory type;
    float large_probability;
    float cluster_probability;
};

class Biome {
public:
    virtual ~Biome() = 0;

    [[nodiscard]] const std::string &getName() const
    {
        return hash.getString();
    }

    [[nodiscard]] BiomeIdType getId() const
    {
        return id_;
    }

    HashedString hash;                         // +8
    float temperature;                         // +56
    float downfall;                            // +60
    float red_spore_density;                   // +64
    float blue_spore_density;                  // +68
    float ash_density;                         // +72
    float white_ash_density;                   // +76
    float snow_accumulation;                   // +80
    float foliage_snow;                        // +84
    float min_snow_level;                      // +88
    float max_snow_level;                      // +92
    float depth;                               // +96
    float scale;                               // +100
    int map_water_color;                       // +104
    float water_transparency;                  // +108
    bool rain;                                 // +112
    OceanRuinConfiguration ocean_ruin_config;  // +116

protected:
    MobList mobs_;             // +128
    MobCategoryMap mobs_map_;  // +152
    struct CachedClientComponentData {
        bool has_noise_based_color_palette;
        bool is_roofed_forest;
    };
    static_assert(sizeof(CachedClientComponentData) == 2);
    CachedClientComponentData cached_client_component_data_;  // +344

private:
    BiomeIdType id_;                                 // +346
    BiomeComponentStorage biome_component_storage_;  // +352
};
