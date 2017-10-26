/*
 * Copyright (c) 2011-2016, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Jie (Jay) Tan <jtan34@cc.gatech.edu>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
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

#ifndef DART_LCPSOLVER_ODELCPSOLVER_H_
#define DART_LCPSOLVER_ODELCPSOLVER_H_

#include <Eigen/Dense>

namespace dart {
namespace lcpsolver {

/// \brief
class ODELCPSolver {
public:
  /// \brief
  ODELCPSolver();

  /// \brief
  virtual ~ODELCPSolver();

  /// \brief
  bool Solve(const Eigen::MatrixXd& _A,
             const Eigen::VectorXd& _b,
             Eigen::VectorXd* _x,
             int numContacts,
             double mu = 0,
             int numDir = 0,
             bool bUseODESolver = false);

private:
  /// \brief
  void transferToODEFormulation(const Eigen::MatrixXd& _A,
                                const Eigen::VectorXd& _b,
                                Eigen::MatrixXd* _AOut,
                                Eigen::VectorXd* _bOut,
                                int _numDir,
                                int _numContacts);

  /// \brief
  void transferSolFromODEFormulation(const Eigen::VectorXd& _x,
                                     Eigen::VectorXd* _xOut,
                                     int _numDir,
                                     int _numContacts);

  /// \brief
  bool checkIfSolution(const Eigen::MatrixXd& _A,
                       const Eigen::VectorXd& _b,
                       const Eigen::VectorXd& _x);
};

}  // namespace lcpsolver
}  // namespace dart

#endif  // DART_LCPSOLVER_ODELCPSOLVER_H_