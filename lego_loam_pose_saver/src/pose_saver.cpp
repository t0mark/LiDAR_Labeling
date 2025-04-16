#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>
#include <fstream>
#include <string>
#include <iomanip>

std::ofstream poseFile;

void poseCallback(const nav_msgs::Odometry::ConstPtr& odomMsg)
{
    // 쿼터니언에서 회전 행렬 얻기
    tf::Quaternion q(
        odomMsg->pose.pose.orientation.x,
        odomMsg->pose.pose.orientation.y,
        odomMsg->pose.pose.orientation.z,
        odomMsg->pose.pose.orientation.w);
    tf::Matrix3x3 rotMatrix(q);
    
    // 위치 정보 추출
    double tx = odomMsg->pose.pose.position.x;
    double ty = odomMsg->pose.pose.position.y;
    double tz = odomMsg->pose.pose.position.z;
    
    // KITTI 형식으로 파일에 저장 (3x4 행렬의 모든 요소를 한 줄에)
    poseFile << std::fixed << std::setprecision(6)
        // 첫 번째 행
        << rotMatrix[0][0] << " " << rotMatrix[0][1] << " " << rotMatrix[0][2] << " " << tx << " "
        // 두 번째 행
        << rotMatrix[1][0] << " " << rotMatrix[1][1] << " " << rotMatrix[1][2] << " " << ty << " "
        // 세 번째 행
        << rotMatrix[2][0] << " " << rotMatrix[2][1] << " " << rotMatrix[2][2] << " " << tz
        << std::endl;
    
    ROS_INFO("Pose saved: x=%.3f y=%.3f z=%.3f", tx, ty, tz);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pose_saver_kitti_format");
    ros::NodeHandle nh;
    
    // 파라미터 설정
    std::string poseTopicName;
    std::string saveFilePath;
    
    // 파라미터 가져오기, 기본값 설정
    nh.param<std::string>("pose_topic", poseTopicName, "/aft_mapped_to_init");
    nh.param<std::string>("save_path", saveFilePath, "poses.txt");
    
    // 파일 열기
    poseFile.open(saveFilePath);
    if (!poseFile.is_open()) {
        ROS_ERROR("Failed to open file: %s", saveFilePath.c_str());
        return -1;
    }
    
    // 토픽 구독
    ros::Subscriber poseSub = nh.subscribe<nav_msgs::Odometry>(
        poseTopicName, 100, poseCallback);
    
    ROS_INFO("Pose saver started. Subscribing to %s and saving to %s in KITTI format", 
             poseTopicName.c_str(), saveFilePath.c_str());
    
    ros::spin();
    
    poseFile.close();
    return 0;
}
