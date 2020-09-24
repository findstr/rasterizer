.PHONY:all

#CC=g++10 -O0 -g3 -std=c++17 -fsanitize=address -fno-omit-frame-pointer
CC=g++10 -O3 -g3 -std=c++17
INCLUDE=-Icommon/ -I/usr/local/Cellar/opencv/4.4.0_1/include/opencv4 -D_GLIBCXX_USE_CXX11_ABI=0
LIB=-L/usr/local/gcc10/lib64 -lpthread \
	-lopencv_calib3d -lopencv_contrib \
	-lopencv_core -lopencv_features2d \
	-lopencv_flann -lopencv_highgui -lopencv_imgproc -lopencv_legacy \
	-lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching \
	-lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab

SRC= common/primitive.cpp common/auxiliary.cpp

RST=	rasterizer/main.cpp \
	rasterizer/rasterizer.cpp \
    	rasterizer/camera.cpp

RT=	raytracer/main.cpp \
	raytracer/scene.cpp \
	raytracer/raytracer.cpp

PT=	raytracer/main.cpp \
	raytracer/scene.cpp \
	raytracer/pathtracer.cpp

all:ray path

rasterizer:$(SRC) $(RST)
	$(CC) $(INCLUDE) -Irasterizer/ -o $@ $^ $(LIB)

ray:$(SRC) $(PT)
	$(CC) $(INCLUDE) -Iraytracer/ -o $@ $^ $(LIB)

path:$(SRC) $(PT)
	$(CC) $(INCLUDE) -Iraytracer/ -o $@ $^ $(LIB)

clean:
	-rm path
	-rm ray
	-rm main

