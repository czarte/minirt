FROM	ubuntu

RUN	apt-get update -y && \
	apt-get upgrade -y && \
	apt-get install build-essential git vim valgrind clang x11-apps -y

RUN	git clone https://github.com/czarte/minirt.git minirt && \
	apt-get install libxext-dev -y && \
	apt-get install libbsd-dev -y

RUN	cd minirt \
	git checkout camera_movement_linux

