/*
 * Copyright 2022 NWChemEx-Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <pluginplay/pluginplay.hpp>

namespace nwchemex {

DECLARE_MODULE(ReferenceEnergyDriver);
DECLARE_MODULE(ReferenceEnergyDensityDriver);
DECLARE_MODULE(CorrelatedEnergyDriver);
DECLARE_MODULE(CorrelationEnergyDriver);

namespace drivers {

inline void load_modules(pluginplay::ModuleManager& mm) {
    mm.add_module<ReferenceEnergyDriver>("SCF Energy");
    mm.add_module<ReferenceEnergyDensityDriver>("SCF Energy From Density");
    mm.add_module<CorrelatedEnergyDriver>("MP2 Energy");
    mm.add_module<CorrelationEnergyDriver>("MP2 Correlation Energy");
}

} // namespace drivers

} // namespace nwchemex
