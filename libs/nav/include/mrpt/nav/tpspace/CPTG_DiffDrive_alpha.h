/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2016, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */
#pragma once

#include <mrpt/nav/tpspace/CPTG_DiffDrive_CollisionGridBased.h>

namespace mrpt
{
  namespace nav
  {
	DEFINE_SERIALIZABLE_PRE_CUSTOM_BASE_LINKAGE(CPTG_DiffDrive_alpha, CParameterizedTrajectoryGenerator, NAV_IMPEXP)

	/** The "a(symptotic)-alpha PTG", as named in PTG papers.
	 * - **Compatible kinematics**: differential-driven / Ackermann steering
	 * - **Compatible robot shape**: Arbitrary 2D polygon
	 * 
	 * Accepted parameters in the constructor:
	 * - params["ref_distance"]: Maximum trayectory distance (meters).
	 * - params["v_max"]: Maximum linear velocity (m/s)
	 * - params["w_max"]: Maximum angular velocity (rad/s)
	 * - params["cte_a0v"]: Constant related to the generation of linear velocities, read below (in radians).
	 * - params["cte_a0w"]: Constant related to the generation of angular velocities, read below  (in radians).
	 * 
	 * This PT generator functions are: 
	 *
	 * \f[ v(\alpha) = V_{MAX} e^{ -\left( \dfrac{\alpha-\phi}{cte_{a0v}} \right)^2} \f]
	 * \f[ \omega(\alpha) = W_{MAX} \left( -\dfrac{1}{2} +\dfrac{1}{1+ e^{ - \dfrac{\alpha-\phi}{cte_{a0w}} } } \right) \f]
	 *
	 * So, the radius of curvature of each trajectory is NOT constant for each "alpha" value in this PTG:
	 *
	 *  ![C-PTG path examples](PTG2_paths.png)
	 *
	 * \note [Before MRPT 1.5.0 this was named CPTG2]
	 *  \ingroup nav_tpspace
	 */
	class NAV_IMPEXP  CPTG_DiffDrive_alpha : public CPTG_DiffDrive_CollisionGridBased
	{
		DEFINE_SERIALIZABLE(CPTG_DiffDrive_alpha)
	 public:
		CPTG_DiffDrive_alpha() : cte_a0v(0),cte_a0w(0) { }
		CPTG_DiffDrive_alpha(const mrpt::utils::TParameters<double> &params) {
			setParams(params);
		}
		void setParams(const mrpt::utils::TParameters<double> &params) MRPT_OVERRIDE;
		std::string getDescription() const MRPT_OVERRIDE;
		void ptgDiffDriveSteeringFunction( float alpha, float t,float x, float y, float phi, float &v, float &w ) const MRPT_OVERRIDE;

	 protected:
		double cte_a0v, cte_a0w;
	};
	DEFINE_SERIALIZABLE_POST_CUSTOM_BASE_LINKAGE(CPTG_DiffDrive_alpha, CParameterizedTrajectoryGenerator, NAV_IMPEXP)

  }
}
