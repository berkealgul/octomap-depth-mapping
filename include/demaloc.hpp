#ifndef OCTOMAP_DEPTH_MAPPING_HPP
#define OCTOMAP_DEPTH_MAPPING_HPP

#include <memory>
#include <fstream>
#include <iostream> //for debug

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include <rclcpp_components/register_node_macro.hpp>
#include "octomap_msgs/conversions.h"
#include "octomap_msgs/msg/octomap.hpp"
#include "geometry_msgs/msg/point32.hpp"

// temporary
#include "sensor_msgs/msg/point_cloud.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/point_cloud_conversion.hpp" 


#include <opencv2/opencv.hpp>
#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Vector3.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include "octomap/OcTree.h"
#include "octomap/Pointcloud.h"
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose.hpp"


using namespace std::chrono_literals;


namespace octomap_depth_mapping
{
class OctomapDemap : public rclcpp::Node
{
public:
    
    explicit OctomapDemap(const rclcpp::NodeOptions&, const std::string = "octomap_server");

    rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<octomap_msgs::msg::Octomap>::SharedPtr octomap_publisher_;
	rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pc_publisher_;
	size_t count_;
    octomap::Pointcloud pc;
    octomap::OcTree ocmap = octomap::OcTree(0.05);
    //std::shared_ptr<octomap::OcTree> ocmap;
    std::ifstream myfile;
    int data_counter = 0;
	std::string p = "/home/berke/Downloads/rgbd-scenes-v2_imgs/rgbd-scenes-v2/imgs/scene_01/";
    std::string p1 = "/home/berke/Downloads/rgbd-scenes-v2_pc/rgbd-scenes-v2/pc/01.pose";

    double rawDepthToMeters(ushort raw_depth);
    void read_dataset_once();
    void update_map(cv::Mat& img, geometry_msgs::msg::Pose& pose);
    void timer_callback();
};

} // octomap_depth_mapping


#endif // OCTOMAP_DEPTH_MAPPING_HPP