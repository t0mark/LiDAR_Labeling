# Point Cloud Labeling Tool
 
<img src="https://user-images.githubusercontent.com/11506664/63230808-340d5680-c212-11e9-8902-bc08f0f64dc8.png" width=500>

## 사전 설치
- Eigen >= 3.2
- boost >= 1.54
- QT >= 5.2
- OpenGL Core Profile >= 4.0

## 수정
- Ouster의 intensity 문제
    - src/shaders/draw_points.vert 
``` glsl
# 수정 전
in_remission = clamp(in_remission, 0.0, 1.0);

# 수정 후
in_remission = clamp(in_remission / 255.0, 0.0, 1.0);
``` 


## 빌드
```bash
# 의존성
sudo apt install cmake g++ git libeigen3-dev libboost-all-dev qtbase5-dev libglew-dev

cd ~/Desktop
git clone https://github.com/t0mark/LiDAR_Labeling
cd LiDAR_Labeling

# 빌드
cmake -S . -B build
cmake --build build
```

## 실행
``` bash
cd bin
./labeler

# 데이터 디렉토리 선택 (SemanticKITTI 구조)
```

## 사용법
- 폴더 구조 (SemanticKITTi 구조)
<pre>
point cloud folder
├── velodyne/             -- point cloud (.bin) 파일
├── labels/   [선택 사항]   -- label 파일
├── image_2/  [선택 사항]   -- image (.png)파일
├── calib.txt             -- LiDAR - Camera calibrataion 파일
└── poses.txt             -- 각 스캔 당 pose 정보 파일
</pre>

- 설정 파일 변경 (bin/settings.cfg)
``` txt
tile size: 50.0
max scans: 100
min range: 0.0
max range: 30.0
gpu memory: 8
add car points: true
```

- 이미지 보기

- 단축키

## calibration 파일
- calib.txt 파일 (임의 작성, 아래 내용 복/붙)
```txt
P0: 1 0 0 0 0 1 0 0 0 0 1 0
P1: 1 0 0 0 0 1 0 0 0 0 1 0
P2: 1 0 0 0 0 1 0 0 0 0 1 0
P3: 1 0 0 0 0 1 0 0 0 0 1 0
Tr: 1 0 0 0 0 1 0 0 0 0 1 0
```