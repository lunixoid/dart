/*
 * Copyright (c) 2016, Graphics Lab, Georgia Tech Research Corporation
 * Copyright (c) 2016, Humanoid Lab, Georgia Tech Research Corporation
 * Copyright (c) 2016, Personal Robotics Lab, Carnegie Mellon University
 * All rights reserved.
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DART_MATH_DETAIL_SO3MATRIX_IMPL_HPP_
#define DART_MATH_DETAIL_SO3MATRIX_IMPL_HPP_

#include "dart/math/SO3Matrix.hpp"

namespace dart {
namespace math {

//==============================================================================
template <typename S>
SO3Matrix<S>::SO3Matrix() : Base()
{
  // Do nothing
}

//==============================================================================
template <typename S>
SO3Matrix<S>::SO3Matrix(const SO3Matrix& other) : Base(), mRepData(other.mRepData)
{
  // Do nothing
}

//==============================================================================
template <typename S>
SO3Matrix<S>::SO3Matrix(SO3Matrix&& other) : Base(), mRepData(std::move(other.mRepData))
{
  // Do nothing
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Matrix<S>::SO3Matrix(const SO3Base<Derived>& other)
  : Base(), mRepData()
{
  *this = other;
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Matrix<S>::SO3Matrix(SO3Base<Derived>&& other)
  : Base(), mRepData()
{
  *this = std::move(other);
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Matrix<S>::SO3Matrix(const Eigen::MatrixBase<Derived>& matrix)
  : Base(), mRepData(matrix)
{
  assert(matrix.rows() == 3);
  assert(matrix.cols() == 3);
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Matrix<S>::SO3Matrix(Eigen::MatrixBase<Derived>&& matrix)
  : Base(), mRepData(std::move(matrix))
{
  assert(matrix.rows() == 3);
  assert(matrix.cols() == 3);
}

//==============================================================================
template <typename S>
SO3Matrix<S>::SO3Matrix(const Eigen::AngleAxis<S>& aa)
  : Base(), mRepData(aa)
{
  // Do nothing
}

//==============================================================================
template <typename S>
SO3Matrix<S>::SO3Matrix(const Eigen::Quaternion<S>& quat)
  : Base(), mRepData(quat)
{
  // Do nothing
}

//==============================================================================
template <typename S>
SO3Matrix<S>& SO3Matrix<S>::operator=(const SO3Matrix& other)
{
  mRepData = other.mRepData;
  return *this;
}

//==============================================================================
template <typename S>
SO3Matrix<S>& SO3Matrix<S>::operator=(SO3Matrix&& other)
{
  mRepData = std::move(other.mRepData);
  return *this;
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Matrix<S>& SO3Matrix<S>::operator=(const Eigen::MatrixBase<Derived>& matrix)
{
  mRepData = matrix;
  return *this;
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Matrix<S>& SO3Matrix<S>::operator=(Eigen::MatrixBase<Derived>&& matrix)
{
  mRepData = std::move(matrix);
  return *this;
}

//==============================================================================
template <typename S>
template <typename RotationDerived>
SO3Matrix<S>& SO3Matrix<S>::operator=(const Eigen::RotationBase<RotationDerived, Base::Dim>& rot)
{
  mRepData = rot;
  return *this;
}

//==============================================================================
template <typename S>
template <typename RotationDerived>
SO3Matrix<S>& SO3Matrix<S>::operator=(Eigen::RotationBase<RotationDerived, Base::Dim>&& rot)
{
  mRepData = std::move(rot);
  return *this;
}

//==============================================================================
template <typename S>
const typename SO3Matrix<S>::Vector3 SO3Matrix<S>::operator*(const Vector3& vector)
{
  return mRepData * vector;
}

//==============================================================================
template <typename S>
bool SO3Matrix<S>::operator==(const SO3Matrix& other)
{
  return mRepData == other.mRepData;
}

//==============================================================================
template <typename S>
void SO3Matrix<S>::fromCanonical(const SO3Matrix& mat)
{
  *this = mat;
}

//==============================================================================
template <typename S>
SO3Matrix<S> SO3Matrix<S>::toCanonical() const
{
  return *this;
}

//==============================================================================
template <typename S>
template <typename Derived>
void SO3Matrix<S>::setRotationMatrix(const Eigen::MatrixBase<Derived>& matrix)
{
  assert(matrix.rows() == 3);
  assert(matrix.cols() == 3);

  mRepData = matrix;
}

//==============================================================================
template <typename S>
template <typename Derived>
void SO3Matrix<S>::setRotationMatrix(Eigen::MatrixBase<Derived>&& mat)
{
  assert(mat.rows() == 3);
  assert(mat.cols() == 3);

  mRepData = std::move(mat);
}

//==============================================================================
template <typename S>
const typename SO3Matrix<S>::Matrix3& SO3Matrix<S>::getRotationMatrix() const
{
  return mRepData;
}

//==============================================================================
template <typename S>
void SO3Matrix<S>::setRandom()
{
  *this = Exp(Tangent::Random());
  // TODO(JS): improve
}

//==============================================================================
template <typename S>
void SO3Matrix<S>::setIdentity()
{
  mRepData.setIdentity();
}

//==============================================================================
template <typename S>
bool SO3Matrix<S>::isIdentity()
{
  return mRepData == RepData::Identity();
}

//==============================================================================
template <typename S>
void SO3Matrix<S>::invert()
{
  mRepData.transposeInPlace();
}

//==============================================================================
template <typename S>
const SO3Matrix<S> SO3Matrix<S>::getInverse() const
{
  return SO3Matrix(mRepData.transpose());
}

//==============================================================================
template <typename S>
SO3Matrix<S> SO3Matrix<S>::Exp(const so3& tangent)
{
  SO3Matrix<S> res;
  res.setExp(tangent);

  return res;
}

//==============================================================================
template <typename S>
SO3Matrix<S> SO3Matrix<S>::Exp(so3&& tangent)
{
  SO3Matrix<S> res;
  res.setExp(std::move(tangent));

  return res;
}

//==============================================================================
template <typename S>
void SO3Matrix<S>::setExp(const so3& tangent)
{
  setExp(tangent);
}

//==============================================================================
template <typename S>
void SO3Matrix<S>::setExp(so3&& tangent)
{
  setExp(std::move(tangent));
}

//==============================================================================
template <typename S>
typename SO3Matrix<S>::so3 SO3Matrix<S>::Log(const SO3Matrix<S>& point)
{
//  return detail::SO3RepDataConvertImpl<Derived, SO3Vector<S>>::run(
//        point.getRepData());
  return SO3Matrix<S>::so3();
  // TODO(JS):
}

//==============================================================================
template <typename S>
typename SO3Matrix<S>::so3 SO3Matrix<S>::Log(SO3Matrix<S>&& point)
{
//  return detail::SO3RepDataConvertImpl<Derived, SO3Vector<S>>::run(
//        std::move(point.getRepData()));
  return SO3Matrix<S>::so3();
  // TODO(JS):
}

//==============================================================================
template <typename S>
typename SO3Matrix<S>::so3 SO3Matrix<S>::getLog() const
{
  return Log(*this);
}

} // namespace math
} // namespace dart

#endif // DART_MATH_DETAIL_SO3MATRIX_IMPL_HPP_
