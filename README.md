# AWS Lambda CPP Example

## Setup (Ubuntu 22)
- Install AWS C++ SDK (https://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/setup-linux.html)
```
sudo apt-get install libcurl4-openssl-dev libssl-dev uuid-dev zlib1g-dev libpulse-dev
git clone --recurse-submodules https://github.com/aws/aws-sdk-cpp
mkdir sdk_build
cd sdk_build
cmake ../aws-sdk-cpp -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=/usr/local/ -DCMAKE_INSTALL_PREFIX=/usr/local/
make
make install
```

- Install AWS Lambda C++ Runtime (https://github.com/awslabs/aws-lambda-cpp)  
```
git clone https://github.com/awslabs/aws-lambda-cpp.git
cd aws-lambda-cpp
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/lambda-install
make && make install
```

- Install Libdmtx through apt or from source (https://github.com/dmtx/libdmtx)
```
sudo apt install libdmtx0b libdmtx-dev
# Install from source [Optional]
git clone --depth 1 --branch v0.7.7 https://github.com/dmtx/libdmtx.git
cd libdmtx
./autogen.sh
./configure 
make 
make install
```

- Install torch (https://pytorch.org/)
```
wget https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-1.13.1%2Bcpu.zip
unzip libtorch-shared-with-deps-1.13.1%2Bcpu.zip -d ~/libtorch
```

- Install Opencv (https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)
```
sudo apt update && sudo apt install -y cmake g++ wget unzip
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip
unzip opencv.zip
unzip opencv_contrib.zip
mkdir -p build && cd build
cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.x/modules ../opencv-4.x
cmake --build .
```

- Install NumCpp (https://github.com/dpilger26/NumCpp/blob/master/docs/markdown/Installation.md)
```
git clone https://github.com/dpilger26/NumCpp.git
cd NumCpp
mkdir build
cd build
cmake ..
cmake --build . --target install
``` 