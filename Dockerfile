FROM debian:buster-slim

MAINTAINER Labhesh Valechha <labheshvalechha@gmail.com>
MAINTAINER Varun Bal <varun.bal.work@gmail.com>

ARG opencv_version=4.4.0
ARG pythonVersion=3.7
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get upgrade -y \
	&& apt-get install -y --no-install-recommends apt-utils \
	&& apt-get install -y wget

RUN wget -O Miniconda.sh "https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh" \
	&& chmod u+x Miniconda.sh \
	&& ./Miniconda.sh -bfp /usr/local -u \
	&& rm -f Miniconda.sh \
	&& conda install -y python=$pythonVersion \
	&& conda update conda -y \
	&& conda install -y xeus-cling -c conda-forge \
	&& conda install -y matplotlib -c conda-forge \
	&& conda install -y numpy -c conda-forge \
	&& conda clean --all --yes

RUN apt-get install -y cmake git vim libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev libeigen3-dev libgflags-dev libgoogle-glog-dev libhdf5-dev \
	&& pip install notebook

ENV PYTHONPATH=/usr/local/lib/python3.7/
ENV PYTHONHOME=/usr/local

RUN git clone https://github.com/opencv/opencv_contrib.git \
	&& cd opencv_contrib \
	&& git checkout $opencv_version \
	&& cd .. \
	&& git clone https://github.com/opencv/opencv.git \
	&& cd opencv \
	&& git checkout $opencv_version \
	&& mkdir build \
	&& cd build \
	&& cmake \
	-D CMAKE_BUILD_TYPE=Release \
	-D CMAKE_INSTALL_PREFIX=/usr/local \
	-D BUILD_EXAMPLES=ON \
	-D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
	-D PYTHON3_NUMPY_INCLUDE_DIRS=/usr/local/lib/python"$pythonVersion"/site-packages/numpy/core/include/ \
        -D OPENCV_GENERATE_PKGCONFIG=ON \
	.. \
	&& make install/strip \
	&& cd /home \
	&& rm -rf opencv opencv_contrib

COPY script.sh displayImages.h matplotlibcpp.h /usr/local/lib/
COPY sampleCode /home/sampleCode

RUN cd /usr/local/lib \
	&& chmod u+x script.sh \
	&& ./script.sh $opencv_version $pythonVersion \
	&& rm -f script.sh

CMD ["bash"]
