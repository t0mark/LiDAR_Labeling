# LeGO-LOAM
### 내용
- LeGO-LOAM 빌드
- 빌드 과정 중 발생하는 오류 수정
---
### 참조
[LeGO-LOAM](https://github.com/RobustFieldAutonomyLab/LeGO-LOAM.git)
---
### 사전 준비
- ROS1 Noetic
- catkin_package
---
### build
- GTSAM
    ``` bash
    wget -O ~/Downloads/gtsam.zip https://github.com/borglab/gtsam/archive/4.0.0-alpha2.zip
    cd ~/Downloads/ && unzip gtsam.zip -d ~/Downloads/
    cd ~/Downloads/gtsam-4.0.0-alpha2/
    mkdir build && cd build
    cmake ..
    sudo make install
    ```
- LeGO-LOAM
    ``` bash
    mkdir -p ~/catkin_ws/src
    cd ~/catkin_ws/src
    git clone https://github.com/RobustFieldAutonomyLab/LeGO-LOAM.git
    cd ..
    rosdep install --from-paths src --ignore-src -r -y

    # 수정 후 build
    catkin_make
    source ~/catkin_ws/devel/setup.bash
    ```
---
### 수정
- 참고
    - [빌드 설정](https://blog.csdn.net/qq_59475883/article/details/130253465)
    - [Rviz 설정](https://blog.csdn.net/weixin_47451478/article/details/116792047) (현재 미적용)
- LeGO-LOAM/LeGO-LOAM/include/utility.h
    ``` cpp
    # 수정 전
    13| #include <opencv/cv.h>

    # 수정 후
    13| #include <opencv2/opencv.hpp>
    ```
- LeGO-LOAM/LeGO-LOAM/CMakeLists.txt
    ``` Cmake
    # 수정 전
    4| set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -03")

    # 수정 후
    4| set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -03")
    ```
- LiDAR 모델 수정
    ``` cpp
    # 수정 전 : 주석 처리
    62| // VLP-16
    63| extern const int N_SCAN = 16;
    64| extern const int Horizon_SCAN = 1800;
    65| extern const float ang_res_x = 0.2;
    66| extern const float ang_res_y = 2.0;
    67| extern const float ang_bottom = 15.0+0.1;
    68| extern const int groundScanInd = 7;

    # 수정 후 : 내용 추가
    70| // Ouster OS1-32
    71| extern const int N_SCAN = 32;
    72| extern const int Horizon_SCAN = 1024;
    73| extern const float ang_res_x = 360.0 / float(Horizon_SCAN); // 약 0.3515도
    74| extern const float ang_res_y = 33.2 / float(N_SCAN - 1);    // 약 1.07도
    75| extern const float ang_bottom = 16.6 + 0.1;                 // 하향 각도 중심
    76| extern const int groundScanInd = 15;  // 또는 실험적으로 14~17 사이에서 조정
    ```
---
### 실행
``` bash
# LeGO-LOAM 실행
roslaunch lego_loam run.launch

# bag 파일 play
rosbag play {bag 파일} --clock --topic {pcd 토픽} {imu 토픽}
```
---