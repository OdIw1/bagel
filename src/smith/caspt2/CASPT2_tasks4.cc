//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: CASPT2_tasks4.cc
// Copyright (C) 2014 Quantum Simulation Technologies, Inc.
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

#include <bagel_config.h>
#ifdef COMPILE_SMITH

#include <src/smith/caspt2/CASPT2_tasks4.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;
using namespace bagel::SMITH::CASPT2;

void Task150::Task_local::compute() {
  const Index x3 = b(0);
  const Index a1 = b(1);
  // tensor label: I172
  std::unique_ptr<double[]> odata(new double[out()->get_size(x3, a1)]);
  std::fill_n(odata.get(), out()->get_size(x3, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x3, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, a1), 0.0);
  for (auto& a3 : *range_[2]) {
    for (auto& c2 : *range_[0]) {
      // tensor label: f1
      std::unique_ptr<double[]> i0data = in(0)->get_block(a3, c2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(a3, c2)]);
      sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, a3.size(), c2.size());
      // tensor label: I173
      std::unique_ptr<double[]> i1data = in(1)->get_block(x3, a3, c2, a1);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, a3, c2, a1)]);
      sort_indices<1,2,0,3,0,1,1,1>(i1data, i1data_sorted, x3.size(), a3.size(), c2.size(), a1.size());
      dgemm_("T", "N", 1, x3.size()*a1.size(), a3.size()*c2.size(),
             1.0, i0data_sorted, a3.size()*c2.size(), i1data_sorted, a3.size()*c2.size(),
             1.0, odata_sorted, 1);
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x3.size(), a1.size());
  out()->add_block(odata, x3, a1);
}

void Task151::Task_local::compute() {
  const Index x3 = b(0);
  const Index a3 = b(1);
  const Index c2 = b(2);
  const Index a1 = b(3);
  // tensor label: I173
  std::unique_ptr<double[]> odata(new double[out()->get_size(x3, a3, c2, a1)]);
  std::fill_n(odata.get(), out()->get_size(x3, a3, c2, a1), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a3, c2, a1);
    sort_indices<0,1,2,3,1,1,-1,1>(i0data, odata, x3.size(), a3.size(), c2.size(), a1.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(x3, a1, c2, a3);
    sort_indices<0,3,2,1,1,1,2,1>(i1data, odata, x3.size(), a1.size(), c2.size(), a3.size());
  }
  out()->add_block(odata, x3, a3, c2, a1);
}

void Task152::Task_local::compute() {
  const Index a1 = b(0);
  const Index x0 = b(1);
  const Index x2 = b(2);
  const Index x1 = b(3);
  // tensor label: I160
  std::unique_ptr<double[]> odata(new double[out()->get_size(a1, x0, x2, x1)]);
  std::fill_n(odata.get(), out()->get_size(a1, x0, x2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a1, x0, x2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a1, x0, x2, x1), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: Gamma59
        std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x0, x4, x3, x2, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, x0, x4, x3, x2, x1)]);
        sort_indices<0,2,3,1,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x0.size(), x4.size(), x3.size(), x2.size(), x1.size());
        // tensor label: I178
        std::unique_ptr<double[]> i1data = in(1)->get_block(x5, a1, x4, x3);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x5, a1, x4, x3)]);
        sort_indices<0,2,3,1,0,1,1,1>(i1data, i1data_sorted, x5.size(), a1.size(), x4.size(), x3.size());
        dgemm_("T", "N", x0.size()*x2.size()*x1.size(), a1.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, x0.size()*x2.size()*x1.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x0.size(), x2.size(), x1.size(), a1.size());
  out()->add_block(odata, a1, x0, x2, x1);
}

void Task153::Task_local::compute() {
  const Index x5 = b(0);
  const Index a1 = b(1);
  const Index x4 = b(2);
  const Index x3 = b(3);
  // tensor label: I178
  std::unique_ptr<double[]> odata(new double[out()->get_size(x5, a1, x4, x3)]);
  std::fill_n(odata.get(), out()->get_size(x5, a1, x4, x3), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x5, a1, x4, x3);
    dscal_(x5.size()*a1.size()*x4.size()*x3.size(), e0_, i0data.get(), 1);
    sort_indices<0,1,2,3,1,1,-1,1>(i0data, odata, x5.size(), a1.size(), x4.size(), x3.size());
  }
  out()->add_block(odata, x5, a1, x4, x3);
}

void Task154::Task_local::compute() {
  const Index x5 = b(0);
  const Index a1 = b(1);
  const Index x4 = b(2);
  const Index x3 = b(3);
  // tensor label: I178
  std::unique_ptr<double[]> odata(new double[out()->get_size(x5, a1, x4, x3)]);
  std::fill_n(odata.get(), out()->get_size(x5, a1, x4, x3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x5, a1, x4, x3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x5, a1, x4, x3), 0.0);
  for (auto& a2 : *range_[2]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(a2, x3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(a2, x3)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, a2.size(), x3.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(x5, a1, x4, a2);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x5, a1, x4, a2)]);
    sort_indices<3,0,1,2,0,1,2,1>(i1data, i1data_sorted, x5.size(), a1.size(), x4.size(), a2.size());
    dgemm_("T", "N", x3.size(), x5.size()*a1.size()*x4.size(), a2.size(),
           1.0, i0data_sorted, a2.size(), i1data_sorted, a2.size(),
           1.0, odata_sorted, x3.size());
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, x3.size(), x5.size(), a1.size(), x4.size());
  out()->add_block(odata, x5, a1, x4, x3);
}

void Task155::Task_local::compute() {
  const Index c3 = b(0);
  const Index a4 = b(1);
  const Index c1 = b(2);
  const Index a2 = b(3);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, a4, c1, a2)]);
  std::fill_n(odata.get(), out()->get_size(c3, a4, c1, a2), 0.0);
  {
    // tensor label: I180
    std::unique_ptr<double[]> i0data = in(0)->get_block(a2, c1, a4, c3);
    sort_indices<3,2,1,0,1,1,1,1>(i0data, odata, a2.size(), c1.size(), a4.size(), c3.size());
  }
  {
    // tensor label: I180
    std::unique_ptr<double[]> i0data = in(0)->get_block(a4, c3, a2, c1);
    sort_indices<1,0,3,2,1,1,1,1>(i0data, odata, a4.size(), c3.size(), a2.size(), c1.size());
  }
  out()->add_block(odata, c3, a4, c1, a2);
}

void Task156::Task_local::compute() {
  const Index a2 = b(0);
  const Index c1 = b(1);
  const Index a4 = b(2);
  const Index c3 = b(3);
  // tensor label: I180
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a4, c3, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a4, c3, x1)]);
    sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a4.size(), c3.size(), x1.size());
    // tensor label: I181
    std::unique_ptr<double[]> i1data = in(1)->get_block(a2, x1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a2, x1)]);
    sort_indices<1,0,0,1,1,1>(i1data, i1data_sorted, a2.size(), x1.size());
    dgemm_("T", "N", c1.size()*a4.size()*c3.size(), a2.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, c1.size()*a4.size()*c3.size());
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, c1.size(), a4.size(), c3.size(), a2.size());
  out()->add_block(odata, a2, c1, a4, c3);
}

void Task157::Task_local::compute() {
  const Index a2 = b(0);
  const Index x1 = b(1);
  // tensor label: I181
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, x1)]);
  std::fill_n(odata.get(), out()->get_size(a2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    // tensor label: Gamma16
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size());
    // tensor label: f1
    std::unique_ptr<double[]> i1data = in(1)->get_block(x0, a2);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, a2)]);
    sort_indices<0,1,0,1,-1,1>(i1data, i1data_sorted, x0.size(), a2.size());
    dgemm_("T", "N", x1.size(), a2.size(), x0.size(),
           1.0, i0data_sorted, x0.size(), i1data_sorted, x0.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), a2.size());
  out()->add_block(odata, a2, x1);
}

void Task158::Task_local::compute() {
  const Index a2 = b(0);
  const Index c1 = b(1);
  const Index a4 = b(2);
  const Index c3 = b(3);
  // tensor label: I180
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, x1)]);
    sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x1.size());
    // tensor label: I184
    std::unique_ptr<double[]> i1data = in(1)->get_block(a4, x1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a4, x1)]);
    sort_indices<1,0,0,1,1,1>(i1data, i1data_sorted, a4.size(), x1.size());
    dgemm_("T", "N", c1.size()*a2.size()*c3.size(), a4.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, c1.size()*a2.size()*c3.size());
  }
  sort_indices<1,0,3,2,1,1,1,1>(odata_sorted, odata, c1.size(), a2.size(), c3.size(), a4.size());
  out()->add_block(odata, a2, c1, a4, c3);
}

void Task159::Task_local::compute() {
  const Index a4 = b(0);
  const Index x1 = b(1);
  // tensor label: I184
  std::unique_ptr<double[]> odata(new double[out()->get_size(a4, x1)]);
  std::fill_n(odata.get(), out()->get_size(a4, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a4, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a4, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    // tensor label: Gamma16
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size());
    // tensor label: f1
    std::unique_ptr<double[]> i1data = in(1)->get_block(x0, a4);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, a4)]);
    sort_indices<0,1,0,1,2,1>(i1data, i1data_sorted, x0.size(), a4.size());
    dgemm_("T", "N", x1.size(), a4.size(), x0.size(),
           1.0, i0data_sorted, x0.size(), i1data_sorted, x0.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), a4.size());
  out()->add_block(odata, a4, x1);
}

void Task160::Task_local::compute() {
  const Index a2 = b(0);
  const Index c1 = b(1);
  const Index a4 = b(2);
  const Index c3 = b(3);
  // tensor label: I180
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  // tensor label: f1
  std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a2);
  std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a2)]);
  sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), a2.size());
  // tensor label: I187
  std::unique_ptr<double[]> i1data = in(1)->get_block(a4, c1);
  std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a4, c1)]);
  sort_indices<0,1,0,1,1,1>(i1data, i1data_sorted, a4.size(), c1.size());
  dgemm_("T", "N", c3.size()*a2.size(), a4.size()*c1.size(), 1,
         1.0, i0data_sorted, 1, i1data_sorted, 1,
         1.0, odata_sorted, c3.size()*a2.size());
  sort_indices<1,3,2,0,1,1,1,1>(odata_sorted, odata, c3.size(), a2.size(), a4.size(), c1.size());
  out()->add_block(odata, a2, c1, a4, c3);
}

void Task161::Task_local::compute() {
  const Index a4 = b(0);
  const Index c1 = b(1);
  // tensor label: I187
  std::unique_ptr<double[]> odata(new double[out()->get_size(a4, c1)]);
  std::fill_n(odata.get(), out()->get_size(a4, c1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a4, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a4, c1), 0.0);
  for (auto& x1 : *range_[1]) {
    for (auto& x0 : *range_[1]) {
      // tensor label: Gamma38
      std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0)]);
      sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size());
      // tensor label: I188
      std::unique_ptr<double[]> i1data = in(1)->get_block(x1, a4, c1, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, a4, c1, x0)]);
      sort_indices<0,3,1,2,0,1,1,1>(i1data, i1data_sorted, x1.size(), a4.size(), c1.size(), x0.size());
      dgemm_("T", "N", 1, a4.size()*c1.size(), x1.size()*x0.size(),
             1.0, i0data_sorted, x1.size()*x0.size(), i1data_sorted, x1.size()*x0.size(),
             1.0, odata_sorted, 1);
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, a4.size(), c1.size());
  out()->add_block(odata, a4, c1);
}

void Task162::Task_local::compute() {
  const Index x1 = b(0);
  const Index a4 = b(1);
  const Index c1 = b(2);
  const Index x0 = b(3);
  // tensor label: I188
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, a4, c1, x0)]);
  std::fill_n(odata.get(), out()->get_size(x1, a4, c1, x0), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a4, c1, x0);
    sort_indices<0,1,2,3,1,1,1,1>(i0data, odata, x1.size(), a4.size(), c1.size(), x0.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a4, x1, x0);
    sort_indices<2,1,0,3,1,1,-2,1>(i1data, odata, c1.size(), a4.size(), x1.size(), x0.size());
  }
  out()->add_block(odata, x1, a4, c1, x0);
}

void Task163::Task_local::compute() {
  const Index a2 = b(0);
  const Index c1 = b(1);
  const Index a4 = b(2);
  const Index c3 = b(3);
  // tensor label: I180
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  // tensor label: f1
  std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a4);
  std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a4)]);
  sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), a4.size());
  // tensor label: I190
  std::unique_ptr<double[]> i1data = in(1)->get_block(a2, c1);
  std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a2, c1)]);
  sort_indices<0,1,0,1,1,1>(i1data, i1data_sorted, a2.size(), c1.size());
  dgemm_("T", "N", c3.size()*a4.size(), a2.size()*c1.size(), 1,
         1.0, i0data_sorted, 1, i1data_sorted, 1,
         1.0, odata_sorted, c3.size()*a4.size());
  sort_indices<2,3,1,0,1,1,1,1>(odata_sorted, odata, c3.size(), a4.size(), a2.size(), c1.size());
  out()->add_block(odata, a2, c1, a4, c3);
}

void Task164::Task_local::compute() {
  const Index a2 = b(0);
  const Index c1 = b(1);
  // tensor label: I190
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c1)]);
  std::fill_n(odata.get(), out()->get_size(a2, c1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, c1), 0.0);
  for (auto& x1 : *range_[1]) {
    for (auto& x0 : *range_[1]) {
      // tensor label: Gamma38
      std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0)]);
      sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size());
      // tensor label: I191
      std::unique_ptr<double[]> i1data = in(1)->get_block(x1, a2, c1, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, a2, c1, x0)]);
      sort_indices<0,3,1,2,0,1,1,1>(i1data, i1data_sorted, x1.size(), a2.size(), c1.size(), x0.size());
      dgemm_("T", "N", 1, a2.size()*c1.size(), x1.size()*x0.size(),
             1.0, i0data_sorted, x1.size()*x0.size(), i1data_sorted, x1.size()*x0.size(),
             1.0, odata_sorted, 1);
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size());
  out()->add_block(odata, a2, c1);
}

void Task165::Task_local::compute() {
  const Index x1 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x0 = b(3);
  // tensor label: I191
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, a2, c1, x0)]);
  std::fill_n(odata.get(), out()->get_size(x1, a2, c1, x0), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a2, c1, x0);
    sort_indices<0,1,2,3,1,1,-2,1>(i0data, odata, x1.size(), a2.size(), c1.size(), x0.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a2, x1, x0);
    sort_indices<2,1,0,3,1,1,4,1>(i1data, odata, c1.size(), a2.size(), x1.size(), x0.size());
  }
  out()->add_block(odata, x1, a2, c1, x0);
}

void Task166::Task_local::compute() {
  const Index a2 = b(0);
  const Index c1 = b(1);
  const Index a4 = b(2);
  const Index c3 = b(3);
  // tensor label: I180
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a4, c1, a2);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, a4, c1, a2)]);
    sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x1.size(), a4.size(), c1.size(), a2.size());
    // tensor label: I199
    std::unique_ptr<double[]> i1data = in(1)->get_block(c3, x1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, x1)]);
    sort_indices<1,0,0,1,1,1>(i1data, i1data_sorted, c3.size(), x1.size());
    dgemm_("T", "N", a4.size()*c1.size()*a2.size(), c3.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, a4.size()*c1.size()*a2.size());
  }
  sort_indices<2,1,0,3,1,1,1,1>(odata_sorted, odata, a4.size(), c1.size(), a2.size(), c3.size());
  out()->add_block(odata, a2, c1, a4, c3);
}

void Task167::Task_local::compute() {
  const Index c3 = b(0);
  const Index x1 = b(1);
  // tensor label: I199
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, x1)]);
  std::fill_n(odata.get(), out()->get_size(c3, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    // tensor label: Gamma38
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size());
    // tensor label: f1
    std::unique_ptr<double[]> i1data = in(1)->get_block(c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, x0)]);
    sort_indices<1,0,0,1,-2,1>(i1data, i1data_sorted, c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), c3.size(), x0.size(),
           1.0, i0data_sorted, x0.size(), i1data_sorted, x0.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), c3.size());
  out()->add_block(odata, c3, x1);
}

void Task168::Task_local::compute() {
  const Index a2 = b(0);
  const Index c1 = b(1);
  const Index a4 = b(2);
  const Index c3 = b(3);
  // tensor label: I180
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, c1, a4, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, c1, a4, c3), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a2, c1, a4);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, a2, c1, a4)]);
    sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x1.size(), a2.size(), c1.size(), a4.size());
    // tensor label: I202
    std::unique_ptr<double[]> i1data = in(1)->get_block(c3, x1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, x1)]);
    sort_indices<1,0,0,1,1,1>(i1data, i1data_sorted, c3.size(), x1.size());
    dgemm_("T", "N", a2.size()*c1.size()*a4.size(), c3.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, a2.size()*c1.size()*a4.size());
  }
  sort_indices<0,1,2,3,1,1,1,1>(odata_sorted, odata, a2.size(), c1.size(), a4.size(), c3.size());
  out()->add_block(odata, a2, c1, a4, c3);
}

void Task169::Task_local::compute() {
  const Index c3 = b(0);
  const Index x1 = b(1);
  // tensor label: I202
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, x1)]);
  std::fill_n(odata.get(), out()->get_size(c3, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    // tensor label: Gamma38
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size());
    // tensor label: f1
    std::unique_ptr<double[]> i1data = in(1)->get_block(c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, x0)]);
    sort_indices<1,0,0,1,1,1>(i1data, i1data_sorted, c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), c3.size(), x0.size(),
           1.0, i0data_sorted, x0.size(), i1data_sorted, x0.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), c3.size());
  out()->add_block(odata, c3, x1);
}

void Task170::Task_local::compute() {
  const Index c2 = b(0);
  const Index a3 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(c2, a3, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(c2, a3, x0, a1), 0.0);
  {
    // tensor label: I204
    std::unique_ptr<double[]> i0data = in(0)->get_block(a3, c2, x0, a1);
    sort_indices<1,0,2,3,1,1,1,1>(i0data, odata, a3.size(), c2.size(), x0.size(), a1.size());
  }
  out()->add_block(odata, c2, a3, x0, a1);
}

void Task171::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, a1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), a1.size());
    // tensor label: I205
    std::unique_ptr<double[]> i1data = in(1)->get_block(a3, c2, x1, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a3, c2, x1, x0)]);
    sort_indices<2,0,1,3,0,1,1,1>(i1data, i1data_sorted, a3.size(), c2.size(), x1.size(), x0.size());
    dgemm_("T", "N", a1.size(), a3.size()*c2.size()*x0.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, a1.size());
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, a1.size(), a3.size(), c2.size(), x0.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task172::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I205
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x1, x0)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x1, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma35
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, x1, x0);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x2, x1, x0)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x2.size(), x1.size(), x0.size());
      // tensor label: I206
      std::unique_ptr<double[]> i1data = in(1)->get_block(x3, a3, c2, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, a3, c2, x2)]);
      sort_indices<0,3,1,2,0,1,1,1>(i1data, i1data_sorted, x3.size(), a3.size(), c2.size(), x2.size());
      dgemm_("T", "N", x1.size()*x0.size(), a3.size()*c2.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x1.size()*x0.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), a3.size(), c2.size());
  out()->add_block(odata, a3, c2, x1, x0);
}

void Task173::Task_local::compute() {
  const Index x3 = b(0);
  const Index a3 = b(1);
  const Index c2 = b(2);
  const Index x2 = b(3);
  // tensor label: I206
  std::unique_ptr<double[]> odata(new double[out()->get_size(x3, a3, c2, x2)]);
  std::fill_n(odata.get(), out()->get_size(x3, a3, c2, x2), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a3, c2, x2);
    sort_indices<0,1,2,3,1,1,-1,1>(i0data, odata, x3.size(), a3.size(), c2.size(), x2.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(c2, a3, x3, x2);
    sort_indices<2,1,0,3,1,1,2,1>(i1data, odata, c2.size(), a3.size(), x3.size(), x2.size());
  }
  out()->add_block(odata, x3, a3, c2, x2);
}

void Task174::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, a3)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), a3.size());
    // tensor label: I208
    std::unique_ptr<double[]> i1data = in(1)->get_block(a1, c2, x0, x1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a1, c2, x0, x1)]);
    sort_indices<3,0,1,2,0,1,1,1>(i1data, i1data_sorted, a1.size(), c2.size(), x0.size(), x1.size());
    dgemm_("T", "N", a3.size(), a1.size()*c2.size()*x0.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, a3.size());
  }
  sort_indices<0,2,3,1,1,1,1,1>(odata_sorted, odata, a3.size(), a1.size(), c2.size(), x0.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task175::Task_local::compute() {
  const Index a1 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index x1 = b(3);
  // tensor label: I208
  std::unique_ptr<double[]> odata(new double[out()->get_size(a1, c2, x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(a1, c2, x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a1, c2, x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a1, c2, x0, x1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma32
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x0, x1, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x0, x1, x2)]);
      sort_indices<0,3,1,2,0,1,1,1>(i0data, i0data_sorted, x3.size(), x0.size(), x1.size(), x2.size());
      // tensor label: t2
      std::unique_ptr<double[]> i1data = in(1)->get_block(x3, a1, c2, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, a1, c2, x2)]);
      sort_indices<0,3,1,2,0,1,1,1>(i1data, i1data_sorted, x3.size(), a1.size(), c2.size(), x2.size());
      dgemm_("T", "N", x0.size()*x1.size(), a1.size()*c2.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x0.size()*x1.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), a1.size(), c2.size());
  out()->add_block(odata, a1, c2, x0, x1);
}

void Task176::Task_local::compute() {
  const Index a1 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index x1 = b(3);
  // tensor label: I208
  std::unique_ptr<double[]> odata(new double[out()->get_size(a1, c2, x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(a1, c2, x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a1, c2, x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a1, c2, x0, x1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma35
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, x1, x0);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x2, x1, x0)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x2.size(), x1.size(), x0.size());
      // tensor label: t2
      std::unique_ptr<double[]> i1data = in(1)->get_block(c2, a1, x3, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c2, a1, x3, x2)]);
      sort_indices<2,3,0,1,0,1,-1,1>(i1data, i1data_sorted, c2.size(), a1.size(), x3.size(), x2.size());
      dgemm_("T", "N", x1.size()*x0.size(), c2.size()*a1.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x1.size()*x0.size());
    }
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), c2.size(), a1.size());
  out()->add_block(odata, a1, c2, x0, x1);
}

void Task177::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  // tensor label: f1
  std::unique_ptr<double[]> i0data = in(0)->get_block(c2, a1);
  std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c2, a1)]);
  sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c2.size(), a1.size());
  // tensor label: I217
  std::unique_ptr<double[]> i1data = in(1)->get_block(a3, x0);
  std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a3, x0)]);
  sort_indices<0,1,0,1,1,1>(i1data, i1data_sorted, a3.size(), x0.size());
  dgemm_("T", "N", c2.size()*a1.size(), a3.size()*x0.size(), 1,
         1.0, i0data_sorted, 1, i1data_sorted, 1,
         1.0, odata_sorted, c2.size()*a1.size());
  sort_indices<2,0,3,1,1,1,1,1>(odata_sorted, odata, c2.size(), a1.size(), a3.size(), x0.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task178::Task_local::compute() {
  const Index a3 = b(0);
  const Index x0 = b(1);
  // tensor label: I217
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, x0)]);
  std::fill_n(odata.get(), out()->get_size(a3, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: Gamma60
        std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x0, x2, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x0, x2, x1)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, x3.size(), x0.size(), x2.size(), x1.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(1)->get_block(x3, a3, x2, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, a3, x2, x1)]);
        sort_indices<0,2,3,1,0,1,-1,1>(i1data, i1data_sorted, x3.size(), a3.size(), x2.size(), x1.size());
        dgemm_("T", "N", x0.size(), a3.size(), x3.size()*x2.size()*x1.size(),
               1.0, i0data_sorted, x3.size()*x2.size()*x1.size(), i1data_sorted, x3.size()*x2.size()*x1.size(),
               1.0, odata_sorted, x0.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x0.size(), a3.size());
  out()->add_block(odata, a3, x0);
}

void Task179::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  // tensor label: f1
  std::unique_ptr<double[]> i0data = in(0)->get_block(c2, a3);
  std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c2, a3)]);
  sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c2.size(), a3.size());
  // tensor label: I220
  std::unique_ptr<double[]> i1data = in(1)->get_block(a1, x0);
  std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a1, x0)]);
  sort_indices<0,1,0,1,1,1>(i1data, i1data_sorted, a1.size(), x0.size());
  dgemm_("T", "N", c2.size()*a3.size(), a1.size()*x0.size(), 1,
         1.0, i0data_sorted, 1, i1data_sorted, 1,
         1.0, odata_sorted, c2.size()*a3.size());
  sort_indices<1,0,3,2,1,1,1,1>(odata_sorted, odata, c2.size(), a3.size(), a1.size(), x0.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task180::Task_local::compute() {
  const Index a1 = b(0);
  const Index x0 = b(1);
  // tensor label: I220
  std::unique_ptr<double[]> odata(new double[out()->get_size(a1, x0)]);
  std::fill_n(odata.get(), out()->get_size(a1, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: Gamma60
        std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x0, x2, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x0, x2, x1)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, x3.size(), x0.size(), x2.size(), x1.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(1)->get_block(x3, a1, x2, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, a1, x2, x1)]);
        sort_indices<0,2,3,1,0,1,2,1>(i1data, i1data_sorted, x3.size(), a1.size(), x2.size(), x1.size());
        dgemm_("T", "N", x0.size(), a1.size(), x3.size()*x2.size()*x1.size(),
               1.0, i0data_sorted, x3.size()*x2.size()*x1.size(), i1data_sorted, x3.size()*x2.size()*x1.size(),
               1.0, odata_sorted, x0.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x0.size(), a1.size());
  out()->add_block(odata, a1, x0);
}

void Task181::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  for (auto& c4 : *range_[0]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c2, a3, c4, a1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c2, a3, c4, a1)]);
    sort_indices<2,0,1,3,0,1,1,1>(i0data, i0data_sorted, c2.size(), a3.size(), c4.size(), a1.size());
    // tensor label: I223
    std::unique_ptr<double[]> i1data = in(1)->get_block(c4, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c4, x0)]);
    sort_indices<0,1,0,1,1,1>(i1data, i1data_sorted, c4.size(), x0.size());
    dgemm_("T", "N", c2.size()*a3.size()*a1.size(), x0.size(), c4.size(),
           1.0, i0data_sorted, c4.size(), i1data_sorted, c4.size(),
           1.0, odata_sorted, c2.size()*a3.size()*a1.size());
  }
  sort_indices<1,0,3,2,1,1,1,1>(odata_sorted, odata, c2.size(), a3.size(), a1.size(), x0.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task182::Task_local::compute() {
  const Index c4 = b(0);
  const Index x0 = b(1);
  // tensor label: I223
  std::unique_ptr<double[]> odata(new double[out()->get_size(c4, x0)]);
  std::fill_n(odata.get(), out()->get_size(c4, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c4, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c4, x0), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: Gamma38
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size());
    // tensor label: f1
    std::unique_ptr<double[]> i1data = in(1)->get_block(x1, c4);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, c4)]);
    sort_indices<0,1,0,1,-4,1>(i1data, i1data_sorted, x1.size(), c4.size());
    dgemm_("T", "N", x0.size(), c4.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, x0.size());
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x0.size(), c4.size());
  out()->add_block(odata, c4, x0);
}

void Task183::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  for (auto& c4 : *range_[0]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c2, a1, c4, a3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c2, a1, c4, a3)]);
    sort_indices<2,0,1,3,0,1,1,1>(i0data, i0data_sorted, c2.size(), a1.size(), c4.size(), a3.size());
    // tensor label: I226
    std::unique_ptr<double[]> i1data = in(1)->get_block(c4, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c4, x0)]);
    sort_indices<0,1,0,1,1,1>(i1data, i1data_sorted, c4.size(), x0.size());
    dgemm_("T", "N", c2.size()*a1.size()*a3.size(), x0.size(), c4.size(),
           1.0, i0data_sorted, c4.size(), i1data_sorted, c4.size(),
           1.0, odata_sorted, c2.size()*a1.size()*a3.size());
  }
  sort_indices<2,0,3,1,1,1,1,1>(odata_sorted, odata, c2.size(), a1.size(), a3.size(), x0.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task184::Task_local::compute() {
  const Index c4 = b(0);
  const Index x0 = b(1);
  // tensor label: I226
  std::unique_ptr<double[]> odata(new double[out()->get_size(c4, x0)]);
  std::fill_n(odata.get(), out()->get_size(c4, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c4, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c4, x0), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: Gamma38
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size());
    // tensor label: f1
    std::unique_ptr<double[]> i1data = in(1)->get_block(x1, c4);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, c4)]);
    sort_indices<0,1,0,1,2,1>(i1data, i1data_sorted, x1.size(), c4.size());
    dgemm_("T", "N", x0.size(), c4.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, x0.size());
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x0.size(), c4.size());
  out()->add_block(odata, c4, x0);
}

void Task185::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  for (auto& x3 : *range_[1]) {
    // tensor label: Gamma79
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x0);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x0)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x3.size(), x0.size());
    // tensor label: I229
    std::unique_ptr<double[]> i1data = in(1)->get_block(x3, a3, c2, a1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, a3, c2, a1)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, x3.size(), a3.size(), c2.size(), a1.size());
    dgemm_("T", "N", x0.size(), a3.size()*c2.size()*a1.size(), x3.size(),
           1.0, i0data_sorted, x3.size(), i1data_sorted, x3.size(),
           1.0, odata_sorted, x0.size());
  }
  sort_indices<1,2,0,3,1,1,1,1>(odata_sorted, odata, x0.size(), a3.size(), c2.size(), a1.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task186::Task_local::compute() {
  const Index x3 = b(0);
  const Index a3 = b(1);
  const Index c2 = b(2);
  const Index a1 = b(3);
  // tensor label: I229
  std::unique_ptr<double[]> odata(new double[out()->get_size(x3, a3, c2, a1)]);
  std::fill_n(odata.get(), out()->get_size(x3, a3, c2, a1), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a3, c2, a1);
    sort_indices<0,1,2,3,1,1,-1,1>(i0data, odata, x3.size(), a3.size(), c2.size(), a1.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(x3, a1, c2, a3);
    sort_indices<0,3,2,1,1,1,2,1>(i1data, odata, x3.size(), a1.size(), c2.size(), a3.size());
  }
  out()->add_block(odata, x3, a3, c2, a1);
}

void Task187::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  for (auto& c4 : *range_[0]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c2, c4);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c2, c4)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, c2.size(), c4.size());
    // tensor label: I233
    std::unique_ptr<double[]> i1data = in(1)->get_block(a3, c4, a1, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a3, c4, a1, x0)]);
    sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, a3.size(), c4.size(), a1.size(), x0.size());
    dgemm_("T", "N", c2.size(), a3.size()*a1.size()*x0.size(), c4.size(),
           1.0, i0data_sorted, c4.size(), i1data_sorted, c4.size(),
           1.0, odata_sorted, c2.size());
  }
  sort_indices<1,0,3,2,1,1,1,1>(odata_sorted, odata, c2.size(), a3.size(), a1.size(), x0.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task188::Task_local::compute() {
  const Index a3 = b(0);
  const Index c4 = b(1);
  const Index a1 = b(2);
  const Index x0 = b(3);
  // tensor label: I233
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c4, a1, x0)]);
  std::fill_n(odata.get(), out()->get_size(a3, c4, a1, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c4, a1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c4, a1, x0), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: Gamma38
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size());
    // tensor label: I234
    std::unique_ptr<double[]> i1data = in(1)->get_block(x1, a3, c4, a1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, a3, c4, a1)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, x1.size(), a3.size(), c4.size(), a1.size());
    dgemm_("T", "N", x0.size(), a3.size()*c4.size()*a1.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, x0.size());
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, x0.size(), a3.size(), c4.size(), a1.size());
  out()->add_block(odata, a3, c4, a1, x0);
}

void Task189::Task_local::compute() {
  const Index x1 = b(0);
  const Index a3 = b(1);
  const Index c4 = b(2);
  const Index a1 = b(3);
  // tensor label: I234
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, a3, c4, a1)]);
  std::fill_n(odata.get(), out()->get_size(x1, a3, c4, a1), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a3, c4, a1);
    sort_indices<0,1,2,3,1,1,1,1>(i0data, odata, x1.size(), a3.size(), c4.size(), a1.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(x1, a1, c4, a3);
    sort_indices<0,3,2,1,1,1,-2,1>(i1data, odata, x1.size(), a1.size(), c4.size(), a3.size());
  }
  out()->add_block(odata, x1, a3, c4, a1);
}

void Task190::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  for (auto& a4 : *range_[2]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(a4, a1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(a4, a1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, a4.size(), a1.size());
    // tensor label: I239
    std::unique_ptr<double[]> i1data = in(1)->get_block(a4, c2, a3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a4, c2, a3, x0)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, a4.size(), c2.size(), a3.size(), x0.size());
    dgemm_("T", "N", a1.size(), c2.size()*a3.size()*x0.size(), a4.size(),
           1.0, i0data_sorted, a4.size(), i1data_sorted, a4.size(),
           1.0, odata_sorted, a1.size());
  }
  sort_indices<2,1,3,0,1,1,1,1>(odata_sorted, odata, a1.size(), c2.size(), a3.size(), x0.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task191::Task_local::compute() {
  const Index a4 = b(0);
  const Index c2 = b(1);
  const Index a3 = b(2);
  const Index x0 = b(3);
  // tensor label: I239
  std::unique_ptr<double[]> odata(new double[out()->get_size(a4, c2, a3, x0)]);
  std::fill_n(odata.get(), out()->get_size(a4, c2, a3, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a4, c2, a3, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a4, c2, a3, x0), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: Gamma38
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size());
    // tensor label: I240
    std::unique_ptr<double[]> i1data = in(1)->get_block(x1, a4, c2, a3);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, a4, c2, a3)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, x1.size(), a4.size(), c2.size(), a3.size());
    dgemm_("T", "N", x0.size(), a4.size()*c2.size()*a3.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, x0.size());
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, x0.size(), a4.size(), c2.size(), a3.size());
  out()->add_block(odata, a4, c2, a3, x0);
}

void Task192::Task_local::compute() {
  const Index x1 = b(0);
  const Index a4 = b(1);
  const Index c2 = b(2);
  const Index a3 = b(3);
  // tensor label: I240
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, a4, c2, a3)]);
  std::fill_n(odata.get(), out()->get_size(x1, a4, c2, a3), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a4, c2, a3);
    sort_indices<0,1,2,3,1,1,2,1>(i0data, odata, x1.size(), a4.size(), c2.size(), a3.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(x1, a3, c2, a4);
    sort_indices<0,3,2,1,1,1,-1,1>(i1data, odata, x1.size(), a3.size(), c2.size(), a4.size());
  }
  out()->add_block(odata, x1, a4, c2, a3);
}

void Task193::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  for (auto& a4 : *range_[2]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(a4, a3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(a4, a3)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, a4.size(), a3.size());
    // tensor label: I245
    std::unique_ptr<double[]> i1data = in(1)->get_block(a4, c2, a1, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a4, c2, a1, x0)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, a4.size(), c2.size(), a1.size(), x0.size());
    dgemm_("T", "N", a3.size(), c2.size()*a1.size()*x0.size(), a4.size(),
           1.0, i0data_sorted, a4.size(), i1data_sorted, a4.size(),
           1.0, odata_sorted, a3.size());
  }
  sort_indices<0,1,3,2,1,1,1,1>(odata_sorted, odata, a3.size(), c2.size(), a1.size(), x0.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task194::Task_local::compute() {
  const Index a4 = b(0);
  const Index c2 = b(1);
  const Index a1 = b(2);
  const Index x0 = b(3);
  // tensor label: I245
  std::unique_ptr<double[]> odata(new double[out()->get_size(a4, c2, a1, x0)]);
  std::fill_n(odata.get(), out()->get_size(a4, c2, a1, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a4, c2, a1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a4, c2, a1, x0), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: Gamma38
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size());
    // tensor label: I246
    std::unique_ptr<double[]> i1data = in(1)->get_block(x1, a4, c2, a1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, a4, c2, a1)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, x1.size(), a4.size(), c2.size(), a1.size());
    dgemm_("T", "N", x0.size(), a4.size()*c2.size()*a1.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, x0.size());
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, x0.size(), a4.size(), c2.size(), a1.size());
  out()->add_block(odata, a4, c2, a1, x0);
}

void Task195::Task_local::compute() {
  const Index x1 = b(0);
  const Index a4 = b(1);
  const Index c2 = b(2);
  const Index a1 = b(3);
  // tensor label: I246
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, a4, c2, a1)]);
  std::fill_n(odata.get(), out()->get_size(x1, a4, c2, a1), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a4, c2, a1);
    sort_indices<0,1,2,3,1,1,-1,1>(i0data, odata, x1.size(), a4.size(), c2.size(), a1.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(x1, a1, c2, a4);
    sort_indices<0,3,2,1,1,1,2,1>(i1data, odata, x1.size(), a1.size(), c2.size(), a4.size());
  }
  out()->add_block(odata, x1, a4, c2, a1);
}

void Task196::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c2, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c2, x1)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, c2.size(), x1.size());
    // tensor label: I251
    std::unique_ptr<double[]> i1data = in(1)->get_block(a1, a3, x0, x1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a1, a3, x0, x1)]);
    sort_indices<3,0,1,2,0,1,1,1>(i1data, i1data_sorted, a1.size(), a3.size(), x0.size(), x1.size());
    dgemm_("T", "N", c2.size(), a1.size()*a3.size()*x0.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, c2.size());
  }
  sort_indices<2,0,3,1,1,1,1,1>(odata_sorted, odata, c2.size(), a1.size(), a3.size(), x0.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task197::Task_local::compute() {
  const Index a1 = b(0);
  const Index a3 = b(1);
  const Index x0 = b(2);
  const Index x1 = b(3);
  // tensor label: I251
  std::unique_ptr<double[]> odata(new double[out()->get_size(a1, a3, x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(a1, a3, x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a1, a3, x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a1, a3, x0, x1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma60
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x0, x2, x1);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x0, x2, x1)]);
      sort_indices<0,2,1,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x0.size(), x2.size(), x1.size());
      // tensor label: t2
      std::unique_ptr<double[]> i1data = in(1)->get_block(x3, a1, x2, a3);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, a1, x2, a3)]);
      sort_indices<0,2,1,3,0,1,-2,1>(i1data, i1data_sorted, x3.size(), a1.size(), x2.size(), a3.size());
      dgemm_("T", "N", x0.size()*x1.size(), a1.size()*a3.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x0.size()*x1.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), a1.size(), a3.size());
  out()->add_block(odata, a1, a3, x0, x1);
}

void Task198::Task_local::compute() {
  const Index a3 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index a1 = b(3);
  // tensor label: I204
  std::unique_ptr<double[]> odata(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a3, c2, x0, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a3, c2, x0, a1), 0.0);
  for (auto& x1 : *range_[1]) {
    // tensor label: Gamma38
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size());
    // tensor label: I283
    std::unique_ptr<double[]> i1data = in(1)->get_block(x1, a3, c2, a1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, a3, c2, a1)]);
    sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, x1.size(), a3.size(), c2.size(), a1.size());
    dgemm_("T", "N", x0.size(), a3.size()*c2.size()*a1.size(), x1.size(),
           1.0, i0data_sorted, x1.size(), i1data_sorted, x1.size(),
           1.0, odata_sorted, x0.size());
  }
  sort_indices<1,2,0,3,1,1,1,1>(odata_sorted, odata, x0.size(), a3.size(), c2.size(), a1.size());
  out()->add_block(odata, a3, c2, x0, a1);
}

void Task199::Task_local::compute() {
  const Index x1 = b(0);
  const Index a3 = b(1);
  const Index c2 = b(2);
  const Index a1 = b(3);
  // tensor label: I283
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, a3, c2, a1)]);
  std::fill_n(odata.get(), out()->get_size(x1, a3, c2, a1), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a3, c2, a1);
    dscal_(x1.size()*a3.size()*c2.size()*a1.size(), e0_, i0data.get(), 1);
    sort_indices<0,1,2,3,1,1,1,1>(i0data, odata, x1.size(), a3.size(), c2.size(), a1.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(x1, a1, c2, a3);
    dscal_(x1.size()*a1.size()*c2.size()*a3.size(), e0_, i1data.get(), 1);
    sort_indices<0,3,2,1,1,1,-2,1>(i1data, odata, x1.size(), a1.size(), c2.size(), a3.size());
  }
  out()->add_block(odata, x1, a3, c2, a1);
}

#endif
