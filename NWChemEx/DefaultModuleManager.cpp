#include <NWChemEx/DefaultModuleManager.hpp>

#include <SCF/SCF_MM.hpp>

namespace NWChemEx {
  SDE::ModuleManager default_mm(){
    auto mm = SDE::ModuleManager();
    scf::load_modules(mm);
    return mm;
  }
}
