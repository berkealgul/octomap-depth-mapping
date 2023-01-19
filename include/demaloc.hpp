#pragma once
#ifndef OCTOMAP_DEPTH_MAPPING_HPP
#define OCTOMAP_DEPTH_MAPPING_HPP

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include <rclcpp_components/register_node_macro.hpp>

#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"

#include "octomap/OcTree.h"
#include "octomap/Pointcloud.h"
#include "octomap_msgs/conversions.h"
#include "octomap_msgs/msg/octomap.hpp"

#include "sensor_msgs/msg/image.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

#include <opencv2/opencv.hpp>

namespace ph = std::placeholders;


namespace octomap_depth_mapping
{

class OctomapDemap : public rclcpp::Node
{
protected:

    double fx;
    double fy;
    double cx;
    double cy;
    double resolution;
    int padding;    
    std::string encoding;
    std::string frame_id;

    std::shared_ptr<octomap::OcTree> ocmap;

    rclcpp::Publisher<octomap_msgs::msg::Octomap>::SharedPtr octomap_publisher_;

    message_filters::Subscriber<sensor_msgs::msg::Image> depth_sub_;
    message_filters::Subscriber<geometry_msgs::msg::PoseStamped> pose_sub_;

    std::shared_ptr<message_filters::TimeSynchronizer
        <sensor_msgs::msg::Image, geometry_msgs::msg::PoseStamped>> sync_;


    void update_map(const cv::Mat&, const geometry_msgs::msg::Pose&);

    void publish_all();

    void print_params();

    void demap_callback(const sensor_msgs::msg::Image::ConstSharedPtr&, 
        const geometry_msgs::msg::PoseStamped::ConstSharedPtr&);

public:

    explicit OctomapDemap(const rclcpp::NodeOptions&, const std::string = "octomap_depth_mapping");

};

} // octomap_depth_mapping

#endif // OCTOMAP_DEPTH_MAPPING_HPP