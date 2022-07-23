#pragma once
#include <pluginplay/pluginplay.hpp>
#include <simde/simde.hpp>

namespace nwchemex {

/** @brief Convenience function for loading all of NWChemEx's modules into an
 *         existing ModuleManager instance.
 *
 *  @param[in] mm The ModuleManager instance to load the modules into.
 *
 *  @throw std::bad_alloc if there is insufficient memory to create the new
 *                        modules. Weak throw guarantee.
 */
void load_modules(pluginplay::ModuleManager& mm);

} // namespace nwchemex

namespace simde {

DECLARE_PROPERTY_TYPE(TransformedElectronicHamiltonian);
PROPERTY_TYPE_INPUTS(TransformedElectronicHamiltonian) {
    using simde::type::derived_space;
    using simde::type::els_hamiltonian;

    auto rv = pluginplay::declare_input()
                .add_field<const els_hamiltonian&>("Electronic Hamiltonian")
                .add_field<const derived_space&>("Orbital Space");
    return rv;
}

PROPERTY_TYPE_RESULTS(TransformedElectronicHamiltonian) {
    using simde::type::tensor;

    auto rv = pluginplay::declare_result()
                .add_field<tensor>("T")
                .add_field<tensor>("V");
    return rv;
}

DECLARE_MODULE(SecondQuantizedHamiltonian);

DECLARE_PROPERTY_TYPE(QCSchemaFactory);
PROPERTY_TYPE_INPUTS(QCSchemaFactory) {
    using simde::type::canonical_reference;
    using simde::type::els_hamiltonian;
    auto rv = pluginplay::declare_input()
                .add_field<const els_hamiltonian&>("Electronic Hamiltonian")
                .add_field<const canonical_reference&>("Reference Wavefunction");
    return rv;
}

PROPERTY_TYPE_RESULTS(QCSchemaFactory) {
    return pluginplay::declare_result();
}

DECLARE_MODULE(HDF5QCSchema);

}
