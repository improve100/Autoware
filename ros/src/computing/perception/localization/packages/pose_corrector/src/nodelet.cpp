/*
 *  Copyright (c) 2017, Tier IV, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither the name of Autoware nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>

#include <boost/shared_ptr.hpp>

#include "pose_corrector/combine_imu_odom.h"
#include "pose_corrector/pose_corrector.h"

class PoseCorrectorNodelet : public nodelet::Nodelet
{
  public:
    PoseCorrectorNodelet()  {};

    ~PoseCorrectorNodelet() {};
  
    virtual void onInit()
    {
      combine_sub_base_ptr_.reset(new CombineImuOdom(getNodeHandle(), getPrivateNodeHandle(), "imu_raw", "odom_pose"));
      pose_corrector_ptr_.reset(new PoseCorrector(getNodeHandle(), getPrivateNodeHandle(), combine_sub_base_ptr_));

    }

  private:
    boost::shared_ptr<CombineSubBase> combine_sub_base_ptr_;
    boost::shared_ptr<PoseCorrector> pose_corrector_ptr_;
};

PLUGINLIB_EXPORT_CLASS(PoseCorrectorNodelet, nodelet::Nodelet)