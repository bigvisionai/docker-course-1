# Course-1 Docker Image
This image consists of CPP and Python3 installation of OpenCV. You can use this image to run CPP and Python3 code on the terminal, or create CPP and Python3 notebooks.

# How to run
### Our favourite run command is:
#### `docker run -it --rm --mount type=bind,source="$(pwd)"/work,target=/work -p 8888:8888 opencvcourses/course-1`

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
#### `docker run -it opencvcourses/course-1`

This will start the container with an interactive shell. This is the most basic command to run the image.
<br>
Here, you can run python, or c++ code (using cmake), or even cling. 
<br>
To start cling, enter `cling` on the terminal and code in c++ like python.
<br>
**In this mode, you can only access the terminal.**

To use Jupyter Notebook as well, you'll need to expose a port from the container to the host. You can expose ports using the `-p` switch.

# How to use:
The image contains sample code in `/home/sampleCode`. You can go through it to understand differnt ways to use the image.
### Terminal:
#### CPP
You can run CPP code on the terminal using cmake.<br>
You can also start a `cling` session on the terminal. Cling is an interactive CPP interpreter. You can code CPP on it just like you code on Python.
#### Python
You can create `.py` scripts and run them on the terminal.<br>
Moreover, you can also run python code directly on the terminal using the `python` command.
### Notebooks:
Run the container and execute the following command to start a Jupyter Notebook session:
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
Check the course contents or the sample code on how to print in cpp using matplotlib-cpp.
