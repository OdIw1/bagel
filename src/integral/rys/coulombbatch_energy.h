//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: coulombbatch_energy.h
// Copyright (C) 2009 Quantum Simulation Technologies, Inc.
//
// Author: Toru Shiozaki <shiozaki@qsimulate.com>
// Maintainer: QSimulate
//
// This file is part of the BAGEL package.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef __SRC_INTEGRAL_RYS_COULOMBBATCH_ENERGY_H
#define __SRC_INTEGRAL_RYS_COULOMBBATCH_ENERGY_H

#include <src/integral/rys/coulombbatch_base.h>

namespace bagel {

class CoulombBatch_energy : public CoulombBatch_Base<double> {

  protected:

    void root_weight(const int ps) override;
    virtual double scale_root(const double root, const double p, const double zeta) { return root; }
    virtual double scale_weight(const double weight) { return weight; }
    std::vector<int> indexecp_;
    int max_rterms_;

  public:

    CoulombBatch_energy(const std::array<std::shared_ptr<const Shell>,2>& _info, std::shared_ptr<const Molecule> mol, std::shared_ptr<StackMem> stack = nullptr)
      :  CoulombBatch_Base<double>(_info, mol, 0, 0, stack) {
    }

     ~CoulombBatch_energy() {}

    void compute() override;

    constexpr static int Nblocks() { return 1; }

};

}

#endif
