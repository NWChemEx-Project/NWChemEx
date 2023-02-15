#include "geometries.hpp"
#include <integrals/property_types/integral_shape.hpp>
#include <nwchemex/nwchemex.hpp>
#include <tiledarray.h>

int main(int argc, char* argv[]) {
    auto& world = TA::initialize(argc, argv);

    /// Arg parsing
    std::vector<std::string> args(argv + 1, argv + argc);
    const auto mol_name       = args.at(0);
    const auto basis_name     = args.at(1);
    const auto aux_basis_name = args.at(1);

    /// NWX setup
    pluginplay::ModuleManager mm;
    nwchemex::load_modules(mm);

    /// Hacky way to check if we have GPU modules
    bool have_gpu_modules = mm.count("DFJ_JEngine");

    /// Job specifications
    auto mol = from_name(mol_name);
    auto aos = nwchemex::apply_basis(basis_name, mol);
    auto aux = nwchemex::apply_basis(aux_basis_name, mol);
    auto cs  = simde::type::chemical_system(mol);

    // Set inputs
    mm.change_input("Overlap CS", "Screening Threshold", 1e-12);
    mm.change_input("Kinetic CS", "Screening Threshold", 1e-12);
    mm.change_input("Nuclear CS", "Screening Threshold", 1e-12);
    mm.change_input("DFJK", "Fitting Basis", aux);
    if(have_gpu_modules) {
        mm.change_input("DFJ_JEngine", "Fitting Basis", aux);
        mm.change_input("GauXC Quadrature Batches", "On GPU", true);
        mm.change_input("snLinK", "On GPU", true);
        mm.change_input("XC", "On GPU", true);
    }

    /// Setup modules
    /// Will need to handle shape lambdas here
    mm.change_submod("CoreH", "Electron-Nuclear Attraction", "Nuclear CS");
    mm.change_submod("CoreH", "Kinetic Energy", "Kinetic CS");
    mm.change_submod("CoreGuess", "Overlap", "Overlap CS");
    mm.change_submod("SCF Step", "Overlap", "Overlap CS");
    mm.change_submod("SCF Step", "Overlap", "Overlap CS");
    mm.change_submod("Fock Matrix", "J Builder", "DFJK");
    mm.change_submod("Fock Matrix", "K Builder", "DFJK");
    if(have_gpu_modules) {
        mm.change_submod("Fock Matrix", "J Builder", "DFJ_JEngine");
        mm.change_submod("Fock Matrix", "K Builder", "snLinK");
    }

    // Run and print profile info
    auto [E] = mm.at("SCF Energy").run_as<simde::AOEnergy>(aos, cs);
    world.gop.fence();
    std::cout << "SCF Energy = " << E << std::endl;
    std::cout << "SCF Profile:" << std::endl;
    std::cout << mm.at("SCF Energy").profile_info() << std::endl;

    TA::finalize();
    return 0;
}