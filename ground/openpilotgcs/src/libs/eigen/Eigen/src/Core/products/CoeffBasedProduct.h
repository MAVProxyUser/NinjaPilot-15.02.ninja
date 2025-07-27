// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_COEFFBASEDPRODUCT_H
#define EIGEN_COEFFBASEDPRODUCT_H

namespace Eigen { 

namespace internal {

// CoeffBasedProduct was removed in Eigen 3.3+
// Its functionality has been integrated into the main Product classes
// This provides backward compatibility

template<typename Lhs, typename Rhs, int Mode>
struct CoeffBasedProduct
{
  typedef typename scalar_product_traits<typename Lhs::Scalar, typename Rhs::Scalar>::ReturnType Scalar;
  
  enum {
    Unroll = CoeffBasedProductMode
  };
  
  template<typename Dest>
  static void run(Dest& dst, const Lhs& lhs, const Rhs& rhs, const Scalar& alpha)
  {
    // Use modern Eigen product evaluation
    if(alpha == Scalar(1))
      dst.noalias() = lhs * rhs;
    else
      dst.noalias() = alpha * lhs * rhs;
  }
  
  template<typename Dest>
  static void addTo(Dest& dst, const Lhs& lhs, const Rhs& rhs, const Scalar& alpha)
  {
    if(alpha == Scalar(1))
      dst.noalias() += lhs * rhs;
    else
      dst.noalias() += alpha * lhs * rhs;
  }
};

} // end namespace internal

} // end namespace Eigen

#endif // EIGEN_COEFFBASEDPRODUCT_H