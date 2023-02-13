#pragma once
#include <nwchemex/nwchemex.hpp>

inline simde::type::molecule benzene() {
    simde::type::molecule benzene;

    using atom_t   = simde::type::atom;
    using name_t   = typename atom_t::name_type;
    using number_t = typename atom_t::size_type;
    using coord_t  = typename atom_t::coord_type;

    benzene.push_back(atom_t{name_t("H"), number_t(1),
                             coord_t{0.00000000, 2.47523400, 0.00000000}});
    benzene.push_back(atom_t{name_t("C"), number_t(6),
                             coord_t{0.00000000, 1.38980400, 0.00000000}});
    benzene.push_back(atom_t{name_t("H"), number_t(1),
                             coord_t{2.14361600, 1.23761700, 0.00000000}});
    benzene.push_back(atom_t{name_t("C"), number_t(6),
                             coord_t{1.20360500, 0.69490200, 0.00000000}});
    benzene.push_back(atom_t{name_t("H"), number_t(1),
                             coord_t{2.14361600, -1.23761700, 0.00000000}});
    benzene.push_back(atom_t{name_t("C"), number_t(6),
                             coord_t{1.20360500, -0.69490200, 0.00000000}});
    benzene.push_back(atom_t{name_t("H"), number_t(1),
                             coord_t{-2.14361600, 1.23761700, 0.00000000}});
    benzene.push_back(atom_t{name_t("C"), number_t(6),
                             coord_t{-1.20360500, 0.69490200, 0.00000000}});
    benzene.push_back(atom_t{name_t("H"), number_t(1),
                             coord_t{-2.14361600, -1.23761700, 0.00000000}});
    benzene.push_back(atom_t{name_t("C"), number_t(6),
                             coord_t{-1.20360500, -0.69490200, 0.00000000}});
    benzene.push_back(atom_t{name_t("H"), number_t(1),
                             coord_t{0.00000000, -2.47523400, 0.00000000}});
    benzene.push_back(atom_t{name_t("C"), number_t(6),
                             coord_t{0.00000000, -1.38980400, 0.00000000}});

    return benzene;
}

inline simde::type::molecule from_name(std::string input) {
    if(input == "benzene") return benzene();
    return simde::type::molecule{};
}