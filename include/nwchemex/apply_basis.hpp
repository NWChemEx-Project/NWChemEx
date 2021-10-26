#include <chemcache/chemcache.hpp>
#include <libchemist/libchemist.hpp>

namespace nwx {

/**
 * @brief Convenience function for applying a basis set to a molecule
 *
 * @param[in] name The name of the basis set to apply
 * @param[in] mol The molecule instance to apply the basis set to.
 * @param[in] man The BasisSetManager instance to read the basis set from.
 *                Defaults to a default constructed variant.
 * @return The basis set resulting from applying it to @p mol.
 * @throw std::bad_alloc if there is insufficient memory to create the basis
 *                       set. Strong throw guarantee.
 */
inline auto apply_basis(
  const std::string& name, const libchemist::Molecule& mol,
  const libchemist::BasisSetManager& man = chemcache::nwx_basis_set_manager()) {
    libchemist::AOBasisSet<double> aos;

    for(const auto& ai : mol) {
        auto ci = man.get_basis(name, ai.Z());
        for(auto i : {0, 1, 2}) ci.coord(i) = ai.coords()[i];
        aos.add_center(ci);
    }

    return libchemist::orbital_space::AOSpaceD(aos);
}

} // namespace nwx
