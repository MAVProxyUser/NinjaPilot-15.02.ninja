// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2009-2010 Gael Guennebaud <gael.guennebaud@inria.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_PRODUCTBASE_H
#define EIGEN_PRODUCTBASE_H

namespace Eigen { 

/** \class ProductBase
  * \ingroup Core_Module
  *
  * Compatibility class for older Eigen versions.
  * ProductBase functionality has been integrated into Product in Eigen 3.3+
  */

namespace internal {
template<typename Derived, typename _Lhs, typename _Rhs>
struct traits<ProductBase<Derived,_Lhs,_Rhs> >
{
  typedef MatrixXpr XprKind;
  typedef typename remove_all<_Lhs>::type Lhs;
  typedef typename remove_all<_Rhs>::type Rhs;
  typedef typename scalar_product_traits<typename Lhs::Scalar, typename Rhs::Scalar>::ReturnType Scalar;
  typedef typename promote_storage_type<typename traits<Lhs>::StorageKind,
                                           typename traits<Rhs>::StorageKind>::ret StorageKind;
  typedef typename promote_index_type<typename traits<Lhs>::StorageIndex,
                                         typename traits<Rhs>::StorageIndex>::type StorageIndex;
  
  enum {
    RowsAtCompileTime = traits<Lhs>::RowsAtCompileTime,
    ColsAtCompileTime = traits<Rhs>::ColsAtCompileTime,
    MaxRowsAtCompileTime = traits<Lhs>::MaxRowsAtCompileTime,
    MaxColsAtCompileTime = traits<Rhs>::MaxColsAtCompileTime,
    
    Flags = (MaxRowsAtCompileTime==1 ? RowMajorBit : 0)
          | EvalBeforeNestingBit
          | EvalBeforeAssigningBit
          | NestByRefBit,
    
    CoeffReadCost = 0
  };
};
}

template<typename Derived, typename Lhs, typename Rhs>
class ProductBase : public MatrixBase<Derived>
{
  public:
    typedef MatrixBase<Derived> Base;
    EIGEN_DENSE_PUBLIC_INTERFACE(Derived)
    
    typedef typename Base::PlainObject PlainObject;
    
    ProductBase(const Lhs& lhs, const Rhs& rhs) : m_lhs(lhs), m_rhs(rhs)
    {
      eigen_assert(lhs.cols() == rhs.rows());
    }

    inline Index rows() const { return m_lhs.rows(); }
    inline Index cols() const { return m_rhs.cols(); }

    template<typename Dest> void evalTo(Dest& dst) const
    {
      dst.noalias() = m_lhs * m_rhs;
    }

    template<typename Dest> void addTo(Dest& dst) const
    {
      dst.noalias() += m_lhs * m_rhs;
    }

    template<typename Dest> void subTo(Dest& dst) const
    {
      dst.noalias() -= m_lhs * m_rhs;
    }

    template<typename Dest> void scaleAndAddTo(Dest& dst, const Scalar& alpha) const
    {
      dst.noalias() += alpha * m_lhs * m_rhs;
    }

    const Lhs& lhs() const { return m_lhs; }
    const Rhs& rhs() const { return m_rhs; }

  protected:
    typename internal::add_const_on_value_type_if_arithmetic<typename internal::remove_all<Lhs>::type>::type m_lhs;
    typename internal::add_const_on_value_type_if_arithmetic<typename internal::remove_all<Rhs>::type>::type m_rhs;
};

} // end namespace Eigen

#endif // EIGEN_PRODUCTBASE_H