# docker-opencv
This image consists of CPP and Python3 installation of OpenCV-4.4.0. You can use it to run CPP and Python3 code on the terminal, or create CPP and Python3 notebooks.

# How to run
### Our favourite run command is:
#### `docker run -it --rm --mount type=bind,source="$(pwd)"/work,target=/work -p 8888:8888 opencvcourses/opencv:440`

`-it` starts an interactive shell. This switch is always needed to start the container. Otherwise, it will start and stop instantly.
<br>
`--rm` specifies to kill the container after it is exited.
<br>
`--mount` creates persistent storage to save all the work. Read more about it [here](https://docs.docker.com/storage/).
<br>
`-p` is used to expose a container's port to the host.
<br>
**Note:** Run this command in the parent directory of `work` folder.

In this configuration, you can use all the functions of our image

### Minimal run command:
`docker run -it opencvcourses/opencv:440`
<br>
This will start the container with an interactive shell. This is the most basic command to run the image.
<br>
Here, you can run python, or c++ code (using cmake), or even cling. 
<br>
To start cling, enter `cling` on the terminal and code in c++ like python.
<br>
**In this mode, you can only access the terminal.**

To use Jupyter Notebook as well, you'll need to expose a port from the container to the host. You can expose ports using the `-p` switch.

# How to use:
### cmake
You can run CPP codes using cmake. Try the sample code available in our course.
### Jupyter Notebook:
Start the container and execute the below command to start a Jupyter Notebook session:
<br>
`jupyter notebook --ip 0.0.0.0 --allow-root --no-browser`
<br>
You can create Python3 or CPP notebooks in jupyter notebook.
#### CPP in Jupyter Notebook
Xeus-cling is the CPP interpreter kernel. Coding is similar in xeus-cling, but you need to include a few helper header files. They are:
```
#include "/usr/local/lib/includeLibraries.h"
#include "/usr/local/lib/displayImages.h"
#include "/usr/local/lib/matplotlibcpp.h"
```
Check the course contents on how to print in cpp using matplotlib-cpp
