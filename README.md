# System Dependencies
This program requires the following libraries to be installed:
* libcurl >= 7.47.0

# Machine Learning Applied
Within Marvin we use Machine Learning (ML) models to do the filtering and categorization of data.
This project has chosen to use [Google TensorFlow](https://github.com/tensorflow) as its core ML engine.
First of you will need to checkout the tensorflow source and create the dynamic TensorFlow library.
Secondly you will need to add the tensorflow headers to a logical path on your system (ex. symbolic link in /usr/local/include).
In order for you to be able to work with the different ML models, you will need to create them.

The [TensorFlow repository](https://github.com/tensorflow/models) gives an overview of all available models. 

Train a new model with TensorFlow and export it to the resources folder in this project in order to use it.
Apply the new model within tensorflow.h and tensorflow.cpp.

Currently implemented models:
* InceptionV3 (image recognition)

# Fixes for errors when trying to compile

- DecodePng et.al. not found -> The files should be in bazel-genfiles (add the path), if they are not there, run `bazel build tensorflow/cc:cc_ops` in TensorFlow directory root. 